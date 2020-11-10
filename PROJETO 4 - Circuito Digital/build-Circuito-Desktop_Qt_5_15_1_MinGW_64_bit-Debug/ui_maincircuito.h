/********************************************************************************
** Form generated from reading UI file 'maincircuito.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINCIRCUITO_H
#define UI_MAINCIRCUITO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_maincircuito
{
public:
    QAction *actionNovo;
    QAction *actionLer;
    QAction *actionSalvar;
    QAction *actionSair;
    QAction *actionGerar_tabela;
    QWidget *centralwidget;
    QTableWidget *portasConexoesWidget;
    QTableWidget *saidasWidget;
    QLabel *portasConexoesLabel;
    QLabel *saidasLabel;
    QTableWidget *tabelaVerdadeWidget;
    QLabel *tabelaVerdadeLabel;
    QLabel *circuitosLabel;
    QMenuBar *menubar;
    QMenu *menuCircuito;
    QMenu *menuSimular;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *maincircuito)
    {
        if (maincircuito->objectName().isEmpty())
            maincircuito->setObjectName(QString::fromUtf8("maincircuito"));
        maincircuito->resize(985, 571);
        actionNovo = new QAction(maincircuito);
        actionNovo->setObjectName(QString::fromUtf8("actionNovo"));
        actionLer = new QAction(maincircuito);
        actionLer->setObjectName(QString::fromUtf8("actionLer"));
        actionSalvar = new QAction(maincircuito);
        actionSalvar->setObjectName(QString::fromUtf8("actionSalvar"));
        actionSair = new QAction(maincircuito);
        actionSair->setObjectName(QString::fromUtf8("actionSair"));
        actionGerar_tabela = new QAction(maincircuito);
        actionGerar_tabela->setObjectName(QString::fromUtf8("actionGerar_tabela"));
        centralwidget = new QWidget(maincircuito);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        portasConexoesWidget = new QTableWidget(centralwidget);
        if (portasConexoesWidget->columnCount() < 6)
            portasConexoesWidget->setColumnCount(6);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setTextAlignment(Qt::AlignCenter);
        portasConexoesWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        __qtablewidgetitem1->setTextAlignment(Qt::AlignCenter);
        portasConexoesWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        __qtablewidgetitem2->setTextAlignment(Qt::AlignCenter);
        portasConexoesWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        __qtablewidgetitem3->setTextAlignment(Qt::AlignCenter);
        portasConexoesWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        __qtablewidgetitem4->setTextAlignment(Qt::AlignCenter);
        portasConexoesWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        __qtablewidgetitem5->setTextAlignment(Qt::AlignCenter);
        portasConexoesWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        portasConexoesWidget->setObjectName(QString::fromUtf8("portasConexoesWidget"));
        portasConexoesWidget->setGeometry(QRect(20, 49, 350, 481));
        portasConexoesWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        portasConexoesWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        portasConexoesWidget->setTabKeyNavigation(false);
        portasConexoesWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        portasConexoesWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        portasConexoesWidget->horizontalHeader()->setDefaultSectionSize(50);
        portasConexoesWidget->verticalHeader()->setDefaultSectionSize(50);
        saidasWidget = new QTableWidget(centralwidget);
        if (saidasWidget->columnCount() < 1)
            saidasWidget->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        saidasWidget->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        saidasWidget->setObjectName(QString::fromUtf8("saidasWidget"));
        saidasWidget->setGeometry(QRect(370, 49, 120, 481));
        saidasWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        saidasWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        saidasWidget->setTabKeyNavigation(false);
        saidasWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        saidasWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        saidasWidget->horizontalHeader()->setDefaultSectionSize(80);
        portasConexoesLabel = new QLabel(centralwidget);
        portasConexoesLabel->setObjectName(QString::fromUtf8("portasConexoesLabel"));
        portasConexoesLabel->setGeometry(QRect(20, 30, 350, 21));
        portasConexoesLabel->setAlignment(Qt::AlignCenter);
        saidasLabel = new QLabel(centralwidget);
        saidasLabel->setObjectName(QString::fromUtf8("saidasLabel"));
        saidasLabel->setGeometry(QRect(370, 30, 120, 21));
        saidasLabel->setAlignment(Qt::AlignCenter);
        tabelaVerdadeWidget = new QTableWidget(centralwidget);
        tabelaVerdadeWidget->setObjectName(QString::fromUtf8("tabelaVerdadeWidget"));
        tabelaVerdadeWidget->setGeometry(QRect(520, 30, 450, 500));
        tabelaVerdadeWidget->setTabKeyNavigation(false);
        tabelaVerdadeWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tabelaVerdadeWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tabelaVerdadeLabel = new QLabel(centralwidget);
        tabelaVerdadeLabel->setObjectName(QString::fromUtf8("tabelaVerdadeLabel"));
        tabelaVerdadeLabel->setGeometry(QRect(520, 10, 450, 21));
        tabelaVerdadeLabel->setAlignment(Qt::AlignCenter);
        circuitosLabel = new QLabel(centralwidget);
        circuitosLabel->setObjectName(QString::fromUtf8("circuitosLabel"));
        circuitosLabel->setGeometry(QRect(20, 10, 470, 21));
        circuitosLabel->setAlignment(Qt::AlignCenter);
        maincircuito->setCentralWidget(centralwidget);
        menubar = new QMenuBar(maincircuito);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 985, 21));
        menuCircuito = new QMenu(menubar);
        menuCircuito->setObjectName(QString::fromUtf8("menuCircuito"));
        menuSimular = new QMenu(menubar);
        menuSimular->setObjectName(QString::fromUtf8("menuSimular"));
        maincircuito->setMenuBar(menubar);
        statusbar = new QStatusBar(maincircuito);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        maincircuito->setStatusBar(statusbar);

        menubar->addAction(menuCircuito->menuAction());
        menubar->addAction(menuSimular->menuAction());
        menuCircuito->addAction(actionNovo);
        menuCircuito->addAction(actionLer);
        menuCircuito->addAction(actionSalvar);
        menuCircuito->addSeparator();
        menuCircuito->addAction(actionSair);
        menuSimular->addAction(actionGerar_tabela);

        retranslateUi(maincircuito);

        QMetaObject::connectSlotsByName(maincircuito);
    } // setupUi

    void retranslateUi(QMainWindow *maincircuito)
    {
        maincircuito->setWindowTitle(QCoreApplication::translate("maincircuito", "Simulador de Circuitos Digitais", nullptr));
        actionNovo->setText(QCoreApplication::translate("maincircuito", "Novo...", nullptr));
        actionLer->setText(QCoreApplication::translate("maincircuito", "Ler...", nullptr));
        actionSalvar->setText(QCoreApplication::translate("maincircuito", "Salvar...", nullptr));
        actionSair->setText(QCoreApplication::translate("maincircuito", "Sair", nullptr));
        actionGerar_tabela->setText(QCoreApplication::translate("maincircuito", "Gerar tabela", nullptr));
        QTableWidgetItem *___qtablewidgetitem = portasConexoesWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("maincircuito", "TIPO", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = portasConexoesWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("maincircuito", "N\302\260 ENTR", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = portasConexoesWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("maincircuito", "ENTR 1", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = portasConexoesWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("maincircuito", "ENTR 2", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = portasConexoesWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("maincircuito", "ENTR 3", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = portasConexoesWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("maincircuito", "ENTR 4", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = saidasWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("maincircuito", "ORIG/SAIDA", nullptr));
        portasConexoesLabel->setText(QCoreApplication::translate("maincircuito", "PORTAS E CONEX\303\225ES", nullptr));
        saidasLabel->setText(QCoreApplication::translate("maincircuito", "SA\303\215DAS", nullptr));
        tabelaVerdadeLabel->setText(QCoreApplication::translate("maincircuito", "TABELA VERDADE", nullptr));
        circuitosLabel->setText(QCoreApplication::translate("maincircuito", "CIRCUITOS", nullptr));
        menuCircuito->setTitle(QCoreApplication::translate("maincircuito", "Circuito", nullptr));
        menuSimular->setTitle(QCoreApplication::translate("maincircuito", "Simular", nullptr));
    } // retranslateUi

};

namespace Ui {
    class maincircuito: public Ui_maincircuito {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINCIRCUITO_H
