/********************************************************************************
** Form generated from reading UI file 'mainloja.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINLOJA_H
#define UI_MAINLOJA_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainLoja
{
public:
    QAction *actionLer;
    QAction *actionSalvar;
    QAction *actionSair;
    QAction *actionIncluirLivro;
    QAction *actionIncluirCD;
    QAction *actionIncluirDVD;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *itensLayout;
    QHBoxLayout *produtosLayout;
    QVBoxLayout *livrosLayout;
    QLabel *livrosLabel;
    QTableWidget *livrosWidget;
    QVBoxLayout *cdsLayout;
    QLabel *cdsLabel;
    QTableWidget *cdsWidget;
    QVBoxLayout *dvdsLayout;
    QLabel *dvdsLabel;
    QTableWidget *dvdsWidget;
    QMenuBar *menubar;
    QMenu *menuArquivo;
    QMenu *menuItem;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainLoja)
    {
        if (MainLoja->objectName().isEmpty())
            MainLoja->setObjectName(QString::fromUtf8("MainLoja"));
        MainLoja->resize(1000, 600);
        actionLer = new QAction(MainLoja);
        actionLer->setObjectName(QString::fromUtf8("actionLer"));
        actionSalvar = new QAction(MainLoja);
        actionSalvar->setObjectName(QString::fromUtf8("actionSalvar"));
        actionSair = new QAction(MainLoja);
        actionSair->setObjectName(QString::fromUtf8("actionSair"));
        actionIncluirLivro = new QAction(MainLoja);
        actionIncluirLivro->setObjectName(QString::fromUtf8("actionIncluirLivro"));
        actionIncluirCD = new QAction(MainLoja);
        actionIncluirCD->setObjectName(QString::fromUtf8("actionIncluirCD"));
        actionIncluirDVD = new QAction(MainLoja);
        actionIncluirDVD->setObjectName(QString::fromUtf8("actionIncluirDVD"));
        centralwidget = new QWidget(MainLoja);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_3 = new QHBoxLayout(centralwidget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        itensLayout = new QVBoxLayout();
        itensLayout->setObjectName(QString::fromUtf8("itensLayout"));
        produtosLayout = new QHBoxLayout();
        produtosLayout->setObjectName(QString::fromUtf8("produtosLayout"));
        livrosLayout = new QVBoxLayout();
        livrosLayout->setObjectName(QString::fromUtf8("livrosLayout"));
        livrosLabel = new QLabel(centralwidget);
        livrosLabel->setObjectName(QString::fromUtf8("livrosLabel"));
        livrosLabel->setAlignment(Qt::AlignCenter);

        livrosLayout->addWidget(livrosLabel);

        livrosWidget = new QTableWidget(centralwidget);
        if (livrosWidget->columnCount() < 3)
            livrosWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        livrosWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        livrosWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        livrosWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        livrosWidget->setObjectName(QString::fromUtf8("livrosWidget"));
        livrosWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        livrosWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        livrosWidget->setTabKeyNavigation(false);
        livrosWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        livrosWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        livrosWidget->verticalHeader()->setVisible(false);

        livrosLayout->addWidget(livrosWidget);


        produtosLayout->addLayout(livrosLayout);

        cdsLayout = new QVBoxLayout();
        cdsLayout->setObjectName(QString::fromUtf8("cdsLayout"));
        cdsLabel = new QLabel(centralwidget);
        cdsLabel->setObjectName(QString::fromUtf8("cdsLabel"));
        cdsLabel->setAlignment(Qt::AlignCenter);

        cdsLayout->addWidget(cdsLabel);

        cdsWidget = new QTableWidget(centralwidget);
        if (cdsWidget->columnCount() < 3)
            cdsWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        cdsWidget->setHorizontalHeaderItem(0, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        cdsWidget->setHorizontalHeaderItem(1, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        cdsWidget->setHorizontalHeaderItem(2, __qtablewidgetitem5);
        cdsWidget->setObjectName(QString::fromUtf8("cdsWidget"));
        cdsWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        cdsWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        cdsWidget->setTabKeyNavigation(false);
        cdsWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        cdsWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        cdsWidget->verticalHeader()->setVisible(false);

        cdsLayout->addWidget(cdsWidget);


        produtosLayout->addLayout(cdsLayout);

        dvdsLayout = new QVBoxLayout();
        dvdsLayout->setObjectName(QString::fromUtf8("dvdsLayout"));
        dvdsLabel = new QLabel(centralwidget);
        dvdsLabel->setObjectName(QString::fromUtf8("dvdsLabel"));
        dvdsLabel->setAlignment(Qt::AlignCenter);

        dvdsLayout->addWidget(dvdsLabel);

        dvdsWidget = new QTableWidget(centralwidget);
        if (dvdsWidget->columnCount() < 3)
            dvdsWidget->setColumnCount(3);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        dvdsWidget->setHorizontalHeaderItem(0, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        dvdsWidget->setHorizontalHeaderItem(1, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        dvdsWidget->setHorizontalHeaderItem(2, __qtablewidgetitem8);
        dvdsWidget->setObjectName(QString::fromUtf8("dvdsWidget"));
        dvdsWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        dvdsWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        dvdsWidget->setTabKeyNavigation(false);
        dvdsWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        dvdsWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        dvdsWidget->verticalHeader()->setVisible(false);

        dvdsLayout->addWidget(dvdsWidget);


        produtosLayout->addLayout(dvdsLayout);


        itensLayout->addLayout(produtosLayout);


        horizontalLayout_3->addLayout(itensLayout);

        MainLoja->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainLoja);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1000, 21));
        menuArquivo = new QMenu(menubar);
        menuArquivo->setObjectName(QString::fromUtf8("menuArquivo"));
        menuItem = new QMenu(menubar);
        menuItem->setObjectName(QString::fromUtf8("menuItem"));
        MainLoja->setMenuBar(menubar);
        statusbar = new QStatusBar(MainLoja);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainLoja->setStatusBar(statusbar);

        menubar->addAction(menuArquivo->menuAction());
        menubar->addAction(menuItem->menuAction());
        menuArquivo->addAction(actionLer);
        menuArquivo->addAction(actionSalvar);
        menuArquivo->addSeparator();
        menuArquivo->addAction(actionSair);
        menuItem->addAction(actionIncluirLivro);
        menuItem->addAction(actionIncluirCD);
        menuItem->addAction(actionIncluirDVD);

        retranslateUi(MainLoja);

        QMetaObject::connectSlotsByName(MainLoja);
    } // setupUi

    void retranslateUi(QMainWindow *MainLoja)
    {
        MainLoja->setWindowTitle(QCoreApplication::translate("MainLoja", "Estoque em Loja", nullptr));
        actionLer->setText(QCoreApplication::translate("MainLoja", "Ler...", nullptr));
        actionSalvar->setText(QCoreApplication::translate("MainLoja", "Salvar...", nullptr));
        actionSair->setText(QCoreApplication::translate("MainLoja", "Sair", nullptr));
        actionIncluirLivro->setText(QCoreApplication::translate("MainLoja", "Incluir Livro...", nullptr));
        actionIncluirCD->setText(QCoreApplication::translate("MainLoja", "Incluir CD...", nullptr));
        actionIncluirDVD->setText(QCoreApplication::translate("MainLoja", "Incluir DVD...", nullptr));
        livrosLabel->setText(QCoreApplication::translate("MainLoja", "LIVROS", nullptr));
        QTableWidgetItem *___qtablewidgetitem = livrosWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainLoja", "NOME", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = livrosWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainLoja", "PRE\303\207O", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = livrosWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainLoja", "AUTOR", nullptr));
        cdsLabel->setText(QCoreApplication::translate("MainLoja", "CDS", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = cdsWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainLoja", "NOME", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = cdsWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainLoja", "PRE\303\207O", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = cdsWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainLoja", "N\302\260 FAIXAS", nullptr));
        dvdsLabel->setText(QCoreApplication::translate("MainLoja", "DVDS", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = dvdsWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainLoja", "NOME", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = dvdsWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainLoja", "PRE\303\207O", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = dvdsWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainLoja", "DURA\303\207\303\203O", nullptr));
        menuArquivo->setTitle(QCoreApplication::translate("MainLoja", "Arquivo", nullptr));
        menuItem->setTitle(QCoreApplication::translate("MainLoja", "Item", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainLoja: public Ui_MainLoja {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINLOJA_H
