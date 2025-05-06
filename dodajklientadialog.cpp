#include "dodajklientadialog.h"
#include "ui_dodajklientadialog.h"
#include <QMessageBox>
#include "klient.h"
#include <QPushButton>
DodajKlientaDialog::DodajKlientaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DodajKlientaDialog)
{
    ui->setupUi(this);
    connect(ui->buttonBox->button(QDialogButtonBox::Ok), &QPushButton::clicked,
            this, &DodajKlientaDialog::onButtonOkClicked);
}

DodajKlientaDialog::~DodajKlientaDialog()
{
    delete ui;
}


Client DodajKlientaDialog::getClient() const
{
    return wynikowyKlient;
}


void DodajKlientaDialog::onButtonOkClicked()
{
    QString name = ui->nameLineEdit->text();
    QString surname = ui->surnameLineEdit->text();

    if (name.isEmpty() || surname.isEmpty()) {
        QMessageBox::warning(this, "Blad", "Uzupelnij wszystkie pola!");
        return;  // dialog zostaje otwarty
    }

    wynikowyKlient = Client(name, surname);
    danePoprawne = true;
    accept();  // zamknij dialog dopiero teraz
}




