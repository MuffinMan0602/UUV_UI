#include "serial_Transmit_worker.h"


// 构造函数
SerialTransmitWorker::SerialTransmitWorker(QSerialPort *sharedSerial,QObject *parent)
    : QThread(parent), serial(sharedSerial)
{
}

// 析构函数
SerialTransmitWorker::~SerialTransmitWorker()
{
    quit();
    wait();
    //terminate();//强制关闭线程
}

// 线程运行函数，负责接收数据
void SerialTransmitWorker::run()
{
    exec(); // 进入事件循环
}


//更新控制参数
void SerialTransmitWorker::updateTransValues(int8_t WorkMode,int8_t tx, int8_t ty, int8_t tz, int8_t tphi, int8_t ttheta, int8_t tpsi, float depth, float yaw)
{
    QMutexLocker locker(&mutex);// 更新控制参数（确保线程安全）
    currentWorkMode = WorkMode;
    taw_x = tx;
    taw_y = ty;
    taw_z = tz;
    taw_phi = tphi;
    taw_theta = ttheta;
    taw_psi = tpsi;
    Depth_d = depth;
    Yaw_d = yaw;
}

void SerialTransmitWorker::updateTransValues2(int8_t WorkMode, float p1, float p2, float p3, float p4, float p5, float p6)
{
    QMutexLocker locker(&mutex);// 更新控制参数（确保线程安全）
    currentWorkMode = WorkMode;
    pos1 = p1;
    pos2 = p2;
    pos3 = p3;
    pos4 = p4;
    pos5 = p5;
    pos6 = p6;

    //qDebug()<<pos1<<pos2<<pos3<<pos4<<pos5<<pos6;
}


//发送数据，使用协议封装
void SerialTransmitWorker::sendSerialData()
{
    QMutexLocker locker(&mutex); // 加锁，保证线程安全
    if (!serial || !serial->isOpen()) return;

    QByteArray packet;

    switch(currentWorkMode)
    {
    case 1:
    case 2:
    case 3:
    case 4:
        //currentWorkMode=0x01;
        packet.append(0xFE); // 包头
        packet.append(currentWorkMode);
        packet.append(taw_x);
        packet.append(taw_y);
        packet.append(taw_z);
        packet.append(taw_phi);
        packet.append(taw_theta);
        packet.append(taw_psi);

        appendFloat(packet,Depth_d);//使用函数占4位
        appendFloat(packet,Yaw_d);
        packet.append(0xFF); // 包尾
        break;
    case 5://全自主模式
        currentWorkMode=0x05;
        packet.append(0xFE); // 包头
        packet.append(currentWorkMode);

        appendFloat(packet,pos1);
        appendFloat(packet,pos2);
        appendFloat(packet,pos3);
        appendFloat(packet,pos4);
        appendFloat(packet,pos5);
        appendFloat(packet,pos6);//使用函数占4位

        packet.append(0xFF); // 包尾
        break;
    default:
        break;
    }
    serial->write(packet); // 发送数据
    QString hexData = packet.toHex(' ').toUpper();  // 字节间用空格分隔
    QString timestamp = QDateTime::currentDateTime().toString("[hh:mm:ss.zzz] ");
    TransmitView = timestamp + hexData;
    emit transmitViewUpdated(TransmitView);  // 发送发送预览更新信号
    //qDebug()<<TransmitView;
}

void SerialTransmitWorker::appendFloat(QByteArray &packet, float value)//使得float变量在Array中占4个字节
{
    char bytes[4];
    memcpy(bytes, &value, sizeof(float)); // 拷贝4字节内存
    packet.append(bytes[0]);  // 按系统字节序追加
    packet.append(bytes[1]);
    packet.append(bytes[2]);
    packet.append(bytes[3]);
}

