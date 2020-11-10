#ifndef NEWCIRCUITO_H
#define NEWCIRCUITO_H

#include <QDialog>

namespace Ui {
class newCircuito;
}

class newCircuito : public QDialog
{
    Q_OBJECT

public:
    explicit newCircuito(QWidget *parent = nullptr);
    ~newCircuito();

signals:
    void signNewCircuito(QString nEntradas, QString nSaidas, QString nPortas);

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::newCircuito *ui;
};

#endif // NEWCIRCUITO_H
