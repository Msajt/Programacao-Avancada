/********************************************************************************
** Form generated from reading UI file 'newcircuito.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWCIRCUITO_H
#define UI_NEWCIRCUITO_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_newCircuito
{
public:
    QDialogButtonBox *buttonBox;
    QSpinBox *entradasSpinBox;
    QLabel *entradasLabel;
    QLabel *saidasLabel;
    QLabel *portasLabel;
    QSpinBox *saidasSpinBox;
    QSpinBox *portasSpinBox;

    void setupUi(QDialog *newCircuito)
    {
        if (newCircuito->objectName().isEmpty())
            newCircuito->setObjectName(QString::fromUtf8("newCircuito"));
        newCircuito->resize(220, 140);
        buttonBox = new QDialogButtonBox(newCircuito);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(0, 100, 221, 41));
        buttonBox->setLayoutDirection(Qt::LeftToRight);
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);
        entradasSpinBox = new QSpinBox(newCircuito);
        entradasSpinBox->setObjectName(QString::fromUtf8("entradasSpinBox"));
        entradasSpinBox->setGeometry(QRect(130, 10, 80, 22));
        entradasLabel = new QLabel(newCircuito);
        entradasLabel->setObjectName(QString::fromUtf8("entradasLabel"));
        entradasLabel->setGeometry(QRect(10, 10, 111, 21));
        saidasLabel = new QLabel(newCircuito);
        saidasLabel->setObjectName(QString::fromUtf8("saidasLabel"));
        saidasLabel->setGeometry(QRect(10, 40, 131, 21));
        portasLabel = new QLabel(newCircuito);
        portasLabel->setObjectName(QString::fromUtf8("portasLabel"));
        portasLabel->setGeometry(QRect(10, 70, 111, 21));
        saidasSpinBox = new QSpinBox(newCircuito);
        saidasSpinBox->setObjectName(QString::fromUtf8("saidasSpinBox"));
        saidasSpinBox->setGeometry(QRect(130, 40, 80, 22));
        portasSpinBox = new QSpinBox(newCircuito);
        portasSpinBox->setObjectName(QString::fromUtf8("portasSpinBox"));
        portasSpinBox->setGeometry(QRect(130, 70, 80, 22));

        retranslateUi(newCircuito);
        QObject::connect(buttonBox, SIGNAL(accepted()), newCircuito, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), newCircuito, SLOT(reject()));

        QMetaObject::connectSlotsByName(newCircuito);
    } // setupUi

    void retranslateUi(QDialog *newCircuito)
    {
        newCircuito->setWindowTitle(QCoreApplication::translate("newCircuito", "Novo circuito", nullptr));
        entradasLabel->setText(QCoreApplication::translate("newCircuito", "N\303\272mero de entradas:", nullptr));
        saidasLabel->setText(QCoreApplication::translate("newCircuito", "N\303\272mero de sa\303\255das:", nullptr));
        portasLabel->setText(QCoreApplication::translate("newCircuito", "N\303\272mero de portas:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class newCircuito: public Ui_newCircuito {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWCIRCUITO_H
