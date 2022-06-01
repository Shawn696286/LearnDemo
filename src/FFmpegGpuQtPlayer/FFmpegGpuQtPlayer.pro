QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = player_ffmpeg_qt_gpu
CONFIG += c++11

contains(QT_ARCH, x86_64){
        message("64-bit")
}else{
        message("32-bit")
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    cplayframe.cpp \
    main.cpp \
    cmainwin.cpp

HEADERS += \
    cmainwin.h \
    cplayframe.h \
    public.h

FORMS += \
    cmainwin.ui \
    cplayframe.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


