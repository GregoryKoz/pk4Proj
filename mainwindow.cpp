#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Salon.h"
#include <QMessageBox>

MainWindow::MainWindow(Salon* salonPtr, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), salon(salonPtr) {
    ui->setupUi(this);
    connect(ui->addClientButton, &QPushButton::clicked, this, &MainWindow::onAddClientClicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::onAddClientClicked() {
    QString name = ui->nameLineEdit->text();
    QString surname = ui->surnameLineEdit->text();



    if (name.isEmpty() || surname.isEmpty() ) {
        QMessageBox::warning(this, "Blad", "Uzupelnij wszystkie pola!");
        return;
    }

    Client nowy(name, surname);
    salon->dodajKlienta(nowy);;
    QMessageBox::information(this, "Sukces", "Dodano klienta.");
}
