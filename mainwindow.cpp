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
    ui->stackedWidget->setCurrentWidget(ui->pageIntro);
    odswiezListeKlientow();
    odswiezListePojazdow();
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
        auto nowyPtr = std::make_shared<Client>(std::move(nowy));
        salon->dodajKlienta(nowyPtr);
        QMessageBox::information(this, "Sukces", "Dodano klienta.");
        odswiezListeKlientow();
    }
}
void MainWindow::on_btnStronaKlient_clicked(){
    ui->stackedWidget->setCurrentWidget(ui->pageKlienci);
}
void MainWindow::on_btnStronaPojazd_clicked(){
    ui->stackedWidget->setCurrentWidget(ui->pagePojazdy);
}
void MainWindow::on_btnStronaRaport_clicked(){
    ui->stackedWidget->setCurrentWidget(ui->pageRaporty);
}
void MainWindow::on_btnStronaSprzedaz_clicked(){
    ui->stackedWidget->setCurrentWidget(ui->pageSprzedaz);
}
void MainWindow::on_btnStronaSerwis_clicked(){
    ui->stackedWidget->setCurrentWidget(ui->pageSerwis);
}
void MainWindow::on_stackedWidget_currentChanged(int arg1)
{

}
void MainWindow::odswiezListeKlientow()
{
    qDebug() << "Wywołano odswiezListeKlientow()";

    ui->listWidgetKlienci->clear();
    for (const auto& k : salon->getKlienci()) {
        ui->listWidgetKlienci->addItem(
            k->getName() + " " + k->getSurname() + " ID: " + k->getId() + " " + k->getEmail() + " " + k->getTel()
            );
    }
}

void MainWindow::on_btnUsunKlienta_clicked()
{
    bool ok;
    int id = QInputDialog::getInt(this, "Usuń klienta", "Podaj ID klienta do usunięcia:", 0, 0, 999999, 1, &ok);

    if (!ok) return;

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
    ui->tableWidgetKlienci->setColumnCount(5);
    ui->tableWidgetKlienci->setHorizontalHeaderLabels({"ID", "Imię", "Nazwisko", "Email", "Telefon"});

    bool ok;
    QString tryb = QInputDialog::getItem(this, "Wyszukiwanie", "Szukaj po:",
                                         {"ID", "Imie", "Nazwisko"}, 0, false, &ok);
    if (!ok || tryb.isEmpty())
        return;

    QString wzorzec = QInputDialog::getText(this, "Wzorzec", "Podaj wzorzec:", QLineEdit::Normal, "", &ok);
    if (!ok || wzorzec.isEmpty())
        return;

    std::regex regex("^" + wzorzec.toStdString(), std::regex_constants::icase);

    const auto& klienci = salon->getKlienci();
    auto pasujacy = klienci | std::views::filter([&](const std::shared_ptr<Client>& k) {
                        if (tryb == "ID")       return std::regex_search(k->getId().toStdString(), regex);
                        if (tryb == "Imie")     return std::regex_search(k->getName().toStdString(), regex);
                        if (tryb == "Nazwisko") return std::regex_search(k->getSurname().toStdString(), regex);
                        return false;
                    });

    int row = 0;
    int ilosc = std::ranges::distance(pasujacy);
    ui->tableWidgetKlienci->setRowCount(static_cast<int>(ilosc));
    for (const auto& klient : pasujacy)
    {
        ui->tableWidgetKlienci->setItem(row, 0, new QTableWidgetItem(klient->getId()));
        ui->tableWidgetKlienci->setItem(row, 1, new QTableWidgetItem(klient->getName()));
        ui->tableWidgetKlienci->setItem(row, 2, new QTableWidgetItem(klient->getSurname()));
        ui->tableWidgetKlienci->setItem(row, 3, new QTableWidgetItem(klient->getEmail()));
        ui->tableWidgetKlienci->setItem(row, 4, new QTableWidgetItem(klient->getTel()));
        ++row;
    }
}
void MainWindow::on_btnEdytujKlienta_clicked() {
    QString id = QInputDialog::getText(this, "Edycja klienta", "Podaj ID klienta:");
    if (id.isEmpty()) return;

    auto& klienci = salon->getKlienci();
    auto it = std::find_if(klienci.begin(), klienci.end(), [&](const std::shared_ptr<Client>& k) {
        return k->getId() == id;
    });

    if (it == klienci.end()) {
        QMessageBox::warning(this, "Nie znaleziono", "Nie znaleziono klienta o podanym ID.");
        return;
    }

    std::regex telefonRegex("^\\d{9}$");
    std::regex emailRegex("^[\\w.-]+@[\\w.-]+\\.[a-zA-Z]{2,}$");

    QString noweImie = QInputDialog::getText(this, "Nowe imię", "Podaj nowe imię:", QLineEdit::Normal, (*it)->getName());
    QString noweNazwisko = QInputDialog::getText(this, "Nowe nazwisko", "Podaj nowe nazwisko:", QLineEdit::Normal, (*it)->getSurname());
    QString nowyEmail = QInputDialog::getText(this, "Nowy email", "Podaj nowy email:", QLineEdit::Normal, (*it)->getEmail());
    if (!std::regex_match(nowyEmail.toStdString(), emailRegex)) {
        QMessageBox::warning(this, "Błąd", "Nieprawidłowy adres email.");
        return;
    }
    QString nowyTel = QInputDialog::getText(this, "Nowy numer telefonu", "Podaj nowy numer telefonu:", QLineEdit::Normal, (*it)->getTel());
    if (!std::regex_match(nowyTel.toStdString(), telefonRegex)) {
        QMessageBox::warning(this, "Błąd", "Numer telefonu musi zawierać dokładnie 9 cyfr.");
        return;
    }

    (*it)->setName(noweImie);
    (*it)->setSurname(noweNazwisko);
    (*it)->setEmail(nowyEmail);
    (*it)->setTel(nowyTel);

    odswiezListeKlientow();
    QMessageBox::information(this, "Zaktualizowano", "Dane klienta zostały zaktualizowane.");
}

void MainWindow::odswiezListePojazdow()
{
    qDebug() << "Wywołano odswiezListePojazdow()";

    ui->listWidgetPojazdy->clear();
    for (const auto& pojazd : salon->getPojazdy()) {
       ui->listWidgetPojazdy->addItem(pojazd->getTyp() + ": " + pojazd->getOpis());
    }
}
void MainWindow::on_btnDodajPojazd_clicked()
{
    QStringList typy = {"Osobowy", "Motocykl", "Ciezarowy"};
    bool ok;
    QString wybor = QInputDialog::getItem(this, "Wybierz typ pojazdu", "Typ:", typy, 0, false, &ok);

    if (!ok || wybor.isEmpty()) return;

    std::unique_ptr<DodajPojazdDialog> dialog;

    if (wybor == "Osobowy")
        dialog = std::make_unique<DodajOsobowyDialog>(salon, this);
    else if (wybor == "Motocykl")
        dialog = std::make_unique<DodajMotocyklDialog>(salon, this);
    else if (wybor == "Ciezarowy")
        dialog = std::make_unique<DodajCiezarowyDialog>(salon, this);

    if (dialog && dialog->exec() == QDialog::Accepted) {
        salon->dodajPojazd(dialog->getPojazd());
        QMessageBox::information(this, "Sukces", "Dodano pojazd.");
        odswiezListePojazdow();
    }
}
void MainWindow::on_btnUsunPojazd_clicked()
{
    QStringList listaVIN;
    for (const auto& p : salon->getPojazdy()) {
        listaVIN << p->getVIN() + " (" + p->getMarka() + " " + p->getModel() + ")";
    }

    bool ok;
    QString wybor = QInputDialog::getItem(this, "Usuń pojazd", "Wybierz pojazd:", listaVIN, 0, false, &ok);

    if (!ok || wybor.isEmpty())
        return;

    // Wyciągamy VIN z tekstu "VIN123456789 (Marka Model)"
    QString vin = wybor.section(' ', 0, 0);

    if (salon->usunPojazdPoVIN(vin)) {
        QMessageBox::information(this, "Sukces", "Pojazd został usunięty.");
        odswiezListePojazdow();
    } else {
        QMessageBox::warning(this, "Błąd", "Nie znaleziono pojazdu o podanym VIN.");
    }
}
void MainWindow::on_btnEdytujPojazd_clicked()
{
    QStringList listaVIN;
    for (const auto& p : salon->getPojazdy()) {
        listaVIN << p->getVIN() + " (" + p->getMarka() + " " + p->getModel() + ")";
    }

    bool ok;
    QString wybor = QInputDialog::getItem(this, "Edytuj pojazd", "Wybierz pojazd:", listaVIN, 0, false, &ok);
    if (!ok || wybor.isEmpty()) return;

    QString vin = wybor.section(' ', 0, 0);  // wyciągamy VIN

    auto pojazd = salon->znajdzPojazdPoVIN(vin);
    if (!pojazd) {
        QMessageBox::warning(this, "Błąd", "Nie znaleziono pojazdu.");
        return;
    }

    std::unique_ptr<DodajPojazdDialog> dialog;

    if (pojazd->getTyp() == "Osobowy") {
        auto dlg = new DodajOsobowyDialog(salon, this);
        dlg->setWindowTitle("Edytuj pojazd - Osobowy");
        dlg->uzupelnijDanymi(std::dynamic_pointer_cast<Osobowy>(pojazd));
        dialog.reset(dlg);
    }
    else if (pojazd->getTyp() == "Motocykl") {
        auto dlg = new DodajMotocyklDialog(salon, this);
        dlg->setWindowTitle("Edytuj pojazd - Motocykl");
        dlg->uzupelnijDanymi(std::dynamic_pointer_cast<Motocykl>(pojazd));
        dialog.reset(dlg);
    }
    else if (pojazd->getTyp() == "Ciezarowy") {
        auto dlg = new DodajCiezarowyDialog(salon, this);
        dlg->setWindowTitle("Edytuj pojazd - Ciezarowy");
        dlg->uzupelnijDanymi(std::dynamic_pointer_cast<Ciezarowy>(pojazd));
        dialog.reset(dlg);
    }

    if (!dialog) return;

    if (dialog->exec() == QDialog::Accepted) {
        auto nowy = dialog->getPojazd();
        nowy->setVIN(pojazd->getVIN());
        salon->zamienPojazd(vin, nowy);
        QMessageBox::information(this, "Zaktualizowano", "Dane pojazdu zostały zaktualizowane.");
        odswiezListePojazdow();
    }
}

void MainWindow::on_btnWyszukajPojazd_clicked(){
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(0);
    ui->tableWidget->setColumnCount(7);
    ui->tableWidget->setHorizontalHeaderLabels({"VIN","Marka","Model","Cena","Rok produkcji","Przebieg","Cecha specyficzna"});
    bool ok;
    QString tryb = QInputDialog::getItem(this, "Wyszukiwanie", "Szukaj po:",
                                         {"Marka", "Model", "Cena","Rok produkcji","Przebieg"}, 0, false, &ok);
    if (!ok || tryb.isEmpty())
        return;

    QString wzorzec = QInputDialog::getText(this, "Wzorzec", "Podaj wzorzec:", QLineEdit::Normal, "", &ok);
    if (!ok || wzorzec.isEmpty())
        return;

    std::regex regex("^" + wzorzec.toStdString(), std::regex_constants::icase);

    auto& pojazdy = salon->getPojazdy();
    auto pasujacy = pojazdy | std::views::filter([&](const std::shared_ptr<Pojazd>& p) {
                        if (tryb == "Marka") return std::regex_search(p->getMarka().toStdString(), regex);
                        if (tryb == "Model") return std::regex_search(p->getModel().toStdString(), regex);
                        if (tryb == "Cena") return std::regex_search(QString::number(p->getCena()).toStdString(), regex);
                        if (tryb == "Rok produkcji") return std::regex_search(QString::number(p->getRok()).toStdString(), regex);
                        if (tryb == "Przebieg") return std::regex_search(QString::number(p->getPrzebieg()).toStdString(), regex);
                        return false;
                    });
    int row = 0;
    int ilosc = std::ranges::distance(pasujacy);
    ui->tableWidget->setRowCount(static_cast<int>(ilosc));

    for (const auto& pojazd : pasujacy) {
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(pojazd->getVIN()));
        ui->tableWidget->setItem(row, 1, new QTableWidgetItem(pojazd->getMarka()));
        ui->tableWidget->setItem(row, 2, new QTableWidgetItem(pojazd->getModel()));
        ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(pojazd->getCena())));
        ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::number(pojazd->getRok())));
        ui->tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(pojazd->getPrzebieg())));

        QString cecha;
        if (auto o = std::dynamic_pointer_cast<Osobowy>(pojazd))
            cecha = QString::number(o->getliczbaMiejsc()) + " miejsc";
        else if (auto m = std::dynamic_pointer_cast<Motocykl>(pojazd))
            cecha = QString::number(m->getMoc()) + " KM";
        else if (auto c = std::dynamic_pointer_cast<Ciezarowy>(pojazd))
            cecha = QString::number(c->getLadownosc()) + " kg";

        ui->tableWidget->setItem(row, 6, new QTableWidgetItem(cecha));
        ++row;
    }
}
void MainWindow::wypelnijTabeleSprzedazy() {
    const auto& sprzedaze = salon->getSprzedaze();

    ui->tableWidgetSprzedaz->clearContents();
    ui->tableWidgetSprzedaz->setRowCount(static_cast<int>(sprzedaze.size()));
    ui->tableWidgetSprzedaz->setColumnCount(6);
    ui->tableWidgetSprzedaz->setHorizontalHeaderLabels({"VIN", "Marka", "Model", "Cena", "Data", "Klient"});

    int row = 0;
    for (const auto& s : sprzedaze) {
        const auto& p = s.getPojazd();
        const auto& k = s.getKlient();

        ui->tableWidgetSprzedaz->setItem(row, 0, new QTableWidgetItem(p->getVIN()));
        ui->tableWidgetSprzedaz->setItem(row, 1, new QTableWidgetItem(p->getMarka()));
        ui->tableWidgetSprzedaz->setItem(row, 2, new QTableWidgetItem(p->getModel()));
        ui->tableWidgetSprzedaz->setItem(row, 3, new QTableWidgetItem(QString::number(s.getCena())));
        ui->tableWidgetSprzedaz->setItem(row, 4, new QTableWidgetItem(s.getData().toString("yyyy-MM-dd HH:mm")));
        ui->tableWidgetSprzedaz->setItem(row, 5, new QTableWidgetItem(k->getName() + " " + k->getSurname()));
        ++row;
    }

    ui->tableWidgetSprzedaz->resizeColumnsToContents();
}

void MainWindow::on_btnSprzedaj_clicked() {
    QStringList vinLista;
    for (const auto& p : salon->getPojazdy()) {
        vinLista << p->getVIN();
    }

    if (vinLista.isEmpty()) {
        QMessageBox::information(this, "Brak pojazdów", "Nie ma dostępnych pojazdów do sprzedaży.");
        return;
    }

    bool ok;
    QString wybranyVIN = QInputDialog::getItem(this, "Sprzedaż", "Wybierz VIN pojazdu:", vinLista, 0, false, &ok);
    if (!ok || wybranyVIN.isEmpty()) return;

    auto pojazdIt = std::find_if(salon->getPojazdy().begin(), salon->getPojazdy().end(),
                                 [&](const auto& p) { return p->getVIN() == wybranyVIN; });

    if (pojazdIt == salon->getPojazdy().end()) {
        QMessageBox::warning(this, "Błąd", "Nie znaleziono pojazdu.");
        return;
    }

    std::shared_ptr<Pojazd> pojazd = *pojazdIt;

    const auto& klienci = salon->getKlienci();
    if (klienci.empty()) {
        QMessageBox::information(this, "Brak klientów", "Brak zarejestrowanych klientów.");
        return;
    }

    QStringList klientLista;
    for (const auto& k : klienci) {
        klientLista << k->getName() + " " + k->getSurname();  // <- poprawka
    }

    QString wybranyKlient = QInputDialog::getItem(this, "Sprzedaż", "Wybierz klienta:", klientLista, 0, false, &ok);
    if (!ok || wybranyKlient.isEmpty()) return;

    auto klientIt = std::find_if(klienci.begin(), klienci.end(),
                                 [&](const auto& k) {
                                     return (k->getName() + " " + k->getSurname()) == wybranyKlient;
                                 });

    if (klientIt == klienci.end()) {
        QMessageBox::warning(this, "Błąd", "Nie znaleziono klienta.");
        return;
    }

    std::shared_ptr<Client> klient = *klientIt;

    double cena = QInputDialog::getDouble(
        this,
        "Sprzedaż",
        "Podaj cenę sprzedaży:",
        pojazd->getCena(),
        0.0,
        10000000.0,
        2,
        &ok
        );
    if (!ok) return;

    salon->sprzedajPojazd(pojazd, klient, cena);
    QMessageBox::information(this, "Sukces", "Pojazd został sprzedany.");

    odswiezListePojazdow();
    wypelnijTabeleSprzedazy();
}
