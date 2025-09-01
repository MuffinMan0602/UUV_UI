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
//#include <QPoint>
#include <QScreen>

#include "serial_Receive_worker.h"
#include "serial_Transmit_worker.h"

#include "ctrans.h"
#include <QDebug>



QT_BEGIN_NAMESPACE
namespace Ui {
class UUV_UI;
}
QT_END_NAMESPACE



class UUV_UI : public QMainWindow
{
    Q_OBJECT

public:
    UUV_UI(QWidget *parent = nullptr);
    ~UUV_UI();


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

    float pos[6];//自主模式点坐标

signals:
    void requestCsvData(int rowIndex);//请求CSV数据信号

private:
    Ui::UUV_UI *ui;


    int m_controllerId = 0; // 默认连接第一个手柄


    QTimer *TransmitTimer = new QTimer(this);//串口发送定时器
    QTimer *Gamepad_timer = new QTimer(this);//手柄刷新率
    QSerialPort *sharedSerial; // 共享串口对象
    SerialTransmitWorker *transmitWorker; // 发送线程
    SerialReceiveWorker *receiveWorker; // 接收解算线程


    void updateButtonStates(); // 更新所有按钮的UI状态

    void configureSerial(); // 串口配置函数

    void ManualControlValue();//计算控制量
    void semiAutoControlValueComput();//半自主模式控制量计算
    void ShowMovement();//展示当前动作
    void updateTransmitPreview(const QString &transmitView); // 更新发送预览框
    void updateReceivePreview(const QString &receiveView);   // 更新接收预览框

    CTrans *ctransWidget = nullptr;//定义全局的连续发送类，指针指向空

    int m_csvCurrentIndex = 0; // 当前CSV数据索引



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

    void TransmitInfo();//**

    // 串口子线程信号槽
    void onSerialErrorOccurred(const QString &errorMessage); // 新增，处理串口错误
    void onSerialDataReceived(float x, float y, float z, float roll, float pitch, float yaw); // 更新UI

    void updateTransValues(); // 更新发送参数

    //文件相关操作
    void on_pushButton_OpenFile_clicked();//开始发送程序按钮
    void onTransWidgetDestroyed();//另负责连续发送的窗口类ctrans指针指空

    void handleCsvData(float p1, float p2, float p3, float p4, float p5, float p6);//处理CSV坐标数据
};
#endif // UUV_UI_H
