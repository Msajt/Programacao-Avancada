#ifndef MODIFYPORTA_H
#define MODIFYPORTA_H

#include <QDialog>

namespace Ui {
class modifyPorta;
}

class modifyPorta : public QDialog
{
    Q_OBJECT

public:
    explicit modifyPorta(QWidget *parent = nullptr);
    ~modifyPorta();

signals:
    void signModifyPorta(QString tipoPorta, QString nEntradas, QString id1, QString id2, QString id3, QString id4);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::modifyPorta *ui;
};

#endif // MODIFYPORTA_H
