/********************************************************************************
** Form generated from reading UI file 'novaconversa.ui'
**
** Created by: Qt User Interface Compiler version 5.15.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NOVACONVERSA_H
#define UI_NOVACONVERSA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_NovaConversa
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *labelConversa;
    QLineEdit *lineEditConversa;

    void setupUi(QDialog *NovaConversa)
    {
        if (NovaConversa->objectName().isEmpty())
            NovaConversa->setObjectName(QString::fromUtf8("NovaConversa"));
        NovaConversa->resize(210, 110);
        buttonBox = new QDialogButtonBox(NovaConversa);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(-140, 60, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        labelConversa = new QLabel(NovaConversa);
        labelConversa->setObjectName(QString::fromUtf8("labelConversa"));
        labelConversa->setGeometry(QRect(10, 10, 51, 16));
        lineEditConversa = new QLineEdit(NovaConversa);
        lineEditConversa->setObjectName(QString::fromUtf8("lineEditConversa"));
        lineEditConversa->setGeometry(QRect(80, 10, 120, 20));

        retranslateUi(NovaConversa);
        QObject::connect(buttonBox, SIGNAL(accepted()), NovaConversa, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), NovaConversa, SLOT(reject()));

        QMetaObject::connectSlotsByName(NovaConversa);
    } // setupUi

    void retranslateUi(QDialog *NovaConversa)
    {
        NovaConversa->setWindowTitle(QCoreApplication::translate("NovaConversa", "Nova Conversa", nullptr));
        labelConversa->setText(QCoreApplication::translate("NovaConversa", "Conversa:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NovaConversa: public Ui_NovaConversa {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NOVACONVERSA_H
