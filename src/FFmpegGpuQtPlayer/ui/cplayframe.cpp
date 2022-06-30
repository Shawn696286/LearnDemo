#include "cplayframe.h"
#include "ui_cplayframe.h"

CPlayFrame::CPlayFrame(QWidget* parent) :
    QFrame(parent),
    ui(new Ui::CPlayFrame)
{
    ui->setupUi(this);
    m_image = nullptr;

    m_nLastW = 0;
    m_nLastH = 0;
}

CPlayFrame::~CPlayFrame()
{
    delete ui;
}

void CPlayFrame::Repaint(AVFrame* pFrame)
{
    {
        std::lock_guard<std::mutex> oGuard(m_oMtxImage);

        if(m_nLastW != width() || m_nLastH != height())
        {
            char* buf = NULL;

            if(m_image)
            {
                buf = (char*)m_image->bits();
                delete[] buf;
                delete m_image;
                m_image = NULL;
            }

            m_nLastW = width();
            m_nLastH = height();
            buf = new char[m_nLastW * m_nLastH * 4];
            m_image = new QImage((uchar*)buf, m_nLastW, m_nLastH, QImage::Format_ARGB32);
        }

        if(m_image)
        {
            YuvToRgb(pFrame, (char*)m_image->bits(), m_image->width(), m_image->height());
        }
    }
    FreeFrame(pFrame);
    update();
}


void CPlayFrame::paintEvent(QPaintEvent* e)
{
    QPainter painter;
    painter.begin(this);
    {
        std::lock_guard<std::mutex> oGuard(m_oMtxImage);

        if(m_image)
        {
            painter.drawImage(QPoint(0, 0), *m_image);
        }
    }

    painter.end();
}