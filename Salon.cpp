#include "Salon.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <filesystem>
#include <QDate>
#include "osobowy.h"
#include "ciezarowy.h"
#include "motocykl.h"


Salon::Salon(QObject *parent)
    : QObject(parent){}

void Salon::dodajKlienta(const std::shared_ptr<Client>& klient) {
    klienci.push_back(klient);
}
std::vector<std::shared_ptr<Client>>& Salon::getKlienci() {
    return klienci;
}

void Salon::zapiszKlientow(const std::string& sciezkaPliku) const{
    std::filesystem::path path = sciezkaPliku;
    QFile file(QString::fromStdString(path.string()));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Nie można otworzyć pliku do zapisu:" << QString::fromStdString(path.string());
        return;
    }
    qDebug() << "Liczba klientów:" << klienci.size();
    qDebug() << "Zapisuję klientów do pliku:" << QString::fromStdString(path.string());
    QTextStream out(&file);
    for (const auto& c : klienci) {
        out << c->getName() << ";" << c->getSurname() << ";" << c->getId() << ";" << c->getEmail() << ";" << c->getTel() <<"\n";
    }
}

void Salon::wczytajKlientow(const std::string& sciezkaPliku) {
    klienci.clear();

    std::filesystem::path path = sciezkaPliku;

    if (!std::filesystem::exists(path)) {
        qWarning() << "Plik nie istnieje:" << QString::fromStdString(path.string());
        return;
    }

    QFile file(QString::fromStdString(path.string()));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Nie można otworzyć pliku do odczytu:" << QString::fromStdString(path.string());
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList parts = line.split(';');
        if (parts.size() == 5) {
            klienci.emplace_back(std::make_shared<Client>(parts[0], parts[1], parts[2], parts[3], parts[4]));
        } else {
            qWarning() << "Błędna liczba pól w linii:" << line;
        }
    }

    qDebug() << "Liczba klientów:" << klienci.size();
    emit klienciWczytani();
}

bool Salon::usunKlientaPoId(int id)
{
    auto it = std::find_if(klienci.begin(), klienci.end(),
                           [id](const std::shared_ptr<Client>& c) {
                               return c->getId() == QString::number(id);
                           });

    if (it != klienci.end()) {
        klienci.erase(it);
        return true;
    }

    return false;
}

std::vector<std::shared_ptr<Pojazd>>& Salon::getPojazdy() {
    return pojazdy;
}
void Salon::wczytajPojazdy(const std::string& sciezkaPliku) {
    pojazdy.clear();

    std::filesystem::path path = sciezkaPliku;
    if (!std::filesystem::exists(path)) {
        qWarning() << "Plik nie istnieje:" << QString::fromStdString(path.string());
        return;
    }

    QFile file(QString::fromStdString(path.string()));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Nie można otworzyć pliku do odczytu:" << QString::fromStdString(path.string());
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList parts = line.split(';');

        if (parts.isEmpty()) continue;

        QString typ = parts[0];
        std::shared_ptr<Pojazd> pojazd;

        if (typ == "Osobowy") {
            pojazd = std::make_shared<Osobowy>();
        } else if (typ == "Ciezarowy") {
            pojazd = std::make_shared<Ciezarowy>();
        } else if (typ == "Motocykl") {
            pojazd = std::make_shared<Motocykl>();
        } else {
            qWarning() << "Nieznany typ pojazdu:" << typ;
            continue;
        }

        // przekształć części do jednego strumienia
        QStringList danePojazdu = parts.mid(1);
        pojazd->wczytaj(danePojazdu);
        pojazdy.push_back(pojazd);
    }

    qDebug() << "Wczytano pojazdów:" << pojazdy.size();
}
void Salon::zapiszPojazdyDoPliku(const std::string& sciezkaPliku) {
    QFile file(QString::fromStdString(sciezkaPliku));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Nie można otworzyć pliku do zapisu:" << QString::fromStdString(sciezkaPliku);
        return;
    }

    QTextStream out(&file);
    for (const auto& pojazd : pojazdy) {
        out << pojazd->zapisz() << "\n";
    }

    file.close();
    qDebug() << "Zapisano pojazdy do pliku:" << QString::fromStdString(sciezkaPliku);
}
void Salon::dodajPojazd(const std::shared_ptr<Pojazd>& pojazd) {
    pojazdy.push_back(pojazd);
}
bool Salon::vinIstnieje(const QString& vin) const {
    return std::any_of(pojazdy.begin(), pojazdy.end(), [&](const auto& p) {
        return p->getVIN() == vin;
    });
}
QString Salon::wygenerujUnikalnyVIN() {
    QString vin;
    do {
        vin = QUuid::createUuid().toString(QUuid::WithoutBraces).remove('-').left(17).toUpper();
    } while (vinIstnieje(vin));
    return vin;
}
bool Salon::usunPojazdPoVIN(const QString& vin) {
    auto it = std::find_if(pojazdy.begin(), pojazdy.end(), [&](const auto& p) {
        return p->getVIN() == vin;
    });
    if (it != pojazdy.end()) {
        pojazdy.erase(it);
        return true;
    }
    return false;
}
std::shared_ptr<Pojazd> Salon::znajdzPojazdPoVIN(const QString& vin) {
    auto it = std::find_if(pojazdy.begin(), pojazdy.end(), [&](auto& p) {
        return p->getVIN() == vin;
    });
    return (it != pojazdy.end()) ? *it : nullptr;
}

void Salon::zamienPojazd(const QString& vin, std::shared_ptr<Pojazd> nowy) {
    auto it = std::find_if(pojazdy.begin(), pojazdy.end(), [&](auto& p) {
        return p->getVIN() == vin;
    });
    if (it != pojazdy.end()) {
        *it = nowy;
    }
}
void Salon::sprzedajPojazd(std::shared_ptr<Pojazd> pojazd, std::shared_ptr<Client> klient, double cena) {
    if (!pojazd || !klient)
        return;

    QString vin = pojazd->getVIN();
    QString typ = pojazd->getTyp();
    QString marka = pojazd->getMarka();
    QString model = pojazd->getModel();
    int rok = pojazd->getRok();
    int przebieg = pojazd->getPrzebieg();

    QString cecha;

    if (typ == "Motocykl") {
        auto m = std::dynamic_pointer_cast<Motocykl>(pojazd);
        cecha = QString::number(m ? m->getMoc() : 0) + " KM";
    } else if (typ == "Osobowy") {
        auto o = std::dynamic_pointer_cast<Osobowy>(pojazd);
        cecha = QString::number(o ? o->getliczbaMiejsc() : 0) + " miejsc";
    } else if (typ == "Ciezarowy") {
        auto c = std::dynamic_pointer_cast<Ciezarowy>(pojazd);
        cecha = QString::number(c ? c->getLadownosc() : 0.0) + " kg";
    } else {
        cecha = "brak";
    }

    QString imie = klient->getName();
    QString nazwisko = klient->getSurname();
    QString id = klient->getId();
    QString data = QDate::currentDate().toString("yyyy-MM-dd");

    Sprzedaz s(vin, typ, marka, model, rok, przebieg, cecha, imie, nazwisko, id, cena, data);
    sprzedane.push_back(s);

    pojazdy.erase(std::remove(pojazdy.begin(), pojazdy.end(), pojazd), pojazdy.end());

}

const std::vector<Sprzedaz>& Salon::getSprzedaze() const {
    return sprzedane;
}
void Salon::zapiszSprzedazDoPliku(const std::string& sciezkaPliku) const {
    std::filesystem::path path = sciezkaPliku;

    QFile file(QString::fromStdString(path.string()));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Nie można otworzyć pliku do zapisu:" << QString::fromStdString(path.string());
        return;
    }

    QTextStream out(&file);
    for (const auto& s : sprzedane) {
        s.zapisz(out);
    }


}
void Salon::wczytajSprzedazZPliku(const std::string& sciezkaPliku) {
    sprzedane.clear();
    QFile file(QString::fromStdString(sciezkaPliku));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Nie można otworzyć pliku sprzedaży do odczytu.";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        QStringList dane = line.split(';');
        Sprzedaz s;
        if (s.wczytaj(dane)) {
            sprzedane.push_back(s);
        } else {
            qWarning() << "Błąd w linii sprzedaży:" << line;
        }
    }
}
void Salon::dodajSerwis(const Serwis& s) {
    serwisy.push_back(s);
}

bool Salon::zakonczSerwisPoVIN(const QString& vin) {
    for (auto& s : serwisy) {
        if (s.getVIN() == vin && !s.czyZakonczone()) {
            s.oznaczJakoZakonczone();
            return true;
        }
    }
    return false;
}

const std::vector<Serwis>& Salon::getSerwisy() const {
    return serwisy;
}

void Salon::zapiszSerwisyDoPliku(const std::string& sciezka) const {
    QFile file(QString::fromStdString(sciezka));
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qWarning() << "Nie można zapisać serwisów do pliku:" << QString::fromStdString(sciezka);
        return;
    }

    QTextStream out(&file);
    for (const auto& s : serwisy) {
        out << s.zapisz() << "\n";
    }
}

void Salon::wczytajSerwisyZPliku(const std::string& sciezka) {
    std::filesystem::path path = sciezka;

    if (!std::filesystem::exists(path)) {
        qWarning() << "Plik serwisów nie istnieje:" << QString::fromStdString(path.string());
        return;
    }

    QFile file(QString::fromStdString(path.string()));
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qWarning() << "Nie można otworzyć pliku serwisów do odczytu:" << QString::fromStdString(path.string());
        return;
    }

    QTextStream in(&file);
    serwisy.clear();

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty()) continue;

        QStringList pola = line.split(';');
        Serwis s;
        if (s.wczytaj(pola)) {
            serwisy.push_back(s);
        } else {
            qWarning() << "Nieprawidłowe zgłoszenie serwisowe:" << line;
        }
    }
}
bool Salon::usunSprzedazPoVIN(const QString& vin){
    auto it = std::remove_if(sprzedane.begin(),sprzedane.end(),[&](const Sprzedaz& s){return s.getVIN()== vin;});
        if (it != sprzedane.end()){
        sprzedane.erase(it,sprzedane.end());
        return true;
    }
    return false;
}
bool Salon::usunSerwisPoIndeksie(int indeks) {
    if (indeks >= 0 && indeks < static_cast<int>(serwisy.size())) {
        serwisy.erase(serwisy.begin() + indeks);
        return true;
    }
    return false;
}
