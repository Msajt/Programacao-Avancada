/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QGridLayout *gridLayout;
    QLabel *labelIpServidor;
    QLineEdit *lineEditIpServidor;
    QLabel *labelNomeUsuario;
    QLineEdit *lineEditNomeUsuario;
    QLabel *labelSenhaUsuario;
    QLineEdit *lineEditSenhaUsuario;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName(QString::fromUtf8("LoginDialog"));
        LoginDialog->resize(248, 125);
        gridLayout = new QGridLayout(LoginDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labelIpServidor = new QLabel(LoginDialog);
        labelIpServidor->setObjectName(QString::fromUtf8("labelIpServidor"));

        gridLayout->addWidget(labelIpServidor, 0, 0, 1, 1);

        lineEditIpServidor = new QLineEdit(LoginDialog);
        lineEditIpServidor->setObjectName(QString::fromUtf8("lineEditIpServidor"));

        gridLayout->addWidget(lineEditIpServidor, 0, 1, 1, 1);

        labelNomeUsuario = new QLabel(LoginDialog);
        labelNomeUsuario->setObjectName(QString::fromUtf8("labelNomeUsuario"));

        gridLayout->addWidget(labelNomeUsuario, 1, 0, 1, 1);

        lineEditNomeUsuario = new QLineEdit(LoginDialog);
        lineEditNomeUsuario->setObjectName(QString::fromUtf8("lineEditNomeUsuario"));

        gridLayout->addWidget(lineEditNomeUsuario, 1, 1, 1, 1);

        labelSenhaUsuario = new QLabel(LoginDialog);
        labelSenhaUsuario->setObjectName(QString::fromUtf8("labelSenhaUsuario"));

        gridLayout->addWidget(labelSenhaUsuario, 2, 0, 1, 1);

        lineEditSenhaUsuario = new QLineEdit(LoginDialog);
        lineEditSenhaUsuario->setObjectName(QString::fromUtf8("lineEditSenhaUsuario"));

        gridLayout->addWidget(lineEditSenhaUsuario, 2, 1, 1, 1);

        buttonBox = new QDialogButtonBox(LoginDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        gridLayout->addWidget(buttonBox, 3, 0, 1, 2);


        retranslateUi(LoginDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), LoginDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), LoginDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Criar ou conectar usu\303\241rio", nullptr));
        labelIpServidor->setText(QCoreApplication::translate("LoginDialog", "Servidor (IP):", nullptr));
        labelNomeUsuario->setText(QCoreApplication::translate("LoginDialog", "Usuario", nullptr));
        labelSenhaUsuario->setText(QCoreApplication::translate("LoginDialog", "Senha", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
