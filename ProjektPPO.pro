QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainppo.cpp

HEADERS += \
        MachineLearningResultDialog.h \
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
    images/darkmode_icon.png \
    images/exit_icon.png \
    images/lightmode_icon.png \
    images/medgen.png \
    lightmode.qss \
    machine_learning.py \
    theme/darkmode.qss \
    theme/lightmode.qss
