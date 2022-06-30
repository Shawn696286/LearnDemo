#ifndef CMAINWIN_H
#define CMAINWIN_H

#include <QWidget>
#include "cplay_thread.h"

class CPlayThread;
QT_BEGIN_NAMESPACE
namespace Ui {
class CMainWin;
}
QT_END_NAMESPACE

class CMainWin : public QWidget
{
    Q_OBJECT

public:
    CMainWin(QWidget* parent = nullptr);
    ~CMainWin();
    void Repaint(AVFrame* pFrame);
private slots:
    void on_toolB_Play_clicked();

    void on_toolB_Stop_clicked();

    void on_toolB_Open_clicked();

    void on_toolB_test_clicked();

private:
    Ui::CMainWin* ui;
    CPlayThread* m_pPlayThread;
};

#endif // CMAINWIN_H
