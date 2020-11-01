#include "incluirlivro.h"
#include "ui_incluirlivro.h"

IncluirLivro::IncluirLivro(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IncluirLivro)
{
    ui->setupUi(this);
}

IncluirLivro::~IncluirLivro()
{
    delete ui;
}

void IncluirLivro::on_buttonBox_accepted()
{
    QString nome, preco, autor;

    // Ler o conteúdo das 3 lineEdit
    nome = ui->nomeLineEdit->text();
    preco = ui->precoLineEdit->text();
    autor = ui->autorLineEdit->text();

    // Emitir sinal
    emit signIncluirLivro(nome, preco, autor);

    // Limpar dados após a execução
    ui->nomeLineEdit->clear();
    ui->precoLineEdit->clear();
    ui->autorLineEdit->clear();
}
