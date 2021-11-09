#include <QApplication>
#include <QMessageBox>
#include <QThread>
#include <QIcon>
#include <thread>

#include "mysocket.h"
#include "whatsprogmain.h"
#include "dados_cliente.h"

// MENSAGENS DE TODAS AS CONVERSAS DO WHATSPROG
DadosCliente DC;

// CLIENTE SOCKET, UTILIZADO PELAS THREADS
tcp_mysocket sock;

// THREAD
thread thr;

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  WhatsProgMain w;

  a.setWindowIcon(QIcon(":/new/images/whatsprog_icon.png"));

  // Inicializar os sockets
  mysocket_status iResult = mysocket::init();

  if(iResult != mysocket_status::SOCK_OK){
      cerr << "A biblioteca não pode ser iniciada\n";
      exit(1);
  }

  // Exibe a janela principal do aplicativo **
  w.show();

  // Entra no laco sem fim de execucao **
  int result = a.exec();

  // Espera pelo fim da thread de recepcao
  if (thr.joinable()) thr.join();

  // Encerra a API de sockets
  mysocket::end();

  return result;
}
