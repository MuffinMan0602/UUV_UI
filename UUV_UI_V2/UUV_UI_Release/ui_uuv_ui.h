/********************************************************************************
** Form generated from reading UI file 'uuv_ui.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UUV_UI_H
#define UI_UUV_UI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UUV_UI
{
public:
    QWidget *centralwidget;
    QLineEdit *lineEdit_DateTime;
    QGroupBox *groupBox;
    QTabWidget *tabWidget_connect;
    QWidget *tab_serial;
    QWidget *gridLayoutWidget_5;
    QGridLayout *gridLayout_4;
    QLabel *label_BaudRate;
    QComboBox *comboBox_BaudRate;
    QLabel *label_name;
    QComboBox *comboBox_name;
    QLabel *label_transmistPeriod;
    QComboBox *comboBox_TransPeriod;
    QWidget *gridLayoutWidget_3;
    QGridLayout *gridLayout_3;
    QComboBox *comboBox_check;
    QLabel *label_check;
    QComboBox *comboBox_data;
    QLabel *label_data;
    QLabel *label_stop;
    QComboBox *comboBox_stop;
    QPushButton *pushButton_scan;
    QCheckBox *checkBox_SerialOpen;
    QPushButton *pushButton_open;
    QFrame *line_5;
    QFrame *line_6;
    QWidget *tab_net;
    QGroupBox *groupBox_WorkMode;
    QComboBox *comboBox_WorkMode;
    QLineEdit *lineEdit_Warning;
    QLabel *label_WorkMode;
    QGroupBox *groupBox_controlpad;
    QTabWidget *tabWidget;
    QWidget *tab_KeyControl;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_X;
    QPushButton *pushButton_E;
    QPushButton *pushButton_F;
    QPushButton *pushButton_C;
    QPushButton *pushButton_Q;
    QPushButton *pushButton_R;
    QPushButton *pushButton_W;
    QPushButton *pushButton_Z;
    QPushButton *pushButton_D;
    QPushButton *pushButton_V;
    QPushButton *pushButton_S;
    QPushButton *pushButton_A;
    QSlider *horizontalSlider_cv;
    QLabel *label_cv;
    QLineEdit *lineEdit_cv;
    QFrame *line_3;
    QWidget *tab_Gamepad;
    QPushButton *pushButton;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox_GamePad;
    QLineEdit *lineEdit_tawx;
    QLineEdit *lineEdit_tawy;
    QLineEdit *lineEdit_tawz;
    QLineEdit *lineEdit_tawphi;
    QLineEdit *lineEdit_tawtheta;
    QLineEdit *lineEdit_tawpsi;
    QLineEdit *lineEdit_Movement;
    QGroupBox *groupBox_2;
    QWidget *gridLayoutWidget_4;
    QGridLayout *gridLayout_2;
    QLabel *label_Depth;
    QDoubleSpinBox *doubleSpinBox_Heading;
    QDoubleSpinBox *doubleSpinBox_Depth;
    QLabel *label_Heading;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QSlider *horizontalSlider_Depth;
    QSlider *horizontalSlider_Heading;
    QPushButton *pushButton_OpenFile;
    QFrame *line_2;
    QComboBox *comboBox_TransMode;
    QLabel *label_cv_2;
    QGroupBox *groupBox_3;
    QTextBrowser *textBrowser_RPreview;
    QLabel *label_RPreview;
    QPushButton *pushButton_RClear;
    QTextBrowser *textBrowser_TPreview;
    QLabel *label_TPreview;
    QPushButton *pushButton_TClear;
    QGroupBox *groupBox_UUVstates;
    QWidget *formLayoutWidget_2;
    QFormLayout *formLayout_2;
    QLabel *label_pos;
    QLabel *label_pos_2;
    QLabel *label_depth;
    QLabel *label_roll;
    QLabel *label_pitch;
    QLabel *label_yaw;
    QLineEdit *lineEdit_X;
    QLineEdit *lineEdit_Y;
    QLineEdit *lineEdit_Z;
    QLineEdit *lineEdit_Roll;
    QLineEdit *lineEdit_Pitch;
    QLineEdit *lineEdit_Yaw;
    QFrame *line;
    QFrame *line_4;

    void setupUi(QMainWindow *UUV_UI)
    {
        if (UUV_UI->objectName().isEmpty())
            UUV_UI->setObjectName("UUV_UI");
        UUV_UI->resize(1200, 800);
        UUV_UI->setMinimumSize(QSize(1200, 800));
        UUV_UI->setMaximumSize(QSize(1200, 800));
        centralwidget = new QWidget(UUV_UI);
        centralwidget->setObjectName("centralwidget");
        lineEdit_DateTime = new QLineEdit(centralwidget);
        lineEdit_DateTime->setObjectName("lineEdit_DateTime");
        lineEdit_DateTime->setGeometry(QRect(10, 760, 491, 31));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\256\213\344\275\223")});
        font.setPointSize(11);
        lineEdit_DateTime->setFont(font);
        lineEdit_DateTime->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lineEdit_DateTime->setReadOnly(true);
        lineEdit_DateTime->setClearButtonEnabled(false);
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        groupBox->setGeometry(QRect(10, 70, 491, 151));
        groupBox->setAutoFillBackground(true);
        groupBox->setInputMethodHints(Qt::InputMethodHint::ImhNone);
        groupBox->setFlat(true);
        tabWidget_connect = new QTabWidget(groupBox);
        tabWidget_connect->setObjectName("tabWidget_connect");
        tabWidget_connect->setGeometry(QRect(10, 20, 471, 123));
        tabWidget_connect->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        tabWidget_connect->setStyleSheet(QString::fromUtf8(""));
        tabWidget_connect->setTabPosition(QTabWidget::TabPosition::East);
        tabWidget_connect->setIconSize(QSize(8, 16));
        tab_serial = new QWidget();
        tab_serial->setObjectName("tab_serial");
        gridLayoutWidget_5 = new QWidget(tab_serial);
        gridLayoutWidget_5->setObjectName("gridLayoutWidget_5");
        gridLayoutWidget_5->setGeometry(QRect(0, 0, 191, 91));
        gridLayout_4 = new QGridLayout(gridLayoutWidget_5);
        gridLayout_4->setSpacing(0);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        label_BaudRate = new QLabel(gridLayoutWidget_5);
        label_BaudRate->setObjectName("label_BaudRate");
        label_BaudRate->setMinimumSize(QSize(90, 20));
        label_BaudRate->setMaximumSize(QSize(90, 20));
        QFont font1;
        font1.setPointSize(12);
        label_BaudRate->setFont(font1);

        gridLayout_4->addWidget(label_BaudRate, 1, 0, 1, 1);

        comboBox_BaudRate = new QComboBox(gridLayoutWidget_5);
        comboBox_BaudRate->addItem(QString());
        comboBox_BaudRate->addItem(QString());
        comboBox_BaudRate->addItem(QString());
        comboBox_BaudRate->addItem(QString());
        comboBox_BaudRate->addItem(QString());
        comboBox_BaudRate->addItem(QString());
        comboBox_BaudRate->addItem(QString());
        comboBox_BaudRate->addItem(QString());
        comboBox_BaudRate->setObjectName("comboBox_BaudRate");
        comboBox_BaudRate->setMinimumSize(QSize(90, 20));
        comboBox_BaudRate->setMaximumSize(QSize(90, 20));

        gridLayout_4->addWidget(comboBox_BaudRate, 1, 1, 1, 1);

        label_name = new QLabel(gridLayoutWidget_5);
        label_name->setObjectName("label_name");
        label_name->setMinimumSize(QSize(90, 20));
        label_name->setMaximumSize(QSize(90, 20));
        label_name->setFont(font1);
        label_name->setAlignment(Qt::AlignmentFlag::AlignLeading|Qt::AlignmentFlag::AlignLeft|Qt::AlignmentFlag::AlignVCenter);

        gridLayout_4->addWidget(label_name, 0, 0, 1, 1);

        comboBox_name = new QComboBox(gridLayoutWidget_5);
        comboBox_name->setObjectName("comboBox_name");
        comboBox_name->setMinimumSize(QSize(90, 20));
        comboBox_name->setMaximumSize(QSize(90, 20));

        gridLayout_4->addWidget(comboBox_name, 0, 1, 1, 1);

        label_transmistPeriod = new QLabel(gridLayoutWidget_5);
        label_transmistPeriod->setObjectName("label_transmistPeriod");
        label_transmistPeriod->setMinimumSize(QSize(90, 20));
        label_transmistPeriod->setMaximumSize(QSize(90, 20));
        QFont font2;
        font2.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font2.setPointSize(12);
        label_transmistPeriod->setFont(font2);

        gridLayout_4->addWidget(label_transmistPeriod, 2, 0, 1, 1);

        comboBox_TransPeriod = new QComboBox(gridLayoutWidget_5);
        comboBox_TransPeriod->addItem(QString());
        comboBox_TransPeriod->addItem(QString());
        comboBox_TransPeriod->addItem(QString());
        comboBox_TransPeriod->setObjectName("comboBox_TransPeriod");
        comboBox_TransPeriod->setMinimumSize(QSize(90, 20));
        comboBox_TransPeriod->setMaximumSize(QSize(90, 20));

        gridLayout_4->addWidget(comboBox_TransPeriod, 2, 1, 1, 1);

        gridLayoutWidget_3 = new QWidget(tab_serial);
        gridLayoutWidget_3->setObjectName("gridLayoutWidget_3");
        gridLayoutWidget_3->setGeometry(QRect(200, 0, 201, 91));
        gridLayout_3 = new QGridLayout(gridLayoutWidget_3);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_3->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        gridLayout_3->setContentsMargins(0, 0, 0, 0);
        comboBox_check = new QComboBox(gridLayoutWidget_3);
        comboBox_check->addItem(QString());
        comboBox_check->addItem(QString());
        comboBox_check->addItem(QString());
        comboBox_check->setObjectName("comboBox_check");
        comboBox_check->setMaximumSize(QSize(90, 20));

        gridLayout_3->addWidget(comboBox_check, 1, 1, 1, 1);

        label_check = new QLabel(gridLayoutWidget_3);
        label_check->setObjectName("label_check");
        label_check->setMinimumSize(QSize(70, 20));
        label_check->setMaximumSize(QSize(70, 20));
        label_check->setFont(font1);

        gridLayout_3->addWidget(label_check, 0, 0, 1, 1);

        comboBox_data = new QComboBox(gridLayoutWidget_3);
        comboBox_data->addItem(QString());
        comboBox_data->addItem(QString());
        comboBox_data->addItem(QString());
        comboBox_data->addItem(QString());
        comboBox_data->setObjectName("comboBox_data");
        comboBox_data->setMaximumSize(QSize(90, 20));

        gridLayout_3->addWidget(comboBox_data, 2, 1, 1, 1);

        label_data = new QLabel(gridLayoutWidget_3);
        label_data->setObjectName("label_data");
        label_data->setMinimumSize(QSize(70, 20));
        label_data->setMaximumSize(QSize(70, 20));
        label_data->setFont(font1);

        gridLayout_3->addWidget(label_data, 1, 0, 1, 1);

        label_stop = new QLabel(gridLayoutWidget_3);
        label_stop->setObjectName("label_stop");
        label_stop->setMinimumSize(QSize(70, 20));
        label_stop->setMaximumSize(QSize(70, 20));
        label_stop->setFont(font1);

        gridLayout_3->addWidget(label_stop, 2, 0, 1, 1);

        comboBox_stop = new QComboBox(gridLayoutWidget_3);
        comboBox_stop->addItem(QString());
        comboBox_stop->addItem(QString());
        comboBox_stop->addItem(QString());
        comboBox_stop->setObjectName("comboBox_stop");
        comboBox_stop->setMinimumSize(QSize(90, 20));
        comboBox_stop->setMaximumSize(QSize(90, 20));

        gridLayout_3->addWidget(comboBox_stop, 0, 1, 1, 1);

        pushButton_scan = new QPushButton(tab_serial);
        pushButton_scan->setObjectName("pushButton_scan");
        pushButton_scan->setGeometry(QRect(95, 90, 90, 25));
        pushButton_scan->setMinimumSize(QSize(90, 25));
        pushButton_scan->setMaximumSize(QSize(90, 25));
        pushButton_scan->setFont(font1);
        checkBox_SerialOpen = new QCheckBox(tab_serial);
        checkBox_SerialOpen->setObjectName("checkBox_SerialOpen");
        checkBox_SerialOpen->setEnabled(false);
        checkBox_SerialOpen->setGeometry(QRect(210, 93, 20, 20));
        checkBox_SerialOpen->setMaximumSize(QSize(20, 20));
        checkBox_SerialOpen->setStyleSheet(QString::fromUtf8("selection-color: rgb(255, 0, 0);"));
        checkBox_SerialOpen->setIconSize(QSize(20, 20));
        checkBox_SerialOpen->setCheckable(true);
        pushButton_open = new QPushButton(tab_serial);
        pushButton_open->setObjectName("pushButton_open");
        pushButton_open->setGeometry(QRect(230, 90, 90, 25));
        pushButton_open->setMinimumSize(QSize(90, 25));
        pushButton_open->setMaximumSize(QSize(90, 25));
        pushButton_open->setFont(font1);
        line_5 = new QFrame(tab_serial);
        line_5->setObjectName("line_5");
        line_5->setGeometry(QRect(0, 80, 451, 16));
        line_5->setFrameShape(QFrame::Shape::HLine);
        line_5->setFrameShadow(QFrame::Shadow::Sunken);
        line_6 = new QFrame(tab_serial);
        line_6->setObjectName("line_6");
        line_6->setGeometry(QRect(190, 0, 16, 85));
        line_6->setFrameShape(QFrame::Shape::VLine);
        line_6->setFrameShadow(QFrame::Shadow::Sunken);
        tabWidget_connect->addTab(tab_serial, QString());
        tab_net = new QWidget();
        tab_net->setObjectName("tab_net");
        tabWidget_connect->addTab(tab_net, QString());
        groupBox_WorkMode = new QGroupBox(centralwidget);
        groupBox_WorkMode->setObjectName("groupBox_WorkMode");
        groupBox_WorkMode->setGeometry(QRect(10, 10, 491, 51));
        groupBox_WorkMode->setFlat(true);
        groupBox_WorkMode->setCheckable(false);
        comboBox_WorkMode = new QComboBox(groupBox_WorkMode);
        comboBox_WorkMode->addItem(QString());
        comboBox_WorkMode->addItem(QString());
        comboBox_WorkMode->addItem(QString());
        comboBox_WorkMode->addItem(QString());
        comboBox_WorkMode->addItem(QString());
        comboBox_WorkMode->setObjectName("comboBox_WorkMode");
        comboBox_WorkMode->setGeometry(QRect(100, 20, 175, 25));
        QFont font3;
        font3.setPointSize(10);
        comboBox_WorkMode->setFont(font3);
        lineEdit_Warning = new QLineEdit(groupBox_WorkMode);
        lineEdit_Warning->setObjectName("lineEdit_Warning");
        lineEdit_Warning->setGeometry(QRect(280, 20, 201, 25));
        lineEdit_Warning->setFont(font);
        lineEdit_Warning->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));
        lineEdit_Warning->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lineEdit_Warning->setReadOnly(true);
        label_WorkMode = new QLabel(groupBox_WorkMode);
        label_WorkMode->setObjectName("label_WorkMode");
        label_WorkMode->setGeometry(QRect(10, 20, 91, 21));
        label_WorkMode->setFont(font2);
        groupBox_controlpad = new QGroupBox(centralwidget);
        groupBox_controlpad->setObjectName("groupBox_controlpad");
        groupBox_controlpad->setGeometry(QRect(10, 230, 491, 331));
        groupBox_controlpad->setFlat(true);
        tabWidget = new QTabWidget(groupBox_controlpad);
        tabWidget->setObjectName("tabWidget");
        tabWidget->setGeometry(QRect(5, 20, 481, 266));
        QFont font4;
        font4.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font4.setPointSize(10);
        tabWidget->setFont(font4);
        tabWidget->setStyleSheet(QString::fromUtf8(""));
        tabWidget->setTabPosition(QTabWidget::TabPosition::East);
        tabWidget->setTabShape(QTabWidget::TabShape::Rounded);
        tabWidget->setElideMode(Qt::TextElideMode::ElideRight);
        tabWidget->setUsesScrollButtons(true);
        tabWidget->setDocumentMode(false);
        tabWidget->setTabsClosable(false);
        tab_KeyControl = new QWidget();
        tab_KeyControl->setObjectName("tab_KeyControl");
        gridLayoutWidget = new QWidget(tab_KeyControl);
        gridLayoutWidget->setObjectName("gridLayoutWidget");
        gridLayoutWidget->setGeometry(QRect(30, 0, 381, 221));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_X = new QPushButton(gridLayoutWidget);
        pushButton_X->setObjectName("pushButton_X");
        pushButton_X->setMinimumSize(QSize(80, 70));
        pushButton_X->setMaximumSize(QSize(80, 70));
        QFont font5;
        font5.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font5.setPointSize(11);
        font5.setBold(false);
        pushButton_X->setFont(font5);

        gridLayout->addWidget(pushButton_X, 2, 1, 1, 1);

        pushButton_E = new QPushButton(gridLayoutWidget);
        pushButton_E->setObjectName("pushButton_E");
        pushButton_E->setMinimumSize(QSize(80, 70));
        pushButton_E->setMaximumSize(QSize(80, 70));
        pushButton_E->setFont(font5);

        gridLayout->addWidget(pushButton_E, 0, 2, 1, 1);

        pushButton_F = new QPushButton(gridLayoutWidget);
        pushButton_F->setObjectName("pushButton_F");
        pushButton_F->setMinimumSize(QSize(80, 70));
        pushButton_F->setMaximumSize(QSize(80, 70));
        pushButton_F->setFont(font5);

        gridLayout->addWidget(pushButton_F, 1, 3, 1, 1);

        pushButton_C = new QPushButton(gridLayoutWidget);
        pushButton_C->setObjectName("pushButton_C");
        pushButton_C->setMinimumSize(QSize(80, 70));
        pushButton_C->setMaximumSize(QSize(80, 70));
        pushButton_C->setFont(font5);

        gridLayout->addWidget(pushButton_C, 2, 2, 1, 1);

        pushButton_Q = new QPushButton(gridLayoutWidget);
        pushButton_Q->setObjectName("pushButton_Q");
        pushButton_Q->setMinimumSize(QSize(80, 70));
        pushButton_Q->setMaximumSize(QSize(80, 70));
        pushButton_Q->setFont(font5);

        gridLayout->addWidget(pushButton_Q, 0, 0, 1, 1);

        pushButton_R = new QPushButton(gridLayoutWidget);
        pushButton_R->setObjectName("pushButton_R");
        pushButton_R->setMinimumSize(QSize(80, 70));
        pushButton_R->setMaximumSize(QSize(80, 70));
        pushButton_R->setFont(font5);

        gridLayout->addWidget(pushButton_R, 0, 3, 1, 1);

        pushButton_W = new QPushButton(gridLayoutWidget);
        pushButton_W->setObjectName("pushButton_W");
        pushButton_W->setMinimumSize(QSize(80, 70));
        pushButton_W->setMaximumSize(QSize(80, 70));
        pushButton_W->setFont(font5);

        gridLayout->addWidget(pushButton_W, 0, 1, 1, 1);

        pushButton_Z = new QPushButton(gridLayoutWidget);
        pushButton_Z->setObjectName("pushButton_Z");
        pushButton_Z->setMinimumSize(QSize(80, 70));
        pushButton_Z->setMaximumSize(QSize(80, 70));
        pushButton_Z->setFont(font5);

        gridLayout->addWidget(pushButton_Z, 2, 0, 1, 1);

        pushButton_D = new QPushButton(gridLayoutWidget);
        pushButton_D->setObjectName("pushButton_D");
        pushButton_D->setMinimumSize(QSize(80, 70));
        pushButton_D->setMaximumSize(QSize(80, 70));
        pushButton_D->setFont(font5);

        gridLayout->addWidget(pushButton_D, 1, 2, 1, 1);

        pushButton_V = new QPushButton(gridLayoutWidget);
        pushButton_V->setObjectName("pushButton_V");
        pushButton_V->setMinimumSize(QSize(80, 70));
        pushButton_V->setMaximumSize(QSize(80, 70));
        pushButton_V->setFont(font5);

        gridLayout->addWidget(pushButton_V, 2, 3, 1, 1);

        pushButton_S = new QPushButton(gridLayoutWidget);
        pushButton_S->setObjectName("pushButton_S");
        pushButton_S->setMinimumSize(QSize(80, 70));
        pushButton_S->setMaximumSize(QSize(80, 70));
        pushButton_S->setFont(font5);

        gridLayout->addWidget(pushButton_S, 1, 1, 1, 1);

        pushButton_A = new QPushButton(gridLayoutWidget);
        pushButton_A->setObjectName("pushButton_A");
        pushButton_A->setMinimumSize(QSize(80, 70));
        pushButton_A->setMaximumSize(QSize(80, 70));
        pushButton_A->setFont(font5);

        gridLayout->addWidget(pushButton_A, 1, 0, 1, 1);

        horizontalSlider_cv = new QSlider(tab_KeyControl);
        horizontalSlider_cv->setObjectName("horizontalSlider_cv");
        horizontalSlider_cv->setGeometry(QRect(160, 235, 281, 21));
        horizontalSlider_cv->setMaximum(127);
        horizontalSlider_cv->setPageStep(10);
        horizontalSlider_cv->setValue(80);
        horizontalSlider_cv->setOrientation(Qt::Orientation::Horizontal);
        label_cv = new QLabel(tab_KeyControl);
        label_cv->setObjectName("label_cv");
        label_cv->setGeometry(QRect(10, 230, 41, 31));
        label_cv->setFont(font2);
        lineEdit_cv = new QLineEdit(tab_KeyControl);
        lineEdit_cv->setObjectName("lineEdit_cv");
        lineEdit_cv->setEnabled(true);
        lineEdit_cv->setGeometry(QRect(60, 235, 81, 25));
        lineEdit_cv->setReadOnly(true);
        line_3 = new QFrame(tab_KeyControl);
        line_3->setObjectName("line_3");
        line_3->setGeometry(QRect(0, 220, 451, 16));
        line_3->setFrameShape(QFrame::Shape::HLine);
        line_3->setFrameShadow(QFrame::Shadow::Sunken);
        tabWidget->addTab(tab_KeyControl, QString());
        tab_Gamepad = new QWidget();
        tab_Gamepad->setObjectName("tab_Gamepad");
        pushButton = new QPushButton(tab_Gamepad);
        pushButton->setObjectName("pushButton");
        pushButton->setEnabled(false);
        pushButton->setGeometry(QRect(-10, 0, 471, 271));
        pushButton->setStyleSheet(QString::fromUtf8("image: url(:/new/prefix1/UUV_gamepad.png);"));
        pushButton->setCheckable(false);
        tabWidget->addTab(tab_Gamepad, QString());
        horizontalLayoutWidget = new QWidget(groupBox_controlpad);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(0, 290, 491, 41));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        checkBox_GamePad = new QCheckBox(horizontalLayoutWidget);
        checkBox_GamePad->setObjectName("checkBox_GamePad");
        checkBox_GamePad->setMinimumSize(QSize(100, 25));
        checkBox_GamePad->setMaximumSize(QSize(100, 25));
        checkBox_GamePad->setFont(font2);

        horizontalLayout->addWidget(checkBox_GamePad);

        lineEdit_tawx = new QLineEdit(horizontalLayoutWidget);
        lineEdit_tawx->setObjectName("lineEdit_tawx");
        lineEdit_tawx->setMinimumSize(QSize(40, 25));
        lineEdit_tawx->setMaximumSize(QSize(40, 25));
        lineEdit_tawx->setReadOnly(true);

        horizontalLayout->addWidget(lineEdit_tawx);

        lineEdit_tawy = new QLineEdit(horizontalLayoutWidget);
        lineEdit_tawy->setObjectName("lineEdit_tawy");
        lineEdit_tawy->setMinimumSize(QSize(40, 25));
        lineEdit_tawy->setMaximumSize(QSize(40, 25));
        lineEdit_tawy->setReadOnly(true);

        horizontalLayout->addWidget(lineEdit_tawy);

        lineEdit_tawz = new QLineEdit(horizontalLayoutWidget);
        lineEdit_tawz->setObjectName("lineEdit_tawz");
        lineEdit_tawz->setMinimumSize(QSize(40, 25));
        lineEdit_tawz->setMaximumSize(QSize(40, 25));
        lineEdit_tawz->setReadOnly(true);

        horizontalLayout->addWidget(lineEdit_tawz);

        lineEdit_tawphi = new QLineEdit(horizontalLayoutWidget);
        lineEdit_tawphi->setObjectName("lineEdit_tawphi");
        lineEdit_tawphi->setMinimumSize(QSize(40, 25));
        lineEdit_tawphi->setMaximumSize(QSize(40, 25));
        lineEdit_tawphi->setReadOnly(true);

        horizontalLayout->addWidget(lineEdit_tawphi);

        lineEdit_tawtheta = new QLineEdit(horizontalLayoutWidget);
        lineEdit_tawtheta->setObjectName("lineEdit_tawtheta");
        lineEdit_tawtheta->setMinimumSize(QSize(40, 25));
        lineEdit_tawtheta->setMaximumSize(QSize(40, 25));
        lineEdit_tawtheta->setReadOnly(true);

        horizontalLayout->addWidget(lineEdit_tawtheta);

        lineEdit_tawpsi = new QLineEdit(horizontalLayoutWidget);
        lineEdit_tawpsi->setObjectName("lineEdit_tawpsi");
        lineEdit_tawpsi->setMinimumSize(QSize(40, 25));
        lineEdit_tawpsi->setMaximumSize(QSize(40, 25));
        lineEdit_tawpsi->setReadOnly(true);

        horizontalLayout->addWidget(lineEdit_tawpsi);

        lineEdit_Movement = new QLineEdit(horizontalLayoutWidget);
        lineEdit_Movement->setObjectName("lineEdit_Movement");
        lineEdit_Movement->setMinimumSize(QSize(130, 25));
        lineEdit_Movement->setMaximumSize(QSize(135, 25));
        lineEdit_Movement->setFont(font);
        lineEdit_Movement->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lineEdit_Movement->setReadOnly(true);

        horizontalLayout->addWidget(lineEdit_Movement);

        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName("groupBox_2");
        groupBox_2->setGeometry(QRect(10, 570, 491, 181));
        groupBox_2->setFlat(true);
        gridLayoutWidget_4 = new QWidget(groupBox_2);
        gridLayoutWidget_4->setObjectName("gridLayoutWidget_4");
        gridLayoutWidget_4->setGeometry(QRect(10, 20, 128, 121));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_4);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_Depth = new QLabel(gridLayoutWidget_4);
        label_Depth->setObjectName("label_Depth");
        label_Depth->setMinimumSize(QSize(120, 24));
        label_Depth->setMaximumSize(QSize(120, 24));
        label_Depth->setFont(font2);

        gridLayout_2->addWidget(label_Depth, 1, 0, 1, 1);

        doubleSpinBox_Heading = new QDoubleSpinBox(gridLayoutWidget_4);
        doubleSpinBox_Heading->setObjectName("doubleSpinBox_Heading");
        doubleSpinBox_Heading->setMinimumSize(QSize(120, 24));
        doubleSpinBox_Heading->setMaximumSize(QSize(120, 24));
        doubleSpinBox_Heading->setDecimals(1);
        doubleSpinBox_Heading->setMinimum(-180.000000000000000);
        doubleSpinBox_Heading->setMaximum(179.900000000000006);
        doubleSpinBox_Heading->setSingleStep(0.100000000000000);

        gridLayout_2->addWidget(doubleSpinBox_Heading, 4, 0, 1, 1);

        doubleSpinBox_Depth = new QDoubleSpinBox(gridLayoutWidget_4);
        doubleSpinBox_Depth->setObjectName("doubleSpinBox_Depth");
        doubleSpinBox_Depth->setMinimumSize(QSize(120, 24));
        doubleSpinBox_Depth->setMaximumSize(QSize(120, 24));
        doubleSpinBox_Depth->setMaximum(10.000000000000000);
        doubleSpinBox_Depth->setSingleStep(0.010000000000000);

        gridLayout_2->addWidget(doubleSpinBox_Depth, 2, 0, 1, 1);

        label_Heading = new QLabel(gridLayoutWidget_4);
        label_Heading->setObjectName("label_Heading");
        label_Heading->setMinimumSize(QSize(120, 24));
        label_Heading->setMaximumSize(QSize(120, 24));
        label_Heading->setFont(font2);

        gridLayout_2->addWidget(label_Heading, 3, 0, 1, 1);

        doubleSpinBox_Depth->raise();
        doubleSpinBox_Heading->raise();
        label_Depth->raise();
        label_Heading->raise();
        verticalLayoutWidget_3 = new QWidget(groupBox_2);
        verticalLayoutWidget_3->setObjectName("verticalLayoutWidget_3");
        verticalLayoutWidget_3->setGeometry(QRect(140, 20, 341, 121));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSlider_Depth = new QSlider(verticalLayoutWidget_3);
        horizontalSlider_Depth->setObjectName("horizontalSlider_Depth");
        horizontalSlider_Depth->setMinimumSize(QSize(330, 40));
        horizontalSlider_Depth->setAutoFillBackground(true);
        horizontalSlider_Depth->setInputMethodHints(Qt::InputMethodHint::ImhNone);
        horizontalSlider_Depth->setMaximum(1000);
        horizontalSlider_Depth->setSingleStep(1);
        horizontalSlider_Depth->setPageStep(10);
        horizontalSlider_Depth->setValue(0);
        horizontalSlider_Depth->setSliderPosition(0);
        horizontalSlider_Depth->setOrientation(Qt::Orientation::Horizontal);
        horizontalSlider_Depth->setInvertedAppearance(false);
        horizontalSlider_Depth->setInvertedControls(false);
        horizontalSlider_Depth->setTickPosition(QSlider::TickPosition::TicksBothSides);
        horizontalSlider_Depth->setTickInterval(50);

        verticalLayout_3->addWidget(horizontalSlider_Depth);

        horizontalSlider_Heading = new QSlider(verticalLayoutWidget_3);
        horizontalSlider_Heading->setObjectName("horizontalSlider_Heading");
        horizontalSlider_Heading->setMinimumSize(QSize(330, 40));
        horizontalSlider_Heading->setMinimum(-1800);
        horizontalSlider_Heading->setMaximum(1799);
        horizontalSlider_Heading->setPageStep(10);
        horizontalSlider_Heading->setOrientation(Qt::Orientation::Horizontal);
        horizontalSlider_Heading->setTickPosition(QSlider::TickPosition::TicksBothSides);
        horizontalSlider_Heading->setTickInterval(100);

        verticalLayout_3->addWidget(horizontalSlider_Heading);

        pushButton_OpenFile = new QPushButton(groupBox_2);
        pushButton_OpenFile->setObjectName("pushButton_OpenFile");
        pushButton_OpenFile->setGeometry(QRect(330, 150, 140, 30));
        pushButton_OpenFile->setMinimumSize(QSize(0, 30));
        pushButton_OpenFile->setMaximumSize(QSize(140, 30));
        pushButton_OpenFile->setFont(font1);
        line_2 = new QFrame(groupBox_2);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(10, 140, 471, 16));
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);
        comboBox_TransMode = new QComboBox(groupBox_2);
        comboBox_TransMode->addItem(QString());
        comboBox_TransMode->addItem(QString());
        comboBox_TransMode->addItem(QString());
        comboBox_TransMode->setObjectName("comboBox_TransMode");
        comboBox_TransMode->setGeometry(QRect(160, 150, 160, 30));
        comboBox_TransMode->setMinimumSize(QSize(160, 30));
        comboBox_TransMode->setMaximumSize(QSize(180, 30));
        comboBox_TransMode->setFont(font3);
        label_cv_2 = new QLabel(groupBox_2);
        label_cv_2->setObjectName("label_cv_2");
        label_cv_2->setGeometry(QRect(20, 150, 121, 30));
        label_cv_2->setMinimumSize(QSize(0, 30));
        label_cv_2->setMaximumSize(QSize(16777215, 30));
        label_cv_2->setFont(font2);
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName("groupBox_3");
        groupBox_3->setGeometry(QRect(510, 360, 681, 441));
        groupBox_3->setFlat(true);
        textBrowser_RPreview = new QTextBrowser(groupBox_3);
        textBrowser_RPreview->setObjectName("textBrowser_RPreview");
        textBrowser_RPreview->setGeometry(QRect(10, 260, 661, 170));
        label_RPreview = new QLabel(groupBox_3);
        label_RPreview->setObjectName("label_RPreview");
        label_RPreview->setGeometry(QRect(10, 230, 91, 25));
        label_RPreview->setMinimumSize(QSize(0, 25));
        label_RPreview->setMaximumSize(QSize(16777215, 25));
        label_RPreview->setFont(font2);
        pushButton_RClear = new QPushButton(groupBox_3);
        pushButton_RClear->setObjectName("pushButton_RClear");
        pushButton_RClear->setGeometry(QRect(600, 230, 70, 30));
        pushButton_RClear->setMinimumSize(QSize(0, 30));
        pushButton_RClear->setMaximumSize(QSize(16777215, 30));
        pushButton_RClear->setFont(font1);
        textBrowser_TPreview = new QTextBrowser(groupBox_3);
        textBrowser_TPreview->setObjectName("textBrowser_TPreview");
        textBrowser_TPreview->setGeometry(QRect(10, 50, 661, 170));
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textBrowser_TPreview->sizePolicy().hasHeightForWidth());
        textBrowser_TPreview->setSizePolicy(sizePolicy);
        label_TPreview = new QLabel(groupBox_3);
        label_TPreview->setObjectName("label_TPreview");
        label_TPreview->setGeometry(QRect(10, 20, 91, 25));
        label_TPreview->setMinimumSize(QSize(0, 25));
        label_TPreview->setMaximumSize(QSize(16777215, 25));
        label_TPreview->setFont(font2);
        pushButton_TClear = new QPushButton(groupBox_3);
        pushButton_TClear->setObjectName("pushButton_TClear");
        pushButton_TClear->setGeometry(QRect(600, 20, 70, 30));
        pushButton_TClear->setMinimumSize(QSize(0, 30));
        pushButton_TClear->setMaximumSize(QSize(16777215, 30));
        pushButton_TClear->setFont(font1);
        groupBox_UUVstates = new QGroupBox(centralwidget);
        groupBox_UUVstates->setObjectName("groupBox_UUVstates");
        groupBox_UUVstates->setGeometry(QRect(510, 10, 681, 341));
        groupBox_UUVstates->setFlat(true);
        formLayoutWidget_2 = new QWidget(groupBox_UUVstates);
        formLayoutWidget_2->setObjectName("formLayoutWidget_2");
        formLayoutWidget_2->setGeometry(QRect(10, 20, 221, 170));
        formLayout_2 = new QFormLayout(formLayoutWidget_2);
        formLayout_2->setObjectName("formLayout_2");
        formLayout_2->setHorizontalSpacing(0);
        formLayout_2->setVerticalSpacing(0);
        formLayout_2->setContentsMargins(0, 0, 0, 0);
        label_pos = new QLabel(formLayoutWidget_2);
        label_pos->setObjectName("label_pos");
        label_pos->setMinimumSize(QSize(0, 28));
        label_pos->setMaximumSize(QSize(16777215, 28));
        QFont font6;
        font6.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font6.setPointSize(11);
        label_pos->setFont(font6);

        formLayout_2->setWidget(0, QFormLayout::ItemRole::LabelRole, label_pos);

        label_pos_2 = new QLabel(formLayoutWidget_2);
        label_pos_2->setObjectName("label_pos_2");
        label_pos_2->setMinimumSize(QSize(0, 28));
        label_pos_2->setMaximumSize(QSize(16777215, 28));
        label_pos_2->setFont(font6);

        formLayout_2->setWidget(1, QFormLayout::ItemRole::LabelRole, label_pos_2);

        label_depth = new QLabel(formLayoutWidget_2);
        label_depth->setObjectName("label_depth");
        label_depth->setMinimumSize(QSize(0, 28));
        label_depth->setMaximumSize(QSize(16777215, 28));
        label_depth->setFont(font6);

        formLayout_2->setWidget(2, QFormLayout::ItemRole::LabelRole, label_depth);

        label_roll = new QLabel(formLayoutWidget_2);
        label_roll->setObjectName("label_roll");
        label_roll->setMinimumSize(QSize(0, 28));
        label_roll->setMaximumSize(QSize(16777215, 28));
        label_roll->setFont(font6);

        formLayout_2->setWidget(3, QFormLayout::ItemRole::LabelRole, label_roll);

        label_pitch = new QLabel(formLayoutWidget_2);
        label_pitch->setObjectName("label_pitch");
        label_pitch->setMinimumSize(QSize(0, 28));
        label_pitch->setMaximumSize(QSize(16777215, 28));
        label_pitch->setFont(font6);

        formLayout_2->setWidget(4, QFormLayout::ItemRole::LabelRole, label_pitch);

        label_yaw = new QLabel(formLayoutWidget_2);
        label_yaw->setObjectName("label_yaw");
        label_yaw->setMinimumSize(QSize(0, 28));
        label_yaw->setMaximumSize(QSize(16777215, 28));
        label_yaw->setFont(font6);

        formLayout_2->setWidget(5, QFormLayout::ItemRole::LabelRole, label_yaw);

        lineEdit_X = new QLineEdit(formLayoutWidget_2);
        lineEdit_X->setObjectName("lineEdit_X");
        lineEdit_X->setEnabled(true);
        lineEdit_X->setMinimumSize(QSize(0, 25));
        lineEdit_X->setMaximumSize(QSize(16777214, 25));
        QFont font7;
        font7.setFamilies({QString::fromUtf8("Times New Roman")});
        font7.setPointSize(12);
        lineEdit_X->setFont(font7);
        lineEdit_X->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lineEdit_X->setReadOnly(true);

        formLayout_2->setWidget(0, QFormLayout::ItemRole::FieldRole, lineEdit_X);

        lineEdit_Y = new QLineEdit(formLayoutWidget_2);
        lineEdit_Y->setObjectName("lineEdit_Y");
        lineEdit_Y->setEnabled(true);
        lineEdit_Y->setMinimumSize(QSize(0, 25));
        lineEdit_Y->setMaximumSize(QSize(16777215, 25));
        lineEdit_Y->setFont(font7);
        lineEdit_Y->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lineEdit_Y->setReadOnly(true);

        formLayout_2->setWidget(1, QFormLayout::ItemRole::FieldRole, lineEdit_Y);

        lineEdit_Z = new QLineEdit(formLayoutWidget_2);
        lineEdit_Z->setObjectName("lineEdit_Z");
        lineEdit_Z->setEnabled(true);
        lineEdit_Z->setMinimumSize(QSize(0, 25));
        lineEdit_Z->setMaximumSize(QSize(16777215, 25));
        lineEdit_Z->setFont(font7);
        lineEdit_Z->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lineEdit_Z->setReadOnly(true);

        formLayout_2->setWidget(2, QFormLayout::ItemRole::FieldRole, lineEdit_Z);

        lineEdit_Roll = new QLineEdit(formLayoutWidget_2);
        lineEdit_Roll->setObjectName("lineEdit_Roll");
        lineEdit_Roll->setEnabled(true);
        lineEdit_Roll->setMinimumSize(QSize(0, 25));
        lineEdit_Roll->setMaximumSize(QSize(16777215, 25));
        lineEdit_Roll->setFont(font7);
        lineEdit_Roll->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lineEdit_Roll->setReadOnly(true);

        formLayout_2->setWidget(3, QFormLayout::ItemRole::FieldRole, lineEdit_Roll);

        lineEdit_Pitch = new QLineEdit(formLayoutWidget_2);
        lineEdit_Pitch->setObjectName("lineEdit_Pitch");
        lineEdit_Pitch->setEnabled(true);
        lineEdit_Pitch->setMinimumSize(QSize(0, 25));
        lineEdit_Pitch->setMaximumSize(QSize(16777215, 25));
        lineEdit_Pitch->setFont(font7);
        lineEdit_Pitch->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lineEdit_Pitch->setReadOnly(true);

        formLayout_2->setWidget(4, QFormLayout::ItemRole::FieldRole, lineEdit_Pitch);

        lineEdit_Yaw = new QLineEdit(formLayoutWidget_2);
        lineEdit_Yaw->setObjectName("lineEdit_Yaw");
        lineEdit_Yaw->setEnabled(true);
        lineEdit_Yaw->setMinimumSize(QSize(0, 25));
        lineEdit_Yaw->setMaximumSize(QSize(16777215, 25));
        lineEdit_Yaw->setFont(font7);
        lineEdit_Yaw->setAlignment(Qt::AlignmentFlag::AlignCenter);
        lineEdit_Yaw->setReadOnly(true);

        formLayout_2->setWidget(5, QFormLayout::ItemRole::FieldRole, lineEdit_Yaw);

        line = new QFrame(groupBox_UUVstates);
        line->setObjectName("line");
        line->setGeometry(QRect(230, 10, 20, 171));
        line->setFrameShape(QFrame::Shape::VLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        line_4 = new QFrame(centralwidget);
        line_4->setObjectName("line_4");
        line_4->setGeometry(QRect(495, 0, 20, 801));
        line_4->setFrameShape(QFrame::Shape::VLine);
        line_4->setFrameShadow(QFrame::Shadow::Sunken);
        UUV_UI->setCentralWidget(centralwidget);

        retranslateUi(UUV_UI);

        tabWidget_connect->setCurrentIndex(0);
        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(UUV_UI);
    } // setupUi

    void retranslateUi(QMainWindow *UUV_UI)
    {
        UUV_UI->setWindowTitle(QCoreApplication::translate("UUV_UI", "UUV_UI", nullptr));
        lineEdit_DateTime->setText(QCoreApplication::translate("UUV_UI", "2025.03.19 09:00:00 \346\230\237\346\234\237\344\270\211", nullptr));
        groupBox->setTitle(QCoreApplication::translate("UUV_UI", "\351\200\232\344\277\241\350\256\276\347\275\256", nullptr));
        label_BaudRate->setText(QCoreApplication::translate("UUV_UI", "\346\263\242\347\211\271\347\216\207\357\274\232", nullptr));
        comboBox_BaudRate->setItemText(0, QCoreApplication::translate("UUV_UI", "2400", nullptr));
        comboBox_BaudRate->setItemText(1, QCoreApplication::translate("UUV_UI", "4800", nullptr));
        comboBox_BaudRate->setItemText(2, QCoreApplication::translate("UUV_UI", "9600", nullptr));
        comboBox_BaudRate->setItemText(3, QCoreApplication::translate("UUV_UI", "14400", nullptr));
        comboBox_BaudRate->setItemText(4, QCoreApplication::translate("UUV_UI", "19200", nullptr));
        comboBox_BaudRate->setItemText(5, QCoreApplication::translate("UUV_UI", "115200", nullptr));
        comboBox_BaudRate->setItemText(6, QCoreApplication::translate("UUV_UI", "256000", nullptr));
        comboBox_BaudRate->setItemText(7, QCoreApplication::translate("UUV_UI", "460800", nullptr));

        label_name->setText(QCoreApplication::translate("UUV_UI", "\344\270\262\345\217\243\345\220\215\357\274\232", nullptr));
        label_transmistPeriod->setText(QCoreApplication::translate("UUV_UI", "\345\217\221\351\200\201\351\242\221\347\216\207", nullptr));
        comboBox_TransPeriod->setItemText(0, QCoreApplication::translate("UUV_UI", "10HZ", nullptr));
        comboBox_TransPeriod->setItemText(1, QCoreApplication::translate("UUV_UI", "20HZ", nullptr));
        comboBox_TransPeriod->setItemText(2, QCoreApplication::translate("UUV_UI", "5HZ", nullptr));

        comboBox_check->setItemText(0, QCoreApplication::translate("UUV_UI", "none", nullptr));
        comboBox_check->setItemText(1, QCoreApplication::translate("UUV_UI", "\345\245\207\346\240\241\351\252\214", nullptr));
        comboBox_check->setItemText(2, QCoreApplication::translate("UUV_UI", "\345\201\266\346\240\241\351\252\214", nullptr));

        label_check->setText(QCoreApplication::translate("UUV_UI", "\346\240\241\351\252\214\344\275\215\357\274\232", nullptr));
        comboBox_data->setItemText(0, QCoreApplication::translate("UUV_UI", "8", nullptr));
        comboBox_data->setItemText(1, QCoreApplication::translate("UUV_UI", "7", nullptr));
        comboBox_data->setItemText(2, QCoreApplication::translate("UUV_UI", "6", nullptr));
        comboBox_data->setItemText(3, QCoreApplication::translate("UUV_UI", "5", nullptr));

        label_data->setText(QCoreApplication::translate("UUV_UI", "\346\225\260\346\215\256\344\275\215\357\274\232", nullptr));
        label_stop->setText(QCoreApplication::translate("UUV_UI", "\345\201\234\346\255\242\344\275\215\357\274\232", nullptr));
        comboBox_stop->setItemText(0, QCoreApplication::translate("UUV_UI", "1", nullptr));
        comboBox_stop->setItemText(1, QCoreApplication::translate("UUV_UI", "2", nullptr));
        comboBox_stop->setItemText(2, QCoreApplication::translate("UUV_UI", "1.5", nullptr));

        pushButton_scan->setText(QCoreApplication::translate("UUV_UI", "\346\211\253\346\217\217", nullptr));
        checkBox_SerialOpen->setText(QString());
        pushButton_open->setText(QCoreApplication::translate("UUV_UI", "\346\211\223\345\274\200\344\270\262\345\217\243", nullptr));
        tabWidget_connect->setTabText(tabWidget_connect->indexOf(tab_serial), QCoreApplication::translate("UUV_UI", "\344\270\262\345\217\243", nullptr));
        tabWidget_connect->setTabText(tabWidget_connect->indexOf(tab_net), QCoreApplication::translate("UUV_UI", "\347\275\221\347\273\234", nullptr));
        groupBox_WorkMode->setTitle(QCoreApplication::translate("UUV_UI", "\345\267\245\344\275\234\346\250\241\345\274\217", nullptr));
        comboBox_WorkMode->setItemText(0, QCoreApplication::translate("UUV_UI", "\351\201\245\346\216\247\346\250\241\345\274\21701", nullptr));
        comboBox_WorkMode->setItemText(1, QCoreApplication::translate("UUV_UI", "\345\256\232\346\267\261\350\210\252\350\241\214\346\250\241\345\274\21702", nullptr));
        comboBox_WorkMode->setItemText(2, QCoreApplication::translate("UUV_UI", "\345\256\232\350\211\217\345\220\221\350\210\252\350\241\214\346\250\241\345\274\21703", nullptr));
        comboBox_WorkMode->setItemText(3, QCoreApplication::translate("UUV_UI", "\345\256\232\346\267\261+\345\256\232\350\211\217\345\220\221\350\210\252\350\241\214\346\250\241\345\274\21704", nullptr));
        comboBox_WorkMode->setItemText(4, QCoreApplication::translate("UUV_UI", "\350\275\250\350\277\271\347\202\271\350\207\252\344\270\273\350\267\237\350\270\252\346\250\241\345\274\21705", nullptr));

        lineEdit_Warning->setText(QCoreApplication::translate("UUV_UI", "\346\227\240\350\255\246\345\221\212", nullptr));
        label_WorkMode->setText(QCoreApplication::translate("UUV_UI", "\346\250\241\345\274\217\351\200\211\346\213\251", nullptr));
        groupBox_controlpad->setTitle(QCoreApplication::translate("UUV_UI", "\351\201\245\346\216\247\346\223\215\344\275\234", nullptr));
        pushButton_X->setText(QCoreApplication::translate("UUV_UI", "X", nullptr));
        pushButton_E->setText(QCoreApplication::translate("UUV_UI", "E\n"
"\345\217\263\350\275\254", nullptr));
        pushButton_F->setText(QCoreApplication::translate("UUV_UI", "F\n"
"\345\220\216\345\200\276", nullptr));
        pushButton_C->setText(QCoreApplication::translate("UUV_UI", "C\n"
"\344\270\212\346\265\256", nullptr));
        pushButton_Q->setText(QCoreApplication::translate("UUV_UI", "Q\n"
"\345\267\246\350\275\254", nullptr));
        pushButton_R->setText(QCoreApplication::translate("UUV_UI", "R\n"
"\345\211\215\345\200\276", nullptr));
        pushButton_W->setText(QCoreApplication::translate("UUV_UI", "W\n"
"\345\211\215\350\277\233", nullptr));
        pushButton_Z->setText(QCoreApplication::translate("UUV_UI", "Z\n"
"\344\270\213\346\275\234", nullptr));
        pushButton_D->setText(QCoreApplication::translate("UUV_UI", "D\n"
"\345\217\263\345\271\263\347\247\273", nullptr));
        pushButton_V->setText(QCoreApplication::translate("UUV_UI", "V", nullptr));
        pushButton_S->setText(QCoreApplication::translate("UUV_UI", "S\n"
"\345\220\216\351\200\200", nullptr));
        pushButton_A->setText(QCoreApplication::translate("UUV_UI", "A\n"
"\345\267\246\345\271\263\347\247\273", nullptr));
        label_cv->setText(QCoreApplication::translate("UUV_UI", "\346\262\271\351\227\250", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_KeyControl), QCoreApplication::translate("UUV_UI", "\351\224\256\347\233\230\346\216\247\345\210\266", nullptr));
        pushButton->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_Gamepad), QCoreApplication::translate("UUV_UI", "\346\211\213\346\237\204\346\216\247\345\210\266", nullptr));
        checkBox_GamePad->setText(QCoreApplication::translate("UUV_UI", "\346\211\213\346\237\204\346\216\247\345\210\266", nullptr));
        lineEdit_Movement->setText(QCoreApplication::translate("UUV_UI", "\346\227\240\345\212\250\344\275\234", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("UUV_UI", "\350\207\252\344\270\273\345\212\237\350\203\275", nullptr));
        label_Depth->setText(QCoreApplication::translate("UUV_UI", "\346\234\237\346\234\233\346\267\261\345\272\246/m", nullptr));
        label_Heading->setText(QCoreApplication::translate("UUV_UI", "\346\234\237\346\234\233\350\211\217\345\220\221/deg", nullptr));
        pushButton_OpenFile->setText(QCoreApplication::translate("UUV_UI", "\345\274\200\345\220\257\345\217\221\351\200\201\347\250\213\345\272\217", nullptr));
        comboBox_TransMode->setItemText(0, QCoreApplication::translate("UUV_UI", "\350\277\236\347\273\255\345\217\221\351\200\201", nullptr));
        comboBox_TransMode->setItemText(1, QCoreApplication::translate("UUV_UI", "\351\200\220\344\270\252\345\217\221\351\200\201", nullptr));
        comboBox_TransMode->setItemText(2, QCoreApplication::translate("UUV_UI", "\345\217\221\351\200\201\345\215\225\347\202\271", nullptr));

        label_cv_2->setText(QCoreApplication::translate("UUV_UI", "\350\207\252\344\270\273\350\267\237\350\270\252\346\250\241\345\274\217", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("UUV_UI", "\351\200\232\344\277\241\351\242\204\350\247\210", nullptr));
        label_RPreview->setText(QCoreApplication::translate("UUV_UI", "\346\216\245\346\224\266\351\242\204\350\247\210", nullptr));
        pushButton_RClear->setText(QCoreApplication::translate("UUV_UI", "\346\270\205\351\231\244", nullptr));
        label_TPreview->setText(QCoreApplication::translate("UUV_UI", "\345\217\221\351\200\201\351\242\204\350\247\210", nullptr));
        pushButton_TClear->setText(QCoreApplication::translate("UUV_UI", "\346\270\205\351\231\244", nullptr));
        groupBox_UUVstates->setTitle(QCoreApplication::translate("UUV_UI", "UUV\347\212\266\346\200\201", nullptr));
        label_pos->setText(QCoreApplication::translate("UUV_UI", "\344\275\215\347\275\256(X)/m", nullptr));
        label_pos_2->setText(QCoreApplication::translate("UUV_UI", "\344\275\215\347\275\256(Y)/m", nullptr));
        label_depth->setText(QCoreApplication::translate("UUV_UI", "\346\267\261\345\272\246Z/m", nullptr));
        label_roll->setText(QCoreApplication::translate("UUV_UI", "\346\250\252\346\273\232\350\247\222\317\206/deg", nullptr));
        label_pitch->setText(QCoreApplication::translate("UUV_UI", "\347\272\265\345\200\276\350\247\222\316\270/deg", nullptr));
        label_yaw->setText(QCoreApplication::translate("UUV_UI", "\350\211\217\345\220\221\350\247\222\317\210/deg", nullptr));
        lineEdit_X->setText(QCoreApplication::translate("UUV_UI", "0.00", nullptr));
        lineEdit_Y->setInputMask(QString());
        lineEdit_Y->setText(QCoreApplication::translate("UUV_UI", "0.00", nullptr));
        lineEdit_Z->setText(QCoreApplication::translate("UUV_UI", "0.00", nullptr));
        lineEdit_Roll->setText(QCoreApplication::translate("UUV_UI", "0.00", nullptr));
        lineEdit_Pitch->setText(QCoreApplication::translate("UUV_UI", "0.00", nullptr));
        lineEdit_Yaw->setText(QCoreApplication::translate("UUV_UI", "0.00", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UUV_UI: public Ui_UUV_UI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UUV_UI_H
