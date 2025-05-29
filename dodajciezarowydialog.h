#ifndef DODAJCIEZAROWYDIALOG_H
#define DODAJCIEZAROWYDIALOG_H

#include "dodajpojazddialog.h"
#include "ciezarowy.h"
#include "salon.h"

namespace Ui {
class DodajCiezarowyDialog;
}

class DodajCiezarowyDialog : public DodajPojazdDialog {
    Q_OBJECT

public:
    explicit DodajCiezarowyDialog(Salon* salon, QWidget *parent = nullptr);
    ~DodajCiezarowyDialog();

    std::shared_ptr<Pojazd> getPojazd() const override;

private slots:
    void onButtonOkClicked();

private:
    Ui::DodajCiezarowyDialog *ui;
    std::shared_ptr<Ciezarowy> pojazd;
    Salon* salonRef;
};

#endif // DODAJCIEZAROWYDIALOG_H
