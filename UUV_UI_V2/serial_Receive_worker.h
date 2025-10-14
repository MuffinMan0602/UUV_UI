#ifndef SERIAL_RECEIVE_WORKER_H
#define SERIAL_RECEIVE_WORKER_H

#pragma once

#include <QObject>
#include <QSerialPort>
#include <QByteArray>
#include <QThread>
#include <QDateTime>

#include "protocol_receive.h"  // 新协议定义


class SerialReceiveWorker : public QThread
{
    Q_OBJECT
public:
    explicit SerialReceiveWorker(QSerialPort *sharedSerial,QObject *parent = nullptr);
    ~SerialReceiveWorker()override;



signals:

    void frameReceived(UUVRxFrame frame);//每解析出一帧完整数据即触发函数
    void receiveViewUpdated(const QString &receiveView);   // 通知主线程接收预览更新

public slots:
    void startSerialReceive();// 启动串口
    void stopSerialReceive();// 停止串口


protected:
    void run() override; // 重写 QThread 的 run 方法

private:

    QSerialPort *serial {nullptr};// 指向主线程创建的共享串口对象（由主线程统一打开/关闭）
    bool running {false};// 运行标志
    QByteArray receiveBuffer;// 接收缓冲（累计 readAll 数据，供解析）

    void processReceivedData(QByteArray &buffer);// 处理接收到的数据

    static inline float readFloatBE(const QByteArray &buf, int off) {
        return ProtocolRx::readFloatBE(buf.constData() + off);
    }// 工具：从缓冲 buf 的 off 偏移处按大端序读取 float
};

#endif // SERIAL_WORKER_H
