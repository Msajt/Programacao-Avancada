#include <iostream>
#include <fstream>
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

/// Funcao auxiliar para impressao
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

/// Envia para o usuario destinatario as mensagens que estejam
/// arquivadas com status MSG_RECEBIDA e que seja destinada a ele.
/// Apos o envio, altera o status da msg enviada para MSG_ENTREGUE
void DadosServidor::enviarMsgsParaUsuario(iter_Usuario iDest)
{
  list<Mensagem>::iterator M = LM.begin();
  testDestStatus testDest(iDest->getLogin(), MsgStatus::MSG_RECEBIDA);

  while (iDest->connected() && M!=LM.end())
  {
    M = find(M, LM.end(), testDest);
    if(M!=LM.end())
    {
      bool envioOK = (iDest->write_int(CMD_NOVA_MSG) != mysocket_status::SOCK_ERROR);
      if (envioOK) envioOK = (iDest->write_int(M->getId()) != mysocket_status::SOCK_ERROR);
      if (envioOK) envioOK = (iDest->write_string(M->getRemetente()) != mysocket_status::SOCK_ERROR);
      if (envioOK) envioOK = (iDest->write_string(M->getTexto()) != mysocket_status::SOCK_ERROR);
      if (envioOK)
      {
        imprimeComandoEnviado(iDest->getLogin(), CMD_NOVA_MSG, M->getId(), M->getRemetente());
        // Mensagem entregue
        M->setStatus(MsgStatus::MSG_ENTREGUE);
        // Procura o usuario remetente
        iter_Usuario iRemet = find(LU.begin(), LU.end(), M->getRemetente());
        if(iRemet!=LU.end())
        {
          // Remetente existe
          // Testa se o remetente estah concectado
          // Se sim, envia a confirmacao de entrega da mensagem
          if(iRemet->connected())
          {
              envioOK = (iRemet->write_int(CMD_MSG_ENTREGUE) != mysocket_status::SOCK_ERROR);
              if(envioOK) envioOK = (iRemet->write_int(M->getId()) != mysocket_status::SOCK_ERROR);
              if(envioOK)
              {
                imprimeComandoEnviado(iRemet->getLogin(), CMD_MSG_ENTREGUE, M->getId(), "");
              }
          }
        }
        else
        {
            // Nao encontrou o remetente na lista de usuarios
            cerr << "O remetente '" << M->getRemetente() << "' nao existe. Desconectando...\n";
            iDest->close();
        }
      }
      else
      {
        // Nao conseguiu enviar para o destinatario
        cerr << "Erro no envio de msg para o destinatario '" << iDest->getLogin() << "'. Desconectando...\n";
        iDest->close();;
      }

      M++;
    }
  }
}

/// Envia para o usuario as confirmacoes de entrega e visualizacao
/// das mensagens que estejam arquivadas com status MSG_LIDA e
/// MSG_ENTREGUE, e que tenha sido enviada pelo usuario iRemet.
/// Apos o envio da confirmacao, apaga a mensagem.
void DadosServidor::enviarConfirmacoesParaUsuario(iter_Usuario iRemet)
{
  list<Mensagem>::iterator M = LM.begin();
  testRemetStatus remet(iRemet->getLogin(), MsgStatus::MSG_LIDA);
  testRemetStatus testRemet(iRemet->getLogin(), MsgStatus::MSG_ENTREGUE);
  bool envioOK;

  while(iRemet->connected() && M!=LM.end())
  {
      M = find(M, LM.end(), testRemet);
      if(M!=LM.end())
      {
         envioOK = (iRemet->write_int(CMD_MSG_ENTREGUE) != mysocket_status::SOCK_ERROR);
         if(envioOK) envioOK = (iRemet->write_int(M->getId()) != mysocket_status::SOCK_ERROR);
         if(envioOK)
         {
           imprimeComandoEnviado(iRemet->getLogin(), CMD_MSG_ENTREGUE, M->getId(), "");
         }

         M++;
      }
  }

  M = LM.begin();

  while(M!=LM.end() && iRemet->connected())
  {
    M = find(M, LM.end(), remet);
    if(M!=LM.end())
    {
      envioOK = (iRemet->write_int(CMD_MSG_LIDA2) != mysocket_status::SOCK_ERROR);
      if (envioOK) envioOK = (iRemet->write_int(M->getId()) != mysocket_status::SOCK_ERROR);
      if (!envioOK)
      {
        cerr << "Erro no envio de confirmacao de visualizaco para o remetente '"
             << iRemet->getLogin() << "'. Desconectando...\n";
        iRemet->close();
      }
      else
      {
        imprimeComandoEnviado(iRemet->getLogin(), CMD_MSG_LIDA2, M->getId());
        // A confirmacao de visualizacao foi enviada
        // Remove a msg do buffer
        M = LM.erase(M);
      }
    }
  }
}

// Funcao que efetivamente desempenha as tarefas do servidor
int DadosServidor::main()
{
  /// A fila para select (esperar dados em varios sockets)
  mysocket_queue f;

  iter_Usuario iUsuario;
  mysocket_status iResult;
  int32_t cmd;
  int32_t id;

  while (!fim)
  {
    fim = !c.accepting();
    if (fim)
    {
      cerr << "Socket de conexoes nao estah aceitando conexoes. Encerrando...\n";
      return -1;
    }
    // Inclui na fila de sockets para o select todos os sockets que eu
    // quero monitorar para ver se houve chegada de dados
    f.clean();
    f.include(c);

    for(iUsuario=LU.begin(); iUsuario!=LU.end(); iUsuario++)
    {
        if(iUsuario->connected())
        {
            f.include(iUsuario->getSocket());
        }
    }

    // Espera que chegue algum dado em qualquer dos sockets da fila
    iResult = f.wait_read(TIMEOUT_WHATSPROG*1000);

    if (iResult == mysocket_status::SOCK_ERROR)
    {
      if (!fim) cerr << "Erro na espera por alguma atividade.\n";
      fim = true;
    }

    if (iResult == mysocket_status::SOCK_OK)
    {
      // Houve atividade em algum socket da fila
      // Testa em qual socket houve atividade.

      // Primeiro, testa os sockets dos clientes
      for(iUsuario=LU.begin(); iUsuario!=LU.end(); iUsuario++)
      {
          if (!fim && iUsuario->connected() && f.had_activity(iUsuario->getSocket()))
          {
            // Leh o comando recebido do cliente
            iResult = iUsuario->read_int(cmd);
            if (iResult != mysocket_status::SOCK_OK)
            {
              // Pode ser mysocket_status::SOCK_TIMEOUT, mysocket_status::SOCK_DISCONNECTED ou mysocket_status::SOCK_ERRO
              // Nao deve ser mysocket_status::SOCK_TIMEOUT porque a funcao read_int nao foi chamada com tempo maximo
              if (iResult == mysocket_status::SOCK_ERROR)
              {
                cerr << "Erro na leitura de comando do cliente '" << iUsuario->getLogin() << "'. Desconectando...\n";
              }
              iUsuario->close();
            }
            // Se a leitura foi correta, executa o comando lido
            if (iUsuario->connected()) switch(cmd)
              {
              case CMD_NEW_USER:
              case CMD_LOGIN_USER:
              {
                // Soh pode chegar comando de definicao de usuario em socket recem-criado
                cerr << "Tentativa de redefinicao de usuario no socket do cliente '" << iUsuario->getLogin() << "'. Desconectando...\n";
                iUsuario->close();
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
                cerr << "Comando invalido (" << nome_cmd((ComandoWhatsProg)cmd) << ") recebido do cliente '"
                     << iUsuario->getLogin() << "'. Desconectando...\n";
                iUsuario->close();
                break;
              }
              case CMD_NOVA_MSG:
              {
                Mensagem M;
                string destinatario;
                string texto;
                iter_Usuario iUsuario_prov;

                // Recebe a msg
                bool OK = (iUsuario->read_int(id, TIMEOUT_WHATSPROG*1000) == mysocket_status::SOCK_OK);
                if (OK) OK = (iUsuario->read_string(destinatario, TIMEOUT_WHATSPROG*1000) == mysocket_status::SOCK_OK);
                if (OK) OK = (iUsuario->read_string(texto, TIMEOUT_WHATSPROG*1000) == mysocket_status::SOCK_OK);
                if (!OK)
                {
                  // Pode ser mysocket_status::SOCK_TIMEOUT, mysocket_status::SOCK_DISCONNECTED ou mysocket_status::SOCK_ERRO
                  if (iResult == mysocket_status::SOCK_ERROR)
                  {
                    cerr << "Erro na recepcao de parametros de CMD_NOVA_MSG do cliente '"
                         << iUsuario->getLogin() << "'. Desconectando...\n";
                  }
                  iUsuario->close();
                }
                // Comeca a preencher os campos da mensagem recebida
                bool msg_valida = (M.setStatus(MsgStatus::MSG_RECEBIDA) && M.setRemetente(iUsuario->getLogin()));
                // Testa se a id da msg estah correta
                if (msg_valida && iUsuario->connected() &&
                    (!M.setId(id) || (id <= iUsuario->getLastId())))
                {
                  cerr << "Mensagem com ID invalida (" << id << ") recebida do cliente '"
                       << iUsuario->getLogin() << "'. Enviando cmd de erro...\n";
                  iUsuario->write_int(CMD_ID_INVALIDA);
                  iUsuario->write_int(id);
                  msg_valida = false;
                }
                // Testa se o texto da msg estah correto
                if (msg_valida && iUsuario->connected() &&
                    !M.setTexto(texto))
                {
                  cerr << "Mensagem com texto invalido recebida do cliente "
                       << iUsuario->getLogin() << ". Enviando cmd de erro\n";
                  iUsuario->write_int(CMD_MSG_INVALIDA);
                  iUsuario->write_int(id);
                  msg_valida = false;
                }

                if (msg_valida && iUsuario->connected())
                {
                  // Testa se o destinatario da msg estah correto
                  iUsuario_prov = find(LU.begin(), LU.end(), destinatario);
                  if(iUsuario_prov==LU.end())
                  {
                    cerr << "Mensagem com destinatario invalido (" << destinatario << ") recebida do cliente '"
                         << iUsuario->getLogin() << "'. Enviando comando de erro...\n";
                    iUsuario->write_int(CMD_USER_INVALIDO);
                    iUsuario->write_int(id);
                    msg_valida = false;
                  }
                }

                if (msg_valida && iUsuario->connected())
                {
                  // Mensagem valida
                  // Altera o destinatario
                  M.setDestinatario(destinatario);

                  // Imprime comando recebido
                  imprimeComandoRecebido(iUsuario->getLogin(), CMD_NOVA_MSG, id, destinatario);

                  // Insere a mensagem no buffer
                  LM.push_back(M);

                  // Atualiza a ultima ID recebida
                  iUsuario->setLastId(id);

                  // Envia a confirmacao de recebimento para o remetente iUsuario
                  bool envioOK = (iUsuario->write_int(CMD_MSG_RECEBIDA) == mysocket_status::SOCK_OK);
                  if (envioOK) envioOK = (iUsuario->write_int(id) == mysocket_status::SOCK_OK);
                  if (!envioOK)
                  {
                    cerr << "Erro no envio de confirmacao de recebimento para o remetente '" << iUsuario->getLogin()
                         << "'. Desconectando...\n";
                    iUsuario->close();
                  }
                  else
                  {
                    imprimeComandoEnviado(iUsuario->getLogin(), CMD_MSG_RECEBIDA, id);
                  }
                  // Testa se o destinatario estah conectado
                  // Se sim, envia a mensagem e muda status para MSG_ENTREGUE
                  // Neste servidor fake, userfake1 e userfake2 estao sempre conectados
                  // e os envios para eles sempre dao certo...
                  if(iUsuario_prov->connected())
                  {
                      bool envioOK = (iUsuario_prov->write_int(CMD_NOVA_MSG) != mysocket_status::SOCK_ERROR);
                      if (envioOK) envioOK = (iUsuario_prov->write_int(M.getId()) != mysocket_status::SOCK_ERROR);
                      if (envioOK) envioOK = (iUsuario_prov->write_string(M.getRemetente()) != mysocket_status::SOCK_ERROR);
                      if (envioOK) envioOK = (iUsuario_prov->write_string(M.getTexto()) != mysocket_status::SOCK_ERROR);
                      if (envioOK)
                      {
                          // Imprime comando enviado
                          imprimeComandoEnviado(M.getDestinatario(), CMD_NOVA_MSG, M.getId(), M.getRemetente());
                          // Mensagem enviada
                          M.setStatus(MsgStatus::MSG_ENTREGUE);
                          // Testa se o remetente estah conectado
                          // Se sim, envia a confirmacao de entrega da mensagem
                          if (iUsuario->connected())
                          {
                            envioOK = (iUsuario->write_int(CMD_MSG_ENTREGUE) != mysocket_status::SOCK_ERROR);
                            if (envioOK) envioOK = (iUsuario->write_int(M.getId()) != mysocket_status::SOCK_ERROR);
                            if (!envioOK)
                            {
                              cerr << "Erro no envio de confirmacao de entrega para remetente '"
                                   << iUsuario->getLogin() << "'. Desconectando...\n";
                              iUsuario->close();
                            }
                            else
                            {
                              imprimeComandoEnviado(iUsuario->getLogin(), CMD_MSG_ENTREGUE, M.getId(), "");
                            }
                          }
                      }
                      else
                      {
                          cerr << "Erro no envio da mensagem para o destinatario '" << iUsuario_prov->getLogin()
                               << "'. Desconectando este usuario...\n";
                          iUsuario_prov->close();
                      }
                  }
                } // Fim do if para msg_valida

                break;
              } // Fim do case CMD_NOVA_MSG
              case CMD_MSG_LIDA1:
              {
                string remetente;
                list<Mensagem>::iterator M;

                // Receber os parametros do comando
                bool OK = (iUsuario->read_int(id, TIMEOUT_WHATSPROG*1000) == mysocket_status::SOCK_OK);
                if (OK) OK = (iUsuario->read_string(remetente, TIMEOUT_WHATSPROG*1000) == mysocket_status::SOCK_OK);
                if (!OK)
                {
                  // Pode ser mysocket_status::SOCK_TIMEOUT, mysocket_status::SOCK_DISCONNECTED ou mysocket_status::SOCK_ERRO
                  if (iResult == mysocket_status::SOCK_ERROR)
                  {
                    cerr << "Erro na recepcao de parametros de CMD_MSG_LIDA1 do cliente '"
                         << iUsuario->getLogin() << "'. Desconectando...\n";
                  }
                  iUsuario->close();
                }
                if (iUsuario->connected())
                {
                  // Os parametros da confirmacao de visualizacao foram recebidos
                  // Procura pelo remetente. Caso exista o remetente,
                  // procura pela msg que estah sendo confirmada

                  testRemetId M_prov(remetente, id);
                  M = find(LM.begin(), LM.end(), M_prov);

                  if (M==LM.end())
                  {
                    cerr << "CMD_MSG_LIDA1 de mensagem inexistente (" << id << "," << remetente
                         << ") recebida do cliente '" << iUsuario->getLogin() << "'. Desconectando...\n";
                    iUsuario->close();
                  }
                }

                if (iUsuario->connected())
                {
                  // A msg confirmada existe no buffer
                  imprimeComandoRecebido(iUsuario->getLogin(), CMD_MSG_LIDA1, id, remetente);
                  // Altera o status da msg
                  M->setStatus(MsgStatus::MSG_LIDA);
                  // Testa se o remetente estah conectado
                  // Se sim, envia a confirmacao de visualizacao e remove a msg do buffer
                  //
                  // Procura agora o usuario na lista de usuarios, para ter acesso ao socket correspondente
                  iter_Usuario remetente_prov = find(LU.begin(), LU.end(), M->getRemetente());
                  if(remetente_prov!=LU.end())
                  {
                    if(remetente_prov->connected())
                    {
                        bool envioOK = (remetente_prov->write_int(CMD_MSG_LIDA2) != mysocket_status::SOCK_ERROR);
                        if (envioOK) envioOK = (remetente_prov->write_int(M->getId()) != mysocket_status::SOCK_ERROR);
                        if (envioOK)
                        {
                            imprimeComandoEnviado(M->getRemetente(), CMD_MSG_LIDA2, M->getId());
                            LM.erase(M);
                        }
                    }
                  }
                  // Nao deve ocorrer, pois a mensagem jah foi encontrada com o remetente lido
                  else
                  {
                      cerr << "Erro inesperado no remetente '" << M->getRemetente() << "'. Desconectando...\n";
                      iUsuario->close();
                  }
                }
                break;
              } // Fim do case CMD_MSG_LIDA1
              case CMD_LOGOUT_USER:
              {
                imprimeComandoRecebido(iUsuario->getLogin(), CMD_LOGOUT_USER);
                iUsuario->close();
                break;
              } // Fim do case CMD_LOGOUT_USER
              } // Fim do switch
          } // Fim do if (had_activity) no socket do cliente
      } // Fim do for na lista de usuarios

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
            cerr << "Erro na leitura do login. Desconectando...\n";
            t.close();
          }
        }
        // Leh o parametro com a senha do usuario que deseja se conectar
        if (t.connected())
        {
          iResult = t.read_string(senha, TIMEOUT_LOGIN_WHATSPROG*1000);
          if (iResult != mysocket_status::SOCK_OK)
          {
            cerr << "Erro na leitura da senha. Desconectando...\n";
            t.close();
          }
        }
        // Testa o login e senha
        if (t.connected() &&
            (!testarNomeUsuario(login) || !testarSenha(senha)))
        {
          cerr << "Login/senha (" << login << "/" << senha << ") invalido/invalida. Desconectando...\n";
          t.write_int(CMD_LOGIN_INVALIDO);
          t.close();
        }
        // Testa se o usuario eh adequado
        if (t.connected())
        {
          iUsuario = find(LU.begin(), LU.end(), login);

          if (cmd == CMD_NEW_USER)
          {
            imprimeComandoRecebido(login, CMD_NEW_USER);

            // Verifica se jah existe um usuario cadastrado com esse login
            if (iUsuario!=LU.end())
            {
              // Jah existe um usuario com esse login. Nao pode criar
              cerr << "Login (" << login << ") jah utilizado. Desconectando...\n";
              t.write_int(CMD_LOGIN_INVALIDO);
              t.close();
            }

            if (t.connected())
            {
              // Insere novo usuario
              Usuario novo;
              if(novo.setUsuario(login,senha))
              {
                  novo.swapSocket(t);
                  LU.push_back(novo);
                  novo.write_int(CMD_LOGIN_OK);
                  imprimeComandoEnviado(novo.getLogin(), CMD_LOGIN_OK);

                  // Faz com que iUsuario receba o novo usuario
                  iUsuario = find(LU.begin(), LU.end(), login);
              }
              else
              {
                cerr << "Usuario (" << login << "/" << senha << ") e/ou socket invalidos. Desconectando...\n";
                t.write_int(CMD_LOGIN_INVALIDO);
                t.close();
              }
            }
          }
          else  // else cmd == CMD_NEW_USER; implica cmd eh CMD_LOGIN_USER
          {
            imprimeComandoRecebido(login, CMD_LOGIN_USER);

            if(iUsuario==LU.end())
            {
              // Nao existe um usuario com esse login. Nao pode conectar
              cerr << "O login (" << login << ") nao existe. Desconectando...\n";
              t.write_int(CMD_LOGIN_INVALIDO);
              t.close();
            }
            // Testa se a senha confere
            if (t.connected() && !iUsuario->validarSenha(senha))
            {
              // Senha invalida
              cerr << "A senha para o usuario (" << login << ") nao confere. Desconectando...\n";
              t.write_int(CMD_LOGIN_INVALIDO);
              t.close();
            }
            // Testa se o cliente jah estah conectado
            if (t.connected() && iUsuario->connected())
            {
              // O usuario jah estah conectado
              cerr << "O usuario (" << login << ") jah estah conectado. Desconectando...\n";
              t.write_int(CMD_LOGIN_INVALIDO);
              t.close();
            }
            // Associa o socket que se conectou a um usuario cadastrado
            if (t.connected())
            {
              iUsuario->swapSocket(t);
              iUsuario->write_int(CMD_LOGIN_OK);
              imprimeComandoEnviado(iUsuario->getLogin(), CMD_LOGIN_OK);
            }
          } // fim cmd eh CMD_LOGIN_USER

          // Se for um cliente antigo, envia para o cliente que se reconectou:
          // a) as mensagens enviadas para ele que estao no buffer
          // b) as confirmacoes de visualizacao para ele que estao no buffer
          // c) as confirmacoes de entrega para ele que estao no buffer
          if (iUsuario->connected() && cmd==CMD_LOGIN_USER)
          {
            // mensagens enviadas para ele que estao no buffer
            enviarMsgsParaUsuario(iUsuario);
            // as confirmacoes de visualizacao para ele que estao no buffer
            enviarConfirmacoesParaUsuario(iUsuario);
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
  for(iter_Usuario user=LU.begin(); user!=LU.end(); user++)
    user->close();
}
