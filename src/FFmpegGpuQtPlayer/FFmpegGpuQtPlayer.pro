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
    core/D3DVidRender.cpp \
    core/cd3dx_dxva2_render.cpp \
    core/cd3dx_spirte_render.cpp \
    core/cdecode_dxva2.cpp \
    core/cdecode_hard.cpp \
    core/cdemux.cpp \
    core/csws.cpp \
    core/ffmpeg_dxva2.cpp \
    core/idecode.cpp \
    core/irender.cpp \
    play/cplay_thread.cpp \
    ui/cmainwin.cpp \
    ui/cplayframe.cpp

HEADERS += \
    core/D3DVidRender.h \
    core/cd3dx_dxva2_render.h \
    core/cd3dx_spirte_render.h \
    core/cdecode_dxva2.h \
    core/cdecode_hard.h \
    core/cdemux.h \
    core/csws.h \
    core/ffmpeg_dxva2.h \
    core/idecode.h \
    core/irender.h \
    play/cplay_thread.h \
    ui/cmainwin.h \
    ui/cplayframe.h

FORMS += \
    ui/cmainwin.ui \
    ui/cplayframe.ui

INCLUDEPATH += \
    core \
    play \
    ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


