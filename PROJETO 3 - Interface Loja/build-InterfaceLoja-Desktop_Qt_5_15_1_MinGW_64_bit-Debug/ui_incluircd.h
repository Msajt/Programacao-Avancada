/********************************************************************************
** Form generated from reading UI file 'incluircd.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INCLUIRCD_H
#define UI_INCLUIRCD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_IncluirCD
{
public:
    QLabel *titleLabel;
    QLineEdit *nomeLineEdit;
    QLineEdit *precoLineEdit;
    QLabel *nomeLabel;
    QLineEdit *faixasLineEdit;
    QLabel *faixasLabel;
    QLabel *precoLabel;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *IncluirCD)
    {
        if (IncluirCD->objectName().isEmpty())
            IncluirCD->setObjectName(QString::fromUtf8("IncluirCD"));
        IncluirCD->resize(300, 200);
        titleLabel = new QLabel(IncluirCD);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(0, 0, 300, 20));
        titleLabel->setAlignment(Qt::AlignCenter);
        nomeLineEdit = new QLineEdit(IncluirCD);
        nomeLineEdit->setObjectName(QString::fromUtf8("nomeLineEdit"));
        nomeLineEdit->setGeometry(QRect(100, 60, 180, 20));
        precoLineEdit = new QLineEdit(IncluirCD);
        precoLineEdit->setObjectName(QString::fromUtf8("precoLineEdit"));
        precoLineEdit->setGeometry(QRect(100, 90, 180, 20));
        nomeLabel = new QLabel(IncluirCD);
        nomeLabel->setObjectName(QString::fromUtf8("nomeLabel"));
        nomeLabel->setGeometry(QRect(20, 60, 47, 13));
        faixasLineEdit = new QLineEdit(IncluirCD);
        faixasLineEdit->setObjectName(QString::fromUtf8("faixasLineEdit"));
        faixasLineEdit->setGeometry(QRect(100, 120, 180, 20));
        faixasLabel = new QLabel(IncluirCD);
        faixasLabel->setObjectName(QString::fromUtf8("faixasLabel"));
        faixasLabel->setGeometry(QRect(20, 120, 71, 16));
        precoLabel = new QLabel(IncluirCD);
        precoLabel->setObjectName(QString::fromUtf8("precoLabel"));
        precoLabel->setGeometry(QRect(20, 90, 47, 13));
        buttonBox = new QDialogButtonBox(IncluirCD);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(70, 160, 156, 23));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(IncluirCD);

        QMetaObject::connectSlotsByName(IncluirCD);
    } // setupUi

    void retranslateUi(QDialog *IncluirCD)
    {
        IncluirCD->setWindowTitle(QCoreApplication::translate("IncluirCD", "Incluir CD", nullptr));
        titleLabel->setText(QCoreApplication::translate("IncluirCD", "INCLUIR NOVO CD", nullptr));
        nomeLabel->setText(QCoreApplication::translate("IncluirCD", "Nome:", nullptr));
        faixasLabel->setText(QCoreApplication::translate("IncluirCD", "N\302\260 de faixas:", nullptr));
        precoLabel->setText(QCoreApplication::translate("IncluirCD", "Pre\303\247o:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IncluirCD: public Ui_IncluirCD {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INCLUIRCD_H
