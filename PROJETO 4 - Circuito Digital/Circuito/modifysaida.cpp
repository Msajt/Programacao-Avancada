#include "modifysaida.h"
#include "ui_modifysaida.h"

modifySaida::modifySaida(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::modifySaida)
{
    ui->setupUi(this);
}

modifySaida::~modifySaida()
{
    delete ui;
}

void modifySaida::on_buttonBox_accepted()
{
    QString idOrigem;

    // Pegar valores
    idOrigem = ui->idOrigemSpinBox->value();

    emit signModifySaida(idOrigem);

    QDialog::close();
}

void modifySaida::on_buttonBox_rejected()
{
    QDialog::close();
}
