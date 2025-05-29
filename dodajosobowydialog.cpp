#include "dodajosobowydialog.h"
#include "ui_dodajosobowydialog.h"
#include <QMessageBox>

DodajOsobowyDialog::DodajOsobowyDialog(Salon* salon, QWidget *parent) :
    DodajPojazdDialog(parent), ui(new Ui::DodajOsobowyDialog), salonRef(salon)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DodajOsobowyDialog::onButtonOkClicked);
}

DodajOsobowyDialog::~DodajOsobowyDialog() {
    delete ui;
}

void DodajOsobowyDialog::onButtonOkClicked() {
    QString marka = ui->markaLineEdit->text();
    QString model = ui->modelLineEdit->text();
    double cena = ui->cenaLineEdit->text().toDouble();
    int rok = ui->rokLineEdit->text().toInt();
    int przebieg = ui->przebiegLineEdit->text().toInt();
    int miejsca = ui->miejscaLineEdit->text().toInt();

    if (marka.isEmpty() || model.isEmpty()) {
        QMessageBox::warning(this, "Blad", "Wszystkie pola musza byc uzupelnione.");
        return;
    }

    QString vin = salonRef->wygenerujUnikalnyVIN();
    pojazd = std::make_shared<Osobowy>(vin, marka, model, cena, rok, przebieg, miejsca);
    accept();
}

std::shared_ptr<Pojazd> DodajOsobowyDialog::getPojazd() const {
    return pojazd;
}
