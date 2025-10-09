#include "uuv_log_recorder.h"
#include <QSaveFile>
#include <QTextStream>
#include <QLocale>
#include <QFileInfo>

/* 开始记录：清空旧数据，记录当前 UTC 起始时间，置 recording=true */
void UUVLogRecorder::start()
{
    m_rows.clear();
    m_startUtc = QDateTime::currentDateTimeUtc();
    m_recording = true;
}

/* 停止并清空所有记录 */
void UUVLogRecorder::stopAndClear()
{
    m_recording = false;
    m_rows.clear();
    m_startUtc = QDateTime();
}

/* 获取已运行毫秒数（未 start 或已 stop 返回 0） */
qint64 UUVLogRecorder::elapsedMs() const
{
    if (!m_recording || !m_startUtc.isValid()) return 0;
    return m_startUtc.msecsTo(QDateTime::currentDateTimeUtc());
}

/* 返回格式化时长 "hh:mm:ss" */
QString UUVLogRecorder::formattedDuration() const
{
    const qint64 ms = elapsedMs();
    QTime base(0,0,0);
    return base.addMSecs(int(ms)).toString("hh:mm:ss");
}

/* 当前 UTC 时间戳字符串，精确到毫秒 */
QString UUVLogRecorder::nowUtcString()
{
    return QDateTime::currentDateTimeUtc().toString("yyyy-MM-dd HH:mm:ss.zzz");
}

/* 构建 CSV 表头：
 * 列顺序约定：
 * TimestampUTC, Direction,
 * WorkMode, taw_x..taw_psi (6 列), Depth_d, Yaw_d,
 * pos1..pos6,
 * x,y,z,roll,pitch,yaw (接收姿态)
 */
QStringList UUVLogRecorder::buildHeader() const
{
    return {
        "TimestampUTC","Direction",
        "WorkMode",
        "taw_x","taw_y","taw_z","taw_phi","taw_theta","taw_psi",
        "Depth_d","Yaw_d",
        "eta_d1","eta_d2","eta_d3","eta_d4","eta_d5","eta_d6",
        "x","y","z","roll","pitch","yaw"
    };
}

/* 构建发送行：接收相关的 6 列留空 */
QStringList UUVLogRecorder::buildTransmitRow(const TransmitFields& tf) const
{
    QStringList row;
    row.reserve(23);
    row << nowUtcString() << "Transmit"
        << QString::number(tf.workMode)
        << QString::number(tf.taw_x)
        << QString::number(tf.taw_y)
        << QString::number(tf.taw_z)
        << QString::number(tf.taw_phi)
        << QString::number(tf.taw_theta)
        << QString::number(tf.taw_psi)
        << QString::number(tf.depth_d, 'f', 3)
        << QString::number(tf.yaw_d, 'f', 3);

        // 接收 x,y,z,roll,pitch,yaw 六列空
        //<< QString::number(tf.pos[0], 'f', 3)
        //<< QString::number(tf.pos[1], 'f', 3)
        //<< QString::number(tf.pos[2], 'f', 3)
        //<< QString::number(tf.pos[3], 'f', 3)
        //<< QString::number(tf.pos[4], 'f', 3)
        //<< QString::number(tf.pos[5], 'f', 3)

        // 根据 posValid 决定是否写 pos 数值：
        if (tf.posValid) {
            for (int i=0;i<6;++i){
                row << QString::number(tf.pos[i], 'f', 3);
            }
        } else {
            // 未发送 pos（非全自主模式），用空值表示“无”
            for (int i=0;i<6;++i)
                row << ""; // 你也可以改成 "NA"
        }

    // 接收位姿占位空
    row << "" << "" << "" << "" << "" << "";
    return row;
}

/* 构建接收行：发送相关列留空 */
QStringList UUVLogRecorder::buildReceiveRow(const ReceiveFields& rf) const
{
    QStringList row;
    row.reserve(23);
    row << nowUtcString() << "Receive"
        // 发送相关全部空（11 列：WorkMode + 6 taw + Depth_d + Yaw_d + pos1..6 共 1+6+2+6=15 列，注意这里我们对齐顺序）
        << "" // WorkMode
        << "" << "" << "" << "" << "" << "" // 6 个 taw
        << "" << ""                         // Depth_d, Yaw_d
        << "" << "" << "" << "" << "" << "" // pos1..6
        // 接收 6 列
        << QString::number(rf.eta[0], 'f', 3)
        << QString::number(rf.eta[1], 'f', 3)
        << QString::number(rf.eta[2], 'f', 3)
        << QString::number(rf.eta[3], 'f', 3)
        << QString::number(rf.eta[4], 'f', 3)
        << QString::number(rf.eta[5], 'f', 3);
    return row;
}

/* 追加发送行 */
void UUVLogRecorder::appendTransmit(const TransmitFields& tf)
{
    if (!m_recording) return;
    m_rows.push_back(buildTransmitRow(tf));
}

/* 追加接收行 */
void UUVLogRecorder::appendReceive(const ReceiveFields& rf)
{
    if (!m_recording) return;
    m_rows.push_back(buildReceiveRow(rf));
}

/* 保存文件：根据后缀决定走 CSV / TXT */
bool UUVLogRecorder::saveToFile(const QString& path, QString* errMsg) const
{
    if (m_rows.isEmpty()) {
        if (errMsg) *errMsg = "无记录数据";
        return false;
    }
    QFileInfo fi(path);
    const QString suffix = fi.suffix().toLower();
    if (suffix == "txt")
        return saveTxt(path, errMsg);

    // 其余一律按 CSV 处理；若没有 .csv 后缀则追加
    QString realPath = path;
    if (suffix != "csv")
        realPath += ".csv";
    return saveCsv(realPath, errMsg);
}

/* 保存为 CSV：写表头 + 每行 join(',') */
bool UUVLogRecorder::saveCsv(const QString& path, QString* errMsg) const
{
    QSaveFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        if (errMsg) *errMsg = file.errorString();
        return false;
    }
    QTextStream out(&file);
    out.setLocale(QLocale::C); // 保证小数点为 '.'
    out << buildHeader().join(',') << '\n';
    for (const auto& row : m_rows)
        out << row.join(',') << '\n';

    if (!file.commit()) {
        if (errMsg) *errMsg = "提交写入失败";
        return false;
    }
    return true;
}

/* 保存为 TXT：可读性较好，格式简单 */
bool UUVLogRecorder::saveTxt(const QString& path, QString* errMsg) const
{
    QSaveFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        if (errMsg) *errMsg = file.errorString();
        return false;
    }
    QTextStream out(&file);
    out.setLocale(QLocale::C);

    for (const auto& row : m_rows) {
        const QString& direction = row[1]; // 第二列 Direction
        if (direction == "Transmit") {
            out << "[" << row[0] << "] Transmit "
                << "WM=" << row[2]
                << " taw=[" << row[3] << "," << row[4] << "," << row[5]
                << "," << row[6] << "," << row[7] << "," << row[8] << "]"
                << " Depth=" << row[9] << " Yaw=" << row[10]
                << " pos=[" << row[11] << "," << row[12] << "," << row[13]
                << "," << row[14] << "," << row[15] << "," << row[16] << "]\n";
        } else {
            out << "[" << row[0] << "] Receive "
                << "eta=[" << row[17] << "," << row[18] << "," << row[19]
                << "," << row[20] << "," << row[21] << "," << row[22] << "]\n";
        }
    }

    if (!file.commit()) {
        if (errMsg) *errMsg = "提交写入失败";
        return false;
    }
    return true;
}
