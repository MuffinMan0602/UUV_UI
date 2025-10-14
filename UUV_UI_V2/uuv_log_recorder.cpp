#include "uuv_log_recorder.h"
#include <QSaveFile>
#include <QTextStream>
#include <QLocale>
#include <QFileInfo>

UUVLogRecorder::UUVLogRecorder(QObject* parent)
    : QObject(parent)
{}

/* 开始记录：清空旧数据，记录当前 UTC 起始时间，置 recording=true */
void UUVLogRecorder::start()
{
    m_rows.clear();    
    m_recording = true;
    m_startUtc = QDateTime::currentDateTimeUtc();
}

/* 停止并清空所有记录 */
void UUVLogRecorder::stopAndClear()
{
    m_recording = false;
    m_rows.clear();
    //m_startUtc = QDateTime();
}

/* 获取已运行毫秒数（未 start 或已 stop 返回 0） */
qint64 UUVLogRecorder::elapsedMs() const
{
    if (!m_recording || !m_startUtc.isValid()) return 0;
    return m_startUtc.msecsTo(QDateTime::currentDateTimeUtc());
}

/* 返回格式化时长 "hh:mm:ss" */
QString UUVLogRecorder::formattedDuration() const
{
    const qint64 ms = elapsedMs();
    QTime base(0,0,0);
    return base.addMSecs(int(ms)).toString("hh:mm:ss");
}

/* 当前 UTC 时间戳字符串，精确到毫秒 */
QString UUVLogRecorder::nowUtcString()
{
    return QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd HH:mm:ss.zzz");
}

/* 构建 CSV 表头：
 * 列顺序约定：
 * TimestampUTC, Direction,
 * WorkMode, taw_x..taw_psi (6 列), Depth_d, Yaw_d,
 * pos1..pos6,
 * x,y,z,roll,pitch,yaw (接收姿态)
 */
QStringList UUVLogRecorder::buildHeader() const
{
    return {
            "dir",
            "timestamp_utc",
            "elapsed_ms",

            // RX 新协议字段
            "rx_mode",
            "rx_voltage",
            "rx_current",
            "rx_temperature",
            "rx_drop",
            "rx_posSource",
            "x","y","z","phi","theta","psi",
            "u","v","w","p","q","r",
            "T1","T2","T3","T4","T5","T6",

            // TX 原协议字段（mode 1..4）
            "tx_taw_x","tx_taw_y","tx_taw_z","tx_taw_phi","tx_taw_theta","tx_taw_psi",
            "tx_Depth_d","tx_Yaw_d",

            // TX 原协议字段（mode 5）
            "tx_pos1","tx_pos2","tx_pos3","tx_pos4","tx_pos5","tx_pos6"
    };
}

/* 构建发送行：接收相关的 6 列留空 */
QStringList UUVLogRecorder::buildTransmitRow(const TransmitFields& tf) const
{
    QStringList row;
    row.reserve(3 + 5 + 6 + 6 + 6 + 8 + 6);

    row << "TX";
    row << nowUtcString();
    row << QString::number(elapsedMs());

    // —— RX 字段全部占位（5 状态 + 6 位姿 + 6 速度 + 6 推进器 = 23 列）
    for (int i=0;i<23;++i) row << QString();

    // —— TX（mode 1..4）：taw6 + Depth_d + Yaw_d
    row << QString::number(tf.taw_x);
    row << QString::number(tf.taw_y);
    row << QString::number(tf.taw_z);
    row << QString::number(tf.taw_phi);
    row << QString::number(tf.taw_theta);
    row << QString::number(tf.taw_psi);
    row << QString::number(tf.depth_d, 'f', 6);
    row << QString::number(tf.yaw_d,   'f', 6);

    // —— TX（mode 5）：pos1..6；如果不是 mode5/posValid=false，则留空
    if (tf.posValid && tf.workMode == 5) {
        for (int i=0;i<6;++i) row << QString::number(tf.pos[i], 'f', 6);
    } else {
        for (int i=0;i<6;++i) row << QString();
    }

    return row;
}

/* 构建接收行：发送相关列留空 */
QStringList UUVLogRecorder::buildReceiveRow(const ReceiveFields& rf) const
{
    // 公共前缀
    QStringList row;
    row.reserve(3 + 5 + 6 + 6 + 6 + 8 + 6); // 预留容量，减少 realloc
    row << "RX";
    row << nowUtcString();
    row << QString::number(elapsedMs());

    // —— RX 新协议字段
    row << QString::number(rf.mode);
    row << QString::number(rf.voltage);
    row << QString::number(rf.current);
    row << QString::number(rf.cabinTemp);
    row << QString::number(rf.dropSignal);
    row << QString::number(rf.posSource);

    // 位姿 6
    for (int i=0;i<6;++i) row << QString::number(rf.eta[i], 'f', 6);

    // 速度 6
    for (int i=0;i<6;++i) row << QString::number(rf.vel[i], 'f', 6);

    // 推进器 6
    for (int i=0;i<6;++i) row << QString::number(rf.thruster[i], 'f', 6);

    // —— TX 字段占位：taw(6)+Depth_d+Yaw_d 共8列
    for (int i=0;i<8;++i) row << QString();

    // —— TX 全自主 pos1..6 占位
    for (int i=0;i<6;++i) row << QString();

    return row;
}

/* 追加发送行 */
void UUVLogRecorder::appendTransmit(const TransmitFields& tf)
{
    if (!m_recording) return;
    m_rows.push_back(buildTransmitRow(tf));
}

/* 追加接收行 */
void UUVLogRecorder::appendReceive(const ReceiveFields& rf)
{
    if (!m_recording) return;
    m_rows.push_back(buildReceiveRow(rf));
}

/* 保存文件：根据后缀决定走 CSV / TXT */
bool UUVLogRecorder::saveToFile(const QString& path, QString* errMsg) const
{
    if (m_rows.isEmpty()) {
        if (errMsg) *errMsg = "无记录数据";
        return false;
    }
    QFileInfo fi(path);
    const QString suffix = fi.suffix().toLower();
    if (suffix == "txt")
        return saveTxt(path, errMsg);

    // 其余一律按 CSV 处理；若没有 .csv 后缀则追加
    QString realPath = path;
    if (suffix != "csv")
        realPath += ".csv";
    return saveCsv(realPath, errMsg);
}

/* 保存为 CSV：写表头 + 每行 join(',') */
bool UUVLogRecorder::saveCsv(const QString& path, QString* errMsg) const
{
    QSaveFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        if (errMsg) *errMsg = file.errorString();
        return false;
    }
    QTextStream out(&file);
    out.setLocale(QLocale::C); // 保证小数点为 '.'
    out << buildHeader().join(',') << '\n';
    for (const auto& row : m_rows)
        out << row.join(',') << '\n';

    if (!file.commit()) {
        if (errMsg) *errMsg = "提交写入失败";
        return false;
    }
    return true;
}

/* 保存为 TXT：可读性较好，格式简单 */
bool UUVLogRecorder::saveTxt(const QString& path, QString* errMsg) const
{
    QSaveFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        if (errMsg) *errMsg = file.errorString();
        return false;
    }
    QTextStream out(&file);
    out.setLocale(QLocale::C);

    for (const auto& row : m_rows) {
        const QString& direction = row[1]; // 第二列 Direction
        if (direction == "Transmit") {
            out << "[" << row[0] << "] Transmit "
                << "WM=" << row[2]
                << " taw=[" << row[3] << "," << row[4] << "," << row[5]
                << "," << row[6] << "," << row[7] << "," << row[8] << "]"
                << " Depth=" << row[9] << " Yaw=" << row[10]
                << " pos=[" << row[11] << "," << row[12] << "," << row[13]
                << "," << row[14] << "," << row[15] << "," << row[16] << "]\n";
        } else {
            out << "[" << row[0] << "] Receive "
                << "eta=[" << row[17] << "," << row[18] << "," << row[19]
                << "," << row[20] << "," << row[21] << "," << row[22] << "]\n";
        }
    }

    if (!file.commit()) {
        if (errMsg) *errMsg = "提交写入失败";
        return false;
    }
    return true;

}
