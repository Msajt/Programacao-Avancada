#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <cmath>
#include "mainloja.h"
#include "ui_mainloja.h"
#include "incluirlivro.h"
#include "incluircd.h"
#include "incluirdvd.h"

#include <QDebug>

MainLoja::MainLoja(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainLoja)
    , X()
    , inclLivro(NULL)
    , inclCD(NULL)
    , inclDVD(NULL)
    , totalItens(NULL)
{
    ui->setupUi(this);

    // Janelas de inclusão de itens
    inclLivro = new IncluirLivro(this);
    inclCD = new IncluirCD(this);
    inclDVD = new IncluirDVD(this);

    // Barra de status
    statusBar()->insertWidget(0, new QLabel("Total de itens: "));
    totalItens = new QLabel(this);
    totalItens->setNum(0);
    statusBar()->insertWidget(1, totalItens);

    // Conexão entre as janelas
    // --> LIVRO
    connect(inclLivro, SIGNAL(signIncluirLivro(QString, QString, QString)),
            this, SLOT(slotIncluirLivro(QString, QString, QString)));
    // --> CD
    connect(inclCD, SIGNAL(signIncluirCD(QString, QString, QString)),
            this, SLOT(slotIncluirCD(QString, QString, QString)));
    // --> DVD
    connect(inclDVD, SIGNAL(signIncluirDVD(QString, QString, QString)),
            this, SLOT(slotIncluirDVD(QString, QString, QString)));

    // Front-end da tabela
    // --> Label
    ui->livrosLabel->setStyleSheet("background:lightgray; border: 1px solid black;");
    ui->cdsLabel->setStyleSheet("background:lightgray; border: 1px solid black;");
    ui->dvdsLabel->setStyleSheet("background:lightgray; border: 1px solid black;");

    // --> CABEÇALHOS
    // => Livros
    ui->livrosWidget->setStyleSheet("QHeaderView::section{background-color:lightgray}");
    ui->livrosWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->livrosWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->livrosWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->livrosWidget->setHorizontalHeaderLabels(QStringList() << "Nome" << "Preço" << "Autor");
    // => CDS
    ui->cdsWidget->setStyleSheet("QHeaderView::section{background-color:lightgray}");
    ui->cdsWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->cdsWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->cdsWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->cdsWidget->setHorizontalHeaderLabels(QStringList() << "Nome" << "Preço" << "N° de faixas");
    // => DVDS
    ui->dvdsWidget->setStyleSheet("QHeaderView::section{background-color:lightgray}");
    ui->dvdsWidget->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->dvdsWidget->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);
    ui->dvdsWidget->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    ui->dvdsWidget->setHorizontalHeaderLabels(QStringList() << "Nome" << "Preço" << "Duração");

    // Exibir listas
    ExibirListas();
}

MainLoja::~MainLoja()
{
    delete ui;
}
// ======================================================================
// ====================== EXIBIÇÃO DAS LISTAS ===========================
// ======================================================================
void MainLoja::ExibirListas()
{
    // Exibir o total das listas
    ExibirListaLivros();
    ExibirListaCDS();
    ExibirListaDVDS();
}

void MainLoja::ExibirListaLivros()
{
    // Pegar a quantidade de livros
    unsigned numLivros(X.getNumLivro());
    // Limpar conteúdo
    ui->livrosWidget->clearContents();
    // Fixar o novo número de linhas de acordo com o numero de produtos
    ui->livrosWidget->setRowCount(numLivros);

    QLabel *prov;

    for(unsigned i=0; i<numLivros; i++){
        Livro livro = X.getLivro(i);
        // Nome, referente a primeira coluna
            // => c_str: transforma em ponteiro
        prov = new QLabel(livro.getNome().c_str());
            // => alinhamento
        prov->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
            // => setar as mudanças totais na tabela
        ui->livrosWidget->setCellWidget(i, 0, prov);

        // Preço, referente a segunda coluna
            // => transforma o número em string
        prov = new QLabel(QString::number(livro.getPreco(), 'f', 2));
            // => alinhamento
        prov->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
            // => setar as mudanças totais na tabela
        ui->livrosWidget->setCellWidget(i, 1, prov);

        // Autor, referente a terceira coluna
            // => transforma o número em string
        prov = new QLabel(livro.getAutor().c_str());
            // => alinhamento
        prov->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
            // => setar as mudanças totais na tabela
        ui->livrosWidget->setCellWidget(i, 2, prov);
    }

    // Exibir total de itens no rodapé
    ExibirTotal();
}

void MainLoja::ExibirListaCDS()
{
    // Pegar a quantidade de livros
    unsigned numCDS = X.getNumCD();
    // Limpar conteúdo
    ui->cdsWidget->clearContents();
    // Fixar o novo número de linhas de acordo com o numero de produtos
    ui->cdsWidget->setRowCount(numCDS);

    QLabel *prov;

    for(unsigned i=0; i<numCDS; i++){
        CD cd = X.getCD(i);
        // Nome, referente a primeira coluna
            // => c_str: transforma em ponteiro
        prov = new QLabel(cd.getNome().c_str());
            // => alinhamento
        prov->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
            // => setar as mudanças totais na tabela
        ui->cdsWidget->setCellWidget(i, 0, prov);

        // Preço, referente a segunda coluna
            // => transforma o número em string
        prov = new QLabel(QString::number(cd.getPreco(), 'f', 2));
            // => alinhamento
        prov->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
            // => setar as mudanças totais na tabela
        ui->cdsWidget->setCellWidget(i, 1, prov);

        // Número de faixas, referente a terceira coluna
            // => transforma o número em string
        prov = new QLabel(QString::number(cd.getNumFaixas()));
            // => alinhamento
        prov->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
            // => setar as mudanças totais na tabela
        ui->cdsWidget->setCellWidget(i, 2, prov);
    }

    // Exibir total de itens no rodapé
    ExibirTotal();
}

void MainLoja::ExibirListaDVDS()
{
    // Pegar a quantidade de livros
    unsigned numDVDS = X.getNumDVD();
    // Limpar conteúdo
    ui->dvdsWidget->clearContents();
    // Fixar o novo número de linhas de acordo com o numero de produtos
    ui->dvdsWidget->setRowCount(numDVDS);

    QLabel *prov;

    for(unsigned i=0; i<numDVDS; i++){
        DVD dvd = X.getDVD(i);
        // Nome, referente a primeira coluna
            // => c_str: transforma em ponteiro
        prov = new QLabel(dvd.getNome().c_str());
            // => alinhamento
        prov->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
            // => setar as mudanças totais na tabela
        ui->dvdsWidget->setCellWidget(i, 0, prov);

        // Preço, referente a segunda coluna
            // => transforma o número em string
        prov = new QLabel(QString::number(dvd.getPreco(), 'f', 2));
            // => alinhamento
        prov->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
            // => setar as mudanças totais na tabela
        ui->dvdsWidget->setCellWidget(i, 1, prov);

        // Duração, referente a terceira coluna
            // => transforma o número em string
        prov = new QLabel(QString::number(dvd.getDuracao()));
            // => alinhamento
        prov->setAlignment(Qt::AlignLeft|Qt::AlignVCenter);
            // => setar as mudanças totais na tabela
        ui->dvdsWidget->setCellWidget(i, 2, prov);
    }

    // Exibir total de itens no rodapé
    ExibirTotal();
}

void MainLoja::ExibirTotal()
{
    int valorTotal(X.getNumLivro()+X.getNumCD()+X.getNumDVD());
    totalItens->setNum(valorTotal);
}

// ===================================================================
// ================== TABELAS LIVRO, CD E DVD ========================
// ===================================================================

void MainLoja::on_livrosWidget_cellDoubleClicked(int row, int)
{
    /* Ao se dar um clique duplo em uma linha de uma tabela, o objeto
       correspondente deve ser excluído do estoque da loja */

    // Verifica se indice é válido
    if(row >= 0 && unsigned(row) < X.getNumLivro()){
        // Excluir item correspondente
        X.excluirLivro(row);
        // Reexibe a lista correspondente na interface
        ExibirListaLivros();
    }
}

void MainLoja::on_cdsWidget_cellDoubleClicked(int row, int)
{
    // Ao se dar um clique duplo em uma linha de uma tabela, o objeto
    // correspondente deve ser excluído do estoque da loja

    // Verifica se indice é válido
    if(row >= 0 && unsigned(row) < X.getNumCD()){
        // Excluir item correspondente
        X.excluirCD(row);
        // Reexibe a lista correspondente na interface
        ExibirListaCDS();
    }
}

void MainLoja::on_dvdsWidget_cellDoubleClicked(int row, int)
{
    // Ao se dar um clique duplo em uma linha de uma tabela, o objeto
    // correspondente deve ser excluído do estoque da loja

    // Verifica se indice é válido
    if(row >= 0 && unsigned(row) < X.getNumDVD()){
        // Excluir item correspondente
        X.excluirDVD(row);
        // Reexibe a lista correspondente na interface
        ExibirListaDVDS();
    }
}

// ===================================================================
// ========================= ABA ARQUIVO =============================
// ===================================================================

void MainLoja::on_actionLer_triggered()
{
    /* Gera a abertura de uma janela do tipo QFileDialog::getOpenFileName com título “Ler estoque"
     * (ver figura) e lê os dados utilizando o método ler da classe Loja. Em caso de erro na leitura do
     * arquivo, exibe mensagem de erro abrindo uma QMessageBox::critical. Ao final, atualiza na interface
     * as listas de itens.
    */

    // QFileDialog::getOpenFileName(objeto, nomeJanela, diretório, arquivosSuportados)
    QString fileName = QFileDialog::getOpenFileName(this, "Ler estoque", "", "Estoques (*.txt);;Todos (*.*)");
    // Pegar apenas o nome do arquivo
    QString archiveName = QFileInfo(fileName).fileName();
    // Se não estiver vazio
    if(!archiveName.isEmpty()){
        bool okFile = X.ler(archiveName.toStdString());
        // Caso a leitura der falso
        if(!okFile){
            QMessageBox::critical(this, "Erro na leitura", "Houve um erro ao ler o arquivo\n" + archiveName);
        }
        // Se estiver tudo certo vai exibir a lista
        ExibirListas();
    }
}

void MainLoja::on_actionSalvar_triggered()
{
    /* Gera a abertura de uma janela do tipo QFileDialog::getSaveFileName1 com título “Salvar estoque”
     * e salva os dados utilizando o método salvar da classe Loja. Em caso de erro na escrita do arquivo,
     * exibe mensagem de erro abrindo uma QMessageBox::critical
    */

    // QFileDialog::getOpenFileName(objeto, nomeJanela, , arquivosSuportados)
    QString fileName = QFileDialog::getSaveFileName(this, "Salvar estoque", "", "Estoques (*.txt);;Todos (*.*)");
    // Pegar apenas o nome do arquivo
    QString archiveName = QFileInfo(fileName).fileName();
    // Se não estiver vazio
    if(!archiveName.isEmpty()){
        bool okFile = X.salvar(archiveName.toStdString());
        // Caso a leitura der falso
        if(!okFile){
            QMessageBox::critical(this, "Erro ao salvar", "Houve um erro ao salvar o arquivo\n" + archiveName);
        }
    }
}

void MainLoja::on_actionSair_triggered()
{
    QCoreApplication::quit();
}

// ===================================================================
// ======================== ABA ITEM =================================
// ===================================================================

void MainLoja::on_actionIncluirLivro_triggered()
{
    // Vai abrir a janela oculta referente ao incluir livro
    inclLivro->show();
}

void MainLoja::on_actionIncluirCD_triggered()
{
    // Vai abrir a janela oculta referente ao incluir CD
    inclCD->show();
}

void MainLoja::on_actionIncluirDVD_triggered()
{
    // Vai abrir a janela oculta referente ao incluir DVD
    inclDVD->show();
}

// ====================================================================
// ============================ SLOT ==================================
// ====================================================================

void MainLoja::slotIncluirLivro(QString nome, QString preco, QString autor)
{
    /* -> Converter os parâmetros 'QString' para o tipo apropriado para a classe 'Livro', 'CD' e 'DVD'
       -> Criam um objeto (Livro, CD, DVD) e incluem esse objeto no estoque usando a função apropriada
          da classe Loja(incluirLivro, incluirCD, incluirDVD)
       -> Em caso de sucesso na criação do objeto e inclusão, reexibem a lista correspondente na interface.
          Em caso de insucesso, exibem uma mensagem de erro com uma QMessage-Box::critical
    */

    string newNome = nome.toStdString();
    float newPrecoFloat = preco.toFloat();
    unsigned newPrecoUnsigned = round(100.0 * newPrecoFloat);
    string newAutor = autor.toStdString();

    // Cria um objeto do tipo do produto
    Livro livro(newNome, newPrecoUnsigned, newAutor);
    // Verificar se está ok
    if(livro.getNome() != "" && livro.getPreco() != 0 && livro.getAutor() != ""){
        X.incluirLivro(livro);
        ExibirListaLivros();
    } else {
        QMessageBox::critical(this, "Erro ao incluir livro", QString("Preencha todos os dados corretamente:\n")
                              + "Nome: " + nome
                              + "\nPreco: " + preco
                              + "\nFaixas: " + autor);
    }
}

void MainLoja::slotIncluirCD(QString nome, QString preco, QString faixas)
{
    string newNome = nome.toStdString();
    float newPrecoFloat = preco.toFloat();
    unsigned newPrecoUnsigned = round(100.0 * newPrecoFloat);
    unsigned newFaixas = faixas.toUInt();

    // Cria um objeto do tipo do produto
    CD cd(newNome, newPrecoUnsigned, newFaixas);
    // Verificar se está ok
    if(cd.getNome() != "" && cd.getPreco() != 0 && cd.getNumFaixas() != 0){
        X.incluirCD(cd);
        ExibirListaCDS();
    } else {
        QMessageBox::critical(this, "Erro ao incluir CD", QString("Preencha todos os dados corretamente:\n")
                              + "Nome: " + nome
                              + "\nPreco: " + preco
                              + "\nFaixas: " + faixas);
    }
}

void MainLoja::slotIncluirDVD(QString nome, QString preco, QString duracao)
{
    string newNome = nome.toStdString();
    float newPrecoFloat = preco.toFloat();
    unsigned newPrecoUnsigned = round(100.0 * newPrecoFloat);
    unsigned newDuracao = duracao.toUInt();

    // Cria um objeto do tipo do produto
    DVD dvd(newNome, newPrecoUnsigned, newDuracao);
    // Verificar se está ok
    if(dvd.getNome() != "" && dvd.getPreco() != 0 && dvd.getDuracao() != 0){
        X.incluirDVD(dvd);
        ExibirListaDVDS();
    } else {
        QMessageBox::critical(this, "Erro ao incluir DVD", QString("Preencha todos os dados corretamente:\n")
                              + "Nome: " + nome
                              + "\nPreco: " + preco
                              + "\nFaixas: " + duracao);
    }
}


