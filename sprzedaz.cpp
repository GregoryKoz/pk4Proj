#include "sprzedaz.h"

Sprzedaz::Sprzedaz(std::shared_ptr<Client> k, std::shared_ptr<Pojazd> p, double cena)
    : klient(k), pojazd(p), cenaFinalna(cena), dataSprzedazy(QDateTime::currentDateTime()) {}

QString Sprzedaz::getOpis() const {
    return QString("Sprzedano %1 %2 klientowi %3 %4 za %5 zł, dnia %6")
        .arg(pojazd->getMarka())
        .arg(pojazd->getModel())
        .arg(klient->getName())
        .arg(klient->getSurname())
        .arg(cenaFinalna)
        .arg(dataSprzedazy.toString("yyyy-MM-dd HH:mm"));
}

std::shared_ptr<Client> Sprzedaz::getKlient() const { return klient; }
std::shared_ptr<Pojazd> Sprzedaz::getPojazd() const { return pojazd; }
QDateTime Sprzedaz::getData() const { return dataSprzedazy; }
double Sprzedaz::getCena() const { return cenaFinalna; }
