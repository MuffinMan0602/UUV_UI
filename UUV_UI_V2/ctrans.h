#ifndef CTRANS_H
#define CTRANS_H

#include <QWidget>
#include <QFileDialog>
#include <QVector>
#include <QMutex>

// 前向声明CsvWorker类
class CsvWorker;

namespace Ui {
class CTrans;
}

class CTrans : public QWidget
{
    Q_OBJECT

public:
    explicit CTrans(QWidget *parent = nullptr);
    ~CTrans();

    QString filePath;//文件路径
    float pos_temp[6];//暂存点坐标

signals:
    void requestData(int rowIndex);//请求数据信号
    void updatePositions(float p1, float p2, float p3, float p4, float p5, float p6);

private slots:
    void on_pushButton_ChoseFile_clicked();//选择文件

    void on_pushButton_BeginTrans_clicked();//开始发送

    void on_checkBox_Record_checkStateChanged();//勾选开启记录

    void on_pushButton_StopTrans_clicked();//停止发送

    void handleDataRequest(int rowIndex);//处理数据请求

    void handleDataLoaded(int totalRows);//处理数据加载完成信号

    void on_pushButton_PauseTrans_clicked();

private:
    Ui::CTrans *ui2;
    CsvWorker* m_csvWorker = nullptr; // CSV工作线程指针
    int m_currentIndex = 0; // 当前发送的行索引
    bool trans_flag = false;//发送标志
    int m_totalRows = 0; // CSV文件总行数

};

#endif // CTRANS_H
