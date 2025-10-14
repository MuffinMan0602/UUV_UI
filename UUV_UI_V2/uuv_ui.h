#ifndef UUV_UI_H
#define UUV_UI_H

#pragma once
#include <QMainWindow>
#include <QTimer>
#include <QDateTime>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QKeyEvent>
#include <QDoubleSpinBox>
#include <QSlider>
#include <windows.h>  // 包含 ZeroMemory 宏的定义
#include <XInput.h>
#include <QThread>
#include <QScreen>
#include <QScrollBar>

#include "serial_Receive_worker.h"
#include "serial_Transmit_worker.h"

#include "ctrans.h"
#include <QDebug>

#include "uuv_log_recorder.h"   // 引入自定义独立日志记录类

#include "protocol_receive.h"
// 协议头（仅用于“接收”方向），包含帧偏移、常量与 UUVRxFrame 结构体。
// 该文件中声明了 Q_DECLARE_METATYPE(UUVRxFrame)，
// 且在 SerialReceiveWorker 构造函数中进行了 qRegisterMetaType 注册，
// 使得 frameReceived(UUVRxFrame) 信号可以安全跨线程传递。

QT_BEGIN_NAMESPACE
namespace Ui {
class UUV_UI;
}
QT_END_NAMESPACE

class QSerialPort;
class SerialTransmitWorker;
class SerialReceiveWorker;

class UUV_UI : public QMainWindow
{
    Q_OBJECT

public:
    UUV_UI(QWidget *parent = nullptr);
    ~UUV_UI();
    // ========================= 公开控制参数 ======================//
    int8_t WorkMode = 0x01;//工作模式,默认遥控
    int TransmitPeriod = 100;//默认发送周期
    int8_t taw_x = 0;
    int8_t taw_y = 0;
    int8_t taw_z = 0;
    int8_t taw_phi = 0;
    int8_t taw_theta = 0;
    int8_t taw_psi = 0;
    float Depth_d =0.00;//半自主的期望深度
    float Yaw_d =0.00;//半自主的期望艏向
    float etaData[6];// 存储x,y,z,roll,pitch,yaw
    int cv=80;//默认油门
    float pos[6] = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f}; // 初始化，避免未定义值

signals:
    void requestCsvData(int rowIndex);//请求CSV数据信号（全自主模式用）

protected:
    // 窗口关闭事件：用于在正在记录时,询问是否保存记录
    void closeEvent(QCloseEvent *event) override;

private:
    //Ui::UUV_UI *ui;
    Ui::UUV_UI *ui = nullptr;

    int m_controllerId = 0; // 默认连接第一个手柄

    QTimer *TransmitTimer = new QTimer(this);//串口发送定时器
    QTimer *Gamepad_timer = new QTimer(this);//手柄刷新率

    QSerialPort *sharedSerial = nullptr;              // 共享串口对象
    SerialTransmitWorker *transmitWorker = nullptr;   // 发送线程
    SerialReceiveWorker  *receiveWorker  = nullptr;   // 接收解算线程
    // QSerialPort *sharedSerial; // 共享串口对象
    // SerialTransmitWorker *transmitWorker; // 发送线程
    // SerialReceiveWorker *receiveWorker; // 接收解算线程

    CTrans *ctransWidget = nullptr;//连续发送子窗口,定义全局的连续发送类，指针指向空
    bool csvDataflag = false; // 是否已拿到CSV的有效数据
    int m_csvCurrentIndex = 0; // 当前CSV数据索引

    //与日志记录相关
    UUVLogRecorder m_recorder;     // 日志记录器实例（同步）
    QTimer *m_recordUiTimer = new QTimer(this); // 每秒刷新“记录时长”等显示

    // ================== 内部私有辅助函数 ==================//
    void updateButtonStates(); // 更新所有按钮的UI状态
    void configureSerial(); // 串口配置函数
    void ManualControlValue();//计算控制量
    void semiAutoControlValueComput();//半自主模式控制量计算
    void ShowMovement();//展示当前动作

    void updateTransmitPreview(const QString &transmitView); // 更新发送预览框
    void updateReceivePreview(const QString &receiveView);   // 更新接收预览框

    void refreshRecordUi(); // 刷新记录行数与时长（由 m_recordUiTimer 触发）
    void logTransmitFrame(); //统一在预览回调中记录发送帧


private slots:
    //界面操作
    void currentTimerUpdate();//更新时间框函数
    void on_pushButton_scan_clicked();//扫描串口
    void on_pushButton_open_clicked();//打开串口的按钮
    void on_comboBox_TransPeriod_currentIndexChanged();//改变发送频率
    void on_pushButton_RClear_clicked();//清除接收预览框
    void on_pushButton_TClear_clicked();//清除发送预览框
    void on_comboBox_WorkMode_currentIndexChanged();//发送工作模式选择
    void on_horizontalSlider_cv_valueChanged(int value);//油门

    //期望深度、艏向数值与进度条关联
    void on_doubleSpinBox_Depth_valueChanged(double arg1);
    void on_horizontalSlider_Depth_valueChanged(int value);
    void on_doubleSpinBox_Heading_valueChanged(double arg1);
    void on_horizontalSlider_Heading_valueChanged(int value);

    //按键操作
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    //手柄操作
    void updateJoystickData();//更新手柄
    void on_checkBox_GamePad_checkStateChanged();//勾选手柄操作

    void requestTransmit();//

    // 串口子线程信号槽
    //void onSerialErrorOccurred(const QString &errorMessage); // 新增，处理串口错误
    //void onSerialDataReceived(float x, float y, float z, float roll, float pitch, float yaw); // 更新UI

    // 处理完整帧并更新 UI
    void onUUVFrameReceived(const UUVRxFrame &f);

    void updateTransValues(); // 更新发送参数给线程

    //文件相关操作/全自主模式相关
    void on_pushButton_AutoTrans_clicked();//开始发送程序按钮
    void onTransWidgetDestroyed();//另负责连续发送的窗口类ctrans指针指空
    void handleCsvData(int Index, float p1, float p2, float p3, float p4, float p5, float p6);//处理CSV坐标数据

    // 与 UI 控件绑定的槽
    void on_checkBox_Record_stateChanged(int state); // 勾选开始记录
    void on_pushButton_RClear_2_clicked();            // 保存日志
    void on_pushButton_RClear_3_clicked();            // 清除日志（不保存）


};
#endif // UUV_UI_H
