#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Salon.h"
#include <QMessageBox>
#include "dodajklientadialog.h"
#include <QInputDialog>
#include <QPixmap>
#include <QPalette>
#include <QImage>

MainWindow::MainWindow(Salon* salonPtr, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), salon(salonPtr) {
    ui->setupUi(this);
    odswiezListeKlientow();
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
        odswiezListeKlientow();
    }
}

void MainWindow::on_stackedWidget_currentChanged(int arg1)
{

}
void MainWindow::odswiezListeKlientow()
{
    qDebug() << "Wywołano odswiezListeKlientow()";

    ui->listWidgetKlienci->clear();
    for (const Client& k : salon->getKlienci()) {
        ui->listWidgetKlienci->addItem(k.getName() + " " + k.getSurname() + " ID: " + k.getId());
    }
}

void MainWindow::on_btnUsunKlienta_clicked()
{
    bool ok;
    int id = QInputDialog::getInt(this, "Usuń klienta", "Podaj ID klienta do usunięcia:", 0, 0, 999999, 1, &ok);

    if (!ok) return;  // Użytkownik anulował

    if (salon->usunKlientaPoId(id)) {
        QMessageBox::information(this, "Sukces", "Klient usunięty.");
        odswiezListeKlientow();
    } else {
        QMessageBox::warning(this, "Błąd", "Nie znaleziono klienta o podanym ID.");
    }
}
void MainWindow::on_btnWyszukaj_clicked()
{
    ui->tableWidgetKlienci->clearContents();
    ui->tableWidgetKlienci->setRowCount(0);
    ui->tableWidgetKlienci->setColumnCount(3);
    ui->tableWidgetKlienci->setHorizontalHeaderLabels({"ID", "Imię", "Nazwisko"});
    bool ok;
    QString tryb = QInputDialog::getItem(this, "Wyszukiwanie", "Szukaj po:",
                                         {"ID", "Imie", "Nazwisko"}, 0, false, &ok);
    if (!ok || tryb.isEmpty())
        return;

    QString wzorzec = QInputDialog::getText(this, "Wzorzec", "Podaj wzorzec:", QLineEdit::Normal, "", &ok);
    if (!ok || wzorzec.isEmpty())
        return;

    std::regex regex("^" + wzorzec.toStdString(), std::regex_constants::icase);

    auto& klienci = salon->getKlienci(); // salon to Salon*
    auto pasujacy = klienci | std::views::filter([&](const Client& k) {
                        if (tryb == "ID")       return std::regex_search(k.getId().toStdString(), regex);
                        if (tryb == "Imie")     return std::regex_search(k.getName().toStdString(), regex);
                        if (tryb == "Nazwisko") return std::regex_search(k.getSurname().toStdString(), regex);
                        return false;
                    });

    int row = 0;
    int ilosc = std::ranges::distance(pasujacy);
    ui->tableWidgetKlienci->setRowCount(static_cast<int>(ilosc));
    for (const Client& klient : pasujacy)
    {
        ui->tableWidgetKlienci->setItem(row, 0, new QTableWidgetItem(klient.getId()));
        ui->tableWidgetKlienci->setItem(row, 1, new QTableWidgetItem(klient.getName()));
        ui->tableWidgetKlienci->setItem(row, 2, new QTableWidgetItem(klient.getSurname()));
        ++row;
    }
}
void MainWindow::on_btnEdytujKlienta_clicked() {
    QString id = QInputDialog::getText(this, "Edycja klienta", "Podaj ID klienta:");
    if (id.isEmpty()) return;

    auto& klienci = salon->getKlienci();
    auto it = std::find_if(klienci.begin(), klienci.end(), [&](Client& k) {
        return k.getId() == id;
    });

    if (it == klienci.end()) {
        QMessageBox::warning(this, "Nie znaleziono", "Nie znaleziono klienta o podanym ID.");
        return;
    }

    QString noweImie = QInputDialog::getText(this, "Nowe imię", "Podaj nowe imię:", QLineEdit::Normal, it->getName());
    QString noweNazwisko = QInputDialog::getText(this, "Nowe nazwisko", "Podaj nowe nazwisko:", QLineEdit::Normal, it->getSurname());

    it->setName(noweImie);
    it->setSurname(noweNazwisko);
    odswiezListeKlientow();
    QMessageBox::information(this, "Zaktualizowano", "Dane klienta zostały zaktualizowane.");
}

