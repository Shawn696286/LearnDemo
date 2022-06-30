#pragma once
#include <qthread.h>
#include "cdemux.h"
#include "idecode.h"
#include "ffmpeg_dxva2.h"
#include "D3DVidRender.h"
class CMainWin;

enum EDecodeMode
{
    Mode_Hard_Hard,         //< Ó²½â¡¢Ó²¼þäÖÈ¾
    Mode_Hard_Soft,         //< Ó²½â¡¢Èí¼þäÖÈ¾
};


class CPlayThread : public QThread
{
public:
    CPlayThread(CMainWin* pMainWin);
    ~CPlayThread();

    int Open(QString qstrFilename, EDecodeMode eMode);

    void run() override;

    void Stop();
    HWND m_pHwnd;
private:
    IDecode* m_pDecoder;
    CDemux m_oDemux;
    bool m_bPlay;
    CMainWin* m_pMainWin;
    EDecodeMode m_eMode;
};


