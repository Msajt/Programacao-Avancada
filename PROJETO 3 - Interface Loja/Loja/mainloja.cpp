#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <cmath>  // round
#include "mainloja.h"
#include "ui_mainloja.h"

MainLoja::MainLoja(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainLoja)
  , X()
  , inclLivro(NULL)
  , inclCD(NULL)
  , inclDVD(NULL)
  , total_itens(NULL)
{
  ui->setupUi(this);

  // Cria as janelas para inclusao de novos itens
  inclLivro = new IncluirLivro(this);
  inclCD = new IncluirCD(this);
  inclDVD = new IncluirDVD(this);

  // Cria os QLabel da barra de status
  statusBar()->insertWidget(0,new QLabel("Total de itens: "));
  total_itens = new QLabel(this);
  total_itens->setNum(0);
  statusBar()->insertWidget(1,total_itens);

  // Conexao dos sinais e slots para inclusao de itens
  connect(inclLivro, SIGNAL(signIncluirLivro(QString,QString,QString)),
          this, SLOT(slotIncluirLivro(QString,QString,QString)));
  connect(inclCD, SIGNAL(signIncluirCD(QString,QString,QString)),
          this, SLOT(slotIncluirCD(QString,QString,QString)));
  connect(inclDVD, SIGNAL(signIncluirDVD(QString,QString,QString)),
          this, SLOT(slotIncluirDVD(QString,QString,QString)));

  // Altera a cor de fundo dos titulos das tabelas
  ui->label_livro->setStyleSheet("background:lightgray");
  ui->label_CD->setStyleSheet("background:lightgray");
  ui->label_DVD->setStyleSheet("background:lightgray");

  // Cabecalhos da tabela de livros
  ui->table_livro->setStyleSheet("QHeaderView::section { background-color:lightgray }");
  ui->table_livro->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
  ui->table_livro->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
  ui->table_livro->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
  ui->table_livro->setHorizontalHeaderLabels(QStringList() << "NOME" << "PRECO" << "AUTOR");

  // Cabecalhos da tabela de CDs
  ui->table_CD->setStyleSheet("QHeaderView::section { background-color:lightgray }");
  ui->table_CD->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
  ui->table_CD->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
  ui->table_CD->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
  ui->table_CD->setHorizontalHeaderLabels(QStringList() << "NOME" << "PRECO" << "N FAIXAS");

  // Cabecalhos da tabela de DVDs
  ui->table_DVD->setStyleSheet("QHeaderView::section { background-color:lightgray }");
  ui->table_DVD->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
  ui->table_DVD->horizontalHeader()->setSectionResizeMode(1,QHeaderView::ResizeToContents);
  ui->table_DVD->horizontalHeader()->setSectionResizeMode(2,QHeaderView::ResizeToContents);
  ui->table_DVD->setHorizontalHeaderLabels(QStringList() << "NOME" << "PRECO" << "DURACAO");

  // Reexibe todas as tabelas
  exibeListas();
}

MainLoja::~MainLoja()
{
  delete ui;
}


void MainLoja::on_actionLer_triggered()
{
  QString fileName = QFileDialog::getOpenFileName(this, "Ler estoque", "",
          "Estoques (*.txt);;Todos (*.*)");

  if (!fileName.isEmpty())
  {
    // Le o estoque com nome "fileName", usando a funcao apropriada da classe Loja
    bool tudo_OK = X.ler(fileName.toStdString());
    if (!tudo_OK)
    {
      // Exibe uma msg de erro na leitura
      QMessageBox::critical(this,"Erro na leitura",
                            "Erro ao ler um estoque a partir do arquivo:\n"+fileName);
    }

    // Feita a leitura, reexibe todas as listas
    exibeListas();
  }
}

void MainLoja::on_actionSalvar_triggered()
{
  QString fileName = QFileDialog::getSaveFileName(this, "Salvar estoque", "",
          "Estoques (*.txt);;Todos (*.*)");

  if (!fileName.isEmpty())
  {
    // Salva o estoque no arquivo com nome "fileName", usando a funcao apropriada da classe Loja
    bool tudo_OK = X.salvar(fileName.toStdString());
    if (!tudo_OK)
    {
      // Exibe uma msg de erro na leitura
      QMessageBox::critical(this,"Erro na escrita",
                            "Erro ao salvar o estoque no arquivo:\n"+fileName);
    }
  }
}

void MainLoja::on_actionSair_triggered()
{
  QCoreApplication::quit();
}

void MainLoja::on_actionIncluir_livro_triggered()
{
  inclLivro->show();
}

void MainLoja::on_actionIncluir_CD_triggered()
{
  inclCD->show();
}

void MainLoja::on_actionIncluir_DVD_triggered()
{
  inclDVD->show();
}

void MainLoja::on_table_livro_cellDoubleClicked(int row, int)
{
  if (row>=0 && unsigned(row)<X.getNumLivro())
  {
    // O teste sempre deve ser true, se nao cometeu nenhum erro de programacao
    X.excluirLivro(row);
    exibeListaLivro();
  }
}

void MainLoja::on_table_CD_cellDoubleClicked(int row, int)
{
  if (row>=0 && unsigned(row)<X.getNumCD())
  {
    // O teste sempre deve ser true, se nao cometeu nenhum erro de programacao
    X.excluirCD(row);
    exibeListaCD();
  }
}

void MainLoja::on_table_DVD_cellDoubleClicked(int row, int)
{
  if (row>=0 && unsigned(row)<X.getNumDVD())
  {
    // O teste sempre deve ser true, se nao cometeu nenhum erro de programacao
    X.excluirDVD(row);
    exibeListaDVD();
  }
}

void MainLoja::slotIncluirLivro(QString nome, QString preco, QString autor)
{
  double preco_double = preco.toFloat();
  unsigned preco_uint = round(100.0*preco_double);
  Livro L(nome.toStdString(), preco_uint, autor.toStdString());
  if (L.getNome()!="" && L.getPreco()!=0.0 && L.getAutor()!="")
  {
    X.incluirLivro(L);
    exibeListaLivro();
  }
  else
  {
    QMessageBox::critical(this, "Livro invalido", QString("Nao foi possivel incluir o livro:\n")+
                          "Nome="+nome+"\nPreco="+preco+"\nAutor="+autor);
  }
}

void MainLoja::slotIncluirCD(QString nome, QString preco, QString numfaixas)
{
  double preco_double = preco.toFloat();
  unsigned preco_uint = round(100.0*preco_double);
  unsigned numfaixas_uint = numfaixas.toUInt();
  CD C(nome.toStdString(), preco_uint, numfaixas_uint);
  if (C.getNome()!="" && C.getPreco()!=0.0 && C.getNumFaixas()!=0)
  {
    X.incluirCD(C);
    exibeListaCD();
  }
  else
  {
    QMessageBox::critical(this, "CD invalido", QString("Nao foi possivel incluir o CD:\n")+
                          "Nome="+nome+"\nPreco="+preco+"\nNum faixas="+numfaixas);
  }
}

void MainLoja::slotIncluirDVD(QString nome, QString preco, QString duracao)
{
  double preco_double = preco.toFloat();
  unsigned preco_uint = round(100.0*preco_double);
  unsigned duracao_uint = duracao.toUInt();
  DVD D(nome.toStdString(), preco_uint, duracao_uint);
  if (D.getNome()!="" && D.getPreco()!=0.0 && D.getDuracao()!=0)
  {
    X.incluirDVD(D);
    exibeListaDVD();
  }
  else
  {
    QMessageBox::critical(this, "DVD invalido", QString("Nao foi possivel incluir o DVD:\n")+
                          "Nome="+nome+"\nPreco="+preco+"\nDuracao="+duracao);
  }
}

void MainLoja::exibeListaLivro()
{
  unsigned numItens(X.getNumLivro());

  // Limpa o conteudo, mas nao os cabecalhos
  ui->table_livro->clearContents();

  // Fixa o numero de linhas da tabela
  ui->table_livro->setRowCount(numItens);

  // Fixa os labels da tabela de acordo com o conteudo da loja
  QLabel *prov;
  for (unsigned i=0; i<numItens; i++)
  {
    Livro It = X.getLivro(i);
    // Coluna 0
    prov = new QLabel(It.getNome().c_str());
    prov->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->table_livro->setCellWidget(i,0,prov);
    // Coluna 1
    prov = new QLabel(QString::number(It.getPreco(),'f',2));
    prov->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->table_livro->setCellWidget(i,1,prov);
    // Coluna 2
    prov = new QLabel(It.getAutor().c_str());
    prov->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->table_livro->setCellWidget(i,2,prov);
  }

  // Exibe o total de itens na barra de status
  exibeStatus();
}

void MainLoja::exibeListaCD()
{
  unsigned numItens(X.getNumCD());

  // Limpa o conteudo, mas nao os cabecalhos
  ui->table_CD->clearContents();

  // Fixa o numero de linhas da tabela
  ui->table_CD->setRowCount(numItens);

  // Fixa os labels da tabela de acordo com o conteudo da loja
  QLabel *prov;
  for (unsigned i=0; i<numItens; i++)
  {
    CD It = X.getCD(i);
    // Coluna 0
    prov = new QLabel(It.getNome().c_str());
    prov->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->table_CD->setCellWidget(i,0,prov);
    // Coluna 1
    prov = new QLabel(QString::number(It.getPreco(),'f',2));
    prov->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->table_CD->setCellWidget(i,1,prov);
    // Coluna 2
    prov = new QLabel(QString::number(It.getNumFaixas()));
    prov->setAlignment(Qt::AlignCenter);
    ui->table_CD->setCellWidget(i,2,prov);
  }

  // Exibe o total de itens na barra de status
  exibeStatus();
}

void MainLoja::exibeListaDVD()
{
  unsigned numItens(X.getNumDVD());

  // Limpa o conteudo, mas nao os cabecalhos
  ui->table_DVD->clearContents();

  // Fixa o numero de linhas da tabela
  ui->table_DVD->setRowCount(numItens);

  // Fixa os labels da tabela de acordo com o conteudo da loja
  QLabel *prov;
  for (unsigned i=0; i<numItens; i++)
  {
    DVD It = X.getDVD(i);
    // Coluna 0
    prov = new QLabel(It.getNome().c_str());
    prov->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
    ui->table_DVD->setCellWidget(i,0,prov);
    // Coluna 1
    prov = new QLabel(QString::number(It.getPreco(),'f',2));
    prov->setAlignment(Qt::AlignRight|Qt::AlignVCenter);
    ui->table_DVD->setCellWidget(i,1,prov);
    // Coluna 3
    prov = new QLabel(QString::number(It.getDuracao()));
    prov->setAlignment(Qt::AlignCenter);
    ui->table_DVD->setCellWidget(i,2,prov);
  }

  // Exibe o total de itens na barra de status
  exibeStatus();
}

void MainLoja::exibeListas()
{
  exibeListaLivro();
  exibeListaCD();
  exibeListaDVD();
}

// Exibe o total de itens na barra de status
void MainLoja::exibeStatus()
{
  int total = X.getNumLivro()+X.getNumCD()+X.getNumDVD();
  total_itens->setNum(total);
}

