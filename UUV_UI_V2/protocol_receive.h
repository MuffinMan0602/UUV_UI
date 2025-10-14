#ifndef PROTOCOL_RECEIVE_H
#define PROTOCOL_RECEIVE_H

#endif // PROTOCOL_RECEIVE_H

#pragma once
#include <QtGlobal>
#include <QMetaType>
#include <cstring>

/*
 * UUV → 上位机 80 字节状态帧（大端浮点）
 * 结构：
 * [0]  0xFE                     // 帧头
 * [1]  mode (0x01~0x05)         // 工作模式
 * [2]  int8  voltage            // 机器人安全状态-电压值（工程缩放由双方约定）
 * [3]  int8  current            // 电流值
 * [4]  int8  cabin_temperature  // 舱内温度
 * [5]  int8  drop_signal        // 抛载信号
 * [6]  uint8 pos_source         // 位置信息来源（0x01/0x02）
 * [7..30]   6×float big-endian  // x,y,z,phi,theta,psi
 * [31..54]  6×float big-endian  // u,v,w,p,q,r
 * [55..78]  6×float big-endian  // T1..T6
 * [79] 0xFF                     // 帧尾
 */

namespace ProtocolRx {
// 常量与整体规格
static constexpr quint8  HEAD     = 0xFE;
static constexpr quint8  TAIL     = 0xFF;
static constexpr quint8  MIN_MODE = 0x01;
static constexpr quint8  MAX_MODE = 0x05;
static constexpr int     SIZE     = 80;

// 偏移（相对帧头）
static constexpr int OFF_HEAD       = 0;
static constexpr int OFF_MODE       = 1;
static constexpr int OFF_SAFE_0     = 2;  // voltage
static constexpr int OFF_SAFE_1     = 3;  // current
static constexpr int OFF_SAFE_2     = 4;  // cabin temp
static constexpr int OFF_SAFE_3     = 5;  // drop signal
static constexpr int OFF_POS_SRC    = 6;  // 位置来源
static constexpr int OFF_FLOATS     = 7;  // 连续18个float：ETA(6)+VEL(6)+T(6)
static constexpr int FLOAT_COUNT    = 18;
static constexpr int OFF_TAIL       = 79;

// 从大端字节序读取 float（不依赖主机端字节序；使用 memcpy 避免别名规则问题）
inline float readFloatBE(const char* bytes) {
    quint32 be = (static_cast<quint8>(bytes[0]) << 24) |
                 (static_cast<quint8>(bytes[1]) << 16) |
                 (static_cast<quint8>(bytes[2]) <<  8) |
                 (static_cast<quint8>(bytes[3])      );
    float f;
    std::memcpy(&f, &be, sizeof(f));
    return f;
}
}

// 一帧业务数据承载体
struct UUVRxFrame {
    quint8 mode;          // 0x01~0x05

    qint8  voltage;       // int8
    qint8  current;       // int8
    qint8  cabinTemp;     // int8
    qint8  dropSignal;    // int8
    quint8 posSource;     // 0x01/0x02

    // 位姿
    float x, y, z;
    float phi, theta, psi;

    // 速度
    float u, v, w;
    float p, q, r;

    // 推进器推力
    float T[6];
};
Q_DECLARE_METATYPE(UUVRxFrame)
