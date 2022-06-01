set QT_BIN_PATH=C:\Qt\Qt5.12.12\5.12.12\msvc2017_64\bin
set SRC_PATH=D:\workspace\code\github\LearnDemo\src\FFmpegGpuQtPlayer

del /f /s /q %SRC_PATH%\ui_*.h
del /f /s /q %SRC_PATH%\moc_*.cpp

%QT_BIN_PATH%\uic.exe %SRC_PATH%\cmainwin.ui		-o %SRC_PATH%\ui_cmainwin.h
%QT_BIN_PATH%\uic.exe %SRC_PATH%\cplayframe.ui		-o %SRC_PATH%\ui_cplayframe.h

%QT_BIN_PATH%\moc.exe %SRC_PATH%\cmainwin.h			-o %SRC_PATH%\moc_cmainwin.cpp
%QT_BIN_PATH%\moc.exe %SRC_PATH%\cplayframe.h		-o %SRC_PATH%\moc_cplayframe.cpp