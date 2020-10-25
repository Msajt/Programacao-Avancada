/********************************************************************************
** Form generated from reading UI file 'incluirdvd.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INCLUIRDVD_H
#define UI_INCLUIRDVD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_IncluirDVD
{
public:
    QLabel *titleLabel;
    QLineEdit *nomeLineEdit;
    QLineEdit *precoLineEdit;
    QLabel *nomeLabel;
    QLineEdit *duracaoLineEdit;
    QLabel *duracaoLabel;
    QLabel *precoLabel;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *IncluirDVD)
    {
        if (IncluirDVD->objectName().isEmpty())
            IncluirDVD->setObjectName(QString::fromUtf8("IncluirDVD"));
        IncluirDVD->resize(300, 200);
        titleLabel = new QLabel(IncluirDVD);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(0, 0, 300, 20));
        titleLabel->setAlignment(Qt::AlignCenter);
        nomeLineEdit = new QLineEdit(IncluirDVD);
        nomeLineEdit->setObjectName(QString::fromUtf8("nomeLineEdit"));
        nomeLineEdit->setGeometry(QRect(100, 60, 180, 20));
        precoLineEdit = new QLineEdit(IncluirDVD);
        precoLineEdit->setObjectName(QString::fromUtf8("precoLineEdit"));
        precoLineEdit->setGeometry(QRect(100, 90, 180, 20));
        nomeLabel = new QLabel(IncluirDVD);
        nomeLabel->setObjectName(QString::fromUtf8("nomeLabel"));
        nomeLabel->setGeometry(QRect(20, 60, 47, 13));
        duracaoLineEdit = new QLineEdit(IncluirDVD);
        duracaoLineEdit->setObjectName(QString::fromUtf8("duracaoLineEdit"));
        duracaoLineEdit->setGeometry(QRect(100, 120, 180, 20));
        duracaoLabel = new QLabel(IncluirDVD);
        duracaoLabel->setObjectName(QString::fromUtf8("duracaoLabel"));
        duracaoLabel->setGeometry(QRect(20, 120, 47, 13));
        precoLabel = new QLabel(IncluirDVD);
        precoLabel->setObjectName(QString::fromUtf8("precoLabel"));
        precoLabel->setGeometry(QRect(20, 90, 47, 13));
        buttonBox = new QDialogButtonBox(IncluirDVD);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(70, 160, 156, 23));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(IncluirDVD);

        QMetaObject::connectSlotsByName(IncluirDVD);
    } // setupUi

    void retranslateUi(QDialog *IncluirDVD)
    {
        IncluirDVD->setWindowTitle(QCoreApplication::translate("IncluirDVD", "Dialog", nullptr));
        titleLabel->setText(QCoreApplication::translate("IncluirDVD", "INCLUIR NOVO DVD", nullptr));
        nomeLabel->setText(QCoreApplication::translate("IncluirDVD", "Nome:", nullptr));
        duracaoLabel->setText(QCoreApplication::translate("IncluirDVD", "Dura\303\247\303\243o:", nullptr));
        precoLabel->setText(QCoreApplication::translate("IncluirDVD", "Pre\303\247o:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IncluirDVD: public Ui_IncluirDVD {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INCLUIRDVD_H
