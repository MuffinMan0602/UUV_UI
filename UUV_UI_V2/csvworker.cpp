#include "csvworker.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>


CsvWorker::CsvWorker(const QString& filePath, QObject* parent)
    : QThread(parent), m_filePath(filePath)
{
    //Q_ASSERT(metaObject() != nullptr); // 确保元对象存在
}

CsvWorker::~CsvWorker()
{
    // 确保线程安全停止
    stop();
}

void CsvWorker::run()
{
    QFile file(m_filePath);
    // 尝试以只读文本模式打开文件
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "无法打开文件:" << m_filePath;
        return;
    }

    QTextStream in(&file);
    int rowCount = 0;

    // 清空现有数据（加锁保护）
    {
        QMutexLocker locker(&m_mutex);
        m_data.clear();
    }

    // 逐行读取文件内容
    while (m_running && !in.atEnd()) {
        QString line = in.readLine();    // 读取一行
        QStringList fields = line.split(','); // 按逗号分割字段

        // 跳过列数不足7的行
        if (fields.size() < 7) continue;

        QVector<float> row; // 存储当前行的6个坐标值
        bool ok; // 转换成功标志

        // 跳过第一列（序号），处理第2-7列
        for (int i = 1; i < 7; i++) {
            float value = fields[i].toFloat(&ok);
            if (!ok) {
                // 转换失败时记录警告并使用0作为默认值
                value = 0.0f;
                qWarning() << "转换错误:" << fields[i];
            }
            row.append(value);
        }

        // 加锁保护数据存储
        {
            QMutexLocker locker(&m_mutex);
            m_data.append(row);
        }

        rowCount++; // 行计数器增加
    }

    file.close(); // 关闭文件

    // 发出数据加载完成信号
    emit dataLoaded(rowCount);
}

void CsvWorker::stop()
{
    // 设置停止标志
    m_running = false;

    wait(500);  // 等待500ms线程正常退出
    if (isRunning()) {// 如果超时，强制终止线程
        terminate();
        wait();
    }
}

QVector<float> CsvWorker::getRow(int index)//获取指定行的数据
{
    QMutexLocker locker(&m_mutex); // 加锁保护共享数据

    // 检查索引有效性
    if (index >= 0 && index < m_data.size()) {
        return m_data[index]; // 返回请求的行数据
    }

    // 索引无效时返回空向量
    return QVector<float>();
}
