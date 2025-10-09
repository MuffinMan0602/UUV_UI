# UUV_UI 地面站用户界面

> **项目简介**  
UUV_UI 是一个为无人水下航行器（UUV）设计的地面站用户界面，采用 [Qt](https://www.qt.io/) 框架开发。该项目旨在为 UUV 操作人员提供友好、高效的图形化控制界面，便于任务规划、数据监控与设备管理。

---

## 主要功能

- **设备连接与管理**  
  支持与 UUV 进行稳定连接，实时监控设备状态，便捷进行参数配置和管理。

- **任务规划与执行（还没实现，努力中...）**
  可视化任务规划，支持航线编辑、任务下发与执行状态反馈。

- **实时数据展示**  
  展示 UUV 传感器数据（如深度、速度、姿态等），支持图表与历史数据查询。

- **报警与故障提示**  
  实时显示异常或故障信息，辅助操作人员及时处理设备问题。

- **日志记录与回放**  
  自动记录运行过程中的关键信息，支持日志回放与分析。

---

## 技术栈

- **主要语言**：C++ (98.3%)
- **工程构建**：QMake (1.7%)
- **界面开发**：Qt Widgets / Qt Quick（根据实际情况填写）
- **平台支持**：Windows 

---

## 环境依赖

1. **Qt 开发环境**  
   - 推荐使用 Qt 5.12 及以上版本
   - 请确保安装 Qt Creator 和对应的 C++ 编译器

2. **C++ 编译器**  
   - Windows：MinGW 或 MSVC
   - Linux：GCC
   - macOS：Clang

3. **其他依赖库**  
   - 使用了Windows的手柄库（XBox）

---

## 安装与编译

1. **克隆仓库**
   ```bash
   git clone https://github.com/MuffinMan0602/UUV_UI.git
   cd UUV_UI
   ```

2. **使用 Qt Creator 打开项目文件**
   - 打开 `UUV_UI.pro` 工程文件

3. **配置并编译项目**
   - 选择合适的构建套件（如 Desktop Qt 5.12 MSVC、MinGW、GCC 等）
   - 点击“构建”按钮进行编译

4. **运行程序**
   - 编译完成后，直接在 Qt Creator 内运行，或在构建目录下执行生成的可执行文件

---

## 使用说明

- 启动程序后，按照界面提示进行 UUV 设备连接

---


## 联系与支持

- 作者：[@MuffinMan0602](https://github.com/MuffinMan0602)
- 问题反馈：请提交 [Issues](https://github.com/MuffinMan0602/UUV_UI/issues)

---

> **备注**  
如需定制或扩展功能，请联系作者或在 Issue 中留言。



## 补充

> # 串口通信协议（UUV ↔ 上位机）

本文档基于当前仓库实现梳理出 UUV 与上位机（地面站 UI）之间的串口数据帧格式，便于双方对接与联调。

注意：
- 本文仅描述帧层格式与字段定义，不约束串口物理层参数（波特率、校验等），请按实际软件设置。
- 浮点数均为 IEEE-754 单精度 float，采用大端（Big-Endian）字节序，详见“字节序与数值编码”。

代码参考（永久链接）：
- 上位机发送封包（PC → UUV）：[serial_Transmit_worker.cpp](https://github.com/MuffinMan0602/UUV_UI/blob/40ea83dd34d765f034dc15f49b7cec55f6482629/UUV_UI_V2/serial_Transmit_worker.cpp#L57-L115)
- 上位机接收解包（UUV → PC）：[serial_Receive_worker.cpp](https://github.com/MuffinMan0602/UUV_UI/blob/40ea83dd34d765f034dc15f49b7cec55f6482629/UUV_UI_V2/serial_Receive_worker.cpp#L95-L144)

---

## 1. 帧通用结构

所有方向的帧均采用如下包头/包尾进行同步：
- 包头（Header）：0xFE（1 字节）
- 模式（Mode）：1 字节，合法范围 0x01 ~ 0x05
- 负载（Payload）：根据模式与方向不同而长度不同（详见后文）
- 包尾（Tail）：0xFF（1 字节）

通用格式：
[0xFE][Mode][Payload...][0xFF]

---

## 2. 字节序与数值编码

- 浮点数：IEEE-754 单精度 float（4 字节），大端序（Big-Endian）
  - 参考接收端解码设置：QDataStream::setByteOrder(QDataStream::BigEndian); QDataStream::SinglePrecision
- 有符号整型：int8_t（1 字节，范围 -128 ~ 127）

---

## 3. 上位机 → UUV（控制帧）

上位机根据模式发送不同的控制数据。代码中 currentWorkMode ∈ {0x01,0x02,0x03,0x04,0x05}。

A) 手动/半自主控制（Mode = 0x01 ~ 0x04）

帧结构（总长 17 字节）：
[0xFE][Mode][taw_x][taw_y][taw_z][taw_phi][taw_theta][taw_psi][Depth_d(float,BE)][Yaw_d(float,BE)][0xFF]

字段说明：
- Mode：工作模式，0x01~0x04 表示手动/半自主（具体语义由双方约定）
- taw_x, taw_y, taw_z, taw_phi, taw_theta, taw_psi：6 个通道的有符号 8 位控制量（int8_t）
  - 建议含义：机体系 6 自由度的期望力/矩归一化指令（或舵量），范围与标定由双方约定
- Depth_d：期望深度，float（单位建议：米，向下为正）
- Yaw_d：期望艏向，float（单位建议：弧度或度，需双方统一）
- 字节序：两个 float 均为大端序

示例（十六进制，Mode=0x01，六通道全 0，Depth_d=10.0，Yaw_d=1.57）：
FE 01 00 00 00 00 00 00 41 20 00 00 3F C9 F0 70 FF
说明：
- 10.0f 大端：41 20 00 00
- 1.57f 大端：3F C9 F0 70

B) 全自主/航点控制（Mode = 0x05）

帧结构（总长 27 字节）：
[0xFE][0x05][pos1(float)][pos2(float)][pos3(float)][pos4(float)][pos5(float)][pos6(float)][0xFF]
每个 float 均为大端序，总计 6×4=24 字节的负载。

字段建议映射（需双方确认）：
- pos1..pos3：目标位置 x, y, z（单位：米）
- pos4..pos6：目标姿态 roll, pitch, yaw（单位：弧度或度）
- 实际含义取决于任务定义（如航点坐标系、姿态欧拉角顺序等）

示例（十六进制，x=1.0, y=2.0, z=3.0, roll=0, pitch=0, yaw=0）：
FE 05 3F 80 00 00 40 00 00 00 40 40 00 00 00 00 00 00 00 00 00 00 00 00 00 00 FF

---

## 4. UUV → 上位机（状态帧）

接收端状态机与解码逻辑见代码注释“典型数据包结构：包头0xFE | 模式1字节 | 24字节数据（6*float） | 包尾0xFF”。

帧结构（总长 27 字节）：
[0xFE][Mode][x(float)][y(float)][z(float)][roll(float)][pitch(float)][yaw(float)][0xFF]
- 6 个 float 均为大端序
- Mode 合法范围仍为 0x01~0x05（用于在日志/回放中区分来源模式，或供上位机状态机校验）

字段含义建议：
- x, y, z：位置（单位：米；坐标系需双方约定）
- roll, pitch, yaw：姿态（单位：弧度或度；旋转顺序需双方约定）

---

## 5. 解析状态机（接收端健壮性）

为处理半包/粘包和脏数据，接收端采用 4 态解析状态机：
1) WAIT_HEADER：查找包头 0xFE，丢弃其前所有无效字节
2) READ_MODE：读取 Mode（1 字节），校验范围 0x01~0x05，不合法则丢弃 1 字节并回到 WAIT_HEADER
3) COLLECT_DATA：按需读取 Payload
   - 状态帧固定为 24 字节（6×float，大端）
   - 解析成功后进入 CHECK_TAIL
4) CHECK_TAIL：读取并校验包尾 0xFF，正确则完成一帧；错误则丢弃 1 字节后回到 WAIT_HEADER

参考实现：
- 模式校验与重同步：[READ_MODE](https://github.com/MuffinMan0602/UUV_UI/blob/40ea83dd34d765f034dc15f49b7cec55f6482629/UUV_UI_V2/serial_Receive_worker.cpp#L103-L111)
- 大端 float 解码与取数：[COLLECT_DATA](https://github.com/MuffinMan0602/UUV_UI/blob/40ea83dd34d765f034dc15f49b7cec55f6482629/UUV_UI_V2/serial_Receive_worker.cpp#L112-L131)
- 包尾校验与复位：[CHECK_TAIL](https://github.com/MuffinMan0602/UUV_UI/blob/40ea83dd34d765f034dc15f49b7cec55f6482629/UUV_UI_V2/serial_Receive_worker.cpp#L132-L142)

---

## 6. 长度汇总

- 控制帧（0x01~0x04）：17 字节
  - 1(头) + 1(Mode) + 6×1(int8) + 2×4(float) + 1(尾)
- 控制帧（0x05）：27 字节
  - 1(头) + 1(Mode) + 6×4(float) + 1(尾)
- 状态帧（UUV → 上位机）：27 字节
  - 1(头) + 1(Mode) + 6×4(float) + 1(尾)

---

## 7. 兼容性与扩展建议

- 校验：当前协议无 CRC/校验和，依赖头尾同步与长度约束。建议未来在包尾前增加 1~2 字节校验以提升鲁棒性。
- 版本：可在 Mode 后新增 1 字节版本号或在 Payload 前保留 1 字节扩展标志，逐步演进而不影响现有解析。
- 单位与坐标系：请在双方联调时明确 Depth_d、Yaw_d、x/y/z/roll/pitch/yaw 的单位与坐标系定义（NED/ENU、机体/世界），避免歧义。
- 限幅与饱和：taw_* 为 int8_t，建议在 UUV 侧进行限幅与安全检查。

---

## 8. 快速对照表

- 包头/包尾：0xFE / 0xFF
- Mode 合法值：0x01 ~ 0x05（0x05 为“全自主模式”）
- Float 字节序：大端（Big-Endian）
- 上位机→UUV（0x01~0x04）：6×int8 + Depth_d(float) + Yaw_d(float)
- 上位机→UUV（0x05）：6×float（pos1..pos6）
- UUV→上位机：6×float（x,y,z,roll,pitch,yaw）
