#ifndef _DADOS_SERVIDOR_
#define _DADOS_SERVIDOR_

#include <string>
#include <list>
#include "mysocket.h"
#include "dados_whatsprog.h"

using namespace std;

/// Os usuarios cadastrados no servidor
class Usuario
{
private:
  /// Identificacao do usuario
  string login;
  string senha;

  /// Socket de comunicacao (idle se nao conectado)
  tcp_mysocket s;

  /// Ultima id de mensagem recebida
  int32_t last_id;

public:
  /// Construtor default
  inline Usuario(): login(""), senha(""), s(), last_id(0) {}

  /// Funcao de consulta ao valor para login
  inline const string& getLogin() const {return login;}

  /// Funcao de consulta ao valor para senha
  inline const string& getSenha() const {return senha;}

  /// Funcao de fixacao de valor para login e senha
  /// Retorna true em caso de sucesso, false se erro
  bool setUsuario(const string &L, const string &S);

  /// Testa se a senha eh valida
  /// Aqui normalmente haveria criptografia.
  /// Mas como eh um software didatico...
  inline bool validarSenha(const string& S) const {return senha==S;}

  /// Funcoes de acesso ao socket do usuario
  inline const tcp_mysocket& getSocket() const {return s;}

  /// Alteracao do socket de um usuario
  inline void swapSocket(tcp_mysocket& S) {s.swap(S);}

  /// Consulta do estado do socket
  inline bool connected() const {return s.connected();}
  inline bool closed() const {return s.closed();}

  /// Funcoes de envio de dados via socket
  inline mysocket_status read_int(int32_t &num, long milisec=-1) const
  {
    return s.read_int(num,milisec);
  }
  inline mysocket_status write_int(int32_t num) const
  {
    return s.write_int(num);
  }
  inline mysocket_status read_string(string &msg, long milisec=-1) const
  {
    return s.read_string(msg,milisec);
  }
  inline mysocket_status write_string(const string &msg) const
  {
    return s.write_string(msg);
  }

  /// Fechamento do socket
  inline void close() {s.close();}

  /// Consulta da ultima ID do usuario
  inline int32_t getLastId() const {return last_id;}

  /// Alteracao da ultima ID do usuario
  bool setLastId(int32_t ID);

  /// Reinicializa a ID do usuario
  inline void resetId() {last_id=0;}

  /// Sobrecarga do operador de igualdade
  inline bool operator==(const string &M) const {return login == M;}
};

/// Apelidos para uma lista de usuarios e para o iterator correspondente
typedef list<Usuario> listUsuario;
typedef listUsuario::iterator iter_Usuario;

class DadosServidor
{
private:
  /// O socket de conexoes
  tcp_mysocket_server c;

  // Lista dos usuarios que estao conectados ou nao
  list<Usuario> LU;

  // Buffer de mensagens
  list<Mensagem> LM;

  /// Envia para o usuario as mensagens que estejam arquivadas (paraUsuario[])
  /// com status MSG_RECEBIDA e que seja destinada ao usuario.
  /// Apos o envio, altera o status das msgs enviada para MSG_ENTREGUE
  void enviarMsgsParaUsuario(iter_Usuario iDest);

  /// Envia para o usuario as confirmacoes de visualizacao das mensagens
  /// que estejam arquivadas (doUsuario[]) com status MSG_LIDA
  /// e que tenha sido enviada pelo usuario.
  /// Apos o envio da confirmacao, apaga as msgs
  void enviarConfirmacoesParaUsuario(iter_Usuario iRemet);

public:
  /// Funcoes de acesso aas funcionalidades basicas dos sockets
  inline mysocket_status listen(const char *port, int nconex=1)
  {
    return c.listen(port,nconex);
  }

  /// Fecha os sockets de conexao e de todos os usuarios conectados
  void closeSockets();

  /// Thread que efetivamente desempenha as tarefas do servidor
  int main();
};

#endif //DADOS_SERVIDOR_
