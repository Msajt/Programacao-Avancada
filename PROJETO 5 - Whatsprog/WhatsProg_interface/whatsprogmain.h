#ifndef WHATSPROGMAIN_H
#define WHATSPROGMAIN_H

#include <QMainWindow>
#include <QLabel>
#include "logindialog.h"
#include "novaconversa.h"
#include "dados_cliente.h"
#include "dados_whatsprog.h"

namespace Ui {
class WhatsProgMain;
}

class WhatsProgMain : public QMainWindow
{
  Q_OBJECT

private:
  Ui::WhatsProgMain *ui;

  LoginDialog *loginDialog;
  NovaConversa *novaConversa;
  QLabel *labelConexao;

public:
  explicit WhatsProgMain(QWidget *parent = 0);
  ~WhatsProgMain();

  //void main_thread();
  bool aceitaUsuario(const string &IP, const string &login, const string &senha, bool novoUsuario); // OK
  void interfaceDesconectada(); // OK
  void interfaceConectada(string user, string servidor); // OK
  void listarMensagens(IterConversa it);
  void listarConversas();

public slots:
  void on_actionNovo_usuario_triggered(); // OK
  void on_actionUsuario_existente_triggered();
  void on_actionDesconectar_triggered(); // OK
  void on_actionSair_triggered();
  void on_tableConversas_cellActivated(int row, int column);
  void on_tableConversas_cellClicked(int row, int column);
  void on_lineEditMensagem_returnPressed();
  void on_actionNova_conversa_triggered();
  void on_actionRemover_conversa_triggered();
  void on_actionApagar_mensagens_triggered();
  void slotCriarUsuario(QString ip, QString usuario, QString senha);
  void slotLogarUsuario(QString ip, QString usuario, QString senha);

  void slotNovaConversa(QString usuario);

};

#endif // WHATSPROGMAIN_H
