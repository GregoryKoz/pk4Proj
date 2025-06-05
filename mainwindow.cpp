#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "Salon.h"
#include <QMessageBox>
#include "dodajklientadialog.h"
#include <QInputDialog>
#include <QPixmap>
#include <QPalette>
#include <QImage>
#include "Eksport.h"

MainWindow::MainWindow(Salon* salonPtr, QWidget* parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), salon(salonPtr) {
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->pageIntro);
    odswiezListeKlientow();
    odswiezListePojazdow();
    wypelnijTabeleSprzedazy();
    wypelnijTabeleSerwisow();
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
        salon->zapisManager.dodajZadanie([this]() {
            salon->zapiszKlientow("C:/Users/Janusz/Desktop/PK4- Laby/pliki do projektu/klienci.txt");
        });
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
        salon->zapisManager.dodajZadanie([this]() {
            salon->zapiszKlientow("C:/Users/Janusz/Desktop/PK4- Laby/pliki do projektu/klienci.txt");
        });
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
    salon->zapisManager.dodajZadanie([this]() {
        salon->zapiszKlientow("C:/Users/Janusz/Desktop/PK4- Laby/pliki do projektu/klienci.txt");
    });
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
        salon->zapisManager.dodajZadanie([this]() {
            salon->zapiszPojazdyDoPliku("C:/Users/Janusz/Desktop/PK4- Laby/pliki do projektu/pojazdy.txt");
        });
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
        salon->zapisManager.dodajZadanie([this]() {
            salon->zapiszPojazdyDoPliku("C:/Users/Janusz/Desktop/PK4- Laby/pliki do projektu/pojazdy.txt");
        });
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
        salon->zapisManager.dodajZadanie([this]() {
            salon->zapiszPojazdyDoPliku("C:/Users/Janusz/Desktop/PK4- Laby/pliki do projektu/pojazdy.txt");
        });
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
        ui->tableWidgetSprzedaz->setItem(row, 0, new QTableWidgetItem(s.getVIN()));
        ui->tableWidgetSprzedaz->setItem(row, 1, new QTableWidgetItem(s.getMarka()));
        ui->tableWidgetSprzedaz->setItem(row, 2, new QTableWidgetItem(s.getModel()));
        ui->tableWidgetSprzedaz->setItem(row, 3, new QTableWidgetItem(QString::number(s.getCenaSprzedazy(), 'f', 2)));
        ui->tableWidgetSprzedaz->setItem(row, 4, new QTableWidgetItem(s.getData()));
        ui->tableWidgetSprzedaz->setItem(row, 5, new QTableWidgetItem(s.getImieKlienta() + " " + s.getNazwiskoKlienta()));
        ++row;
    }

    ui->tableWidgetSprzedaz->resizeColumnsToContents();
}

void MainWindow::on_btnSprzedaj_clicked() {
    QStringList vinLista;
    for (const auto& p : salon->getPojazdy()) {
        vinLista << p->getVIN() + " (" + p->getMarka() + " " + p->getModel() + ")";
    }

    if (vinLista.isEmpty()) {
        QMessageBox::information(this, "Brak pojazdów", "Nie ma dostępnych pojazdów do sprzedaży.");
        return;
    }

    bool ok;
    QString wybranyVINOpis = QInputDialog::getItem(this, "Sprzedaż", "Wybierz VIN pojazdu:", vinLista, 0, false, &ok);
    if (!ok || wybranyVINOpis.isEmpty()) return;

    QString wybranyVIN = wybranyVINOpis.section(" ", 0, 0); // tylko VIN

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
    salon->zapisManager.dodajZadanie([this]() {
        salon->zapiszPojazdyDoPliku("C:/Users/Janusz/Desktop/PK4- Laby/pliki do projektu/pojazdy.txt");
    });
    salon->zapisManager.dodajZadanie([this]() {
        salon->zapiszSprzedazDoPliku("C:/Users/Janusz/Desktop/PK4- Laby/pliki do projektu/sprzedaz.txt");
    });
    odswiezListePojazdow();
    wypelnijTabeleSprzedazy();
}
void MainWindow::wypelnijTabeleSerwisow() {
    const auto& serwisy = salon->getSerwisy();

    ui->tableWidgetSerwisy->clearContents();
    ui->tableWidgetSerwisy->setRowCount(static_cast<int>(serwisy.size()));
    ui->tableWidgetSerwisy->setColumnCount(6);
    ui->tableWidgetSerwisy->setHorizontalHeaderLabels({"Klient ID", "VIN", "Opis usterki", "Zgłoszono", "Umówiono", "Status"});

    int row = 0;
    for (const auto& s : serwisy) {
        ui->tableWidgetSerwisy->setItem(row, 0, new QTableWidgetItem(s.getIdKlienta()));
        ui->tableWidgetSerwisy->setItem(row, 1, new QTableWidgetItem(s.getVIN()));
        ui->tableWidgetSerwisy->setItem(row, 2, new QTableWidgetItem(s.getOpis()));
        ui->tableWidgetSerwisy->setItem(row, 3, new QTableWidgetItem(s.getDataZgloszenia().toString("yyyy-MM-dd")));
        ui->tableWidgetSerwisy->setItem(row, 4, new QTableWidgetItem(s.getDataUmowiona().toString("yyyy-MM-dd")));
        ui->tableWidgetSerwisy->setItem(row, 5, new QTableWidgetItem(s.czyZakonczone() ? "Zakończone" : "W toku"));
        ++row;
    }

    ui->tableWidgetSerwisy->resizeColumnsToContents();
}
void MainWindow::on_btnZglos_clicked() {
    QStringList vinLista;

    // Dodaj dostępne pojazdy
    for (const auto& p : salon->getPojazdy()) {
        vinLista << p->getVIN() + " (" + p->getMarka() + " " + p->getModel() + ")";
    }

    // Dodaj sprzedane
    for (const auto& s : salon->getSprzedaze()) {
        vinLista << s.getVIN() + " (" + s.getMarka() + " " + s.getModel() + ") [SPRZEDANY]";
    }

    if (vinLista.isEmpty()) {
        QMessageBox::information(this, "Brak pojazdów", "Nie ma dostępnych pojazdów do zgłoszenia serwisowego.");
        return;
    }

    bool ok;
    QString wybranyVINOpis = QInputDialog::getItem(this, "Zgłoszenie serwisowe", "Wybierz VIN pojazdu:", vinLista, 0, false, &ok);
    if (!ok || wybranyVINOpis.isEmpty()) return;

    QString wybranyVIN = wybranyVINOpis.section(" ", 0, 0); // tylko VIN
    std::shared_ptr<Pojazd> pojazd = nullptr;

    // Szukaj w dostępnych
    auto pojazdIt = std::find_if(salon->getPojazdy().begin(), salon->getPojazdy().end(),
                                 [&](const auto& p) { return p->getVIN() == wybranyVIN; });

    if (pojazdIt != salon->getPojazdy().end()) {
        pojazd = *pojazdIt;
    } else {
        // Szukaj w sprzedanych
        const auto& sprzedane = salon->getSprzedaze();
        auto sIt = std::find_if(sprzedane.begin(), sprzedane.end(),
                                [&](const Sprzedaz& s) { return s.getVIN() == wybranyVIN; });

        if (sIt != sprzedane.end()) {
            const auto& s = *sIt;
            if (s.getTypPojazdu() == "Osobowy") {
                int miejsca = s.getCechaSpecyficzna().toInt();
                pojazd = std::make_shared<Osobowy>(
                    s.getVIN(), s.getMarka(), s.getModel(), s.getCenaSprzedazy(),
                    s.getRokProdukcji(), s.getPrzebieg(), miejsca);
            } else if (s.getTypPojazdu() == "Motocykl") {
                int moc = s.getCechaSpecyficzna().toInt();
                pojazd = std::make_shared<Motocykl>(
                    s.getVIN(), s.getMarka(), s.getModel(), s.getCenaSprzedazy(),
                    s.getRokProdukcji(), s.getPrzebieg(), moc);
            } else if (s.getTypPojazdu() == "Ciezarowy") {
                double ladownosc = s.getCechaSpecyficzna().toDouble();
                pojazd = std::make_shared<Ciezarowy>(
                    s.getVIN(), s.getMarka(), s.getModel(), s.getCenaSprzedazy(),
                    s.getRokProdukcji(), s.getPrzebieg(), ladownosc);
            }
        }
    }

    if (!pojazd) {
        QMessageBox::warning(this, "Błąd", "Nie znaleziono pojazdu.");
        return;
    }

    const auto& klienci = salon->getKlienci();
    if (klienci.empty()) {
        QMessageBox::information(this, "Brak klientów", "Brak zarejestrowanych klientów.");
        return;
    }

    QStringList klientLista;
    for (const auto& k : klienci) {
        klientLista << k->getName() + " " + k->getSurname();
    }

    QString wybranyKlient = QInputDialog::getItem(this, "Zgłoszenie serwisowe", "Wybierz klienta:", klientLista, 0, false, &ok);
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

    QString opis = QInputDialog::getText(this, "Zgłoszenie serwisowe", "Podaj opis usterki:", QLineEdit::Normal, "", &ok);
    if (!ok || opis.isEmpty()) return;

    QString dataTekst = QInputDialog::getText(this, "Zgłoszenie serwisowe", "Podaj datę umówienia (rrrr-mm-dd):", QLineEdit::Normal, "", &ok);
    if (!ok || dataTekst.isEmpty()) return;

    QDate dataUmowiona = QDate::fromString(dataTekst, "yyyy-MM-dd");
    if (!dataUmowiona.isValid()) {
        QMessageBox::warning(this, "Błąd", "Nieprawidłowy format daty. Użyj formatu RRRR-MM-DD.");
        return;
    }

    salon->dodajSerwis(Serwis(klient->getId(), pojazd->getVIN(), opis, dataUmowiona));
    salon->zapisManager.dodajZadanie([this]() {
        salon->zapiszSerwisyDoPliku("C:/Users/Janusz/Desktop/PK4- Laby/pliki do projektu/serwisy.txt");
    });
    QMessageBox::information(this, "Zgłoszono", "Zgłoszenie serwisowe zostało zapisane.");
    wypelnijTabeleSerwisow();
}
void MainWindow::on_btnWykonaj_clicked() {
    const auto& serwisy = salon->getSerwisy();


    QStringList aktywneVINy;
    for (const auto& s : serwisy) {
        if (!s.czyZakonczone()) {
            aktywneVINy << s.getVIN() + " (" + s.getIdKlienta() + ")";
        }
    }

    if (aktywneVINy.isEmpty()) {
        QMessageBox::information(this, "Brak zgłoszeń", "Nie ma aktywnych zgłoszeń serwisowych.");
        return;
    }

    bool ok;
    QString wybranyVINOpis = QInputDialog::getItem(this, "Zakończ serwis", "Wybierz VIN pojazdu:", aktywneVINy, 0, false, &ok);
    if (!ok || wybranyVINOpis.isEmpty()) return;

    QString wybranyVIN = wybranyVINOpis.section(" ", 0, 0); // tylko VIN


    if (salon->zakonczSerwisPoVIN(wybranyVIN)) {
        QMessageBox::information(this, "Sukces", "Serwis został oznaczony jako zakończony.");
        wypelnijTabeleSerwisow();
        salon->zapisManager.dodajZadanie([this]() {
            salon->zapiszSerwisyDoPliku("C:/Users/Janusz/Desktop/PK4- Laby/pliki do projektu/serwisy.txt");
        });

    } else {
        QMessageBox::warning(this, "Błąd", "Nie znaleziono aktywnego zgłoszenia z tym VIN.");
    }
}
void MainWindow::on_btnUsunSprzedaz_clicked(){
    const auto& sprzedaze = salon->getSprzedaze();
    if(sprzedaze.empty()){
        QMessageBox::information(this,"Brak danych", "Nie ma żadnych zapisanych sprzedaży do usunięcia");
        return;
    }
    QStringList listaOpisow;
    for(const auto& s: sprzedaze){
        listaOpisow << s.getVIN() + " - " + s.getIdKlienta();
    }
    bool ok;
    QString wybor = QInputDialog::getItem(this, "Usun sprzedaż", "Wybierz sprzedaż do usunięcia:", listaOpisow,0,false,&ok);
    if (!ok || wybor.isEmpty()) return;

    QString vin = wybor.section(" ", 0, 0); // tylko VIN

    if (salon->usunSprzedazPoVIN(vin)) {
        QMessageBox::information(this, "Usunięto", "Sprzedaż została usunięta.");
        wypelnijTabeleSprzedazy();
        salon->zapisManager.dodajZadanie([this]() {
            salon->zapiszSprzedazDoPliku("C:/Users/Janusz/Desktop/PK4- Laby/pliki do projektu/sprzedaz.txt");
        });
    } else {
        QMessageBox::warning(this, "Błąd", "Nie udało się znaleźć sprzedaży z podanym VIN.");
    }

}
void MainWindow::on_btnUsunSerwis_clicked() {
    const auto& serwisy = salon->getSerwisy();

    if (serwisy.empty()) {
        QMessageBox::information(this, "Brak zgłoszeń", "Brak zgłoszeń serwisowych do usunięcia.");
        return;
    }

    QStringList listaSerwisow;
    for (const auto& s : serwisy) {
        QString opis = s.getVIN() + " | " + s.getDataUmowiona().toString("yyyy-MM-dd") + " | " + s.getOpis();
        listaSerwisow << opis;
    }

    bool ok;
    QString wybor = QInputDialog::getItem(this, "Usuń serwis", "Wybierz zgłoszenie do usunięcia:", listaSerwisow, 0, false, &ok);
    if (!ok || wybor.isEmpty()) return;

    int index = listaSerwisow.indexOf(wybor);
    if (index >= 0 && salon->usunSerwisPoIndeksie(index)) {
        QMessageBox::information(this, "Usunięto", "Zgłoszenie serwisowe zostało usunięte.");
        wypelnijTabeleSerwisow();
        salon->zapisManager.dodajZadanie([this]() {
            salon->zapiszSprzedazDoPliku("C:/Users/Janusz/Desktop/PK4- Laby/pliki do projektu/serwisy.txt");
        });
    } else {
        QMessageBox::warning(this, "Błąd", "Nie udało się usunąć zgłoszenia.");
    }
}
void MainWindow::on_btnSuma_clicked() {
    Eksport::podsumujSprzedaz(salon->getSprzedaze());
    QMessageBox::information(this, "Eksport", "Podsumowanie sprzedaży zostało zapisane.");
}
void MainWindow::on_btnPojazdyKlienta_clicked() {
    const auto& klienci = salon->getKlienci();
    if (klienci.empty()) {
        QMessageBox::warning(this, "Brak danych", "Brak klientów.");
        return;
    }

    QStringList lista;
    for (const auto& k : klienci) {
        lista << k->getName() + " " + k->getSurname();
    }

    bool ok;
    QString wybrany = QInputDialog::getItem(this, "Eksport", "Wybierz klienta:", lista, 0, false, &ok);
    if (!ok || wybrany.isEmpty()) return;

    auto it = std::find_if(klienci.begin(), klienci.end(), [&](const auto& k) {
        return k->getName() + " " + k->getSurname() == wybrany;
    });

    if (it == klienci.end()) return;

    const auto& klient = *it;
    Eksport::pojazdyKlienta(salon->getSprzedaze(), klient->getId(), klient->getName(), klient->getSurname());
    QMessageBox::information(this, "Eksport", "Lista pojazdów została zapisana.");
}
void MainWindow::on_btnSerwisyKlienta_clicked() {
    const auto& klienci = salon->getKlienci();
    if (klienci.empty()) {
        QMessageBox::warning(this, "Brak danych", "Brak klientów.");
        return;
    }

    QStringList lista;
    for (const auto& k : klienci) {
        lista << k->getName() + " " + k->getSurname();
    }

    bool ok;
    QString wybrany = QInputDialog::getItem(this, "Eksport", "Wybierz klienta:", lista, 0, false, &ok);
    if (!ok || wybrany.isEmpty()) return;

    auto it = std::find_if(klienci.begin(), klienci.end(), [&](const auto& k) {
        return k->getName() + " " + k->getSurname() == wybrany;
    });

    if (it == klienci.end()) return;

    const auto& klient = *it;
    Eksport::serwisyKlienta(salon->getSerwisy(), klient->getId(), klient->getName(), klient->getSurname());
    QMessageBox::information(this, "Eksport", "Lista serwisów klienta została zapisana.");
}
void MainWindow::on_btnSerwisyPojazdu_clicked() {
    const auto& wszystkie = salon->getSerwisy();
    if (wszystkie.empty()) {
        QMessageBox::warning(this, "Brak danych", "Brak zgłoszeń serwisowych.");
        return;
    }

    QStringList viny;
    for (const auto& s : wszystkie) {
        if (!viny.contains(s.getVIN()))
            viny << s.getVIN();
    }

    bool ok;
    QString wybranyVIN = QInputDialog::getItem(this, "Eksport", "Wybierz VIN pojazdu:", viny, 0, false, &ok);
    if (!ok || wybranyVIN.isEmpty()) return;

    Eksport::serwisyPojazdu(wszystkie, wybranyVIN);
    QMessageBox::information(this, "Eksport", "Lista serwisów pojazdu została zapisana.");
}

