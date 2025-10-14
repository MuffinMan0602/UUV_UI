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
                        //累加缓冲并解析
                        receiveBuffer.append(serial->readAll());
                        processReceivedData(receiveBuffer);
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
    start();
}

// 停止串口
void SerialReceiveWorker::stopSerialReceive()
{
    running = false;
    if (isRunning()) {
        terminate();//强制关闭线程
    }
}


void SerialReceiveWorker::processReceivedData(QByteArray &buffer)
{
    int guard = 0;
    while (++guard < 200) {
        // 1) 找帧头
        int headPos = buffer.indexOf(char(ProtocolRx::HEAD));
        if (headPos < 0) { buffer.clear(); return; }
        if (headPos > 0) { buffer.remove(0, headPos); }

        // 2) 长度不够一帧
        if (buffer.size() < ProtocolRx::SIZE) return;

        // 3) 校验尾
        const quint8 tail = static_cast<quint8>(buffer[ProtocolRx::OFF_TAIL]);
        if (tail != ProtocolRx::TAIL) {
            buffer.remove(0, 1);
            continue;
        }

        // 4) 校验模式
        const quint8 mode = static_cast<quint8>(buffer[ProtocolRx::OFF_MODE]);
        if (mode < ProtocolRx::MIN_MODE || mode > ProtocolRx::MAX_MODE) {
            buffer.remove(0, 1);
            continue;
        }

        // 在移除之前，先把这一整帧做预览行（一次一行、一个时间戳）
        const QByteArray frameBytes = buffer.left(ProtocolRx::SIZE);
        QString hex = frameBytes.toHex().toUpper();
        QString spaced; spaced.reserve(hex.size() + hex.size()/2);
        for (int i = 0; i < hex.size(); i += 2) { spaced += hex.mid(i, 2); spaced += ' '; }
        const QString line = QDateTime::currentDateTime().toString("[hh:mm:ss.zzz] ")
                             + spaced.trimmed();
        emit receiveViewUpdated(line);

        // 5) 解析字段
        UUVRxFrame f;
        f.mode       = mode;
        f.voltage    = static_cast<qint8>(buffer[ProtocolRx::OFF_SAFE_0]);
        f.current    = static_cast<qint8>(buffer[ProtocolRx::OFF_SAFE_1]);
        f.cabinTemp  = static_cast<qint8>(buffer[ProtocolRx::OFF_SAFE_2]);
        f.dropSignal = static_cast<qint8>(buffer[ProtocolRx::OFF_SAFE_3]);
        f.posSource  = static_cast<quint8>(buffer[ProtocolRx::OFF_POS_SRC]);

        int off = ProtocolRx::OFF_FLOATS;
        f.x = readFloatBE(buffer, off); off+=4;
        f.y = readFloatBE(buffer, off); off+=4;
        f.z = readFloatBE(buffer, off); off+=4;
        f.phi   = readFloatBE(buffer, off); off+=4;
        f.theta = readFloatBE(buffer, off); off+=4;
        f.psi   = readFloatBE(buffer, off); off+=4;
        f.u = readFloatBE(buffer, off); off+=4;
        f.v = readFloatBE(buffer, off); off+=4;
        f.w = readFloatBE(buffer, off); off+=4;
        f.p = readFloatBE(buffer, off); off+=4;
        f.q = readFloatBE(buffer, off); off+=4;
        f.r = readFloatBE(buffer, off); off+=4;
        for (int i=0;i<6;++i) { f.T[i] = readFloatBE(buffer, off); off+=4; }

        emit frameReceived(f);

        // 6) 丢弃这一帧，继续处理可能的粘包
        buffer.remove(0, ProtocolRx::SIZE);
    }
}


