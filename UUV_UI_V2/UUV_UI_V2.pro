QT       += core gui
QT       += serialport
LIBS     += -lXInput

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    csvworker.cpp \
    ctrans.cpp \
    main.cpp \
    serial_Receive_worker.cpp \
    serial_Transmit_worker.cpp \
    uuv_log_recorder.cpp \
    uuv_ui.cpp

HEADERS += \
    csvworker.h \
    ctrans.h \
    serial_Receive_worker.h \
    serial_Transmit_worker.h \
    uuv_log_recorder.h \
    uuv_ui.h

FORMS += \
    ctrans.ui \
    uuv_ui.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=

RESOURCES += \
    Image/Gamepad.qrc
