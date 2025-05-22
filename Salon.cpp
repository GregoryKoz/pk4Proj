#include "Salon.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <filesystem>


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
        out << c.getName() << ";" << c.getSurname() << ";" << c.getId() << "\n";
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
        if (parts.size() == 3) {
            klienci.emplace_back(parts[0], parts[1], parts[2]);
        }
    }
    qDebug() << "Liczba klientów:" << klienci.size();
    emit klienciWczytani();
    qDebug() << "Sygnal:";
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
