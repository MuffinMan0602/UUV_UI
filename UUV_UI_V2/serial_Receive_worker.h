#ifndef SERIAL_RECEIVE_WORKER_H
#define SERIAL_RECEIVE_WORKER_H

#pragma once

#include <QObject>
#include <QSerialPort>
#include <QByteArray>
//#include <QDataStream>
#include <QThread>
#include <QDateTime>

#include "protocol_receive.h"  // 新协议定义


// enum ParseState//串口解算状态机状态表
// {
//     WAIT_HEADER,
//     READ_BODY
//     // READ_MODE,
//     // COLLECT_DATA,
//     // CHECK_TAIL
// };



class SerialReceiveWorker : public QThread
{
    Q_OBJECT
public:
    explicit SerialReceiveWorker(QSerialPort *sharedSerial,QObject *parent = nullptr);
    ~SerialReceiveWorker();



signals:
    // void dataReceived(float x, float y, float z, float roll, float pitch, float yaw); // 数据接收信号,解算后的数据
    // void errorOccurred(const QString &errorMessage); // 错误信号
    // void receiveViewUpdated(const QString &receiveView);   // 通知主线程接收预览更新

    void frameReceived(UUVRxFrame frame);//每解析出一帧完整数据即触发函数

public slots:
    void startSerialReceive();// 启动串口
    void stopSerialReceive();// 停止串口


protected:
    void run() override; // 重写 QThread 的 run 方法

private:

    QSerialPort *serial {nullptr};// 指向主线程创建的共享串口对象（由主线程统一打开/关闭）
    bool running {false};// 运行标志

    //ParseState currentState = WAIT_HEADER;//串口解算状态机默认值
    QByteArray receiveBuffer;// 接收缓冲（累计 readAll 数据，供解析）

    void processReceivedData(QByteArray &buffer);// 处理接收到的数据

    static inline float readFloatBE(const QByteArray &buf, int off) {
        return ProtocolRx::readFloatBE(buf.constData() + off);
    }// 工具：从缓冲 buf 的 off 偏移处按大端序读取 float


    // QSerialPort *serial; // 指向共享的串口对象
    // ParseState currentState = WAIT_HEADER;//串口解算状态机默认值

    // bool running; // 运行标志
    // QByteArray receiveBuffer; // 接收缓冲区
    // float etaData[6];// 存储x,y,z,roll,pitch,yaw
    // QString ReceiveView;//接收预览

    //void processReceivedData(QByteArray &buffer); // 处理接收到的数据
};

#endif // SERIAL_WORKER_H
