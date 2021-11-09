#include <QMessageBox>
#include <QDebug>
#include "logindialog.h"
#include "ui_logindialog.h"
#include "whatsprogmain.h"
#include "dados_cliente.h"
#include "dados_whatsprog.h"

LoginDialog::LoginDialog(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::LoginDialog)
{
  ui->setupUi(this);

  ui->lineEditSenhaUsuario->setEchoMode( QLineEdit::Password );

}

LoginDialog::~LoginDialog()
{
  delete ui;
}

void LoginDialog::on_buttonBox_accepted()
{
    QString ip, login, senha;
    ip = ui->lineEditIpServidor->text();
    login = ui->lineEditNomeUsuario->text();
    senha = ui->lineEditSenhaUsuario->text();
    qDebug() << login << ":" << testarNomeUsuario(login.toStdString()) << senha << ":" << " " << testarSenha(senha.toStdString());
    if(testarNomeUsuario(login.toStdString()) && testarSenha(senha.toStdString())){
        if(QWidget::windowTitle() == "Usuário - Criar"){
            emit signCriarUsuario(ip, login, senha);
        } else if(QWidget::windowTitle() == "Usuário - Existente"){
            emit signLogarUsuario(ip, login, senha);
        }
    } else{
        QMessageBox::critical(this, "Erro ao realizar o login", "Dados inválidos");
    }

    ui->lineEditIpServidor->clear();
    ui->lineEditNomeUsuario->clear();
    ui->lineEditSenhaUsuario->clear();
}
