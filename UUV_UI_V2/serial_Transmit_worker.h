#ifndef SERIAL_TRANSMIT_WORKER_H
#define SERIAL_TRANSMIT_WORKER_H

#include <QObject>
#include <QSerialPort>
#include <QByteArray>
#include <QDataStream>
#include <QThread>
#include <QDateTime>
#include <QMutex>
#include <QDebug>

class SerialTransmitWorker : public QThread
{
    Q_OBJECT
public:
    explicit SerialTransmitWorker(QSerialPort *sharedSerial,QObject *parent = nullptr);
    ~SerialTransmitWorker();

    // 配置串口参数
    void configureSerial(const QString &portName, qint32 baudRate, int dataBits, int parity, int stopBits);

    // 更新发送参数
    void updateTransValues(int8_t WorkMode, int8_t tx, int8_t ty, int8_t tz, int8_t tphi, int8_t ttheta, int8_t tpsi, float depth, float yaw);
    void updateTransValues2(int8_t WorkMode, float p1, float p2, float p3, float p4, float p5, float p6);//自主模式

signals:
    void transmitViewUpdated(const QString &transmitView); // 通知主线程发送预览更新


public slots:
    void sendSerialData(); // 发送数据，使用协议封装

protected:
    void run() override; // 重写 QThread 的 run 方法

private:
    QSerialPort *serial; // 指向共享的串口对象
    QString TransmitView;//发送预览
    void appendFloat(QByteArray &packet, float value);//使得float变量在Array中占4个字节

    // 控制参数
    int8_t currentWorkMode, taw_x, taw_y, taw_z, taw_phi, taw_theta, taw_psi;
    float Depth_d, Yaw_d;
    float pos1,pos2,pos3,pos4,pos5,pos6;
    QMutex mutex;
};

#endif // SERIAL_TRANSMIT_WORKER_H
