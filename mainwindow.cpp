#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Salon.h"
#include <QMessageBox>
#include "dodajklientadialog.h"

MainWindow::MainWindow(Salon* salonPtr, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), salon(salonPtr) {
    ui->setupUi(this);

    connect(ui->actionKlienci, &QAction::triggered, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageKlienci);
    });

    connect(ui->actionPojazdy, &QAction::triggered, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pagePojazdy);
    });

    connect(ui->actionIntro, &QAction::triggered, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageIntro);
    });

    connect(ui->actionSprzedaz, &QAction::triggered, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageSprzedaz);
    });

    connect(ui->actionSerwis, &QAction::triggered, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageSerwis);
    });

    connect(ui->actionRaporty, &QAction::triggered, this, [this]() {
        ui->stackedWidget->setCurrentWidget(ui->pageRaporty);
    });
}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_btnDodajKlienta_clicked()
{
    DodajKlientaDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        Client nowy = dlg.getClient();
        salon->dodajKlienta(nowy);
        QMessageBox::information(this, "Sukces", "Dodano klienta.");
    }
}

void MainWindow::on_stackedWidget_currentChanged(int arg1)
{

}


