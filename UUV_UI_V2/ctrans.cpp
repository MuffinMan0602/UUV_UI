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
    ui2->pushButton_PauseTrans->setDisabled(true);//停止按钮按下后停用暂停按钮


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
    //handleDataRequest(0); // 同步发送第一个点
    ui2->progressBar->setValue(0);

    // 连接数据请求信号到处理函数
    connect(this, &CTrans::requestData, this, &CTrans::handleDataRequest);


    ui2->pushButton_BeginTrans->setDisabled(true);//开始按钮按下后停用开始按钮，防止重复开始
    ui2->pushButton_PauseTrans->setDisabled(false);//停止按钮按下后停用暂停按钮


}
void CTrans::on_pushButton_PauseTrans_clicked()//暂停按钮
{
    if (!pause_flag) {
        pause_flag = true;
        trans_flag = false;
        ui2->pushButton_PauseTrans->setText("继续"); // 改按钮文本为继续
        ui2->pushButton_BeginTrans->setDisabled(true);
    } else {
        pause_flag = false;
        trans_flag = true;
        ui2->pushButton_PauseTrans->setText("暂停");
        ui2->pushButton_BeginTrans->setDisabled(true);
        // 如果用的是定时器或循环驱动发送，需要手动触发下一条数据的发送
        emit requestData(m_currentIndex);
    }
}

void CTrans::on_pushButton_StopTrans_clicked()//停止发送
{

    ui2->pushButton_PauseTrans->setDisabled(true);//停止按钮按下后停用暂停按钮
    //trans_flag = false;
    pause_flag = true;

    QMessageBox msgBox(this);
    msgBox.setWindowTitle("操作选择");
    msgBox.setText("请选择接下来的操作：");

    // 添加四个自定义按钮
    QPushButton *btnCloseRemote = msgBox.addButton("关闭并回到遥控模式", QMessageBox::ActionRole);
    QPushButton *btnAutoReturn = msgBox.addButton("一键自主返航", QMessageBox::ActionRole);
    QPushButton *btnResend = msgBox.addButton("重新发送", QMessageBox::ActionRole);
    QPushButton *btnCancel = msgBox.addButton("取消", QMessageBox::RejectRole);

    msgBox.exec();

    if (msgBox.clickedButton() == btnCloseRemote) {
        // TODO: 回到遥控模式的处理
        // 断开信号
        disconnect(this, &CTrans::requestData, this, &CTrans::handleDataRequest);


        // 停止并清理CSV工作线程
        if (m_csvWorker) {
            m_csvWorker->stop();
            delete m_csvWorker;
            m_csvWorker = nullptr;
        }

        // 重置所有状态
        m_currentIndex = 0;
        trans_flag = false;
        pause_flag = false;
        // 复位UI
        ui2->progressBar->setValue(0);
        ui2->pushButton_BeginTrans->setDisabled(false);
        ui2->pushButton_PauseTrans->setText("暂停");
        // 关闭当前窗口
        this->close();


    } else if (msgBox.clickedButton() == btnAutoReturn) {
        // TODO: 一键自主返航逻辑
        // 保证m_csvWorker存在且有数据
        if (m_csvWorker && m_totalRows > 0) {
            QVector<float> firstRow = m_csvWorker->getRow(0);
            // 重置所有状态
            m_currentIndex = 0;

            trans_flag = false;
            pause_flag = false;
            // 复位UI
            ui2->progressBar->setValue(0);
            ui2->pushButton_BeginTrans->setDisabled(false);
            ui2->pushButton_PauseTrans->setText("暂停");

            if (firstRow.size() == 6) {
                // 发射信号，让主窗口或下位机处理返航（你可以直接复用已有信号）
                emit updatePositions(0,
                    firstRow[0], firstRow[1], firstRow[2],
                    firstRow[3], firstRow[4], firstRow[5]
                    );
                handleDataRequest(0); // 同步发送第一个点
                // UI同步（可选：在界面显示已返航）
                ui2->lineEdit_p1->setText(QString::number(firstRow[0], 'f', 2));
                ui2->lineEdit_p2->setText(QString::number(firstRow[1], 'f', 2));
                ui2->lineEdit_p3->setText(QString::number(firstRow[2], 'f', 2));
                ui2->lineEdit_p4->setText(QString::number(firstRow[3], 'f', 2));
                ui2->lineEdit_p5->setText(QString::number(firstRow[4], 'f', 2));
                ui2->lineEdit_p6->setText(QString::number(firstRow[5], 'f', 2));
                // //QMessageBox::information(this, "返航", "已发送返航点。");
            } else {
                QMessageBox::warning(this, "返航", "CSV数据格式错误！");
            }
        } else {
            QMessageBox::warning(this, "返航", "CSV数据不存在！");
        }
        // 返航后，传输仍可继续，窗口不关闭

    } else if (msgBox.clickedButton() == btnResend) {
        // TODO: 重新发送逻辑

    } else if (msgBox.clickedButton() == btnCancel) {
        // TODO: 取消，什么都不做
        ui2->pushButton_PauseTrans->setDisabled(false);
        ui2->pushButton_PauseTrans->setText("继续");
        pause_flag = true;
    }
}

void CTrans::handleDataRequest(int rowIndex)
{
    //当收到主线程的更新请求以后打包数据发送更新，实际的更新函数是CTrans::updatePositions()

    // 检查是否有有效的工作线程和数据
    if (!m_csvWorker || m_totalRows == 0) return;
    // 检查暂停和停止标志
    if (!trans_flag || pause_flag)
        return;
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
        emit updatePositions(m_currentIndex,
            rowData[0], rowData[1], rowData[2],
            rowData[3], rowData[4], rowData[5]
            );
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





