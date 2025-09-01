#ifndef SERIAL_RECEIVE_WORKER_H
#define SERIAL_RECEIVE_WORKER_H

#pragma once

#include <QObject>
#include <QSerialPort>
#include <QByteArray>
#include <QDataStream>
#include <QThread>
#include <QDateTime>


enum ParseState//串口解算状态机状态表
{
    WAIT_HEADER,
    READ_MODE,
    COLLECT_DATA,
    CHECK_TAIL
};



class SerialReceiveWorker : public QThread
{
    Q_OBJECT
public:
    explicit SerialReceiveWorker(QSerialPort *sharedSerial,QObject *parent = nullptr);
    ~SerialReceiveWorker();



signals:
    void dataReceived(float x, float y, float z, float roll, float pitch, float yaw); // 数据接收信号,解算后的数据
    void errorOccurred(const QString &errorMessage); // 错误信号
    void receiveViewUpdated(const QString &receiveView);   // 通知主线程接收预览更新

public slots:
    void startSerialReceive();// 启动串口
    void stopSerialReceive();// 停止串口


protected:
    void run() override; // 重写 QThread 的 run 方法

private:
    QSerialPort *serial; // 指向共享的串口对象
    ParseState currentState = WAIT_HEADER;//串口解算状态机默认值

    bool running; // 运行标志
    QByteArray receiveBuffer; // 接收缓冲区
    float etaData[6];// 存储x,y,z,roll,pitch,yaw
    QString ReceiveView;//接收预览


    void processReceivedData(QByteArray &buffer); // 处理接收到的数据
};

#endif // SERIAL_WORKER_H
