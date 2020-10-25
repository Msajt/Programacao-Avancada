#ifndef MAINLOJA_H
#define MAINLOJA_H

#include <QMainWindow>
#include <QLabel>
#include "incluirlivro.h"
#include "incluircd.h"
#include "incluirdvd.h"
#include "loja.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainLoja; }
QT_END_NAMESPACE

class MainLoja : public QMainWindow
{
    Q_OBJECT

public:
    MainLoja(QWidget *parent = nullptr);
    ~MainLoja();

    // Exibir total de listas
    void ExibirListas();
    // Exibir listas
    void ExibirListaLivros();
    void ExibirListaCDS();
    void ExibirListaDVDS();
    // Exibir o número total das listas
    void ExibirTotal();

private slots:
    void on_livrosWidget_cellDoubleClicked(int row, int column);

    void on_cdsWidget_cellDoubleClicked(int row, int column);

    void on_dvdsWidget_cellDoubleClicked(int row, int column);

    void on_actionLer_triggered();

    void on_actionSalvar_triggered();

    void on_actionSair_triggered();

    void on_actionIncluirLivro_triggered();

    void on_actionIncluirCD_triggered();

    void on_actionIncluirDVD_triggered();

    void slotIncluirLivro(QString nome, QString preco, QString autor);

    void slotIncluirCD(QString nome, QString preco, QString faixas);

    void slotIncluirDVD(QString nome, QString preco, QString duracao);

private:
    Ui::MainLoja *ui;

    Loja X;
    IncluirLivro *inclLivro;
    IncluirCD *inclCD;
    IncluirDVD *inclDVD;
    QLabel *totalItens;
};
#endif // MainLoja_H
