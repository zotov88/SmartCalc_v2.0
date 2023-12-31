QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    controller/controller.cc \
    model/model.cc \
    view/creditcalc.cc \
    view/depositcalc.cc \
    view/qcustomplot.cc \
    view/mainwindow.cc

HEADERS += \
    controller/controller.h \
    model/model.h \
    view/creditcalc.h \
    view/depositcalc.h \
    view/qcustomplot.h \
    view/mainwindow.h

FORMS += \
    view/creditcalc.ui \
    view/depositcalc.ui \
    view/mainwindow.ui

INCLUDEPATH += $$PWD/view

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resources.qrc
