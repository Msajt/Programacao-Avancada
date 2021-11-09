#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>

using namespace std;

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
  Q_OBJECT

public:
  explicit LoginDialog(QWidget *parent = 0);
  ~LoginDialog();

private slots:
  void on_buttonBox_accepted();

signals:
  void signCriarUsuario(QString ip, QString usuario, QString senha);
  void signLogarUsuario(QString ip, QString usuario, QString senha);

private:
  Ui::LoginDialog *ui;
};

#endif // LOGINDIALOG_H
