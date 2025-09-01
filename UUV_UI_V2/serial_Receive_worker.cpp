#include "serial_Receive_worker.h"
#include <QDebug>

// 构造函数
SerialReceiveWorker::SerialReceiveWorker(QSerialPort *sharedSerial,QObject *parent)
    : QThread(parent), serial(sharedSerial), running(false)
{
}

// 析构函数
SerialReceiveWorker::~SerialReceiveWorker()
{
    stopSerialReceive(); // 停止线程
}

// 线程运行函数，负责接收数据
void SerialReceiveWorker::run()
{
    while (running) {
        if (serial&&serial->isOpen()) {
            if (serial->waitForReadyRead(40)) {// 等待新数据,-1为无限等待，可以改成xx毫秒
                 while (serial->bytesAvailable()) {
                    QByteArray received = serial->readAll();
                    qDebug()<<"ready";
                    if (!received.isEmpty()) {

                        //发送预览
                        QString hexStr = received.toHex().toUpper(); // 转换为大写十六进制字符串
                        QString formattedHex;
                        for (int i = 0; i < hexStr.length(); i += 2) {// 添加空格分隔
                            formattedHex += hexStr.mid(i, 2) + " ";
                        }
                        QString timestamp = QDateTime::currentDateTime().toString("[hh:mm:ss.zzz] ");
                        formattedHex = formattedHex.trimmed(); // 去除末尾多余空格
                        ReceiveView = timestamp+formattedHex;//加时间戳的
                        emit receiveViewUpdated(ReceiveView);   // 发送接收预览更新信号
                        qDebug()<<ReceiveView;

                        //解算数据
                        receiveBuffer.append(received);
                        processReceivedData(receiveBuffer);// 处理数据
                    }
                 }
            }
        }
        else {
            msleep(100);
        }
    }
}


// 启动串口
void SerialReceiveWorker::startSerialReceive()
{
    running = true;//开启子线程
    receiveBuffer.clear();
    currentState = WAIT_HEADER;
    start();
}

// 停止串口
void SerialReceiveWorker::stopSerialReceive()
{
    running = false;
    if (isRunning()) {
        //quit();
        //wait(); // 保证线程已退出
        terminate();//强制关闭线程
    }
}



// 处理接收到的数据
/*
 * 协议解析状态机
 * 支持自动丢弃无效数据、自动同步包头、处理半包/粘包
 * 典型数据包结构：包头0xFE | 模式1字节 | 24字节数据（6*float） | 包尾0xFF
 */
void SerialReceiveWorker::processReceivedData(QByteArray &buffer)
{
    int safetyCounter = 0; // 防止极端情况下死循环
    while (++safetyCounter < 100 && !buffer.isEmpty())
    {
        switch (currentState)
        {
        case WAIT_HEADER: {
            // 查找包头0xFE
            int headPos = buffer.indexOf('\xFE');
            if (headPos == -1) {
                buffer.clear(); // 没有包头，全部丢弃
                return;
            }
            if (headPos > 0) buffer.remove(0, headPos); // 丢弃包头前的垃圾数据
            if (buffer.size() < 1) return; // 只剩包头，等待下次
            buffer.remove(0, 1); // 移除包头
            currentState = READ_MODE;
            break;
        }
        case READ_MODE: {
            if (buffer.size() < 1) return; // 不够一个模式字节
            quint8 mode = static_cast<quint8>(buffer[0]);
            if (mode < 0x01 || mode > 0x05) {
                // 非法模式字节，丢弃1字节，重新查找包头
                buffer.remove(0, 1);
                currentState = WAIT_HEADER;
                break;
            }
            // 合法模式，移除模式字节，进入收集数据
            buffer.remove(0, 1);
            //currentMode = mode; // 可选：记录当前模式
            currentState = COLLECT_DATA;
            break;
        }
        case COLLECT_DATA: {
            if (buffer.size() < 24) return; // 数据体不够，等待下次
            // 解析6个float（24字节）
            QDataStream stream(buffer.left(24));
            stream.setByteOrder(QDataStream::BigEndian);
            stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
            for (int i = 0; i < 6; ++i) {
                stream >> etaData[i];
            }
            buffer.remove(0, 24);
            // 解算成功，发信号（如有需要可加包完整性检查）
            emit dataReceived(etaData[0], etaData[1], etaData[2], etaData[3], etaData[4], etaData[5]);
            currentState = CHECK_TAIL;
            break;
        }
        case CHECK_TAIL: {
            if (buffer.size() < 1) return; // 没有包尾，等待下次
            if (static_cast<quint8>(buffer[0]) == 0xFF) {
                // 包尾正确，移除
                buffer.remove(0, 1);
            } else {
                // 包尾错误，丢弃一个字节，恢复查找包头
                buffer.remove(0, 1);
            }
            currentState = WAIT_HEADER;
            break;
        }
        }
    }
}


