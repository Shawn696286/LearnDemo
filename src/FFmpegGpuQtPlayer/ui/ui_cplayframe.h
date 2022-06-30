/********************************************************************************
** Form generated from reading UI file 'cplayframe.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CPLAYFRAME_H
#define UI_CPLAYFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>

QT_BEGIN_NAMESPACE

class Ui_CPlayFrame
{
public:

    void setupUi(QFrame *CPlayFrame)
    {
        if (CPlayFrame->objectName().isEmpty())
            CPlayFrame->setObjectName(QString::fromUtf8("CPlayFrame"));
        CPlayFrame->resize(400, 300);

        retranslateUi(CPlayFrame);

        QMetaObject::connectSlotsByName(CPlayFrame);
    } // setupUi

    void retranslateUi(QFrame *CPlayFrame)
    {
        CPlayFrame->setWindowTitle(QApplication::translate("CPlayFrame", "Frame", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CPlayFrame: public Ui_CPlayFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CPLAYFRAME_H
