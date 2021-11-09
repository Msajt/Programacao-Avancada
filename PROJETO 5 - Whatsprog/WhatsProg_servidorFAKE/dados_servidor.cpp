#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include "dados_servidor.h"

/// O flag que indica que o software deve encerrar todas as threads
extern bool fim;

/// Funcao auxiliar que imprime um comando tratado pelo servidor
static void imprimeComando(bool recebido, const string& user, ComandoWhatsProg cmd,
                           int id, const string& user2)
{
  cout << "CMD " << (recebido ? "REC DE" : "ENV P/") << ' '
       << user << ": " << nome_cmd(cmd);
  if (id > 0) cout << ',' << id;
  if (user2.size() > 0) cout << ',' << user2;
  cout << endl;
}

/// Funcao auxiliar que imprime um comando enviado pelo servidor
inline static void imprimeComandoEnviado(const string& user, ComandoWhatsProg cmd,
    int id=-1, const string& user2="")
{
  imprimeComando(false, user, cmd, id, user2);
}

/// Funcao auxiliar que imprime um comando recebido pelo servidor
inline static void imprimeComandoRecebido(const string& user, ComandoWhatsProg cmd,
    int id=-1, const string& user2="")
{
  imprimeComando(true, user, cmd, id, user2);
}

/// Funcoes auxiliares para impressao
ostream& operator<<(ostream& O, const Mensagem& M)
{
  O << M.getId() << ';' << nome_status(M.getStatus()) << ';'
    << M.getRemetente() << ';' << M.getDestinatario() << ';'
    << M.getTexto();
  return O;
}
ostream& operator<<(ostream& O, const Usuario& U)
{
  O << U.getLogin() << ';' << U.getLastId();
  return O;
}

// Fixa login e senha do usuario
// Retorna true se OK; false em caso de erro
bool Usuario::setUsuario(const string &L, const string &S)
{
  if (!testarNomeUsuario(L) || !testarSenha(S))
  {
    return false;
  }
  login = L;
  senha = S;
  return true;
}

bool Usuario::setLastId(int32_t ID)
{
  if (ID<=0 || ID<=last_id)
  {
    return false;
  }
  last_id = ID;
  return true;
}

/// Envia para o usuario as mensagens que estejam arquivadas (paraUsuario[])
/// com status MSG_RECEBIDA e que seja destinada ao usuario.
/// Apos o envio, altera o status da msg enviada para MSG_ENTREGUE
void DadosServidor::enviarMsgsParaUsuario()
{
  Mensagem M;
  if (user.connected()) for (int i=0; i<2; i++)
  {
    M = paraUsuario[i];
    if (M.getDestinatario()==user.getLogin() &&
        M.getStatus()==MsgStatus::MSG_RECEBIDA)
    {
      bool envioOK = (user.write_int(CMD_NOVA_MSG) != mysocket_status::SOCK_ERROR);
      if (envioOK) envioOK = (user.write_int(M.getId()) != mysocket_status::SOCK_ERROR);
      if (envioOK) envioOK = (user.write_string(M.getRemetente()) != mysocket_status::SOCK_ERROR);
      if (envioOK) envioOK = (user.write_string(M.getTexto()) != mysocket_status::SOCK_ERROR);
      if (envioOK)
      {
        imprimeComandoEnviado(user.getLogin(), CMD_NOVA_MSG, M.getId(), M.getRemetente());
        // Mensagem enviada
        M.setStatus(MsgStatus::MSG_ENTREGUE);
        // Procura o usuario remetente
        if (M.getRemetente()=="userfake1" || M.getRemetente()=="userfake2")
        {
          // Remetente existe
          // Testa se o remetente estah concectado
          // Se sim, envia a confirmacao de entrega da mensagem
          // Os usuarios simulados estao sempre conectados...
          imprimeComandoEnviado(M.getRemetente(), CMD_MSG_ENTREGUE, M.getId(), "");
          paraUsuario[i] = M;
        }
      }
      else
      {
        // Nao conseguiu enviar para o destinatario
        cerr << "Erro no envio de msg para destinatario " << user.getLogin() << ". Desconectando\n";
        user.close();
      }
    }
  }
}

/// Envia para o usuario as confirmacoes de visualizacao das mensagens
/// que estejam arquivadas (doUsuario[]) com status MSG_LIDA
/// e que tenha sido enviada pelo usuario.
/// Apos o envio da confirmacao, apaga a msg
void DadosServidor::enviarConfirmacoesParaUsuario()
{
  Mensagem M;
  if (user.connected()) for (int i=0; i<2; i++)
  {
    M = doUsuario[i];
    if (M.getRemetente()==user.getLogin() &&
        M.getStatus()==MsgStatus::MSG_LIDA)
    {
      bool envioOK = (user.write_int(CMD_MSG_LIDA2) != mysocket_status::SOCK_ERROR);
      if (envioOK) envioOK = (user.write_int(M.getId()) != mysocket_status::SOCK_ERROR);
      if (!envioOK)
      {
        cerr << "Erro no envio de confirmacao de visualizaco para remetente "
             << user.getLogin() << ". Desconectando\n";
        user.close();
      }
      else
      {
        imprimeComandoEnviado(user.getLogin(), CMD_MSG_LIDA2, M.getId());
        // A confirmacao de visualizacao foi enviada
        // Remove a msg do buffer
        doUsuario[i] = Mensagem();
      }
    }
  }
}

// Funcao que efetivamente desempenha as tarefas do servidor
int DadosServidor::main()
{
  /// A fila para select (esperar dados em varios sockets)
  mysocket_queue f;

  mysocket_status iResult;
  int32_t cmd;
  int32_t id;

  /// As ultimas ids dos usuarios fake (soh faz sentido no servidor fake)
  int32_t last_id[2] = {0,0};

  while (!fim)
  {
    fim = !c.accepting();
    if (fim)
    {
      cerr << "Socket de conexoes nao estah aceitando conexoes. Encerrando\n";
      return -1;
    }
    // Inclui na fila de sockets para o select todos os sockets que eu
    // quero monitorar para ver se houve chegada de dados
    f.clean();
    f.include(c);
    // Soh tem um usuario neste servidor fake...
    if (user.connected())
    {
      f.include(user.getSocket());
    }
    // Espera que chegue algum dado em qualquer dos sockets da fila
    iResult = f.wait_read(TIMEOUT_WHATSPROG*1000);

    if (iResult == mysocket_status::SOCK_ERROR)
    {
      if (!fim) cerr << "Erro na espera por alguma atividade\n";
      fim = true;
    }
    if (iResult == mysocket_status::SOCK_TIMEOUT)
    {
      // Saiu por timeout: nao houve atividade em nenhum socket da fila
      // Pode aproveitar para salvar o arquivo de dados
      //
      // NESTE SERVIDOR FAKE, VAMOS UTILIZAR PARA SIMULAR O COMPORTAMENTO DOS
      // USUARIOS FAKE: userfake1 e userfake2

      //
      // Simula a visualizacao das msgs enviadas pelo usuario para os fakes
      //
      string destinatario = "userfake0";
      for (int i=0; i<2; i++)
      {
        destinatario[8] = char('1'+i);
        if (doUsuario[i].getRemetente()==user.getLogin() &&
            doUsuario[i].getDestinatario()==destinatario &&
            doUsuario[i].getStatus()==MsgStatus::MSG_ENTREGUE)
        {
          // A msg confirmada existe no buffer
          imprimeComandoRecebido(destinatario, CMD_MSG_LIDA1, doUsuario[i].getId(), user.getLogin());
          // Altera o status da msg
          doUsuario[i].setStatus(MsgStatus::MSG_LIDA);
        }
      }
      // Testa se o remetente estah conectado
      // Se sim, envia a confirmacao de visualizacao e remove a msg do buffer
      if (user.connected())
      {
        enviarConfirmacoesParaUsuario();
      }

      //
      // Simula o envio de msgs dos fakes para o usuario
      //
      string remetente = "userfake0";
      Mensagem M;
      // Tem um usuario definido?
      // Senao, nao envia mensagens
      if (testarNomeUsuario(user.getLogin()))
      {
        for (int i=0; i<2; i++)
        {
          // Soh escreve uma mensagem nova a cada 10 iteracoes em media
          // e se nao houver mensagem esperando. Caso haja, nao sobreescreve
          if (rand()%10==0 && paraUsuario[i].getStatus()==MsgStatus::MSG_INVALIDA)
          {
            remetente[8] = char('1'+i);
            last_id[i]++;

            // Forma a mensagem
            M.setStatus(MsgStatus::MSG_RECEBIDA);
            M.setRemetente(remetente);
            M.setDestinatario(user.getLogin());
            M.setId(last_id[i]);
            M.setTexto(string("Msg")+to_string(last_id[i]));

            // Mensagem valida
            imprimeComandoRecebido(remetente, CMD_NOVA_MSG, M.getId(), user.getLogin());
            // Insere a mensagem no buffer
            paraUsuario[i]=M;
          }
        }
        // Testa se o destinatario estah conectado
        // Se sim, envia a mensagem e muda status para MSG_ENTREGUE
        if (user.connected())
        {
          enviarMsgsParaUsuario();
        }
        //
        // Imprime os dados para debug
        //
        cout << "Usuario=" << user << endl;
        cout << "Mensagens do usuario armazenadas:" << endl;
        for (int i=0; i<2; i++) {cout << doUsuario[i] << endl;}
        cout << "Mensagens para o usuario armazenadas:" << endl;
        for (int i=0; i<2; i++) {cout << paraUsuario[i] << endl;}
      }
    }
    if (iResult == mysocket_status::SOCK_OK)
    {
      // Houve atividade em algum socket da fila
      // Testa em qual socket houve atividade.

      // Primeiro, testa os sockets dos clientes
      // Soh tem um usuario neste servidor fake...
      if (!fim && user.connected() && f.had_activity(user.getSocket()))
      {
        // Leh o comando recebido do cliente
        iResult = user.read_int(cmd);
        if (iResult != mysocket_status::SOCK_OK)
        {
          // Pode ser mysocket_status::SOCK_TIMEOUT, mysocket_status::SOCK_DISCONNECTED ou mysocket_status::SOCK_ERRO
          // Nao deve ser mysocket_status::SOCK_TIMEOUT porque a funcao read_int nao foi chamada com tempo maximo
          if (iResult == mysocket_status::SOCK_ERROR)
          {
            cerr << "Erro na leitura de comando do cliente " << user.getLogin() << ". Desconectando\n";
          }
          user.close();
        }
        // Se a leitura foi correta, executa o comando lido
        if (user.connected()) switch(cmd)
          {
          case CMD_NEW_USER:
          case CMD_LOGIN_USER:
          {
            // Soh pode chegar comando de definicao de usuario em socket recem-criado
            cerr << "Tentativa de redefinicao de usuario no socket do cliente " << user.getLogin() << ". Desconectando\n";
            user.close();
            break;
          }
          case CMD_LOGIN_OK:
          case CMD_LOGIN_INVALIDO:
          case CMD_MSG_RECEBIDA:
          case CMD_MSG_ENTREGUE:
          case CMD_MSG_LIDA2:
          case CMD_ID_INVALIDA:
          case CMD_USER_INVALIDO:
          case CMD_MSG_INVALIDA:
          default:
          {
            // Comando invalido
            cerr << "Comando invalido (" << nome_cmd((ComandoWhatsProg)cmd) << ") recebido do cliente "
                 << user.getLogin() << ". Desconectando\n";
            user.close();
            break;
          }
          case CMD_NOVA_MSG:
          {
            Mensagem M;
            string destinatario;
            string texto;

            // Receber a msg
            iResult = user.read_int(id, TIMEOUT_WHATSPROG*1000);
            if (iResult == mysocket_status::SOCK_OK)
            {
              iResult = user.read_string(destinatario, TIMEOUT_WHATSPROG*1000);
            }
            if (iResult == mysocket_status::SOCK_OK)
            {
              iResult = user.read_string(texto, TIMEOUT_WHATSPROG*1000);
            }
            if (iResult != mysocket_status::SOCK_OK)
            {
              // Pode ser mysocket_status::SOCK_TIMEOUT, mysocket_status::SOCK_DISCONNECTED ou mysocket_status::SOCK_ERRO
              if (iResult == mysocket_status::SOCK_ERROR)
              {
                cerr << "Erro na recepcao de parametros de CMD_NOVA_MSG do cliente "
                     << user.getLogin() << ". Desconectando\n";
              }
              user.close();
            }
            // Comeca a preencher os campos da mensagem recebida
            bool msg_valida = (M.setStatus(MsgStatus::MSG_RECEBIDA) && M.setRemetente(user.getLogin()));
            // Testa se a id da msg estah correta
            if (msg_valida && user.connected() &&
                (!M.setId(id) || (id <= user.getLastId())))
            {
              cerr << "Mensagem com ID invalida " << id << " recebida do cliente "
                   << user.getLogin() << ". Enviando cmd de erro\n";
              user.write_int(CMD_ID_INVALIDA);
              user.write_int(id);
              msg_valida = false;
            }
            // Testa se o texto da msg estah correto
            if (msg_valida && user.connected() &&
                !M.setTexto(texto))
            {
              cerr << "Mensagem com texto invalido recebida do cliente "
                   << user.getLogin() << ". Enviando cmd de erro\n";
              user.write_int(CMD_MSG_INVALIDA);
              user.write_int(id);
              msg_valida = false;
            }
            // Procura se o destinatario eh um usuario cadastrado
            if (msg_valida && user.connected())
            {
              // Neste servidor fake, nao hah lista de usuarios cadastrados
              // Os unicos outros usuarios cadastrados sao "userfake1" e "userfake2"

              // Testa se o destinatario da msg estah correto
              if (!M.setDestinatario(destinatario) ||
                  (destinatario!="userfake1" && destinatario!="userfake2"))
              {
                cerr << "Mensagem com destinatario invalido " << destinatario << " recebida do cliente "
                     << user.getLogin() << ". Enviando cmd de erro\n";
                user.write_int(CMD_USER_INVALIDO);
                user.write_int(id);
                msg_valida = false;
              }
            }
            if (msg_valida && user.connected())
            {
              // Mensagem valida
              imprimeComandoRecebido(user.getLogin(), CMD_NOVA_MSG, id, destinatario);
              // Insere a mensagem no buffer
              // Este servidor fake nao tem um buffer de verdade
              // Apenas guarda, para simulacao, a ultima msg recebida
              // (do usuario para userfake1 e para userfake2)

              // Atualiza a ultima ID recebida
              user.setLastId(id);
              // Envia a confirmacao de recebimento
              bool envioOK = (user.write_int(CMD_MSG_RECEBIDA) == mysocket_status::SOCK_OK);
              if (envioOK) envioOK = (user.write_int(id) == mysocket_status::SOCK_OK);
              if (!envioOK)
              {
                cerr << "Erro no envio de confirmacao de recebimento para remetente " << user.getLogin() << ". Desconectando\n";
                user.close();
              }
              else
              {
                imprimeComandoEnviado(user.getLogin(), CMD_MSG_RECEBIDA, id);
              }
              // Testa se o destinatario estah conectado
              // Se sim, envia a mensagem e muda status para MSG_ENTREGUE
              // Neste servidor fake, userfake1 e userfake2 estao sempre conectados
              // e os envios para eles sempre dao certo...
              imprimeComandoEnviado(M.getDestinatario(), CMD_NOVA_MSG, M.getId(), M.getRemetente());
              // Mensagem enviada
              M.setStatus(MsgStatus::MSG_ENTREGUE);
              doUsuario[ M.getDestinatario()=="userfake1" ? 0 : 1 ] = M;
              // Testa se o remetente estah conectado
              // Se sim, envia a confirmacao de entrega da mensagem
              if (user.connected())
              {
                envioOK = (user.write_int(CMD_MSG_ENTREGUE) != mysocket_status::SOCK_ERROR);
                if (envioOK) envioOK = (user.write_int(M.getId()) != mysocket_status::SOCK_ERROR);
                if (!envioOK)
                {
                  cerr << "Erro no envio de confirmacao de entrega para remetente "
                       << user.getLogin() << ". Desconectando\n";
                  user.close();
                }
                else
                {
                  imprimeComandoEnviado(user.getLogin(), CMD_MSG_ENTREGUE, M.getId(), "");
                }
              }
            }
            break;
          } // Fim do case CMD_NOVA_MSG
          case CMD_MSG_LIDA1:
          {
            string remetente;

            // Receber os parametros do comando
            iResult = user.read_int(id, TIMEOUT_WHATSPROG*1000);
            if (iResult  == mysocket_status::SOCK_OK) iResult = user.read_string(remetente, TIMEOUT_WHATSPROG*1000);
            if (iResult  != mysocket_status::SOCK_OK)
            {
              // Pode ser mysocket_status::SOCK_TIMEOUT, mysocket_status::SOCK_DISCONNECTED ou mysocket_status::SOCK_ERRO
              if (iResult == mysocket_status::SOCK_ERROR)
              {
                cerr << "Erro na recepcao de parametros de CMD_MSG_LIDA1 do cliente "
                     << user.getLogin() << ". Desconectando\n";
              }
              user.close();
            }
            if (user.connected())
            {
              // Os parametros da confirmacao de visualizacao foram recebidos
              // Procura pelo remetente. Caso exista o remetente,
              // procura pela msg que estah sendo confirmada
              //
              // Neste servidor fake, o remetente eh sempre userfake1 ou userfake2
              bool erro = (remetente!="userfake1" && remetente!="userfake2");
              if (!erro)
              {
                int indice = (remetente=="userfake1" ? 0 : 1);
                erro = (paraUsuario[indice].getRemetente()!=remetente ||
                        paraUsuario[indice].getId()!=id);
              }
              if (erro)
              {
                cerr << "CMD_MSG_LIDA1 de mensagem inexistente (" << id << "," << remetente
                     << ") recebida do cliente " << user.getLogin() << ". Desconectando\n";
                user.close();
              }
            }
            if (user.connected())
            {
              int indice = (remetente=="userfake1" ? 0 : 1);

              // A msg confirmada existe no buffer
              imprimeComandoRecebido(user.getLogin(), CMD_MSG_LIDA1, id, remetente);
              // Altera o status da msg
              paraUsuario[indice].setStatus(MsgStatus::MSG_LIDA);
              // Testa se o remetente estah conectado
              // Se sim, envia a confirmacao de visualizacao e remove a msg do buffer
              // Neste servidor fake, userfake1 e userfake2 estao sempre conectados
              // e os envios para eles sempre dao certo...
              imprimeComandoEnviado(remetente, CMD_MSG_LIDA2, paraUsuario[indice].getId());
              paraUsuario[indice] = Mensagem();
            }
            break;
          } // Fim do case CMD_MSG_LIDA1
          case CMD_LOGOUT_USER:
          {
            imprimeComandoRecebido(user.getLogin(), CMD_LOGOUT_USER);
            user.close();
            break;
          } // Fim do case CMD_LOGOUT_USER
          } // Fim do switch
      } // Fim do if (had_activity) no socket do cliente

      // Depois, testa se houve atividade no socket de conexao
      if (!fim && c.accepting() && f.had_activity(c))
      {
        tcp_mysocket t;
        string login, senha;

        // Aceita provisoriamente a nova conexao
        if (c.accept(t)!=mysocket_status::SOCK_OK)
        {
          cerr << "Não foi possível estabelecer uma conexao\n";
          t.close();
          // Encerra a thread do servidor
          fim = true;
        }
        // Leh o comando
        if (t.connected())
        {
          iResult = t.read_int(cmd, TIMEOUT_LOGIN_WHATSPROG*1000);
          if (iResult != mysocket_status::SOCK_OK)
          {
            // Pode ser mysocket_status::SOCK_TIMEOUT, mysocket_status::SOCK_DISCONNECTED ou mysocket_status::SOCK_ERRO
            cerr << "Erro na leitura do comando de conexao. Desconectando\n";
            t.close();
          }
        }
        // Testa o comando
        if (t.connected() &&
            (cmd!=CMD_LOGIN_USER && cmd!=CMD_NEW_USER))
        {
          cerr << "Comando (" << cmd << ") invalido. Desconectando\n";
          t.close();
        }
        // Leh o parametro com o login do usuario que deseja se conectar
        if (t.connected())
        {
          iResult = t.read_string(login, TIMEOUT_LOGIN_WHATSPROG*1000);
          if (iResult != mysocket_status::SOCK_OK)
          {
            cerr << "Erro na leitura de login. Desconectando\n";
            t.close();
          }
        }
        // Leh o parametro com a senha do usuario que deseja se conectar
        if (t.connected())
        {
          iResult = t.read_string(senha, TIMEOUT_LOGIN_WHATSPROG*1000);
          if (iResult != mysocket_status::SOCK_OK)
          {
            cerr << "Erro na leitura de senha. Desconectando\n";
            t.close();
          }
        }
        // Testa o login e senha
        if (t.connected() &&
            (!testarNomeUsuario(login) || !testarSenha(senha)))
        {
          cerr << "Login/senha (" << login << "/" << senha << ") invalido. Desconectando\n";
          t.write_int(CMD_LOGIN_INVALIDO);
          t.close();
        }
        // Testa se o usuario eh adequado
        if (t.connected())
        {
          if (cmd == CMD_NEW_USER)
          {
            // Verifica se jah existe um usuario cadastrado com esse login
            if (login == user.getLogin())
            {
              // Jah existe um usuario com esse login. Nao pode criar
              cerr << "Login (" << login << ") jah utilizado. Desconectando\n";
              t.write_int(CMD_LOGIN_INVALIDO);
              t.close();
            }
            // Este servidor fake soh pode ter um usuario cadastrado
            // Soh vai aceitar o novo usuario se ninguem estiver conectado
            if (user.connected())
            {
              // Jah existe um usuario conectado. Nao pode criar
              cerr << "Usuario (" << user.getLogin() << ") estah conectado no momento. Desconectando\n";
              t.write_int(CMD_LOGIN_INVALIDO);
              t.close();
            }
            if (t.connected())
            {
              // Insere novo usuario
              // Soh pode ter um usuario cadastrado
              // Portanto, ele vai sobrescrever um eventual usuario previamente cadastrado
              // Esse usuario anterior, caso tente futuramente se conectar com login jah
              // cadastrado, nao serah reconhecido

              // APENAS NO SERVIDOR FAKE:
              // Precisa apagar as msgs armazenadas pq podem ser de um outro usuario
              // que vai ser sobrescrito
              for (int i=0; i<2; i++)
              {
                paraUsuario[i] = Mensagem();
                doUsuario[i] = Mensagem();
              }

              if (user.setUsuario(login,senha))
              {
                user.resetId();
                user.swapSocket(t);
              }
              else
              {
                cerr << "Usuario (" << login << "/" << senha << ") e/ou socket invalidos. Desconectando\n";
                t.write_int(CMD_LOGIN_INVALIDO);
                t.close();
              }
            }
          }
          else  // else cmd == CMD_NEW_USER; implica cmd eh CMD_LOGIN_USER
          {
            if (login != user.getLogin())
            {
              // Nao existe um usuario com esse login. Nao pode conectar
              cerr << "Login (" << login << ") nao existe. Desconectando\n";
              login = "invalido";
              t.write_int(CMD_LOGIN_INVALIDO);
              t.close();
            }
            // Testa se a senha confere
            if (t.connected() && !user.validarSenha(senha))
            {
              // Senha invalida
              cerr << "Senha para usuario (" << login << ") nao confere. Desconectando\n";
              senha = "invalida";
              t.write_int(CMD_LOGIN_INVALIDO);
              t.close();
            }
            // Testa se o cliente jah estah conectado
            if (t.connected() && user.connected())
            {
              // O usuario jah estah conectado
              cerr << "Usuario (" << login << ") jah estah conectado. Desconectando\n";
              login = "invalido";
              t.write_int(CMD_LOGIN_INVALIDO);
              t.close();
            }
            // Associa o socket que se conectou a um usuario cadastrado
            if (t.connected())
            {
              user.swapSocket(t);
            }
          } // fim cmd eh CMD_LOGIN_USER

          // Envia a confirmacao de conexao
          if (login==user.getLogin() && user.connected())
          {
            imprimeComandoRecebido(login, (ComandoWhatsProg)cmd);
            bool envioOK = (user.write_int(CMD_LOGIN_OK) == mysocket_status::SOCK_OK);
            if (!envioOK)
            {
              cerr << "Erro no envio de confirmacao de login para cliente "
                   << user.getLogin() << ". Desconectando\n";
              user.close();
            }
            else
            {
              imprimeComandoEnviado(user.getLogin(), CMD_LOGIN_OK);
            }
          }
          // Se for um cliente antigo, envia para o cliente que se reconectou:
          // a) as mensagens enviadas para ele que estao no buffer
          // b) as confirmacoes de visualizacao para ele que estao no buffer
          if (login==user.getLogin() && user.connected() && cmd==CMD_LOGIN_USER)
          {
            // mensagens enviadas para ele que estao no buffer
            enviarMsgsParaUsuario();
            // as confirmacoes de visualizacao para ele que estao no buffer
            enviarConfirmacoesParaUsuario();
          }
        } // fim do teste se usuario eh adequado
      } // fim if (had_activity) no socket de conexoes
    } // Fim do teste se a espera por atividade foi mysocket_status::SOCK_OK
  } // Fim do while (!fim), laco principal da thread

  cout << "\nServidor encerrado.\n";

  return 0;
}

/// Fecha os sockets de todos os usuarios conectados
void DadosServidor::closeSockets()
{
  c.close();
  user.close();
}
