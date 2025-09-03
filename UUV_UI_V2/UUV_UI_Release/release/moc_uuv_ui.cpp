/****************************************************************************
** Meta object code from reading C++ file 'uuv_ui.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.9.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../uuv_ui.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'uuv_ui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.9.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN6UUV_UIE_t {};
} // unnamed namespace

template <> constexpr inline auto UUV_UI::qt_create_metaobjectdata<qt_meta_tag_ZN6UUV_UIE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "UUV_UI",
        "requestCsvData",
        "",
        "rowIndex",
        "currentTimerUpdate",
        "on_pushButton_scan_clicked",
        "on_pushButton_open_clicked",
        "on_comboBox_TransPeriod_currentIndexChanged",
        "on_pushButton_RClear_clicked",
        "on_pushButton_TClear_clicked",
        "on_comboBox_WorkMode_currentIndexChanged",
        "on_horizontalSlider_cv_valueChanged",
        "value",
        "on_doubleSpinBox_Depth_valueChanged",
        "arg1",
        "on_horizontalSlider_Depth_valueChanged",
        "on_doubleSpinBox_Heading_valueChanged",
        "on_horizontalSlider_Heading_valueChanged",
        "keyPressEvent",
        "QKeyEvent*",
        "event",
        "keyReleaseEvent",
        "updateJoystickData",
        "on_checkBox_GamePad_checkStateChanged",
        "TransmitInfo",
        "onSerialErrorOccurred",
        "errorMessage",
        "onSerialDataReceived",
        "x",
        "y",
        "z",
        "roll",
        "pitch",
        "yaw",
        "updateTransValues",
        "on_pushButton_OpenFile_clicked",
        "onTransWidgetDestroyed",
        "handleCsvData",
        "p1",
        "p2",
        "p3",
        "p4",
        "p5",
        "p6"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'requestCsvData'
        QtMocHelpers::SignalData<void(int)>(1, 2, QMC::AccessPublic, QMetaType::Void, {{
            { QMetaType::Int, 3 },
        }}),
        // Slot 'currentTimerUpdate'
        QtMocHelpers::SlotData<void()>(4, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_scan_clicked'
        QtMocHelpers::SlotData<void()>(5, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_open_clicked'
        QtMocHelpers::SlotData<void()>(6, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_comboBox_TransPeriod_currentIndexChanged'
        QtMocHelpers::SlotData<void()>(7, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_RClear_clicked'
        QtMocHelpers::SlotData<void()>(8, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_TClear_clicked'
        QtMocHelpers::SlotData<void()>(9, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_comboBox_WorkMode_currentIndexChanged'
        QtMocHelpers::SlotData<void()>(10, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_horizontalSlider_cv_valueChanged'
        QtMocHelpers::SlotData<void(int)>(11, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 12 },
        }}),
        // Slot 'on_doubleSpinBox_Depth_valueChanged'
        QtMocHelpers::SlotData<void(double)>(13, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Double, 14 },
        }}),
        // Slot 'on_horizontalSlider_Depth_valueChanged'
        QtMocHelpers::SlotData<void(int)>(15, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 12 },
        }}),
        // Slot 'on_doubleSpinBox_Heading_valueChanged'
        QtMocHelpers::SlotData<void(double)>(16, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Double, 14 },
        }}),
        // Slot 'on_horizontalSlider_Heading_valueChanged'
        QtMocHelpers::SlotData<void(int)>(17, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Int, 12 },
        }}),
        // Slot 'keyPressEvent'
        QtMocHelpers::SlotData<void(QKeyEvent *)>(18, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 19, 20 },
        }}),
        // Slot 'keyReleaseEvent'
        QtMocHelpers::SlotData<void(QKeyEvent *)>(21, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { 0x80000000 | 19, 20 },
        }}),
        // Slot 'updateJoystickData'
        QtMocHelpers::SlotData<void()>(22, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_checkBox_GamePad_checkStateChanged'
        QtMocHelpers::SlotData<void()>(23, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'TransmitInfo'
        QtMocHelpers::SlotData<void()>(24, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onSerialErrorOccurred'
        QtMocHelpers::SlotData<void(const QString &)>(25, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::QString, 26 },
        }}),
        // Slot 'onSerialDataReceived'
        QtMocHelpers::SlotData<void(float, float, float, float, float, float)>(27, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Float, 28 }, { QMetaType::Float, 29 }, { QMetaType::Float, 30 }, { QMetaType::Float, 31 },
            { QMetaType::Float, 32 }, { QMetaType::Float, 33 },
        }}),
        // Slot 'updateTransValues'
        QtMocHelpers::SlotData<void()>(34, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'on_pushButton_OpenFile_clicked'
        QtMocHelpers::SlotData<void()>(35, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'onTransWidgetDestroyed'
        QtMocHelpers::SlotData<void()>(36, 2, QMC::AccessPrivate, QMetaType::Void),
        // Slot 'handleCsvData'
        QtMocHelpers::SlotData<void(float, float, float, float, float, float)>(37, 2, QMC::AccessPrivate, QMetaType::Void, {{
            { QMetaType::Float, 38 }, { QMetaType::Float, 39 }, { QMetaType::Float, 40 }, { QMetaType::Float, 41 },
            { QMetaType::Float, 42 }, { QMetaType::Float, 43 },
        }}),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    return QtMocHelpers::metaObjectData<UUV_UI, qt_meta_tag_ZN6UUV_UIE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums);
}
Q_CONSTINIT const QMetaObject UUV_UI::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6UUV_UIE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6UUV_UIE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN6UUV_UIE_t>.metaTypes,
    nullptr
} };

void UUV_UI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<UUV_UI *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->requestCsvData((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 1: _t->currentTimerUpdate(); break;
        case 2: _t->on_pushButton_scan_clicked(); break;
        case 3: _t->on_pushButton_open_clicked(); break;
        case 4: _t->on_comboBox_TransPeriod_currentIndexChanged(); break;
        case 5: _t->on_pushButton_RClear_clicked(); break;
        case 6: _t->on_pushButton_TClear_clicked(); break;
        case 7: _t->on_comboBox_WorkMode_currentIndexChanged(); break;
        case 8: _t->on_horizontalSlider_cv_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 9: _t->on_doubleSpinBox_Depth_valueChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 10: _t->on_horizontalSlider_Depth_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 11: _t->on_doubleSpinBox_Heading_valueChanged((*reinterpret_cast< std::add_pointer_t<double>>(_a[1]))); break;
        case 12: _t->on_horizontalSlider_Heading_valueChanged((*reinterpret_cast< std::add_pointer_t<int>>(_a[1]))); break;
        case 13: _t->keyPressEvent((*reinterpret_cast< std::add_pointer_t<QKeyEvent*>>(_a[1]))); break;
        case 14: _t->keyReleaseEvent((*reinterpret_cast< std::add_pointer_t<QKeyEvent*>>(_a[1]))); break;
        case 15: _t->updateJoystickData(); break;
        case 16: _t->on_checkBox_GamePad_checkStateChanged(); break;
        case 17: _t->TransmitInfo(); break;
        case 18: _t->onSerialErrorOccurred((*reinterpret_cast< std::add_pointer_t<QString>>(_a[1]))); break;
        case 19: _t->onSerialDataReceived((*reinterpret_cast< std::add_pointer_t<float>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[6]))); break;
        case 20: _t->updateTransValues(); break;
        case 21: _t->on_pushButton_OpenFile_clicked(); break;
        case 22: _t->onTransWidgetDestroyed(); break;
        case 23: _t->handleCsvData((*reinterpret_cast< std::add_pointer_t<float>>(_a[1])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[2])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[3])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[4])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[5])),(*reinterpret_cast< std::add_pointer_t<float>>(_a[6]))); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (UUV_UI::*)(int )>(_a, &UUV_UI::requestCsvData, 0))
            return;
    }
}

const QMetaObject *UUV_UI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *UUV_UI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN6UUV_UIE_t>.strings))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int UUV_UI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 24)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 24;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 24)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 24;
    }
    return _id;
}

// SIGNAL 0
void UUV_UI::requestCsvData(int _t1)
{
    QMetaObject::activate<void>(this, &staticMetaObject, 0, nullptr, _t1);
}
QT_WARNING_POP
