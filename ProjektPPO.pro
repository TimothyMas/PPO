QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainppo.cpp

HEADERS += \
        mainppo.h \
        patientprofile.h \
        ui_mainppo.h

FORMS += \
        mainppo.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    darkmode.qss \
    data_analysis.py \
    lightmode.qss
