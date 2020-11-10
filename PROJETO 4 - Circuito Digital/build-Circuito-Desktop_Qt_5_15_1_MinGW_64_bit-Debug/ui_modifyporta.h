/********************************************************************************
** Form generated from reading UI file 'modifyporta.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODIFYPORTA_H
#define UI_MODIFYPORTA_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_modifyPorta
{
public:
    QDialogButtonBox *buttonBox;
    QLabel *portaLabel;
    QLabel *tipoPortaLabel;
    QLabel *nEntradasLabel;
    QLabel *id1Label;
    QLabel *id2Label;
    QLabel *id3Label;
    QLabel *id4Label;
    QComboBox *tipoPortaComboBox;
    QSpinBox *nEntradasSpinBox;
    QSpinBox *id1SpinBox;
    QSpinBox *id2SpinBox;
    QSpinBox *id3SpinBox;
    QSpinBox *id4SpinBox;
    QLabel *portaNumberLabel;

    void setupUi(QDialog *modifyPorta)
    {
        if (modifyPorta->objectName().isEmpty())
            modifyPorta->setObjectName(QString::fromUtf8("modifyPorta"));
        modifyPorta->resize(180, 250);
        buttonBox = new QDialogButtonBox(modifyPorta);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(0, 220, 181, 31));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);
        portaLabel = new QLabel(modifyPorta);
        portaLabel->setObjectName(QString::fromUtf8("portaLabel"));
        portaLabel->setGeometry(QRect(10, 10, 47, 16));
        tipoPortaLabel = new QLabel(modifyPorta);
        tipoPortaLabel->setObjectName(QString::fromUtf8("tipoPortaLabel"));
        tipoPortaLabel->setGeometry(QRect(10, 40, 71, 21));
        nEntradasLabel = new QLabel(modifyPorta);
        nEntradasLabel->setObjectName(QString::fromUtf8("nEntradasLabel"));
        nEntradasLabel->setGeometry(QRect(10, 70, 81, 21));
        id1Label = new QLabel(modifyPorta);
        id1Label->setObjectName(QString::fromUtf8("id1Label"));
        id1Label->setGeometry(QRect(10, 100, 81, 21));
        id2Label = new QLabel(modifyPorta);
        id2Label->setObjectName(QString::fromUtf8("id2Label"));
        id2Label->setGeometry(QRect(10, 130, 81, 21));
        id3Label = new QLabel(modifyPorta);
        id3Label->setObjectName(QString::fromUtf8("id3Label"));
        id3Label->setGeometry(QRect(10, 160, 81, 21));
        id4Label = new QLabel(modifyPorta);
        id4Label->setObjectName(QString::fromUtf8("id4Label"));
        id4Label->setGeometry(QRect(10, 190, 81, 21));
        tipoPortaComboBox = new QComboBox(modifyPorta);
        tipoPortaComboBox->addItem(QString());
        tipoPortaComboBox->addItem(QString());
        tipoPortaComboBox->addItem(QString());
        tipoPortaComboBox->addItem(QString());
        tipoPortaComboBox->addItem(QString());
        tipoPortaComboBox->addItem(QString());
        tipoPortaComboBox->addItem(QString());
        tipoPortaComboBox->setObjectName(QString::fromUtf8("tipoPortaComboBox"));
        tipoPortaComboBox->setGeometry(QRect(100, 40, 69, 22));
        nEntradasSpinBox = new QSpinBox(modifyPorta);
        nEntradasSpinBox->setObjectName(QString::fromUtf8("nEntradasSpinBox"));
        nEntradasSpinBox->setGeometry(QRect(100, 70, 42, 22));
        id1SpinBox = new QSpinBox(modifyPorta);
        id1SpinBox->setObjectName(QString::fromUtf8("id1SpinBox"));
        id1SpinBox->setGeometry(QRect(100, 100, 42, 22));
        id2SpinBox = new QSpinBox(modifyPorta);
        id2SpinBox->setObjectName(QString::fromUtf8("id2SpinBox"));
        id2SpinBox->setGeometry(QRect(100, 130, 42, 22));
        id3SpinBox = new QSpinBox(modifyPorta);
        id3SpinBox->setObjectName(QString::fromUtf8("id3SpinBox"));
        id3SpinBox->setGeometry(QRect(100, 160, 42, 22));
        id4SpinBox = new QSpinBox(modifyPorta);
        id4SpinBox->setObjectName(QString::fromUtf8("id4SpinBox"));
        id4SpinBox->setGeometry(QRect(100, 190, 42, 22));
        portaNumberLabel = new QLabel(modifyPorta);
        portaNumberLabel->setObjectName(QString::fromUtf8("portaNumberLabel"));
        portaNumberLabel->setGeometry(QRect(100, 10, 61, 16));

        retranslateUi(modifyPorta);
        QObject::connect(buttonBox, SIGNAL(accepted()), modifyPorta, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), modifyPorta, SLOT(reject()));

        QMetaObject::connectSlotsByName(modifyPorta);
    } // setupUi

    void retranslateUi(QDialog *modifyPorta)
    {
        modifyPorta->setWindowTitle(QCoreApplication::translate("modifyPorta", "Dialog", nullptr));
        portaLabel->setText(QCoreApplication::translate("modifyPorta", "Porta:", nullptr));
        tipoPortaLabel->setText(QCoreApplication::translate("modifyPorta", "Tipo da porta:", nullptr));
        nEntradasLabel->setText(QCoreApplication::translate("modifyPorta", "N\302\260 de entradas:", nullptr));
        id1Label->setText(QCoreApplication::translate("modifyPorta", "ID da entrada 1:", nullptr));
        id2Label->setText(QCoreApplication::translate("modifyPorta", "ID da entrada 2:", nullptr));
        id3Label->setText(QCoreApplication::translate("modifyPorta", "ID da entrada 3:", nullptr));
        id4Label->setText(QCoreApplication::translate("modifyPorta", "ID da entrada 4:", nullptr));
        tipoPortaComboBox->setItemText(0, QCoreApplication::translate("modifyPorta", "NOT", nullptr));
        tipoPortaComboBox->setItemText(1, QCoreApplication::translate("modifyPorta", "AND", nullptr));
        tipoPortaComboBox->setItemText(2, QCoreApplication::translate("modifyPorta", "NAND", nullptr));
        tipoPortaComboBox->setItemText(3, QCoreApplication::translate("modifyPorta", "OR", nullptr));
        tipoPortaComboBox->setItemText(4, QCoreApplication::translate("modifyPorta", "NOR", nullptr));
        tipoPortaComboBox->setItemText(5, QCoreApplication::translate("modifyPorta", "XOR", nullptr));
        tipoPortaComboBox->setItemText(6, QCoreApplication::translate("modifyPorta", "NXOR", nullptr));

        portaNumberLabel->setText(QCoreApplication::translate("modifyPorta", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class modifyPorta: public Ui_modifyPorta {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIFYPORTA_H
