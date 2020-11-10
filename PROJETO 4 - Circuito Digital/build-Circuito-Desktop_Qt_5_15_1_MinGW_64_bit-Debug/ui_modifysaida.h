/********************************************************************************
** Form generated from reading UI file 'modifysaida.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODIFYSAIDA_H
#define UI_MODIFYSAIDA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_modifySaida
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *saidaLabel;
    QLabel *idOrigemLabel;
    QLabel *saidaNumberlabel;
    QSpinBox *idOrigemSpinBox;

    void setupUi(QDialog *modifySaida)
    {
        if (modifySaida->objectName().isEmpty())
            modifySaida->setObjectName(QString::fromUtf8("modifySaida"));
        modifySaida->resize(190, 110);
        buttonBox = new QDialogButtonBox(modifySaida);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(0, 70, 191, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);
        saidaLabel = new QLabel(modifySaida);
        saidaLabel->setObjectName(QString::fromUtf8("saidaLabel"));
        saidaLabel->setGeometry(QRect(10, 10, 41, 16));
        idOrigemLabel = new QLabel(modifySaida);
        idOrigemLabel->setObjectName(QString::fromUtf8("idOrigemLabel"));
        idOrigemLabel->setGeometry(QRect(10, 40, 71, 21));
        saidaNumberlabel = new QLabel(modifySaida);
        saidaNumberlabel->setObjectName(QString::fromUtf8("saidaNumberlabel"));
        saidaNumberlabel->setGeometry(QRect(100, 10, 21, 16));
        idOrigemSpinBox = new QSpinBox(modifySaida);
        idOrigemSpinBox->setObjectName(QString::fromUtf8("idOrigemSpinBox"));
        idOrigemSpinBox->setGeometry(QRect(100, 40, 80, 22));

        retranslateUi(modifySaida);
        QObject::connect(buttonBox, SIGNAL(accepted()), modifySaida, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), modifySaida, SLOT(reject()));

        QMetaObject::connectSlotsByName(modifySaida);
    } // setupUi

    void retranslateUi(QDialog *modifySaida)
    {
        modifySaida->setWindowTitle(QCoreApplication::translate("modifySaida", "Dialog", nullptr));
        saidaLabel->setText(QCoreApplication::translate("modifySaida", "SA\303\215DA:", nullptr));
        idOrigemLabel->setText(QCoreApplication::translate("modifySaida", "ID da origem:", nullptr));
        saidaNumberlabel->setText(QCoreApplication::translate("modifySaida", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class modifySaida: public Ui_modifySaida {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIFYSAIDA_H
