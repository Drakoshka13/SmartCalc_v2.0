QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
ICON = ../icon/calc2.png

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../controller/s21_controller.cc \
    ../model/s21_credit_calc.cc \
    ../model/s21_deposit_calc.cc \
    ../model/s21_model.cc \
    main.cpp \
    ../view/s21_view.cc \
    qcustomplot.cpp

HEADERS += \
    ../controller/s21_controller.h \
    ../model/s21_model.h \
    ../view/s21_view.h \
    qcustomplot.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
