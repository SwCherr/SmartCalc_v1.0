QT       += core gui
#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Model/credit.c \
    ../Model/deposit.c \
    ../Model/model.c \
    ../Model/polish_notation.c \
    ../Model/stack.c \
    creditwindow.cpp \
    depositwindow.cpp \
    main.cpp \
    mainwindow.cpp \
    qcustomplot.cpp \


HEADERS += \
    ../Model/model.h \
    creditwindow.h \
    depositwindow.h \
    mainwindow.h \
    qcustomplot.h \

FORMS += \
    creditwindow.ui \
    depositwindow.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
