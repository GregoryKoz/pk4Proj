#include "dodajciezarowydialog.h"
#include "ui_dodajciezarowydialog.h"
#include <QMessageBox>

DodajCiezarowyDialog::DodajCiezarowyDialog(Salon* salon, QWidget *parent) :
    DodajPojazdDialog(parent),
    ui(new Ui::DodajCiezarowyDialog),
    salonRef(salon)
{
    ui->setupUi(this);
    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &DodajCiezarowyDialog::onButtonOkClicked);
}

DodajCiezarowyDialog::~DodajCiezarowyDialog() {
    delete ui;
}

void DodajCiezarowyDialog::onButtonOkClicked() {
    QString marka = ui->markaLineEdit->text();
    QString model = ui->modelLineEdit->text();
    double cena = ui->cenaLineEdit->text().toDouble();
    int rok = ui->rokLineEdit->text().toInt();
    int przebieg = ui->przebiegLineEdit->text().toInt();
    double ladownosc = ui->ladownoscLineEdit->text().toDouble();

    if (marka.isEmpty() || model.isEmpty()) {
        QMessageBox::warning(this, "Blad", "Wszystkie pola musza byc uzupelnione.");
        return;
    }

    QString vin = salonRef->wygenerujUnikalnyVIN();
    pojazd = std::make_shared<Ciezarowy>(vin, marka, model, cena, rok, przebieg, ladownosc);
    accept();
}

std::shared_ptr<Pojazd> DodajCiezarowyDialog::getPojazd() const {
    return pojazd;
}
void DodajCiezarowyDialog::uzupelnijDanymi(std::shared_ptr<Ciezarowy> c)
{
    ui->markaLineEdit->setText(c->getMarka());
    ui->modelLineEdit->setText(c->getModel());
    ui->cenaLineEdit->setText(QString::number(c->getCena()));
    ui->rokLineEdit->setText(QString::number(c->getRok()));
    ui->przebiegLineEdit->setText(QString::number(c->getPrzebieg()));
    ui->ladownoscLineEdit->setText(QString::number(c->getLadownosc()));
}
