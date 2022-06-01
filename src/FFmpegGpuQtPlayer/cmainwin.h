#ifndef CMAINWIN_H
#define CMAINWIN_H

#include <QWidget>
#include <qthread.h>
#include "cdemux.h"
#include "idecode.h"

class CPlayThread;
QT_BEGIN_NAMESPACE
namespace Ui {
class CMainWin;
}
QT_END_NAMESPACE

class CMainWin : public QWidget
{
    Q_OBJECT

public: CMainWin(QWidget* parent = nullptr);
    ~CMainWin();
    void Repaint(AVFrame* pFrame);
private slots:
    void on_toolB_Play_clicked();

    void on_toolB_Stop_clicked();

    void on_toolB_Open_clicked();

private:
    Ui::CMainWin* ui;
    CPlayThread* m_pPlayThread;
};

class CPlayThread: public QThread
{
public:
    CPlayThread(CMainWin* pMainWin)
    {
        m_bPlay = false;
        m_pDecoder = nullptr;
        m_pMainWin = pMainWin;
    }
    ~CPlayThread() {}

    int Open(QString qstrFilename)
    {
        return m_oDemux.Open(qstrFilename.toStdString());
    }

    void run() override
    {
        if(m_pDecoder)
        {
            return;
        }

        m_pDecoder = new IDecode;

        if(!m_pDecoder)
        {
            return;
        }

        auto pParam = m_oDemux.CopyVPara();

        if(!pParam)
        {
            return;
        }

        m_pDecoder->Open(pParam);

        m_bPlay = true;

        while(m_bPlay)
        {
            auto pPacket = m_oDemux.ReadVideo();

            if(pPacket)
            {
                if(Ret_Y_OK != m_pDecoder->Send(pPacket))
                {
                    std::this_thread::sleep_for(std::chrono::milliseconds(1));
                    continue;
                }

                //一次send 多次recv
                while(m_bPlay)
                {
                    AVFrame* pFrame = m_pDecoder->Recv();

                    if(!pFrame)
                    {
                        break;
                    }

                    //显示视频
                    m_pMainWin->Repaint(pFrame);
                }
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(40));
        }

        if(m_pDecoder)
        {
            delete m_pDecoder;
        }
    }

    void Stop()
    {
        m_bPlay = false;
    }
private:
    IDecode* m_pDecoder;
    CDemux m_oDemux;
    bool m_bPlay;
    CMainWin* m_pMainWin;
};

#endif // CMAINWIN_H
