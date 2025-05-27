#include "Salon.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <filesystem>
#include "osobowy.h"
#include "ciezarowy.h"
#include "motocykl.h"

Salon::Salon(QObject *parent)
    : QObject(parent){}

void Salon::dodajKlienta(const Client &klient){
    klienci.push_back(klient);
    emit klienciWczytani();
}

std::vector<Client>& Salon::getKlienci() {
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
    for (const Client& c : klienci) {
        out << c.getName() << ";" << c.getSurname() << ";" << c.getId() << ";" << c.getEmail() << ";" << c.getTel() <<"\n";
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
            klienci.emplace_back(parts[0], parts[1], parts[2], parts[3], parts[4]);
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
                           [id](const Client& c) {
                               return c.getId() == QString::number(id);
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
