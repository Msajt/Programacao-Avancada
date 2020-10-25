/********************************************************************************
** Form generated from reading UI file 'incluirlivro.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INCLUIRLIVRO_H
#define UI_INCLUIRLIVRO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_IncluirLivro
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *titleLabel;
    QLabel *nomeLabel;
    QLabel *precoLabel;
    QLabel *autorLabel;
    QLineEdit *nomeLineEdit;
    QLineEdit *precoLineEdit;
    QLineEdit *autorLineEdit;

    void setupUi(QDialog *IncluirLivro)
    {
        if (IncluirLivro->objectName().isEmpty())
            IncluirLivro->setObjectName(QString::fromUtf8("IncluirLivro"));
        IncluirLivro->resize(300, 200);
        buttonBox = new QDialogButtonBox(IncluirLivro);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(0, 160, 300, 23));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);
        titleLabel = new QLabel(IncluirLivro);
        titleLabel->setObjectName(QString::fromUtf8("titleLabel"));
        titleLabel->setGeometry(QRect(0, 0, 300, 20));
        titleLabel->setAlignment(Qt::AlignCenter);
        nomeLabel = new QLabel(IncluirLivro);
        nomeLabel->setObjectName(QString::fromUtf8("nomeLabel"));
        nomeLabel->setGeometry(QRect(20, 60, 47, 13));
        precoLabel = new QLabel(IncluirLivro);
        precoLabel->setObjectName(QString::fromUtf8("precoLabel"));
        precoLabel->setGeometry(QRect(20, 90, 47, 13));
        autorLabel = new QLabel(IncluirLivro);
        autorLabel->setObjectName(QString::fromUtf8("autorLabel"));
        autorLabel->setGeometry(QRect(20, 120, 47, 13));
        nomeLineEdit = new QLineEdit(IncluirLivro);
        nomeLineEdit->setObjectName(QString::fromUtf8("nomeLineEdit"));
        nomeLineEdit->setGeometry(QRect(100, 60, 180, 20));
        precoLineEdit = new QLineEdit(IncluirLivro);
        precoLineEdit->setObjectName(QString::fromUtf8("precoLineEdit"));
        precoLineEdit->setGeometry(QRect(100, 90, 180, 20));
        autorLineEdit = new QLineEdit(IncluirLivro);
        autorLineEdit->setObjectName(QString::fromUtf8("autorLineEdit"));
        autorLineEdit->setGeometry(QRect(100, 120, 180, 20));

        retranslateUi(IncluirLivro);
        QObject::connect(buttonBox, SIGNAL(accepted()), IncluirLivro, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), IncluirLivro, SLOT(reject()));

        QMetaObject::connectSlotsByName(IncluirLivro);
    } // setupUi

    void retranslateUi(QDialog *IncluirLivro)
    {
        IncluirLivro->setWindowTitle(QCoreApplication::translate("IncluirLivro", "Incluir Livro", nullptr));
        titleLabel->setText(QCoreApplication::translate("IncluirLivro", "INCLUIR NOVO LIVRO", nullptr));
        nomeLabel->setText(QCoreApplication::translate("IncluirLivro", "Nome:", nullptr));
        precoLabel->setText(QCoreApplication::translate("IncluirLivro", "Pre\303\247o:", nullptr));
        autorLabel->setText(QCoreApplication::translate("IncluirLivro", "Autor:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class IncluirLivro: public Ui_IncluirLivro {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INCLUIRLIVRO_H
