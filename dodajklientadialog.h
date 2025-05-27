#ifndef DODAJKLIENTADIALOG_H
#define DODAJKLIENTADIALOG_H

#include <QDialog>
#include "klient.h"
#include <regex>

namespace Ui {
class DodajKlientaDialog;
}

class DodajKlientaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DodajKlientaDialog(QWidget *parent = nullptr);
    ~DodajKlientaDialog();

    Client getClient() const;

private slots:
    void onButtonOkClicked();



private:
    Ui::DodajKlientaDialog *ui;
    Client wynikowyKlient;
    bool danePoprawne = false;
};

#endif // DODAJKLIENTADIALOG_H
