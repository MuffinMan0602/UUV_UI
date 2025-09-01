#include "ctrans.h"
#include "ui_ctrans.h"
#include "csvworker.h"

CTrans::CTrans(QWidget *parent)
    : QWidget(parent)
    , ui2(new Ui::CTrans)
{
    ui2->setupUi(this);
    setWindowTitle("连续发送模式");
    this->setWindowFlags(Qt::Window);


}

CTrans::~CTrans()
{
    // 清理CSV工作线程
    if (m_csvWorker && m_csvWorker->isRunning()) {
        m_csvWorker->stop();
        m_csvWorker->wait();
        delete m_csvWorker;
    }
    delete ui2;
}

void CTrans::on_pushButton_ChoseFile_clicked()//选择文件
{
    filePath = QFileDialog::getOpenFileName(
        this,                       // 父窗口
        "选择文件",                  // 对话框标题
        //QDir::homePath(),           // 默认路径（用户主目录）
        QCoreApplication::applicationDirPath(), // 默认路径设为可执行文件目录
        "坐标文件 (*.csv);;坐标文件 (*.txt);;" // 文件过滤器
        );

    if (!filePath.isEmpty()) {
        // 将路径显示在文本框中
        ui2->lineEdit_pathDisplay->setText(filePath);

        // 清理现有的CSV工作线程
        if (m_csvWorker) {
            m_csvWorker->stop();
            delete m_csvWorker;
        }

        // 创建新的CSV工作线程
        m_csvWorker = new CsvWorker(filePath, this);

        // 连接数据加载完成信号
        connect(m_csvWorker, &CsvWorker::dataLoaded, this, &CTrans::handleDataLoaded);

        // 启动线程读取文件
        m_csvWorker->start();
    }
}


void CTrans::on_pushButton_BeginTrans_clicked()//开始发送
{
    // 检查是否有数据可发送
    if (m_totalRows == 0) {
        qWarning() << "没有数据可发送";
        return;
    }

    trans_flag = true;//发送标志
    // 重置索引和进度条
    m_currentIndex = 0;
    ui2->progressBar->setValue(0);

    // 连接数据请求信号到处理函数
    connect(this, &CTrans::requestData, this, &CTrans::handleDataRequest);

    //记录轨迹
    if(ui2->checkBox_Record->isChecked())
    {
        ;
    }

    ui2->pushButton_BeginTrans->setDisabled(true);//开始按钮按下后停用开始按钮，防止重复开始

}
void CTrans::on_pushButton_PauseTrans_clicked()//暂停按钮
{
    trans_flag = false;//发送标志



}

void CTrans::on_pushButton_StopTrans_clicked()//停止发送
{
    // 断开数据请求信号连接
    disconnect(this, &CTrans::requestData, this, &CTrans::handleDataRequest);

    // 停止并清理CSV工作线程
    if (m_csvWorker) {
        m_csvWorker->stop();
        delete m_csvWorker;
        m_csvWorker = nullptr;
    }

    // 重置进度条
    ui2->progressBar->setValue(0);

    ui2->pushButton_BeginTrans->setDisabled(false);//重新使能开始发送按钮
}

void CTrans::handleDataRequest(int rowIndex)
{
    // 检查是否有有效的工作线程和数据
    if (!m_csvWorker || m_totalRows == 0) return;

    // 循环发送：到达末尾时回到开头
    //if (m_currentIndex >= m_totalRows) {
        //m_currentIndex = 0;
    //}

    // 获取当前行数据
    int currentIndex = rowIndex % m_totalRows;
    QVector<float> rowData = m_csvWorker->getRow(currentIndex);
    if (rowData.size() == 6) {
        // 在UI中显示坐标值
        ui2->lineEdit_p1->setText(QString::number(rowData[0], 'f', 2));
        ui2->lineEdit_p2->setText(QString::number(rowData[1], 'f', 2));
        ui2->lineEdit_p3->setText(QString::number(rowData[2], 'f', 2));
        ui2->lineEdit_p4->setText(QString::number(rowData[3], 'f', 2));
        ui2->lineEdit_p5->setText(QString::number(rowData[4], 'f', 2));
        ui2->lineEdit_p6->setText(QString::number(rowData[5], 'f', 2));

        // 更新进度条
        int progress = static_cast<int>((static_cast<float>(m_currentIndex) / m_totalRows * 100));
        ui2->progressBar->setValue(progress);

        // 发送坐标到主界面
        emit updatePositions(
            rowData[0], rowData[1], rowData[2],
            rowData[3], rowData[4], rowData[5]
            );
        //qDebug()<<rowData[0]<< rowData[1]<<rowData[2]<<rowData[3]<<rowData[4]<< rowData[5];

        // 移动到下一行
        m_currentIndex++;
    }
}

void CTrans::handleDataLoaded(int totalRows)//读取文件以后
{
    // 保存总行数
    m_totalRows = totalRows;

    // 配置进度条
    ui2->progressBar->setMaximum(100);
    ui2->progressBar->setValue(0);

    // 在UI中显示总行数
    //ui2->lineEdit_RecordCount->setText(QString::number(totalRows));
}

void CTrans::on_checkBox_Record_checkStateChanged()//勾选开启记录
{
    if(ui2->checkBox_Record->isChecked())
    {
        ui2->pushButton_BeginTrans->setText("开始并记录");
        ui2->pushButton_StopTrans->setText("停止并保存");
    }
    else{
        ui2->pushButton_BeginTrans->setText("开始发送");
        ui2->pushButton_StopTrans->setText("暂停发送");
    }
}



