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
    QString qstrFilename = QFileDialog::getOpenFileName(this, tr("选择视频文件"));

    if(qstrFilename.isEmpty())
    {
        return;
    }

    int nRet = m_pPlayThread->Open(qstrFilename);

}

void CMainWin::Repaint(AVFrame* pFrame)
{
    ui->frame_PlayWin->Repaint(pFrame);
}