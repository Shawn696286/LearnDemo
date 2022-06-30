#ifndef CPLAYFRAME_H
#define CPLAYFRAME_H

#include <QFrame>
#include <QResizeEvent>
#include <QPainter>
#include <mutex>
#include "irender.h"

namespace Ui {
class CPlayFrame;
}

class CPlayFrame : public QFrame, public IRender
{
    Q_OBJECT

public:
    explicit CPlayFrame(QWidget* parent = nullptr);
    ~CPlayFrame();

    void Repaint(AVFrame* pFrame);

    virtual void paintEvent(QPaintEvent* e);
private:
    Ui::CPlayFrame* ui;
    QImage* m_image;

    int m_nLastW;
    int m_nLastH;

    std::mutex m_oMtxImage;
};

#endif // CPLAYFRAME_H
