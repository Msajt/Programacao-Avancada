#include "newcircuito.h"
#include "ui_newcircuito.h"

newCircuito::newCircuito(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newCircuito)
{
    ui->setupUi(this);
}

newCircuito::~newCircuito()
{
    delete ui;
}

void newCircuito::on_buttonBox_accepted()
{
    QString nEntradas, nSaidas, nPortas;

    // Pegar valores
    nEntradas = ui->entradasSpinBox->value();
    nSaidas = ui->saidasSpinBox->value();
    nPortas = ui->portasSpinBox->value();

    emit signNewCircuito(nEntradas, nSaidas, nPortas);

    QDialog::close();
}

void newCircuito::on_buttonBox_rejected()
{
    QDialog::close();
}
