#include "cmainwin.h"
#include "ui_cmainwin.h"
#include "public.h"

#include <qfiledialog.h>




CMainWin::CMainWin(QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::CMainWin)
{
    ui->setupUi(this);
    LOGY_INFO("CMainWin construct");
    m_pPlayThread = new CPlayThread(this);
}

CMainWin::~CMainWin()
{
    delete ui;

    if(m_pPlayThread)
    {
        delete m_pPlayThread;
        m_pPlayThread = nullptr;
    }
}


void CMainWin::on_toolB_Play_clicked()
{
    m_pPlayThread->start();
}

void CMainWin::on_toolB_Stop_clicked()
{

    m_pPlayThread->Stop();
}

void CMainWin::on_toolB_Open_clicked()
{
    //选择文件
    QString qstrFilename = QFileDialog::getOpenFileName(this, tr("select file"));

    if(qstrFilename.isEmpty())
    {
        return;
    }

    ui->label_Filename->setText(qstrFilename);
    int nMode = ui->comb_mode->currentIndex();
    int nRet = m_pPlayThread->Open(qstrFilename, (EDecodeMode)nMode);
    m_pPlayThread->m_pHwnd = (HWND)ui->frame_PlayWin->winId();
}

void CMainWin::Repaint(AVFrame* pFrame)
{
    ui->frame_PlayWin->Repaint(pFrame);
}

void CMainWin::on_toolB_test_clicked()
{
    QString qstrFilename = ui->label_Filename->text();

    if(qstrFilename.isEmpty())
    {
        return;
    }

    int nCount = ui->lineE_test->text().toInt();
    int nMode = ui->comb_mode->currentIndex();

    while(nCount-- > 0)
    {
        int nRet = m_pPlayThread->Open(qstrFilename, (EDecodeMode)nMode);
        m_pPlayThread->m_pHwnd = (HWND)ui->frame_PlayWin->winId();
        m_pPlayThread->start();
        Sleep(1000);
        m_pPlayThread->Stop();
        Sleep(1000);
    }
}
