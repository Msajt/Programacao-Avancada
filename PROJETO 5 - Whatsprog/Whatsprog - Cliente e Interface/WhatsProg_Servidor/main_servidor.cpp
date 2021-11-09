#include <iostream>
#include <thread>

#include "dados_whatsprog.h"
#include "dados_servidor.h"

using namespace std;

/* ==================================================================

Servidor do aplicativo WhatsProg

================================================================== */

/// Variavel global (das duas threads)
/// O flag que indica que o software deve encerrar todas as threads
bool fim = false;

/// A funcao que vai ser executada na thread
/// Apenas chama o metodo main() do objeto da classe
void main_servidor( DadosServidor* DS )
{
  DS->main();
}

int main(void)
{
  /// Os dados do servidor
  DadosServidor DS;
  /// A thread do servidor
  thread thr;

  string msg;

  // Inicializa a biblioteca de sockets (exigida no Windows)
  if (mysocket::init() != mysocket_status::SOCK_OK)
  {
    cerr << "Biblioteca mysocket nao pode ser inicializada\n";
    exit(1);
  }

  cout << "WhatsProg - SERVIDOR\n";

  if (DS.listen(PORTA_WHATSPROG) != mysocket_status::SOCK_OK)
  {
    cerr << "Não foi possível abrir o socket de controle\n";
    exit(1);
  }

  // Lanca a thread que recebe e reenvia as mensagens
  thr = thread(main_servidor, &DS);

  while (!fim)
  {
    do
    {
      cout << "Digite FIM para terminar:\n";
      cin >> ws;
      getline(cin,msg);
    }
    while (msg != "FIM");
    fim = true;
  }

  // Desliga os sockets
  cout << "Encerrando os sockets...\n";
  DS.closeSockets();

  // Espera pelo fim da thread de recepcao
  if (thr.joinable()) thr.join();

  /// Encerramento da biblioteca de sockets
  mysocket::end();
}
