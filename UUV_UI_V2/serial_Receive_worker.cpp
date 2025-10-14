#include "serial_Receive_worker.h"
#include <QMetaType>
#include <QDebug>

// 构造函数
SerialReceiveWorker::SerialReceiveWorker(QSerialPort *sharedSerial,QObject *parent)
    : QThread(parent), serial(sharedSerial), running(false)
{
    // 注册自定义类型，允许在跨线程（QueuedConnection）信号/槽中传递
    qRegisterMetaType<UUVRxFrame>("UUVRxFrame");
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
                    // 读取本批所有可读字节，累加进缓冲
                    receiveBuffer.append(serial->readAll());
                    // 尝试从缓冲中解析出 0~N 帧
                    processReceivedData(receiveBuffer);



                    // QByteArray received = serial->readAll();

                    // qDebug()<<"ready";
                    // if (!received.isEmpty()) {

                    //     //发送预览
                    //     QString hexStr = received.toHex().toUpper(); // 转换为大写十六进制字符串
                    //     QString formattedHex;
                    //     for (int i = 0; i < hexStr.length(); i += 2) {// 添加空格分隔
                    //         formattedHex += hexStr.mid(i, 2) + " ";
                    //     }
                    //     QString timestamp = QDateTime::currentDateTime().toString("[hh:mm:ss.zzz] ");
                    //     formattedHex = formattedHex.trimmed(); // 去除末尾多余空格
                    //     ReceiveView = timestamp+formattedHex;//加时间戳的
                    //     emit receiveViewUpdated(ReceiveView);   // 发送接收预览更新信号
                    //     qDebug()<<ReceiveView;

                    //     //解算数据
                    //     receiveBuffer.append(received);
                    //     processReceivedData(receiveBuffer);// 处理数据
                    }
                 }
            }else {
                msleep(100);
        }
    }
}


// 启动串口
void SerialReceiveWorker::startSerialReceive()
{
    running = true;//开启子线程
    receiveBuffer.clear();
    //currentState = WAIT_HEADER;
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


void SerialReceiveWorker::processReceivedData(QByteArray &buffer)
{
    // 防止极端情况下的死循环（例如持续噪声）：最多尝试 200 次
    int guard = 0;
    while (++guard < 200) {
        // 1) 从缓冲中寻找帧头 0xFE
        int headPos = buffer.indexOf(char(ProtocolRx::HEAD));
        if (headPos < 0) {        // 没找到帧头，清空等待下一轮
            buffer.clear();
            return;
        }
        if (headPos > 0) {        // 丢弃帧头之前的噪声
            buffer.remove(0, headPos);
        }

        // 2) 若剩余字节不足一个完整帧，等待更多数据
        if (buffer.size() < ProtocolRx::SIZE) {
            return;
        }

        // 此时 buffer[0] == 0xFE
        // 3) 校验尾字节
        quint8 tail = static_cast<quint8>(buffer[ProtocolRx::OFF_TAIL]);
        if (tail != ProtocolRx::TAIL) {
            // 帧尾不对：丢弃本帧头 1 字节，继续重同步
            buffer.remove(0, 1);
            continue;
        }

        // 4) 读取并校验 mode
        quint8 mode = static_cast<quint8>(buffer[ProtocolRx::OFF_MODE]);
        if (mode < ProtocolRx::MIN_MODE || mode > ProtocolRx::MAX_MODE) {
            // 非法模式：同样丢弃 1 字节重同步
            buffer.remove(0, 1);
            continue;
        }

        // 5) 解析所有字段（按固定偏移）
        UUVRxFrame f;
        f.mode       = mode;
        f.voltage    = static_cast<qint8>(buffer[ProtocolRx::OFF_SAFE_0]);
        f.current    = static_cast<qint8>(buffer[ProtocolRx::OFF_SAFE_1]);
        f.cabinTemp  = static_cast<qint8>(buffer[ProtocolRx::OFF_SAFE_2]);
        f.dropSignal = static_cast<qint8>(buffer[ProtocolRx::OFF_SAFE_3]);
        f.posSource  = static_cast<quint8>(buffer[ProtocolRx::OFF_POS_SRC]);

        int off = ProtocolRx::OFF_FLOATS;

        // 位姿 6
        f.x     = readFloatBE(buffer, off); off += 4;
        f.y     = readFloatBE(buffer, off); off += 4;
        f.z     = readFloatBE(buffer, off); off += 4;
        f.phi   = readFloatBE(buffer, off); off += 4;
        f.theta = readFloatBE(buffer, off); off += 4;
        f.psi   = readFloatBE(buffer, off); off += 4;

        // 速度 6
        f.u = readFloatBE(buffer, off); off += 4;
        f.v = readFloatBE(buffer, off); off += 4;
        f.w = readFloatBE(buffer, off); off += 4;
        f.p = readFloatBE(buffer, off); off += 4;
        f.q = readFloatBE(buffer, off); off += 4;
        f.r = readFloatBE(buffer, off); off += 4;

        // 推进器 6
        for (int i = 0; i < 6; ++i) {
            f.T[i] = readFloatBE(buffer, off); off += 4;
        }

        // 6) 发业务信号
        emit frameReceived(f);

        // 7) 从缓冲中移除一个完整帧，继续尝试解析后续粘包
        buffer.remove(0, ProtocolRx::SIZE);
    }
}

    // int safetyCounter = 0; // 防止极端情况下死循环
    // while (++safetyCounter < 100 && !buffer.isEmpty())
    // {
    //     switch (currentState)
    //     {
    //     case WAIT_HEADER: {
    //         // 查找包头0xFE
    //         int headPos = buffer.indexOf('\xFE');
    //         if (headPos == -1) {
    //             buffer.clear(); // 没有包头，全部丢弃
    //             return;
    //         }
    //         if (headPos > 0) buffer.remove(0, headPos); // 丢弃包头前的垃圾数据
    //         if (buffer.size() < 1) return; // 只剩包头，等待下次
    //         buffer.remove(0, 1); // 移除包头
    //         currentState = READ_MODE;
    //         break;
    //     }
    //     case READ_MODE: {
    //         if (buffer.size() < 1) return; // 不够一个模式字节
    //         quint8 mode = static_cast<quint8>(buffer[0]);
    //         if (mode < 0x01 || mode > 0x05) {
    //             // 非法模式字节，丢弃1字节，重新查找包头
    //             buffer.remove(0, 1);
    //             currentState = WAIT_HEADER;
    //             break;
    //         }
    //         // 合法模式，移除模式字节，进入收集数据
    //         buffer.remove(0, 1);
    //         //currentMode = mode; // 可选：记录当前模式
    //         currentState = COLLECT_DATA;
    //         break;
    //     }
    //     case COLLECT_DATA: {
    //         if (buffer.size() < 24) return; // 数据体不够，等待下次
    //         // 解析6个float（24字节）
    //         QDataStream stream(buffer.left(24));
    //         stream.setByteOrder(QDataStream::BigEndian);
    //         stream.setFloatingPointPrecision(QDataStream::SinglePrecision);
    //         for (int i = 0; i < 6; ++i) {
    //             stream >> etaData[i];
    //         }
    //         buffer.remove(0, 24);
    //         // 解算成功，发信号（如有需要可加包完整性检查）
    //         emit dataReceived(etaData[0], etaData[1], etaData[2], etaData[3], etaData[4], etaData[5]);
    //         currentState = CHECK_TAIL;
    //         break;
    //     }
    //     case CHECK_TAIL: {
    //         if (buffer.size() < 1) return; // 没有包尾，等待下次
    //         if (static_cast<quint8>(buffer[0]) == 0xFF) {
    //             // 包尾正确，移除
    //             buffer.remove(0, 1);
    //         } else {
    //             // 包尾错误，丢弃一个字节，恢复查找包头
    //             buffer.remove(0, 1);
    //         }
    //         currentState = WAIT_HEADER;
    //         break;
    //     }
