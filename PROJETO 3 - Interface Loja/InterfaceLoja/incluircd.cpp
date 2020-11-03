#include "incluircd.h"
#include "ui_incluircd.h"

IncluirCD::IncluirCD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirCD)
{
    ui->setupUi(this);
}

IncluirCD::~IncluirCD()
{
    delete ui;
}

void IncluirCD::on_buttonBox_accepted()
{
    QString nome, preco, faixas;

    // Ler o conteúdo das 3 lineEdit
    nome = ui->nomeLineEdit->text();
    preco = ui->precoLineEdit->text();
    faixas = ui->faixasLineEdit->text();

    // Emitir sinal
    emit signIncluirCD(nome, preco, faixas);

    // Limpar dados após a execução
    ui->nomeLineEdit->clear();
    ui->precoLineEdit->clear();
    ui->faixasLineEdit->clear();

    QDialog::close();
}

void IncluirCD::on_buttonBox_rejected()
{
    ui->nomeLineEdit->clear();
    ui->precoLineEdit->clear();
    ui->faixasLineEdit->clear();

    QDialog::close();
}
