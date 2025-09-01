#ifndef CSVWORKER_H
#define CSVWORKER_H

#include <QThread>
#include <QString>
#include <QVector>
#include <QMutex>




class CsvWorker : public QThread
{
    Q_OBJECT
public:
    explicit CsvWorker(const QString& filePath, QObject* parent = nullptr);
    ~CsvWorker();

    void run() override;
    void stop();
    QVector<float> getRow(int index);//获取指定行的数据,index是行号

signals:
    void dataLoaded(int totalRows);//数据加载完成信号，totalRows是加载的总行数

private:
    QString m_filePath;// CSV文件路径
    QVector<QVector<float>> m_data; // 存储所有行数据的二维向量
    QMutex m_mutex;// 互斥锁，保护共享数据
    bool m_running = true;// 线程运行标志
    //int m_totalRows = 0;// 文件总行数
};

#endif // CSVWORKER_H
