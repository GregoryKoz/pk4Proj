#ifndef DODAJOSOBOWYDIALOG_H
#define DODAJOSOBOWYDIALOG_H

#include "dodajpojazddialog.h"
#include "osobowy.h"
#include "salon.h"

namespace Ui {
class DodajOsobowyDialog;
}

class DodajOsobowyDialog : public DodajPojazdDialog {
    Q_OBJECT

public:
    explicit DodajOsobowyDialog(Salon* salon, QWidget *parent = nullptr);
    ~DodajOsobowyDialog();
    std::shared_ptr<Pojazd> getPojazd() const override;

private slots:
    void onButtonOkClicked();

private:
    Ui::DodajOsobowyDialog *ui;
    std::shared_ptr<Osobowy> pojazd;
    Salon* salonRef;
};

#endif // DODAJOSOBOWYDIALOG_H
