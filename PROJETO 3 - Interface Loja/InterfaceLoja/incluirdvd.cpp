#include "incluirdvd.h"
#include "ui_incluirdvd.h"

IncluirDVD::IncluirDVD(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirDVD)
{
    ui->setupUi(this);
}

IncluirDVD::~IncluirDVD()
{
    delete ui;
}

void IncluirDVD::on_buttonBox_accepted()
{
    QString nome, preco, duracao;

    // Ler o conteúdo das 3 lineEdit
    nome = ui->nomeLineEdit->text();
    preco = ui->precoLineEdit->text();
    duracao = ui->duracaoLineEdit->text();

    // Emitir sinal
    emit signIncluirDVD(nome, preco, duracao);

    // Limpar dados após a execução
    ui->nomeLineEdit->clear();
    ui->precoLineEdit->clear();
    ui->duracaoLineEdit->clear();
}
