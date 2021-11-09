#ifndef NOVACONVERSA_H
#define NOVACONVERSA_H

#include <QDialog>

namespace Ui {
class NovaConversa;
}

class NovaConversa : public QDialog
{
  Q_OBJECT

public:
  explicit NovaConversa(QWidget *parent = 0);
  ~NovaConversa();

private slots:
  void on_buttonBox_accepted();

signals:
  void signNovaConversa(QString usuario);

private:
  Ui::NovaConversa *ui;
};

#endif // NOVACONVERSA_H
