/********************************************************************************
** Form generated from reading UI file 'cmainwin.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMAINWIN_H
#define UI_CMAINWIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "cplayframe.h"

QT_BEGIN_NAMESPACE

class Ui_CMainWin
{
public:
    QGridLayout *gridLayout;
    CPlayFrame *frame_PlayWin;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLabel *label_Filename;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QToolButton *toolB_Open;
    QToolButton *toolB_Play;
    QToolButton *toolB_Stop;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *toolB_test;
    QLineEdit *lineE_test;
    QComboBox *comb_mode;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QWidget *CMainWin)
    {
        if (CMainWin->objectName().isEmpty())
            CMainWin->setObjectName(QString::fromUtf8("CMainWin"));
        CMainWin->resize(800, 600);
        gridLayout = new QGridLayout(CMainWin);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        frame_PlayWin = new CPlayFrame(CMainWin);
        frame_PlayWin->setObjectName(QString::fromUtf8("frame_PlayWin"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame_PlayWin->sizePolicy().hasHeightForWidth());
        frame_PlayWin->setSizePolicy(sizePolicy);
        frame_PlayWin->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        frame_PlayWin->setFrameShape(QFrame::StyledPanel);
        frame_PlayWin->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(frame_PlayWin, 2, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(CMainWin);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        label_Filename = new QLabel(CMainWin);
        label_Filename->setObjectName(QString::fromUtf8("label_Filename"));

        horizontalLayout_2->addWidget(label_Filename);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        toolB_Open = new QToolButton(CMainWin);
        toolB_Open->setObjectName(QString::fromUtf8("toolB_Open"));

        horizontalLayout->addWidget(toolB_Open);

        toolB_Play = new QToolButton(CMainWin);
        toolB_Play->setObjectName(QString::fromUtf8("toolB_Play"));

        horizontalLayout->addWidget(toolB_Play);

        toolB_Stop = new QToolButton(CMainWin);
        toolB_Stop->setObjectName(QString::fromUtf8("toolB_Stop"));

        horizontalLayout->addWidget(toolB_Stop);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        toolB_test = new QToolButton(CMainWin);
        toolB_test->setObjectName(QString::fromUtf8("toolB_test"));

        horizontalLayout_3->addWidget(toolB_test);

        lineE_test = new QLineEdit(CMainWin);
        lineE_test->setObjectName(QString::fromUtf8("lineE_test"));

        horizontalLayout_3->addWidget(lineE_test);

        comb_mode = new QComboBox(CMainWin);
        comb_mode->addItem(QString());
        comb_mode->addItem(QString());
        comb_mode->setObjectName(QString::fromUtf8("comb_mode"));

        horizontalLayout_3->addWidget(comb_mode);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        gridLayout->addLayout(horizontalLayout_3, 1, 0, 1, 1);


        retranslateUi(CMainWin);

        QMetaObject::connectSlotsByName(CMainWin);
    } // setupUi

    void retranslateUi(QWidget *CMainWin)
    {
        CMainWin->setWindowTitle(QApplication::translate("CMainWin", "CMainWin", nullptr));
        label->setText(QApplication::translate("CMainWin", "\346\226\207\344\273\266\345\220\215:", nullptr));
        label_Filename->setText(QString());
        toolB_Open->setText(QApplication::translate("CMainWin", "open", nullptr));
        toolB_Play->setText(QApplication::translate("CMainWin", "play", nullptr));
        toolB_Stop->setText(QApplication::translate("CMainWin", "stop", nullptr));
        toolB_test->setText(QApplication::translate("CMainWin", "test", nullptr));
        lineE_test->setText(QApplication::translate("CMainWin", "10", nullptr));
        comb_mode->setItemText(0, QApplication::translate("CMainWin", "\347\241\254\350\247\243\347\240\201+\347\241\254\346\270\262\346\237\223", nullptr));
        comb_mode->setItemText(1, QApplication::translate("CMainWin", "\347\241\254\350\247\243\347\240\201+\350\275\257\346\270\262\346\237\223", nullptr));

    } // retranslateUi

};

namespace Ui {
    class CMainWin: public Ui_CMainWin {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMAINWIN_H
