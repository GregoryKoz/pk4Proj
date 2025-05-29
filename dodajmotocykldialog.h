#ifndef DODAJMOTOCYKLDIALOG_H
#define DODAJMOTOCYKLDIALOG_H

#include "dodajpojazddialog.h"
#include "motocykl.h"
#include "salon.h"

namespace Ui {
class DodajMotocyklDialog;
}

class DodajMotocyklDialog : public DodajPojazdDialog {
    Q_OBJECT

public:
    explicit DodajMotocyklDialog(Salon* salon, QWidget *parent = nullptr);
    ~DodajMotocyklDialog();

    std::shared_ptr<Pojazd> getPojazd() const override;

private slots:
    void onButtonOkClicked();

private:
    Ui::DodajMotocyklDialog *ui;
    std::shared_ptr<Motocykl> pojazd;
    Salon* salonRef;
};

#endif // DODAJMOTOCYKLDIALOG_H
