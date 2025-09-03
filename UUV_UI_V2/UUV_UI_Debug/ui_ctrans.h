/********************************************************************************
** Form generated from reading UI file 'ctrans.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CTRANS_H
#define UI_CTRANS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CTrans
{
public:
    QWidget *horizontalLayoutWidget_3;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *lineEdit_p1;
    QLineEdit *lineEdit_p2;
    QLineEdit *lineEdit_p3;
    QLineEdit *lineEdit_p4;
    QLineEdit *lineEdit_p5;
    QLineEdit *lineEdit_p6;
    QWidget *horizontalLayoutWidget_2;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pushButton_ChoseFile;
    QLineEdit *lineEdit_pathDisplay;
    QProgressBar *progressBar;
    QGraphicsView *graphicsView;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox_Record;
    QLabel *label_RecordCount;
    QLineEdit *lineEdit_RecordCount;
    QWidget *horizontalLayoutWidget_4;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_BeginTrans;
    QPushButton *pushButton_PauseTrans;
    QPushButton *pushButton_StopTrans;

    void setupUi(QWidget *CTrans)
    {
        if (CTrans->objectName().isEmpty())
            CTrans->setObjectName("CTrans");
        CTrans->resize(700, 800);
        CTrans->setMinimumSize(QSize(700, 800));
        CTrans->setMaximumSize(QSize(700, 800));
        horizontalLayoutWidget_3 = new QWidget(CTrans);
        horizontalLayoutWidget_3->setObjectName("horizontalLayoutWidget_3");
        horizontalLayoutWidget_3->setGeometry(QRect(10, 630, 361, 41));
        horizontalLayout_3 = new QHBoxLayout(horizontalLayoutWidget_3);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        lineEdit_p1 = new QLineEdit(horizontalLayoutWidget_3);
        lineEdit_p1->setObjectName("lineEdit_p1");
        lineEdit_p1->setMinimumSize(QSize(55, 30));
        lineEdit_p1->setMaximumSize(QSize(40, 25));
        lineEdit_p1->setReadOnly(true);

        horizontalLayout_3->addWidget(lineEdit_p1);

        lineEdit_p2 = new QLineEdit(horizontalLayoutWidget_3);
        lineEdit_p2->setObjectName("lineEdit_p2");
        lineEdit_p2->setMinimumSize(QSize(55, 30));
        lineEdit_p2->setMaximumSize(QSize(40, 25));
        lineEdit_p2->setReadOnly(true);

        horizontalLayout_3->addWidget(lineEdit_p2);

        lineEdit_p3 = new QLineEdit(horizontalLayoutWidget_3);
        lineEdit_p3->setObjectName("lineEdit_p3");
        lineEdit_p3->setMinimumSize(QSize(55, 30));
        lineEdit_p3->setMaximumSize(QSize(40, 25));
        lineEdit_p3->setReadOnly(true);

        horizontalLayout_3->addWidget(lineEdit_p3);

        lineEdit_p4 = new QLineEdit(horizontalLayoutWidget_3);
        lineEdit_p4->setObjectName("lineEdit_p4");
        lineEdit_p4->setMinimumSize(QSize(55, 30));
        lineEdit_p4->setMaximumSize(QSize(40, 25));
        lineEdit_p4->setReadOnly(true);

        horizontalLayout_3->addWidget(lineEdit_p4);

        lineEdit_p5 = new QLineEdit(horizontalLayoutWidget_3);
        lineEdit_p5->setObjectName("lineEdit_p5");
        lineEdit_p5->setMinimumSize(QSize(55, 30));
        lineEdit_p5->setMaximumSize(QSize(40, 25));
        lineEdit_p5->setReadOnly(true);

        horizontalLayout_3->addWidget(lineEdit_p5);

        lineEdit_p6 = new QLineEdit(horizontalLayoutWidget_3);
        lineEdit_p6->setObjectName("lineEdit_p6");
        lineEdit_p6->setMinimumSize(QSize(55, 30));
        lineEdit_p6->setMaximumSize(QSize(40, 25));
        lineEdit_p6->setReadOnly(true);

        horizontalLayout_3->addWidget(lineEdit_p6);

        horizontalLayoutWidget_2 = new QWidget(CTrans);
        horizontalLayoutWidget_2->setObjectName("horizontalLayoutWidget_2");
        horizontalLayoutWidget_2->setGeometry(QRect(10, 10, 681, 31));
        horizontalLayout_6 = new QHBoxLayout(horizontalLayoutWidget_2);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(0, 0, 0, 0);
        pushButton_ChoseFile = new QPushButton(horizontalLayoutWidget_2);
        pushButton_ChoseFile->setObjectName("pushButton_ChoseFile");
        pushButton_ChoseFile->setMaximumSize(QSize(90, 27));
        QFont font;
        font.setPointSize(12);
        pushButton_ChoseFile->setFont(font);

        horizontalLayout_6->addWidget(pushButton_ChoseFile);

        lineEdit_pathDisplay = new QLineEdit(horizontalLayoutWidget_2);
        lineEdit_pathDisplay->setObjectName("lineEdit_pathDisplay");
        lineEdit_pathDisplay->setMaximumSize(QSize(16777215, 27));
        lineEdit_pathDisplay->setReadOnly(true);

        horizontalLayout_6->addWidget(lineEdit_pathDisplay);

        progressBar = new QProgressBar(CTrans);
        progressBar->setObjectName("progressBar");
        progressBar->setGeometry(QRect(10, 680, 331, 21));
        progressBar->setValue(0);
        progressBar->setOrientation(Qt::Orientation::Horizontal);
        progressBar->setInvertedAppearance(false);
        progressBar->setTextDirection(QProgressBar::Direction::TopToBottom);
        graphicsView = new QGraphicsView(CTrans);
        graphicsView->setObjectName("graphicsView");
        graphicsView->setGeometry(QRect(10, 50, 680, 570));
        graphicsView->setMinimumSize(QSize(680, 570));
        graphicsView->setMaximumSize(QSize(680, 570));
        horizontalLayoutWidget = new QWidget(CTrans);
        horizontalLayoutWidget->setObjectName("horizontalLayoutWidget");
        horizontalLayoutWidget->setGeometry(QRect(10, 750, 291, 31));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        checkBox_Record = new QCheckBox(horizontalLayoutWidget);
        checkBox_Record->setObjectName("checkBox_Record");
        checkBox_Record->setFont(font);

        horizontalLayout->addWidget(checkBox_Record);

        label_RecordCount = new QLabel(horizontalLayoutWidget);
        label_RecordCount->setObjectName("label_RecordCount");
        label_RecordCount->setMinimumSize(QSize(0, 0));
        label_RecordCount->setMaximumSize(QSize(16777215, 28));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221")});
        font1.setPointSize(12);
        label_RecordCount->setFont(font1);
        label_RecordCount->setAlignment(Qt::AlignmentFlag::AlignCenter);

        horizontalLayout->addWidget(label_RecordCount);

        lineEdit_RecordCount = new QLineEdit(horizontalLayoutWidget);
        lineEdit_RecordCount->setObjectName("lineEdit_RecordCount");
        lineEdit_RecordCount->setMinimumSize(QSize(0, 0));
        lineEdit_RecordCount->setMaximumSize(QSize(150, 16777215));
        lineEdit_RecordCount->setReadOnly(true);

        horizontalLayout->addWidget(lineEdit_RecordCount);

        horizontalLayoutWidget_4 = new QWidget(CTrans);
        horizontalLayoutWidget_4->setObjectName("horizontalLayoutWidget_4");
        horizontalLayoutWidget_4->setGeometry(QRect(10, 710, 291, 31));
        horizontalLayout_2 = new QHBoxLayout(horizontalLayoutWidget_4);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        pushButton_BeginTrans = new QPushButton(horizontalLayoutWidget_4);
        pushButton_BeginTrans->setObjectName("pushButton_BeginTrans");
        pushButton_BeginTrans->setMinimumSize(QSize(90, 27));
        pushButton_BeginTrans->setMaximumSize(QSize(90, 30));
        pushButton_BeginTrans->setFont(font);

        horizontalLayout_2->addWidget(pushButton_BeginTrans);

        pushButton_PauseTrans = new QPushButton(horizontalLayoutWidget_4);
        pushButton_PauseTrans->setObjectName("pushButton_PauseTrans");
        pushButton_PauseTrans->setMinimumSize(QSize(90, 27));
        pushButton_PauseTrans->setMaximumSize(QSize(90, 30));
        pushButton_PauseTrans->setFont(font);

        horizontalLayout_2->addWidget(pushButton_PauseTrans);

        pushButton_StopTrans = new QPushButton(horizontalLayoutWidget_4);
        pushButton_StopTrans->setObjectName("pushButton_StopTrans");
        pushButton_StopTrans->setMinimumSize(QSize(90, 27));
        pushButton_StopTrans->setMaximumSize(QSize(90, 30));
        pushButton_StopTrans->setFont(font);

        horizontalLayout_2->addWidget(pushButton_StopTrans);


        retranslateUi(CTrans);

        QMetaObject::connectSlotsByName(CTrans);
    } // setupUi

    void retranslateUi(QWidget *CTrans)
    {
        CTrans->setWindowTitle(QCoreApplication::translate("CTrans", "Form", nullptr));
        pushButton_ChoseFile->setText(QCoreApplication::translate("CTrans", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        checkBox_Record->setText(QCoreApplication::translate("CTrans", "\345\274\200\345\220\257\350\256\260\345\275\225", nullptr));
        label_RecordCount->setText(QCoreApplication::translate("CTrans", "\350\256\260\345\275\225\350\241\214\346\225\260", nullptr));
        pushButton_BeginTrans->setText(QCoreApplication::translate("CTrans", "\345\274\200\345\247\213\345\217\221\351\200\201", nullptr));
        pushButton_PauseTrans->setText(QCoreApplication::translate("CTrans", "\346\232\202\345\201\234\345\217\221\351\200\201", nullptr));
        pushButton_StopTrans->setText(QCoreApplication::translate("CTrans", "\345\201\234\346\255\242\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CTrans: public Ui_CTrans {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CTRANS_H
