#include "uuv_ui.h"
#include "ui_uuv_ui.h"
//#include "csvworker.h"


//按键按下标志
bool QPressed = false;
bool WPressed = false;
bool EPressed = false;
bool RPressed = false;
bool APressed = false;
bool SPressed = false;
bool DPressed = false;
bool FPressed = false;
bool ZPressed = false;
bool XPressed = false;
bool CPressed = false;
bool VPressed = false;

int screen_centerX,screen_centerY = 0;//屏幕中心

UUV_UI::UUV_UI(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::UUV_UI)
    ,sharedSerial(new QSerialPort(this))
    , transmitWorker(new SerialTransmitWorker(sharedSerial,this))
    , receiveWorker(new SerialReceiveWorker(sharedSerial,this))
{
    ui->setupUi(this);

    //居中显示UI
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenRect = screen->geometry();
    screen_centerX = (screenRect.width() - width())/2;
    screen_centerY = (screenRect.height() - height())/2;
    move(screen_centerX, screen_centerY);

    // ------------------ 时间显示定时器 ------------------
    QTimer *timer1 = new QTimer(this);//更新时间框
    connect(timer1,SIGNAL(timeout()),this,SLOT(currentTimerUpdate()));//关联定时器和更新时间函数
    timer1->start(1000);//每1000ms产生一次timeout()信号
    currentTimerUpdate();//先调用一次，然后每1000ms触发一次

    // ------------------ 串口发送定时器 ------------------
    connect(TransmitTimer,SIGNAL(timeout()),this,SLOT(requestTransmit()));//定时发送串口消息
    //TransmitTimer->start(TransmitPeriod);

    // ------------------ 手柄轮询定时器 ------------------
    //中断读取手柄信息
    connect(Gamepad_timer,SIGNAL(timeout()),this,SLOT(updateJoystickData()));

    // ------------------ 线程信号槽 ---------------------
    //连接子线程信号和槽
    connect(receiveWorker, &SerialReceiveWorker::frameReceived,
            this, &UUV_UI::onUUVFrameReceived);

    //connect(receiveWorker, &SerialReceiveWorker::dataReceived, this, &UUV_UI::onSerialDataReceived);
    //connect(receiveWorker, &SerialReceiveWorker::errorOccurred, this, &UUV_UI::onSerialErrorOccurred);
    //connect(receiveWorker, &SerialReceiveWorker::receiveViewUpdated, this, &UUV_UI::updateReceivePreview);

    connect(transmitWorker, &SerialTransmitWorker::transmitViewUpdated, this, &UUV_UI::updateTransmitPreview);//预览框



    // ------------------ 线程信号槽 ---------------------
    // ==== 日志记录：初始化 UI 显示 ====
    if (ui->lineEdit_RecordCount_line) ui->lineEdit_RecordCount_line->setText("0");
    if (ui->lineEdit_RecordCount_time) ui->lineEdit_RecordCount_time->setText("00:00:00");

    // 每秒刷新日志时长/行数（只在记录中才有意义，不记录时也无害）
    m_recordUiTimer->setInterval(1000);
    connect(m_recordUiTimer, &QTimer::timeout, this, &UUV_UI::refreshRecordUi);

    // ------------------ 其他变量 ---------------------
    ui->lineEdit_cv->setText("80");//显示默认油门80
    m_csvCurrentIndex = 0; // 初始化CSV数据索引
}

UUV_UI::~UUV_UI()
{
    if (transmitWorker)transmitWorker->terminate();// 停止子线程
    if (receiveWorker)receiveWorker->stopSerialReceive(); // 停止线程
    if (sharedSerial)sharedSerial->close(); // 由主线程统一关闭

    // 若仍在记录，可在此决定是否自动保存——当前策略：不保存直接销毁
    delete ui;
}

//***********************************************************************************************************//
//                                                  界面操作                                                  //
//***********************************************************************************************************//

void UUV_UI::currentTimerUpdate()//更新时间框函数
{
    QDateTime currentTime = QDateTime::currentDateTime();
    ui->lineEdit_DateTime->setText(currentTime.toString("yyyy.MM.dd  hh:mm:ss ddd"));
}


void UUV_UI::on_pushButton_scan_clicked()//扫描串口
{
    // 清空串口下拉框
    ui->comboBox_name->clear();

    // 遍历当前系统可用的串口
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        QSerialPort _com; // 临时串口对象，用于检测可用性
        _com.setPort(info);

        // 检查端口是否可用（未被其他程序占用）
        if (_com.open(QIODevice::ReadWrite)) {
            ui->comboBox_name->addItem(info.portName()); // 将可用的串口名添加到下拉框
            _com.close(); // 关闭临时串口
        }
    }

    // 检查是否找到可用的串口
    if (ui->comboBox_name->count() == 0) {
        ui->lineEdit_Warning->setText("未找到可用的串口"); // 显示警告信息
    } else {
        ui->lineEdit_Warning->setText("找到可用串口"); // 显示成功信息
    }
}


void UUV_UI::on_pushButton_open_clicked()//打开串口的按钮
{
    if (!sharedSerial->isOpen()) {
        // 配置串口
        configureSerial();

        // 打开串口
        if (sharedSerial->open(QIODevice::ReadWrite)) {
            ui->checkBox_SerialOpen->setChecked(true);
            ui->pushButton_open->setText("关闭串口");
            ui->lineEdit_Warning->setText("串口已打开");
            TransmitTimer->start(TransmitPeriod);
            // 启动发送和接收线程
            transmitWorker->start();
            receiveWorker->startSerialReceive();
        } else {
            // 打开失败，显示错误信息
            ui->lineEdit_Warning->setText("无法打开串口：" + sharedSerial->errorString());
        }
    } else {
        // 关闭串口

        TransmitTimer->stop();
        transmitWorker->terminate();// 停止子线程
        //transmitWorker->quit();
        //transmitWorker->wait();
        receiveWorker->stopSerialReceive(); // 停止线程

        if (sharedSerial->isOpen()) {
            sharedSerial->close();
        }

        ui->checkBox_SerialOpen->setChecked(false);
        ui->pushButton_open->setText("打开串口");
        ui->lineEdit_Warning->setText("串口已关闭");
    }
}

void UUV_UI::configureSerial()
{
    // 根据UI设置配置串口
    sharedSerial->setPortName(ui->comboBox_name->currentText());
    sharedSerial->setBaudRate(ui->comboBox_BaudRate->currentText().toInt());

    // 设置数据位
    switch (ui->comboBox_data->currentText().toInt()) {
    case 5: sharedSerial->setDataBits(QSerialPort::Data5); break;
    case 6: sharedSerial->setDataBits(QSerialPort::Data6); break;
    case 7: sharedSerial->setDataBits(QSerialPort::Data7); break;
    case 8: sharedSerial->setDataBits(QSerialPort::Data8); break;
    }

    // 设置停止位
    switch (ui->comboBox_stop->currentIndex()) {
    case 0: sharedSerial->setStopBits(QSerialPort::OneStop); break;
    case 1: sharedSerial->setStopBits(QSerialPort::TwoStop); break;
    case 2: sharedSerial->setStopBits(QSerialPort::OneAndHalfStop); break;
    }

    // 设置校验位
    switch (ui->comboBox_check->currentIndex()) {
    case 0: sharedSerial->setParity(QSerialPort::NoParity); break;
    case 1: sharedSerial->setParity(QSerialPort::OddParity); break;
    case 2: sharedSerial->setParity(QSerialPort::EvenParity); break;
    }
}

void UUV_UI::on_comboBox_TransPeriod_currentIndexChanged()//调整发送频率
{
    disconnect(TransmitTimer,SIGNAL(timeout()),this,SLOT(TransmitInfo()));
    switch(ui->comboBox_TransPeriod->currentIndex())
    {

    case 0:TransmitPeriod=100;break;
    case 1:TransmitPeriod=50;break;
    case 2:TransmitPeriod=200;break;
    default:break;
    }
    connect(TransmitTimer,SIGNAL(timeout()),this,SLOT(TransmitInfo()));
    TransmitTimer->start(TransmitPeriod);
}


void UUV_UI::on_pushButton_TClear_clicked()//清除发送预览框
{
    ui->textBrowser_TPreview->clear();
}
void UUV_UI::on_pushButton_RClear_clicked()//清除接收预览框
{
    ui->textBrowser_RPreview->clear();
}


void UUV_UI::on_comboBox_WorkMode_currentIndexChanged()//发送工作模式选择
{
    switch(ui->comboBox_WorkMode->currentIndex())
    {
    case 0:WorkMode=0x01;break;
    case 1:WorkMode=0x02;break;
    case 2:WorkMode=0x03;break;
    case 3:WorkMode=0x04;break;
    case 4:WorkMode=0x05;
        //进入自主模式时清空旧 pos，避免上次残留
        csvDataflag = false;
        for (float &v : pos) v = 0.f; // 或设 NaN，如果你喜欢
        break;
    default:break;
    }
}


//期望深度、艏向数值与进度条关联
void UUV_UI::on_doubleSpinBox_Depth_valueChanged(double arg1)
{
    ui->horizontalSlider_Depth->blockSignals(true);// 防止信号循环
    int sliderValue = static_cast<int>(arg1 * 100);
    ui->horizontalSlider_Depth->setValue(sliderValue);
    Depth_d = arg1;
    ui->horizontalSlider_Depth->blockSignals(false);
}
void UUV_UI::on_horizontalSlider_Depth_valueChanged(int value)
{
    ui->doubleSpinBox_Depth->blockSignals(true);// 防止信号循环
    double SpinValue = value / 100.0;
    ui->doubleSpinBox_Depth->setValue(SpinValue);
    Depth_d = SpinValue;
    ui->doubleSpinBox_Depth->blockSignals(false);
}
void UUV_UI::on_doubleSpinBox_Heading_valueChanged(double arg1)
{
    ui->horizontalSlider_Heading->blockSignals(true);// 防止信号循环
    int sliderValue = static_cast<int>(arg1 * 10);
    ui->horizontalSlider_Heading->setValue(sliderValue);
    Yaw_d = arg1;
    ui->horizontalSlider_Heading->blockSignals(false);
}
void UUV_UI::on_horizontalSlider_Heading_valueChanged(int value)
{
    ui->doubleSpinBox_Heading->blockSignals(true);// 防止信号循环
    double SpinValue = value / 10.0;
    ui->doubleSpinBox_Heading->setValue(SpinValue);
    Yaw_d = SpinValue;
    ui->doubleSpinBox_Heading->blockSignals(false);
}

//油门控制
void UUV_UI::on_horizontalSlider_cv_valueChanged(int value)
{
    cv=value;
    ui->lineEdit_cv->setText(QString::number(value));
}


//***********************************************************************************************************//
//                                                  按键操作                                                  //
//***********************************************************************************************************//

void UUV_UI::keyPressEvent(QKeyEvent *event)//按键按下
{
    switch (event->key())
    {
        case Qt::Key_Q:QPressed = true;break;
        case Qt::Key_W:WPressed = true;break;
        case Qt::Key_E:EPressed = true;break;
        case Qt::Key_R:RPressed = true;break;
        case Qt::Key_A:APressed = true;break;
        case Qt::Key_S:SPressed = true;break;
        case Qt::Key_D:DPressed = true;break;
        case Qt::Key_F:FPressed = true;break;
        case Qt::Key_Z:ZPressed = true;break;
        case Qt::Key_X:XPressed = true;break;
        case Qt::Key_C:CPressed = true;break;
        case Qt::Key_V:VPressed = true;break;
        default:break;
    }
    updateButtonStates();
}

void UUV_UI::keyReleaseEvent(QKeyEvent *event)//按键松开
{
    switch (event->key())
    {
        case Qt::Key_Q:QPressed = false;break;
        case Qt::Key_W:WPressed = false;break;
        case Qt::Key_E:EPressed = false;break;
        case Qt::Key_R:RPressed = false;break;
        case Qt::Key_A:APressed = false;break;
        case Qt::Key_S:SPressed = false;break;
        case Qt::Key_D:DPressed = false;break;
        case Qt::Key_F:FPressed = false;break;
        case Qt::Key_Z:ZPressed = false;break;
        case Qt::Key_X:XPressed = false;break;
        case Qt::Key_C:CPressed = false;break;
        case Qt::Key_V:VPressed = false;break;
        default:break;
    }
    updateButtonStates();
}

void UUV_UI::updateButtonStates()// 更新所有按钮的UI状态
{
    ui->pushButton_Q->setDown(QPressed);
    ui->pushButton_W->setDown(WPressed);
    ui->pushButton_E->setDown(EPressed);
    ui->pushButton_R->setDown(RPressed);
    ui->pushButton_A->setDown(APressed);
    ui->pushButton_S->setDown(SPressed);
    ui->pushButton_D->setDown(DPressed);
    ui->pushButton_F->setDown(FPressed);
    ui->pushButton_Z->setDown(ZPressed);
    ui->pushButton_X->setDown(XPressed);
    ui->pushButton_C->setDown(CPressed);
    ui->pushButton_V->setDown(VPressed);
}



//***********************************************************************************************************//
//                                                  手柄操作                                                  //
//***********************************************************************************************************//

void UUV_UI::updateJoystickData()//更新手柄信息
{
    XINPUT_STATE state;                  // 定义XInput手柄状态结构体
    ZeroMemory(&state, sizeof(XINPUT_STATE)); // 清空状态结构体内存，防止残留数据干扰

    // 调用XInput API获取指定控制器ID的状态（参数1为控制器ID，0表示第一个连接的手柄）
    DWORD result = XInputGetState(m_controllerId, &state);
    if (result == ERROR_SUCCESS) {
        // 解析左摇杆原始数据（16位有符号整数，范围：-32768 ~ 32767）
        SHORT lx = -1*state.Gamepad.sThumbLX;   // 左摇杆X轴原始值，代表前倾/后倾方向
        SHORT ly = state.Gamepad.sThumbLY;   // 左摇杆Y轴原始值，代表右转/左转方向
        // 解析右摇杆原始数据（16位有符号整数，范围：-32768 ~ 32767）
        SHORT rx = state.Gamepad.sThumbRX;  // 右摇杆X轴原始值，代表前进/后退方向
        SHORT ry = state.Gamepad.sThumbRY;  // 右摇杆Y轴原始值，代表横滚方向
        // 方向键（DPad）
        bool dpadUp    = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_UP)    != 0; //上浮
        bool dpadDown  = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_DOWN)  != 0; //下潜
        bool dpadLeft  = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT)  != 0; //左平动
        bool dpadRight = (state.Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) != 0; //右平动

        taw_x = ry/256; // 32768(油门单侧分辨力)/128（uint8的一半范围）=256
        taw_y = (dpadRight-dpadLeft)*80; //可根据表现调参
        taw_z = (dpadDown-dpadUp)*80;
        taw_phi = lx/256;
        taw_theta = ly/256;
        taw_psi = rx/256;
    }
    else// 手柄未连接提示
    {
        ui->lineEdit_Warning->setText("未连接手柄");
    }
}


void UUV_UI::on_checkBox_GamePad_checkStateChanged()//勾选/取消勾选手柄控制
{
    if(ui->checkBox_GamePad->isChecked()==true)//勾选手柄
    {
        Gamepad_timer->start(25);//40Hz更新频率
    }
    if(ui->checkBox_GamePad->isChecked()==false)//取消勾选手柄
    {
        Gamepad_timer->stop();
    }
}



//***********************************************************************************************************//
//                                                  串口线程                                                  //
//***********************************************************************************************************//

void UUV_UI::requestTransmit()//串口发送程序
{
    if (transmitWorker->isRunning()) {
        if(WorkMode!=0x05)
        {
            ManualControlValue();
            semiAutoControlValueComput();
            updateTransValues(); // 更新发送参数
            transmitWorker->sendSerialData(); // 子线程发送数据
            ShowMovement();
        }
        else{//自主发送模式（发送 pos）
            if (ctransWidget) {// 请求CSV数据（如果发送窗口存在）
                emit requestCsvData(m_csvCurrentIndex);
            }
            // 只有在拿到有效数据后才发送
            if (csvDataflag) {
                updateTransValues();
                transmitWorker->sendSerialData();
            } else {
                ui->lineEdit_Warning->setText("未打开文件");
            }
        }
    }
    // // ============== 日志记录：记录发送行 ===============
    // if (m_recorder.isRecording()) {
    //     UUVLogRecorder::TransmitFields tf;
    //     tf.workMode = WorkMode;
    //     tf.taw_x = taw_x; tf.taw_y = taw_y; tf.taw_z = taw_z;
    //     tf.taw_phi = taw_phi; tf.taw_theta = taw_theta; tf.taw_psi = taw_psi;
    //     tf.depth_d = Depth_d;
    //     tf.yaw_d   = Yaw_d;

    //     if (WorkMode == 0x05) {            // 仅自主模式真正发送 pos
    //         tf.posValid = true;
    //         for (int i=0;i<6;++i) tf.pos[i] = pos[i];
    //     } else {
    //         tf.posValid = false;           // 非自主模式：不记录 pos 数值（输出为空列）
    //     }
    //     m_recorder.appendTransmit(tf);
    //     if (ui->lineEdit_RecordCount_line)
    //         ui->lineEdit_RecordCount_line->setText(QString::number(m_recorder.recordCount()));
    // }
}

void UUV_UI::updateTransValues()//向子线程发送数据，更新控制参数
{
    if(WorkMode!=0x05){//非全自主模式
        transmitWorker->updateTransValues(WorkMode, taw_x, taw_y, taw_z, taw_phi, taw_theta, taw_psi, Depth_d, Yaw_d);
    }else{//全自主模式
        transmitWorker->updateTransValues2(WorkMode,pos[0],pos[1],pos[2],pos[3],pos[4],pos[5]);
    }
}

void UUV_UI::ShowMovement()//显示当前动作
{
    QString Movement_x,Movement_y,Movement_z,Movement_phi,Movement_theta,Movement_psi;
    if(taw_x>0){Movement_x = "前进";}
    if(taw_x<0){Movement_x = "后退";}
    if(taw_x==0){Movement_x = "";}

    if(taw_y>0){Movement_y = "右平移";}
    if(taw_y<0){Movement_y = "左平移";}
    if(taw_y==0){Movement_y = "";}

    if(taw_z>0){Movement_z = "下潜";}
    if(taw_z<0){Movement_z = "上浮";}
    if(taw_z==0){Movement_z = "";}

    if(taw_phi>0){Movement_phi = "";}
    if(taw_phi<0){Movement_phi = "";}
    if(taw_phi==0){Movement_phi = "";}

    if(taw_theta>0){Movement_theta = "后倾";}
    if(taw_theta<0){Movement_theta = "前倾";}
    if(taw_theta==0){Movement_theta = "";}

    if(taw_psi>0){Movement_psi = "右转";}
    if(taw_psi<0){Movement_psi = "左转";}
    if(taw_psi==0){Movement_psi = "";}

    if(!(Movement_x+Movement_y+Movement_z+Movement_phi+Movement_theta+Movement_psi=="")){
        ui->lineEdit_Movement->setText(Movement_x+Movement_y+Movement_z+Movement_phi+Movement_theta+Movement_psi);
    }
    else{
        ui->lineEdit_Movement->setText("无动作");
    }

    //输出控制量
    ui->lineEdit_tawx->setText(QString::number(static_cast<int>(taw_x)));//先转成int，再转Qstring
    ui->lineEdit_tawy->setText(QString::number(static_cast<int>(taw_y)));
    ui->lineEdit_tawz->setText(QString::number(static_cast<int>(taw_z)));
    ui->lineEdit_tawphi->setText(QString::number(static_cast<int>(taw_phi)));
    ui->lineEdit_tawtheta->setText(QString::number(static_cast<int>(taw_theta)));
    ui->lineEdit_tawpsi->setText(QString::number(static_cast<int>(taw_psi)));
}


void  UUV_UI::ManualControlValue()//计算控制量
{
    if(ui->comboBox_WorkMode->currentIndex()==0
        ||ui->comboBox_WorkMode->currentIndex()==1
        ||ui->comboBox_WorkMode->currentIndex()==2
        ||ui->comboBox_WorkMode->currentIndex()==3)
    {
        if(ui->checkBox_GamePad->isChecked()==false)//没有使用手柄的情况
        {//计算控制量，参数可以根据表现修改，int8_t需要保持在-128-127
            int calculate_x= WPressed-SPressed;taw_x = cv*calculate_x;
            int calculate_y= DPressed-APressed;taw_y = cv*calculate_y;
            int calculate_z= ZPressed-CPressed;taw_z = cv*calculate_z;
            int calculate_phi= 0;taw_phi = cv*calculate_phi;
            int calculate_theta= FPressed-RPressed;taw_theta = cv*calculate_theta;
            int calculate_psi= EPressed-QPressed;taw_psi = cv*calculate_psi;
        }
    }
}


void UUV_UI::semiAutoControlValueComput()//计算半自主控制的期望深度和艏向
{
    switch(ui->comboBox_WorkMode->currentIndex())
    {
    case 0:break;
    case 1:
        if(taw_z>0){
            ui->doubleSpinBox_Depth->setValue(ui->doubleSpinBox_Depth->value()+0.1);
        }
        if(taw_z<0){
            ui->doubleSpinBox_Depth->setValue(ui->doubleSpinBox_Depth->value()-0.1);
        }
        break;
    case 2:
        if(taw_psi>0){
            ui->doubleSpinBox_Heading->setValue(ui->doubleSpinBox_Heading->value()+1);
        }
        if(taw_psi<0){
            ui->doubleSpinBox_Heading->setValue(ui->doubleSpinBox_Heading->value()-1);
        }
        break;
    case 3:
        if(taw_z>0){
            ui->doubleSpinBox_Depth->setValue(ui->doubleSpinBox_Depth->value()+0.05);
        }
        if(taw_z<0){
            ui->doubleSpinBox_Depth->setValue(ui->doubleSpinBox_Depth->value()-0.05);
        }
        if(taw_psi>0){
            ui->doubleSpinBox_Heading->setValue(ui->doubleSpinBox_Heading->value()+1);
        }
        if(taw_psi<0){
            ui->doubleSpinBox_Heading->setValue(ui->doubleSpinBox_Heading->value()-1);
        }
        break;
    default:break;
    }
}


// void UUV_UI::onSerialDataReceived(float x, float y, float z, float roll, float pitch, float yaw)//显示机器人状态
// {
//     // 更新 UI
//     ui->lineEdit_X->setText(QString::number(x, 'f', 2));
//     ui->lineEdit_Y->setText(QString::number(y, 'f', 2));
//     ui->lineEdit_Z->setText(QString::number(z, 'f', 2));
//     ui->lineEdit_Roll->setText(QString::number(roll, 'f', 2));
//     ui->lineEdit_Pitch->setText(QString::number(pitch, 'f', 2));
//     ui->lineEdit_Yaw->setText(QString::number(yaw, 'f', 2));

//     //==== 日志记录：记录接收行 ====
//     if (m_recorder.isRecording()) {
//         UUVLogRecorder::ReceiveFields rf;
//         rf.eta[0]=x; rf.eta[1]=y; rf.eta[2]=z;
//         rf.eta[3]=roll; rf.eta[4]=pitch; rf.eta[5]=yaw;
//         m_recorder.appendReceive(rf);
//         if (ui->lineEdit_RecordCount_line) ui->lineEdit_RecordCount_line->setText(QString::number(m_recorder.recordCount()));
//     }
// }

// 处理串口错误
// void UUV_UI::onSerialErrorOccurred(const QString &errorMessage)
// {
//     ui->lineEdit_Warning->setText(errorMessage);
// }


void UUV_UI::onUUVFrameReceived(const UUVRxFrame &f)
{
    auto setFloat = [&](const char* name, float v, int prec = 2) {
        if (auto w = this->findChild<QLineEdit*>(name)) {
            w->setText(QString::number(v, 'f', prec));
        }
    };
    auto setInt = [&](const char* name, int v) {
        if (auto w = this->findChild<QLineEdit*>(name)) {
            w->setText(QString::number(v));
        }
    };

    // 模式
    setInt("lineEdit_workmode_feedback", f.mode);

    // 安全状态与来源
    setInt("lineEdit_voltage",    f.voltage);
    setInt("lineEdit_current",    f.current);
    setInt("lineEdit_temperature",  f.cabinTemp);
    setInt("lineEdit_DropSignal", f.dropSignal);
    setInt("lineEdit_NAV",  f.posSource);

    // 位姿
    setFloat("lineEdit_X",     f.x);
    setFloat("lineEdit_Y",     f.y);
    setFloat("lineEdit_Z",     f.z);
    setFloat("lineEdit_Roll",  f.phi);
    setFloat("lineEdit_Pitch", f.theta);
    setFloat("lineEdit_Yaw",   f.psi);

    // 速度
    setFloat("lineEdit_velocity_u", f.u);
    setFloat("lineEdit_velocity_v", f.v);
    setFloat("lineEdit_velocity_w", f.w);
    setFloat("lineEdit_velocity_p", f.p);
    setFloat("lineEdit_velocity_q", f.q);
    setFloat("lineEdit_velocity_r", f.r);

    // 推进器推力
    setFloat("lineEdit_T1", f.T[0]);
    setFloat("lineEdit_T2", f.T[1]);
    setFloat("lineEdit_T3", f.T[2]);
    setFloat("lineEdit_T4", f.T[3]);
    setFloat("lineEdit_T5", f.T[4]);
    setFloat("lineEdit_T6", f.T[5]);

    // 若需要记录到日志：可在此处调用你的记录器追加一条记录（建议扩展记录结构体，使其包含新字段）
}



//预览框
void UUV_UI::updateTransmitPreview(const QString &transmitView)
{
    ui->textBrowser_TPreview->append(transmitView);            // 将新内容追加到发送预览框
    ui->textBrowser_TPreview->moveCursor(QTextCursor::End);    // 光标移动到文本框末尾

    //回调中记录日志，真实预览出现后才记录（保证确实构造并准备发送过）
    logTransmitFrame();
}

void UUV_UI::updateReceivePreview(const QString &receiveView)
{
    ui->textBrowser_RPreview->append(receiveView);             // 将新内容追加到接收预览框
    ui->textBrowser_RPreview->moveCursor(QTextCursor::End);    // 光标移动到文本框末尾
}



//***********************************************************************************************************//
//                                                  全自主模式                                                 //
//***********************************************************************************************************//

void UUV_UI::on_pushButton_AutoTrans_clicked()//打开文件按钮
{
    // 若串口未打开，给出提示并返回
    if (!sharedSerial || !sharedSerial->isOpen()) {
        ui->lineEdit_Warning->setText("未打开串口");
        return;
    }
        // 如果弹窗还存在，就让它激活并返回，不再新建
        if (ctransWidget && ctransWidget->isVisible()) {
            ctransWidget->activateWindow();
            ctransWidget->raise(); // 让弹窗置顶
            return;
        }
        //把工作模式设置成0x05
        if(!(ui->comboBox_WorkMode->currentIndex()==4)){
            ui->comboBox_WorkMode->setCurrentIndex(4);
        }
        ctransWidget = new CTrans(this);//如果成员变量是nullptr或者窗口已被关闭，就会用new新建一个并记录到全局的成员变量里。
        ctransWidget->setAttribute(Qt::WA_DeleteOnClose); // 关闭时自动释放内存
        ctransWidget->show(); // 非模态显示
        connect(ctransWidget, &CTrans::destroyed, this, &UUV_UI::onTransWidgetDestroyed);

        // 连接信号槽：
        // 1. 主窗口请求数据 → 连续窗口处理 ()
        connect(this, &UUV_UI::requestCsvData, ctransWidget, &CTrans::requestData);//UUV_UI::requestCsvData在UUV_UI::requestTransmit()中运行

        // 2. 发送窗口更新位置 → 主窗口处理
        connect(ctransWidget, &CTrans::updatePositions, this, &UUV_UI::handleCsvData);

        // 显示窗口并连接销毁信号
        ctransWidget->show();
        connect(ctransWidget, &CTrans::destroyed, this, &UUV_UI::onTransWidgetDestroyed);

    //QPoint currentPos = this->pos();      // 获取当前窗口位置
    // this->move(screen_centerX - 350, screen_centerY); // 主窗口向左平移350像素
    // ctransWidget->move(screen_centerX + 850, screen_centerY);// 弹窗向右平移850像素

        // 强制重置
        m_csvCurrentIndex = 0;
        csvDataflag = false;//未获取到有效数据
}


void UUV_UI::onTransWidgetDestroyed() {//令负责连续发送的窗口类ctrans的指针指空
    ctransWidget = nullptr;
    ui->comboBox_WorkMode->setCurrentIndex(0);
    csvDataflag = false;  // 退出全自主或关闭窗口后复位
    m_csvCurrentIndex = 0;
}

void UUV_UI::handleCsvData(int Index, float p1, float p2, float p3, float p4, float p5, float p6)
{
    m_csvCurrentIndex = Index;
    pos[0] = p1;
    pos[1] = p2;
    pos[2] = p3;
    pos[3] = p4;
    pos[4] = p5;
    pos[5] = p6;
    csvDataflag = true;   // 标记已获取到有效数据
    m_csvCurrentIndex++;          // 仅在实际收到数据时推进到下一行
}



//***********************************************************************************************************//
//                                                  日志记录                                                  //
//***********************************************************************************************************//

// 勾选“开始记录”复选框后：开始新一轮记录并禁用复选框（直到保存或清除）
void UUV_UI::on_checkBox_Record_stateChanged(int state)
{
    if (state == Qt::Checked) {
        m_recorder.start();
        if (ui->lineEdit_RecordCount_line) ui->lineEdit_RecordCount_line->setText("0");
        if (ui->lineEdit_RecordCount_time) ui->lineEdit_RecordCount_time->setText("00:00:00");
        ui->checkBox_Record->setEnabled(false); // 禁用，避免中途取消
        m_recordUiTimer->start();
        ui->lineEdit_Warning->setText("开始记录");
    }
}

// 每秒刷新记录时长与行数（提升用户感知）
void UUV_UI::refreshRecordUi()
{
    if (!m_recorder.isRecording()) return;
    if (ui->lineEdit_RecordCount_time)
        ui->lineEdit_RecordCount_time->setText(m_recorder.formattedDuration());
    if (ui->lineEdit_RecordCount_line)
        ui->lineEdit_RecordCount_line->setText(QString::number(m_recorder.recordCount()));
}

// 保存按钮：推断文件类型并写出，成功后恢复 UI 状态
void UUV_UI::on_pushButton_RClear_2_clicked()
{
    if (!m_recorder.isRecording() && m_recorder.recordCount()==0) {
        ui->lineEdit_Warning->setText("无可保存记录");
        return;
    }
    QString defName = "uuv_log_" + QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss") + ".csv";
    QString filePath = QFileDialog::getSaveFileName(this,"保存航行日志",defName,
                                                    "CSV 文件 (*.csv);;文本文件 (*.txt)");
    if (filePath.isEmpty()) return;

    QString err;
    if (!m_recorder.saveToFile(filePath, &err)) {
        ui->lineEdit_Warning->setText("保存失败: " + err);
        return;
    }
    ui->lineEdit_Warning->setText("保存成功");
    m_recorder.stopAndClear();
    m_recordUiTimer->stop();
    ui->checkBox_Record->setEnabled(true);
    ui->checkBox_Record->setChecked(false);
    if (ui->lineEdit_RecordCount_line) ui->lineEdit_RecordCount_line->setText("0");
    if (ui->lineEdit_RecordCount_time) ui->lineEdit_RecordCount_time->setText("00:00:00");
}

// 清除按钮：不保存直接丢弃，恢复 UI
void UUV_UI::on_pushButton_RClear_3_clicked()
{
    if (!m_recorder.isRecording() && m_recorder.recordCount()==0) {
        ui->lineEdit_Warning->setText("无记录");
        return;
    }
    auto ret = QMessageBox::question(this,"清除日志","确认不保存直接清除？",
                                     QMessageBox::Yes | QMessageBox::No, QMessageBox::No);
    if (ret == QMessageBox::Yes) {
        m_recorder.stopAndClear();
        m_recordUiTimer->stop();
        ui->checkBox_Record->setEnabled(true);
        ui->checkBox_Record->setChecked(false);
        if (ui->lineEdit_RecordCount_line) ui->lineEdit_RecordCount_line->setText("0");
        if (ui->lineEdit_RecordCount_time) ui->lineEdit_RecordCount_time->setText("00:00:00");
        ui->lineEdit_Warning->setText("已清除记录");
    }
}

// 关闭窗口：若正在记录，询问是否保存
void UUV_UI::closeEvent(QCloseEvent *event)
{
    if (m_recorder.isRecording() && m_recorder.recordCount() > 0) {
        auto ret = QMessageBox::question(this,"保存航行日志","当前仍在记录，是否保存？",
                                         QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel,
                                         QMessageBox::Save);
        if (ret == QMessageBox::Save) {
            QString defName = "uuv_log_" + QDateTime::currentDateTime().toString("yyyyMMdd_HHmmss") + ".csv";
            QString filePath = QFileDialog::getSaveFileName(this,"保存航行日志",defName,
                                                            "CSV 文件 (*.csv);;文本文件 (*.txt)");
            if (filePath.isEmpty()) {
                event->ignore();
                return;
            }
            QString err;
            if (!m_recorder.saveToFile(filePath, &err)) {
                QMessageBox::warning(this,"保存失败",err);
                event->ignore();
                return;
            }
            // 保存成功 -> 清理
            m_recorder.stopAndClear();
        } else if (ret == QMessageBox::Cancel) {
            event->ignore();
            return;
        } else { // Discard
            // 丢弃数据正常退出
            m_recorder.stopAndClear();
        }
    }
    QMainWindow::closeEvent(event);
}

// ADDED: 只在发送线程已生成预览（真实帧）后记录，防止“假发送”被写入日志
void UUV_UI::logTransmitFrame()
{
    // 未在录制 → 不记录
    if (!m_recorder.isRecording()) return;

    // WorkMode 可能还在 1~4：记录但 pos 为空
    // WorkMode == 5：只有当我们“确实发送了自主帧”才记录
    // 现在以“预览文本中是否包含工作模式字节”作为已发送依据，可进一步更精确
    // 下面示例假设帧格式中一定能找到模式字节（可按你实际帧格式调整解析）

    // 简易判断：如果串口未打开直接返回（防止某些初始化虚假预览；视实际情况保留/删除）
    if (!sharedSerial || !sharedSerial->isOpen()) return;

    UUVLogRecorder::TransmitFields tf;
    tf.workMode = WorkMode;
    tf.taw_x = taw_x; tf.taw_y = taw_y; tf.taw_z = taw_z;
    tf.taw_phi = taw_phi; tf.taw_theta = taw_theta; tf.taw_psi = taw_psi;
    tf.depth_d = Depth_d;
    tf.yaw_d   = Yaw_d;

    if (WorkMode == 0x05) {
        // 只有当 csvDataflag == true 时才说明当前 pos[] 已被最新点更新并参与本次发送
        // 否则不记录这条（直接 return），避免“打开窗口但未开始”导致的空转
        if (!csvDataflag) {
            return; // 直接抑制记录
        }
        tf.posValid = true;
        for (int i=0;i<6;++i) tf.pos[i] = pos[i];
    } else {
        tf.posValid = false; // 非自主模式，pos 列为空
    }

    m_recorder.appendTransmit(tf);

    if (ui->lineEdit_RecordCount_line) {
        ui->lineEdit_RecordCount_line->setText(QString::number(m_recorder.recordCount()));
    }
}


