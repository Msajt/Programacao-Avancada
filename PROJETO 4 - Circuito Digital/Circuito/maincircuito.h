#ifndef MAINCIRCUITO_H
#define MAINCIRCUITO_H

#include <QMainWindow>
#include <QLabel>
#include <modifyporta.h>
#include <modifysaida.h>
#include <newcircuito.h>

QT_BEGIN_NAMESPACE
namespace Ui { class maincircuito; }
QT_END_NAMESPACE

class maincircuito : public QMainWindow
{
    Q_OBJECT

public:
    maincircuito(QWidget *parent = nullptr);
    ~maincircuito();

private slots:
    void on_actionNovo_triggered();
    /*
    void on_actionLer_triggered();

    void on_actionSalvar_triggered();
    */
    void on_actionSair_triggered();
    /*
    void on_actionGerar_tabela_triggered();

    void on_portasConexoesWidget_cellDoubleClicked(int row, int column);

    void on_saidasWidget_cellDoubleClicked(int row, int column);

    void slotNewCircuito(QString nEntradas, QString nSaidas, QString nPortas);

    void slotModifySaida(QString nSaida, QString idOrigem);

    void slotModifyPorta(QString nPorta, QString tipoPorta, QString nEntradas, QString id1, QString id2, QString id3, QString id4);
    */
private:
    Ui::maincircuito *ui;
    // Janelas
    modifyPorta *modPorta;
    modifySaida *modSaida;
    newCircuito *newCirc;
    // StatusBar
    QLabel *totalEntradas, *totalSaidas, *totalPortas;
};
#endif // MAINCIRCUITO_H
