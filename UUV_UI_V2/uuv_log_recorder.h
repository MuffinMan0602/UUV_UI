#ifndef UUV_LOG_RECORDER_H
#define UUV_LOG_RECORDER_H

#pragma once
#include <QObject>
#include <QString>
#include <QStringList>
#include <QVector>
#include <QDateTime>

/*
 * 轻量级日志记录类（同步版，不使用线程）
 * 作用：
 *  - start()       开始一次新记录（清空旧数据，记录起始时间）
 *  - appendTransmit() / appendReceive() 追加一条发送或接收记录
 *  - recordCount() 返回当前累计的记录行数（不含表头）
 *  - formattedDuration() 返回运行时长 "hh:mm:ss"
 *  - saveToFile(path) 保存为 CSV 或 TXT（根据后缀判断，非 .txt 默认 CSV）
 *  - stopAndClear() 停止记录并清除数据
 *
 * 设计说明：
 *  - 内部用 QVector<QStringList> 保存每一行（已经是“列”分割状态，方便直接 join(',') 输出 CSV）
 *  - 发送与接收行采用相同列布局，缺失字段留空，列定义见 buildHeader()
 */
class UUVLogRecorder: public QObject
{
    Q_OBJECT
public:
    explicit UUVLogRecorder(QObject* parent=nullptr);

    // 发送行字段（Tx）
    struct TransmitFields {
        int workMode = 0;
        int taw_x=0, taw_y=0, taw_z=0, taw_phi=0, taw_theta=0, taw_psi=0; // 六自由度整型控制量
        float depth_d = 0.f;  // 半自主期望深度
        float yaw_d   = 0.f;  // 半自主期望艏向
        float pos[6]  = {0,0,0,0,0,0}; // 自主模式 pos1..6（mode 5）
        bool  posValid = false;        // true 表示实际发送了 pos (WorkMode==5)
    };

    // 接收行字段（Rx）── 适配新接收协议
    struct ReceiveFields {
        int mode = 0;        // 0x01~0x05
        int voltage = 0;     // 原始 int8 值
        int current = 0;     // 原始 int8 值
        int cabinTemp = 0;   // 原始 int8 值
        int dropSignal = 0;  // 1=已触发
        int posSource = 0;   // 1=基站/2=推位

        float eta[6] = {0,0,0,0,0,0};      // x,y,z,phi,theta,psi
        float vel[6] = {0,0,0,0,0,0};      // u,v,w,p,q,r
        float thruster[6] = {0,0,0,0,0,0}; // T1..T6
    };

    // 开始新的记录（重置数据 + 起始时间）
    void start();

    // 停止并清空（调用后 isRecording() 变为 false）
    void stopAndClear();

    // 是否处于记录状态
    bool isRecording() const { return m_recording; }

    // 追加发送/接收记录（只有在 isRecording()==true 时才生效）
    void appendTransmit(const TransmitFields& tf);
    void appendReceive(const ReceiveFields& rf);

    // 当前记录条数（不含表头）
    int recordCount() const { return m_rows.size(); }

    // 从 start() 起算的毫秒数
    qint64 elapsedMs() const;

    // 按 "hh:mm:ss" 返回记录时长
    QString formattedDuration() const;

    // 保存至指定文件（后缀 .txt 则保存为 TXT；否则为 CSV）
    bool saveToFile(const QString& path, QString* errMsg = nullptr) const;

private:
    bool m_recording = false;          // 是否正在记录
    QDateTime m_startUtc;              // UTC 起始时间（用于计算 elapsedMs）
    QVector<QStringList> m_rows;       // 每条日志一行（不含表头）

    // 构建 CSV 表头（适配“接收新协议 + 发送原协议”的总列集合）
    QStringList buildHeader() const;

    // 构建发送/接收行（与表头列对齐；缺失列留空）
    QStringList buildTransmitRow(const TransmitFields& tf) const;
    QStringList buildReceiveRow(const ReceiveFields& rf) const;

    // 保存实现
    bool saveCsv(const QString& path, QString* errMsg) const;
    bool saveTxt(const QString& path, QString* errMsg) const;

    // 当前 UTC 时间字符串（精确到毫秒）
    static QString nowUtcString();
};

#endif // UUV_LOG_RECORDER_H
