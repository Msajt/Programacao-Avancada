#include <QMessageBox>
#include <QWindow>
#include <QDebug>
#include <iostream>
#include <cstdio>
#include <thread>
#include "whatsprogmain.h"
#include "ui_whatsprogmain.h"
#include "mysocket.h"

using namespace std;

// MENSAGENS DE TODAS AS CONVERSAS DO WHATSPROG
extern DadosCliente DC;

// CLIENTE SOCKET, UTILIZADO PELAS THREADS
extern tcp_mysocket sock;

// THREAD
extern thread thr;

/// Construtor da janela principal da interface
WhatsProgMain::WhatsProgMain(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::WhatsProgMain),
  loginDialog(nullptr),
  novaConversa(nullptr),
  labelConexao(nullptr)
{
  ui->setupUi(this);

  // Item a ser incluido nas tabelas
  QTableWidgetItem *newItem;
  QFont boldFont;
  boldFont.setBold(true);

  // A lista da esquerda (conversas)
  ui->tableConversas->setColumnCount(2);
  ui->tableConversas->setShowGrid(false);
  ui->tableConversas->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->tableConversas->setSelectionMode(QAbstractItemView::SingleSelection);
  ui->tableConversas->setTabKeyNavigation(false);
  ui->tableConversas->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
  ui->tableConversas->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
  ui->tableConversas->horizontalHeader()->setSectionsClickable(false);
  // O cabecalho
  ui->tableConversas->setStyleSheet("QHeaderView::section { background-color:lightgray }");
  newItem = new QTableWidgetItem("N Msg");
  newItem->setTextAlignment(Qt::AlignCenter);
  newItem->setFont(boldFont);
  ui->tableConversas->setHorizontalHeaderItem(0, newItem);
  newItem = new QTableWidgetItem("Usuario");
  newItem->setTextAlignment(Qt::AlignCenter);
  newItem->setFont(boldFont);
  ui->tableConversas->setHorizontalHeaderItem(1, newItem);

  // A lista da direita (mensagens)
  ui->tableMensagens->setColumnCount(3);
  ui->tableMensagens->setShowGrid(true);
  ui->tableMensagens->setSelectionBehavior(QAbstractItemView::SelectRows);
  ui->tableMensagens->setSelectionMode(QAbstractItemView::NoSelection);
  ui->tableMensagens->setTabKeyNavigation(false);
  ui->tableMensagens->horizontalHeader()->setSectionResizeMode(0,QHeaderView::ResizeToContents);
  ui->tableMensagens->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
  ui->tableMensagens->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
  ui->tableMensagens->horizontalHeader()->setSectionsClickable(false);
  // O cabecalho
  newItem = new QTableWidgetItem("Id");
  newItem->setTextAlignment(Qt::AlignCenter);
  newItem->setFont(boldFont);
  ui->tableMensagens->setHorizontalHeaderItem(0, newItem);
  ui->tableMensagens->setStyleSheet("QHeaderView::section { background-color:lightgray }");
  newItem = new QTableWidgetItem("Mensagem");
  newItem->setTextAlignment(Qt::AlignCenter);
  newItem->setFont(boldFont);
  ui->tableMensagens->setHorizontalHeaderItem(1, newItem);
  newItem = new QTableWidgetItem("St");
  newItem->setTextAlignment(Qt::AlignCenter);
  newItem->setFont(boldFont);
  ui->tableMensagens->setHorizontalHeaderItem(2, newItem);

  // Cria caixas de dialogos de login e de nova conversa
  loginDialog = new LoginDialog(this);
  novaConversa = new NovaConversa(this);

  // Barra de status
  labelConexao = new QLabel(this);

  // Interface desconectada
  interfaceDesconectada();

  // Conexões
    // ==> CONECTAR SIGNAL - Criar usuário
  connect(loginDialog, SIGNAL(signCriarUsuario(QString, QString, QString)),
          this, SLOT(slotCriarUsuario(QString, QString, QString)));
    // ==> CONECTAR SIGNAL - Usuário existente
  connect(loginDialog, SIGNAL(signLogarUsuario(QString, QString, QString)),
          this, SLOT(slotLogarUsuario(QString, QString, QString)));
    // ==> CONECTAR SIGNAL - Nova conversa
  connect(novaConversa, SIGNAL(signNovaConversa(QString)),
          this, SLOT(slotNovaConversa(QString)));
}

WhatsProgMain::~WhatsProgMain()
{
    delete ui;
}

string toString(int i)
{
    static char buf[80];
    snprintf(buf,80,"%d",i);
    return buf;
}

// ============================== THREAD =========================
void main_thread(void)
{
    // O status de retorno das funcoes do socket
      mysocket_status iResult;

      while (sock.connected())
      {
        int32_t cmd;
        iResult = sock.read_int(cmd,1000*TIMEOUT_WHATSPROG);
        if (iResult == mysocket_status::SOCK_OK)
        {
          IterConversa it;
          int32_t id;

          switch(cmd)
          {
          case CMD_NEW_USER:
          case CMD_LOGIN_USER:
          case CMD_LOGIN_OK:
          case CMD_LOGIN_INVALIDO:
          case CMD_MSG_LIDA1:

          case CMD_LOGOUT_USER:
          default:
            // Ignorar: erro do servidor
            break;
          case CMD_NOVA_MSG:
          {
            string remetente;
            string texto;

            // Receber a msg
            iResult = sock.read_int(id, TIMEOUT_WHATSPROG*1000);
            if (iResult == mysocket_status::SOCK_OK) iResult = sock.read_string(remetente, TIMEOUT_WHATSPROG*1000);
            if (iResult == mysocket_status::SOCK_OK) iResult = sock.read_string(texto, TIMEOUT_WHATSPROG*1000);
            if (iResult == mysocket_status::SOCK_OK)
            {
              it = DC.findConversa(remetente);
              if (it == DC.end())
              {
                if (DC.insertConversa(remetente))
                {
                  // A conversa recem-inserida eh a ultima
                  it = DC.last();
                }
              }
              if (it != DC.end())
              {
                // Conversa existe
                Mensagem M;
                // Testa se os parametros da msg estao corretos
                if (M.setId(id) && M.setRemetente(remetente) && M.setDestinatario(DC.getMeuUsuario()) &&
                    M.setTexto(texto) && M.setStatus(MsgStatus::MSG_ENTREGUE))
                {
                  // Insere a mensagem na conversa
                  DC.pushMessage(it,M);
                  // Move a conversa com a nova msg para o inicio da lista (begin)
                  DC.moveConversaToBegin(it);
                  // Modificou o numero de mensagens da conversa
                  // Atualizar a celula correspondente na janela de conversas
                  //** avisaNovaMsg(it);

                }
              }
            }
            else
            {
              // Nao conseguiu ler a msg recebida
              sock.close();
            }
            break;
          } // fim do case CMD_NOVA_MSG
          case CMD_MSG_RECEBIDA:
          case CMD_MSG_ENTREGUE:
          case CMD_MSG_LIDA2:
          {
            int ind_msg;

            // Receber a id
            iResult = sock.read_int(id, TIMEOUT_WHATSPROG*1000);
            if (iResult == mysocket_status::SOCK_OK)
            {
              // Procura se existe uma mensagem com essa id;
              DC.findMensagem(id, it, ind_msg);
              if (it!=DC.end() && ind_msg>=0)
              {
                // Encontrou a msg com essa id
                // Testa o status atual
                bool status_ok(false);
                MsgStatus novoStatus(MsgStatus::MSG_INVALIDA);
                if (cmd==CMD_MSG_RECEBIDA)
                {
                  status_ok = (it->getMensagem(ind_msg).getStatus()==MsgStatus::MSG_ENVIADA);
                  novoStatus = MsgStatus::MSG_RECEBIDA;
                }
                if (cmd==CMD_MSG_ENTREGUE)
                {
                  status_ok = (it->getMensagem(ind_msg).getStatus()==MsgStatus::MSG_ENVIADA ||
                               it->getMensagem(ind_msg).getStatus()==MsgStatus::MSG_RECEBIDA);
                  novoStatus = MsgStatus::MSG_ENTREGUE;
                }
                if (cmd==CMD_MSG_LIDA2)
                {
                  status_ok = (it->getMensagem(ind_msg).getStatus()==MsgStatus::MSG_ENVIADA ||
                               it->getMensagem(ind_msg).getStatus()==MsgStatus::MSG_RECEBIDA ||
                               it->getMensagem(ind_msg).getStatus()==MsgStatus::MSG_ENTREGUE);
                  novoStatus = MsgStatus::MSG_LIDA;
                }
                // Testa o remetente e o status
                if (it->getMensagem(ind_msg).getRemetente()==DC.getMeuUsuario() && status_ok)
                {
                  // A msg encontrada eh de minha autoria e estah com um dos status correto
                  DC.setStatus(it,ind_msg,novoStatus);
                }
                else
                {
                  // A msg com essa id nao estah na situacao esperada
                  // Ignorar: erro do servidor ou do cliente
                }
              }
              else
              {
                // Nao existe msg com essa id
                // Ignorar: erro do servidor ou do cliente
              }
            }
            else
            {
              // Nao conseguiu ler a id
              sock.close();
            }

            break;
          } // fim do case CMD_MSG_<status>
          case CMD_ID_INVALIDA:
          case CMD_USER_INVALIDO:
          case CMD_MSG_INVALIDA:
          {
            int ind_msg;

            // Receber a id
            iResult = sock.read_int(id, TIMEOUT_WHATSPROG*1000);
            if (iResult == mysocket_status::SOCK_OK)
            {
              // Procura se existe uma mensagem com essa id;
              DC.findMensagem(id, it, ind_msg);
              if (it!=DC.end() && ind_msg>=0)
              {
                // Encontrou a msg com essa id
                // Testa o remetente e o status
                if (it->getMensagem(ind_msg).getRemetente()==DC.getMeuUsuario() &&
                    it->getMensagem(ind_msg).getStatus()==MsgStatus::MSG_ENVIADA)
                {
                  // A msg encontrada eh de minha autoria e estah com um dos status apropriado
                  // Remover msg
                  DC.eraseMessage(it,ind_msg);
                  qDebug() << "Erro na mensagem com id=" << toString(id).c_str() << ". Removendo";
                }
                else
                {
                  // A msg com essa id nao estah na situacao esperada
                  // Ignorar: erro do servidor ou do cliente
                }
              }
              else
              {
                // Nao existe msg com essa id
                // Ignorar: erro do servidor ou do cliente
              }
            }
            else
            {
              // Nao conseguiu ler a id
              sock.close();
            }
            break;
          } // Fim do case CMD_<campo>_INVALIDA
          } // Fim do switch
        }
        else // erro na sock.read_int(cmd)
        {
          // A leitura do comando (int) retornou
          // mysocket_status::SOCK_ERROR, mysocket_status::SOCK_DISCONNECTED ou mysocket_status::SOCK_TIMEOUT
          // Se for mysocket_status::SOCK_TIMEOUT, aproveita para salvar o arquivo com os dados
          // Nos outros dois casos, a conexao encerrou, de forma correta ou com erro.
          if (iResult == mysocket_status::SOCK_TIMEOUT)
          {
            if (!DC.salvar())
            {
              qDebug() << "Erro no salvamento do arquivo " << DC.getNomeArq().c_str();
            }
          }
          else
          {
            sock.close();
          }
        }
      } // fim do while (sock.connected())

      // Envia o comando de logout
      if (sock.connected())
      {
        sock.write_int(CMD_LOGOUT_USER);
      }

      // Encerra o socket
      sock.close();

      // Salva as informacoes do cliente
      DC.salvar();
}

void WhatsProgMain::on_actionNova_conversa_triggered()
{
  novaConversa->show();
}

// ========================= REMOVER CONVERSA =========================
void WhatsProgMain::on_actionRemover_conversa_triggered()
{
    // Pegar o iterador correspondente das mensagens que eu quero apagar
    IterConversa it = DC.getConversaAtual();

    // Deletar a conversa
    DC.eraseConversa(it);

    // Listar conversas
    listarConversas();
    on_actionApagar_mensagens_triggered();
    ui->labelMensagens->setText("NENHUMA MENSAGEM SELECIONADA");
}

// ========================= APAGAR MENSAGENS =========================
void WhatsProgMain::on_actionApagar_mensagens_triggered()
{
    // Pegar o iterador correspondente das mensagens que eu quero apagar
    IterConversa it = DC.getConversaAtual();
    // Deletar mensagens do buffer de mensagens
    DC.clearMessages(it);

    // Mudar a interface com as mudanças atuais
    ui->tableMensagens->clearContents();
    ui->tableMensagens->setRowCount(0);

    // Lista conversas
    listarConversas();
}


void WhatsProgMain::on_actionNovo_usuario_triggered()
{
  // Muda o titulo...
  loginDialog->setWindowTitle("Usuário - Criar");
  loginDialog->show();
}

void WhatsProgMain::on_actionUsuario_existente_triggered()
{
  // Muda o titulo...
  loginDialog->setWindowTitle("Usuário - Existente");
  loginDialog->show();
}

// ========================= DESCONECTAR =========================
void WhatsProgMain::on_actionDesconectar_triggered()
{
    // Desconectar do servidor
    // Envia o comando de logout para o servidor
        if (sock.connected())
        {
          // Envia o comando de logout
          sock.write_int(CMD_LOGOUT_USER);
        }

        // Fecha o socket e, consequentemente,
        // encerra a thread de leitura de dados do socket
        sock.close();

        // Limpa os nomes do servidor e usuario
        DC.unsetServidorUsuario();

    // Exibir interface desconectado
        interfaceDesconectada();
        ui->tableMensagens->setRowCount(0);
}

void WhatsProgMain::on_actionSair_triggered()
{
    QApplication::quit();
}

void WhatsProgMain::on_tableConversas_cellActivated(int row, int)
{
    on_tableConversas_cellClicked(row, 0);
}

// ========================= CLICAR NA TABELA DE CONVERSAS =========================
void WhatsProgMain::on_tableConversas_cellClicked(int row, int)
{
    qDebug() << "TESTE";
    // Setar como nova conversa
    string destinatario = ui->tableConversas->cellWidget(row, 1)->property("text").toString().toStdString();
    qDebug() << "TESTANDO USUARIO " << destinatario.c_str();
    if(!DC.setConversaAtual(destinatario)) QMessageBox::critical(this, "ERRO", "ERRO AO SETAR CONVERSA");
    qDebug() << "TESTE CONVERSA ATUAL";
    if(!DC.moveConversaToBegin(DC.getConversaAtual())) QMessageBox::critical(this, "ERRO", "ERRO AO MANDAR PARA O INICIO");
    qDebug() << "MOVE CONVERSA PRO COMEÇO";

    ui->labelMensagens->setText("CONVERSA: " + QString(destinatario.c_str()));

    listarConversas();

    ui->tableConversas->cellWidget(0, 0)->setStyleSheet("font-weight: bold");
    ui->tableConversas->cellWidget(0, 1)->setStyleSheet("font-weight: bold");

    // Fazer o for pro 'Table Widget' das mensagens e exibir as mensagens correspondentes da linha clicada
    listarMensagens(DC.getConversaAtual());
}

// ========================= AO APERTAR O ENTER PRA MENSAGEM =========================
void WhatsProgMain::on_lineEditMensagem_returnPressed()
{
    IterConversa it = DC.getConversaAtual();
    // Setar a mensagem que será enviada
    Mensagem M;
    string mensagem = ui->lineEditMensagem->text().toStdString();

    if(!testarTextoMensagem(mensagem)) QMessageBox::critical(this, "ERRO AO ENVIAR MENSAGEM", "O texto seguinte é muito longo");
    // Define os campos da msg
        if (!M.setId(DC.getNovaIdMensagem()) ||
            !M.setRemetente(DC.getMeuUsuario()) ||
            !M.setDestinatario(it->getCorrespondente()) ||
            !M.setTexto(mensagem) ||
            !M.setStatus(MsgStatus::MSG_ENVIADA))
        {
          // Desconecta
          sock.close();
          // Mensagem de erro
          QMessageBox::critical(this, "ERRO MENSAGEM", "Mensagem inválida");
        }
    // Incluir no database
        DC.pushMessage(it, M);

        // Envia a msg via socket para o servidor
            bool envioOK = (sock.write_int(CMD_NOVA_MSG) != mysocket_status::SOCK_ERROR);
            if (envioOK) envioOK = (sock.write_int(M.getId()) != mysocket_status::SOCK_ERROR);
            if (envioOK) envioOK = (sock.write_string(M.getDestinatario()) != mysocket_status::SOCK_ERROR);
            if (envioOK) envioOK = (sock.write_string(M.getTexto()) != mysocket_status::SOCK_ERROR);
            if (envioOK)
            {
              // Move a conversa com a nova msg para o inicio da lista (begin)
              DC.moveConversaToBegin(it);
            }
            else
            {
              // Remove ultima msg da conversa
              DC.popMessage(it);
              // Desconecta
              sock.close();
              // Mensagem de erro
              QMessageBox::critical(this, "ERRO", "Erro no envio da mensagem");
            }

    // Limpar
        ui->tableMensagens->clearContents();
        ui->lineEditMensagem->clear();

    // Enviar mensagem (LISTAR MENSAGENS)
        listarMensagens(it);
}

// =============== CONEXÕES CRIAR/LOGAR USUARIO ===============
void WhatsProgMain::slotCriarUsuario(QString ip, QString usuario, QString senha)
{
    qDebug() << "SLOT DE CRIAÇÃO DE USUARIO";
    string newIp = ip.toStdString();
    string newUsuario = usuario.toStdString();
    string newSenha = senha.toStdString();

    if(!aceitaUsuario(newIp, newUsuario, newSenha, 1)) QMessageBox::critical(this, "Erro ao criar usuário", "Houve algum problema");
}

void WhatsProgMain::slotLogarUsuario(QString ip, QString usuario, QString senha)
{
    qDebug() << "SLOT DE LOGIN DO USUARIO";
    string newIp = ip.toStdString();
    string newUsuario = usuario.toStdString();
    string newSenha = senha.toStdString();

    if(!aceitaUsuario(newIp, newUsuario, newSenha, 0)) QMessageBox::critical(this, "Erro ao logar usuário", "Houve algum problema");
}

// ========================= NOVA CONVERSA =========================
void WhatsProgMain::slotNovaConversa(QString usuario)
{
    string destinatario = usuario.toStdString();

    // Testar se o nome é válido
    if(!testarNomeUsuario(destinatario)) QMessageBox::critical(this, "ERRO", "Houve algum problema com o nome do destinatário");

    // Inserir nova conversa
    if(!DC.insertConversa(destinatario)) QMessageBox::critical(this, "ERRO", "Nova conversa com " + QString(destinatario.c_str()) + " é invalida.");

    // Exibir todas as conversas ativas para na tabela (FAZER UMA FUNÇÃO EXIBIR TABELAS)
    ui->menuMensagens->setEnabled(1);
    ui->lineEditMensagem->setEnabled(1);
    DC.setConversaAtual(destinatario);
    //IterConversa it = DC.getConversaAtual();

    listarConversas();

    //listarMensagens(it);
}

// ========================= ACEITAR USUARIO =========================
bool WhatsProgMain::aceitaUsuario(const string &IP, const string &login, const string &senha, bool novoUsuario)
{
    if (sock.connected())
      {
        QMessageBox::critical(this, "ERRO", "Esta funcao soh deve ser chamada quando o cliente estah desconectado");
        return false;
      }

      bool conexaoOK(true);
      int32_t cmd;

      // Conecta o socket
      if (sock.connect(IP.c_str(), PORTA_WHATSPROG) != mysocket_status::SOCK_OK)
      {
        sock.close();
        return false;
      }

      // Envia a msg de conexao para o servidor, atraves do socket
      if (novoUsuario)
      {
        // Testa se eh possivel cadastrar um novo usuario com esses ip, login e senha
        // Envia o comando CMD_NEW_USER
        if (conexaoOK) conexaoOK = (sock.write_int(CMD_NEW_USER) != mysocket_status::SOCK_ERROR);
      }
      else
      {
        // Testa se eh possivel se conectar com esses ip, login e senha
        // Envia o comando CMD_LOGIN_USER
        if (conexaoOK) conexaoOK = (sock.write_int(CMD_LOGIN_USER) != mysocket_status::SOCK_ERROR);
        listarConversas();
      }
      if (!conexaoOK) return false;

      // Envia os parametros do comando (login, senha)
      if (conexaoOK) conexaoOK = (sock.write_string(login) != mysocket_status::SOCK_ERROR);
      if (conexaoOK) conexaoOK = (sock.write_string(senha) != mysocket_status::SOCK_ERROR);
      if (!conexaoOK)
      {
        sock.close();
        return false;
      }
      conexaoOK = (sock.read_int(cmd,1000*TIMEOUT_WHATSPROG) == mysocket_status::SOCK_OK);
      if (conexaoOK) conexaoOK = (cmd == CMD_LOGIN_OK);
      if (!conexaoOK)
      {
        sock.close();
        return false;
      }

      // Armazena o novo nome do servidor e do usuario
      DC.setServidorUsuario(IP,login);

      // Leh o arquivo com os dados de conexao anterior, caso exista
      DC.ler();

      // Lanca a thread de leitura dos dados do socket
      // Tem que ser depois de ler o arquivo com os dados da conexao anterior
      // Senao, pode ficar com duas conversas referentes ao mesmo usuario:
      // 1) Chegou uma msg que estava retida no servidor
      // 2) Leu uma conversa previa com mesmo usuario do arquivo
      thr = std::thread(main_thread);


      // Se soh tiver uma conversa, seleciona-a como ativa
      if (DC.size() == 1)
      {
        DC.setConversaAtual(DC.begin());
      }

      // Tudo OK!
      interfaceConectada(DC.getMeuUsuario(), DC.getServidor());
      return true;
}

// ========================= INTERFACES CONECTADA E DESCONECTADA =========================
void WhatsProgMain::interfaceDesconectada()
{
    ui->tableConversas->clearContents();
    ui->tableMensagens->clearContents();
    labelConexao->setText("NAO CONECTADO");
    statusBar()->insertWidget(0, labelConexao);
    ui->lineEditMensagem->setEnabled(0);
    ui->menuMensagens->setEnabled(0);
    ui->menuConversa->setEnabled(0);
}

void WhatsProgMain::interfaceConectada(string user, string servidor)
{
    string user_servidor = "CONECTADO: " + user + "@" + servidor;
    labelConexao->setText(user_servidor.c_str());
    statusBar()->insertWidget(0, labelConexao);
    ui->menuConversa->setEnabled(1);
}

// ========================= LISTAR MENSAGENS =========================
void WhatsProgMain::listarMensagens(IterConversa it)
{
    bool envioOK = true;
    QLabel *prov;

    ui->tableMensagens->clearContents();
    ui->tableMensagens->setRowCount(it->size());

    for(unsigned i=0; i<it->size(); i++){
        // id
        int id = it->getMensagem(i).getId();
        QString idString = QString::number(id);
        prov = new QLabel(idString.toStdString().c_str());
        prov->setAlignment(Qt::AlignCenter);

        if(it->getMensagem(i).getRemetente() == DC.getMeuUsuario()) prov->setStyleSheet("background: lightgreen");

        ui->tableMensagens->setCellWidget(i, 0, prov);

        if(it->getMensagem(i).getRemetente() == DC.getMeuUsuario()){
            // mensagem
            string mensagem = it->getMensagem(i).getTexto();
            prov = new QLabel(mensagem.c_str());
            prov->setAlignment(Qt::AlignVCenter|Qt::AlignRight);
            prov->setStyleSheet("background: lightgreen");
            ui->tableMensagens->setCellWidget(i, 1, prov);

            // estado
            if (it->getMensagem(i).getStatus() == MsgStatus::MSG_ENVIADA){
                //prov = new QLabel("?");
                prov = new QLabel();
                prov->setPixmap(QPixmap(":/new/images/status0.png"));
            }
            if (it->getMensagem(i).getStatus() == MsgStatus::MSG_RECEBIDA){
                //prov = new QLabel("V");
                prov = new QLabel();
                prov->setPixmap(QPixmap(":/new/images/status1.png"));
            }
            if (it->getMensagem(i).getStatus() == MsgStatus::MSG_ENTREGUE){
                //prov = new QLabel("VV");
                prov = new QLabel();
                prov->setPixmap(QPixmap(":/new/images/status2.png"));
            }
            if (it->getMensagem(i).getStatus() == MsgStatus::MSG_LIDA){
                //prov = new QLabel("VVV");
                prov = new QLabel();
                prov->setPixmap(QPixmap(":/new/images/status3.png"));
            }
            prov->setScaledContents(true);
            ui->tableMensagens->setCellWidget(i, 2, prov);
        } else{
            string mensagem = it->getMensagem(i).getTexto();
            prov = new QLabel(mensagem.c_str());
            prov->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);
            ui->tableMensagens->setCellWidget(i, 1, prov);

            prov = new QLabel();
            prov->setPixmap(QPixmap(":/new/images/status_other.png"));
            prov->adjustSize();
            ui->tableMensagens->setCellWidget(i, 2, prov);

            // A msg eh de autoria do outro
            // Muda o status de todas as msgs que foram enviadas para mim de ENTREGUE -> LIDA
            // Enviar confirmacao de visualizaco
            if(it->getMensagem(i).getStatus() == MsgStatus::MSG_ENTREGUE){
                // Envia msg ao servidor informando que a msg foi lida
                if(envioOK) envioOK = (sock.write_int(CMD_MSG_LIDA1) != mysocket_status::SOCK_ERROR);
                if(envioOK) envioOK = (sock.write_int(it->getMensagem(i).getId()) != mysocket_status::SOCK_ERROR);
                if(envioOK) envioOK = (sock.write_string(it->getMensagem(i).getRemetente()) != mysocket_status::SOCK_ERROR);
                if(envioOK){
                    // Muda status na base de dados local
                    DC.setStatus(it,i,MsgStatus::MSG_LIDA);
                }
            }
        }
        ui->tableMensagens->viewport()->update();
    }

    ui->tableConversas->viewport()->update();

    if (!envioOK){
        // Desconecta
        sock.close();
        // Mensagem de erro
        QMessageBox::critical(this, "ERRO", "Falha no envio das confimacoes de visualizacao");
    }

}

void WhatsProgMain::listarConversas()
{
    // Trocar o estado do 'Table Widget' das conversas
    ui->tableConversas->clearContents();
    ui->tableConversas->setRowCount(DC.size());

    // Ponteiro do QLabel
    QLabel *prov;

    unsigned cont(0);
    for(IterConversa it=DC.begin(); it!=DC.end(); it++){
        QString nMensagens = QString::number(it->getNumMsgsEntregues()) + "/" + QString::number(it->size());
        prov = new QLabel(nMensagens);
        prov->setAlignment(Qt::AlignCenter);
        ui->tableConversas->setCellWidget(cont, 0, prov);

        QString destinatario = it->getCorrespondente().c_str();
        prov = new QLabel(destinatario);
        prov->setAlignment(Qt::AlignCenter);
        ui->tableConversas->setCellWidget(cont, 1, prov);

        if(it->getNumMsgsEntregues() > 0){
            ui->tableConversas->cellWidget(cont, 0)->setStyleSheet("background-color:lightgreen");
            ui->tableConversas->cellWidget(cont, 1)->setStyleSheet("background-color:lightgreen");
        } else{
            ui->tableConversas->cellWidget(cont, 0)->setStyleSheet("background-color:white");
            ui->tableConversas->cellWidget(cont, 1)->setStyleSheet("background-color:white");
        }

        cont++;
    }

    ui->tableConversas->viewport()->update();
}
