#include "dodajmotocykldialog.h"
#include "ui_dodajmotocykldialog.h"
#include <QMessageBox>

DodajMotocyklDialog::DodajMotocyklDialog(Salon* salon, QWidget *parent)
    : DodajPojazdDialog(parent), ui(new Ui::DodajMotocyklDialog), salonRef(salon)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DodajMotocyklDialog::onButtonOkClicked);
}

DodajMotocyklDialog::~DodajMotocyklDialog() {
    delete ui;
}

void DodajMotocyklDialog::onButtonOkClicked() {
    QString marka = ui->markaLineEdit->text();
    QString model = ui->modelLineEdit->text();
    double cena = ui->cenaLineEdit->text().toDouble();
    int rok = ui->rokLineEdit->text().toInt();
    int przebieg = ui->przebiegLineEdit->text().toInt();
    int moc = ui->mocLineEdit->text().toInt();

    if (marka.isEmpty() || model.isEmpty()) {
        QMessageBox::warning(this, "Blad", "Wszystkie pola muszą być uzupełnione.");
        return;
    }

    QString vin = salonRef->wygenerujUnikalnyVIN();
    pojazd = std::make_shared<Motocykl>(vin, marka, model, cena, rok, przebieg, moc);
    accept();
}

std::shared_ptr<Pojazd> DodajMotocyklDialog::getPojazd() const {
    return pojazd;
}
