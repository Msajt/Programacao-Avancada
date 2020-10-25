#ifndef INCLUIRDVD_H
#define INCLUIRDVD_H

#include <QDialog>

namespace Ui {
class IncluirDVD;
}

class IncluirDVD : public QDialog
{
    Q_OBJECT

public:
    explicit IncluirDVD(QWidget *parent = nullptr);
    ~IncluirDVD();

signals:
    void signIncluirDVD(QString nome, QString preco, QString duracao);

private slots:
    void on_buttonBox_accepted();

private:
    Ui::IncluirDVD *ui;
};

#endif // INCLUIRDVD_H
