#include <string>
#include <QMessageBox>
#include "novaconversa.h"
#include "ui_novaconversa.h"
#include "whatsprogmain.h"

using namespace std;

NovaConversa::NovaConversa(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::NovaConversa)
{
  ui->setupUi(this);
}

NovaConversa::~NovaConversa()
{
  delete ui;
}

void NovaConversa::on_buttonBox_accepted()
{
    QString usuario;
    usuario = ui->lineEditConversa->text();

    emit signNovaConversa(usuario);

    ui->lineEditConversa->clear();
}
