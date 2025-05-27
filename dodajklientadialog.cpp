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
    QString email = ui->emailLineEdit->text();
    QString tel = ui->telLineEdit->text();

    std::regex telefonRegex("^\\d{9}$");
    std::regex emailRegex("^[\\w.-]+@[\\w.-]+\\.[a-zA-Z]{2,}$");

    if (name.isEmpty() || surname.isEmpty() || email.isEmpty() || tel.isEmpty()) {
        QMessageBox::warning(this, "Blad", "Uzupelnij wszystkie pola!");
        return;
    }
    if (!std::regex_match(tel.toStdString(), telefonRegex)) {
        QMessageBox::warning(this, "Błąd", "Numer telefonu musi zawierać dokładnie 9 cyfr.");
        return;
    }

    if (!std::regex_match(email.toStdString(), emailRegex)) {
        QMessageBox::warning(this, "Błąd", "Nieprawidłowy adres email.");
        return;
    }
    wynikowyKlient = Client(name, surname, email, tel);
    danePoprawne = true;
    accept();
}




