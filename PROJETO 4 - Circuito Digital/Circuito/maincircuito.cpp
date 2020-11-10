#include "maincircuito.h"
#include "ui_maincircuito.h"

maincircuito::maincircuito(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::maincircuito)
    , modPorta(NULL)
    , modSaida(NULL)
    , newCirc(NULL)
    , totalEntradas(NULL)
    , totalSaidas(NULL)
    , totalPortas(NULL)
{
    ui->setupUi(this);

    // JANELAS QDIALOG
    modPorta = new modifyPorta(this);
    modSaida = new modifySaida(this);
    newCirc = new newCircuito(this);

    // STATUS BAR
    statusBar()->insertWidget(0, new QLabel("N° entradas: "));
        totalEntradas = new QLabel(this);
        totalEntradas->setNum(0);
        statusBar()->insertWidget(1, totalEntradas);
    statusBar()->insertWidget(2, new QLabel("N° saídas: "));
        totalSaidas = new QLabel(this);
        totalSaidas->setNum(0);
        statusBar()->insertWidget(3, totalSaidas);
    statusBar()->insertWidget(4, new QLabel("N° portas: "));
        totalPortas = new QLabel(this);
        totalSaidas->setNum(0);
        statusBar()->insertWidget(5, totalPortas);

    // CONEXÃO ENTRE AS JANELAS
        // ==> Novo Circuito
    connect(newCirc, SLOT(slotNewCircuito(QString, QString, QString)),
            this, SIGNAL(signNewCircuito(QString, QString, QString)));
        // ==> Modificar Porta
    connect(modPorta, SLOT(slotModificarPorta(QString, QString, QString, QString, QString, QString)),
            this, SIGNAL(signModificarPorta(QString, QString, QString, QString, QString, QString)));
        // ==> Modificar Saída
    connect(modSaida, SLOT(slotModificarSaida(QString)), this, SIGNAL(signModificarSaida(QString)));

    // FRONT-END TABELA
    // ==> Labels
    ui->portasConexoesLabel->setStyleSheet("background:lightgray; border: 1px solid black; font-weight: bold;");
    ui->saidasLabel->setStyleSheet("background:lightgray; border: 1px solid black; font-weight: bold;");
    ui->tabelaVerdadeLabel->setStyleSheet("background:lightgray; border: 1px solid black; font-weight: bold;");
    ui->circuitosLabel->setStyleSheet("background:lightgray; border: 1px solid black; font-weight: bold;");
    // ==> Headers
    ui->portasConexoesWidget->setHorizontalHeaderLabels(QStringList() << "TIPO" << "N°\nENTR" << "ENTR\n1" << "ENTR\n2" << "ENTR\n3" << "ENTR\n4");
    ui->saidasWidget->setHorizontalHeaderLabels(QStringList() << "ORIG\nSAÍDA");
    ui->portasConexoesWidget->setStyleSheet("QHeaderView::section{background-color:white}");
    ui->saidasWidget->setStyleSheet("QHeaderView::section{background-color:white}");


}

maincircuito::~maincircuito()
{
    delete ui;
}

// ==========================================
// ============== ITENS MENU ================
// ==========================================

// AO CLICAR NO MENU->NOVO
void maincircuito::on_actionNovo_triggered()
{
    newCirc->show();
}
/*
// AO CLICAR NO MENU->LER
void maincircuito::on_actionLer_triggered()
{

}

// AO CLICAR NO MENU->SALVAR
void maincircuito::on_actionSalvar_triggered()
{

}
*/
// AO CLICAR NO MENU->SAIR
void maincircuito::on_actionSair_triggered()
{
    QCoreApplication::quit();
}
/*
// AO CLICAR NO MENU->GERAR TABELA
void maincircuito::on_actionGerar_tabela_triggered()
{

}

// AO CLICAR NA LINHA PARA ABRIR A JANELA MODIFICAR PORTA
void maincircuito::on_portasConexoesWidget_cellDoubleClicked(int row, int)
{
    modPorta->show();
}

// AO CLICAR NA LINHA PARA ABRIR A JANELA MODIFICAR SAÍDA
void maincircuito::on_saidasWidget_cellDoubleClicked(int row, int)
{
    modSaida->show();
}

// =============================
// ===== SLOTS DAS JANELAS =====
// =============================
void maincircuito::slotNewCircuito(QString nEntradas, QString nSaidas, QString nPortas)
{

}

void maincircuito::slotModifySaida(QString nSaida, QString idOrigem)
{

}

void maincircuito::slotModifyPorta(QString nPorta, QString tipoPorta, QString nEntradas, QString id1, QString id2, QString id3, QString id4)
{

}
*/
