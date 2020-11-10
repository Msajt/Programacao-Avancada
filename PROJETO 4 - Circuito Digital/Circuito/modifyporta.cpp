#include "modifyporta.h"
#include "ui_modifyporta.h"

modifyPorta::modifyPorta(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifyPorta)
{
    ui->setupUi(this);
}

modifyPorta::~modifyPorta()
{
    delete ui;
}

void modifyPorta::on_buttonBox_accepted()
{
    QString tipoPorta, nEntradas, id1, id2, id3, id4;

    // Pegar valores
    tipoPorta = ui->tipoPortaComboBox->currentText();
    nEntradas = ui->nEntradasSpinBox->value();
    id1 = ui->id1SpinBox->value();
    id2 = ui->id1SpinBox->value();
    id3 = ui->id1SpinBox->value();
    id4 = ui->id1SpinBox->value();

    // Emitir sinal
    emit signModifyPorta(tipoPorta, nEntradas, id1, id2, id3, id4);

    QDialog::close();
}

void modifyPorta::on_buttonBox_rejected()
{
    QDialog::close();
}
