#pragma once
#include "klient.h"
#include "Pojazd.h"
#include <QString>
#include <QDateTime>
#include <memory>


class Sprzedaz {
    std::shared_ptr<Client> klient;
    std::shared_ptr<Pojazd> pojazd;
    QDateTime dataSprzedazy;
    double cenaFinalna;

public:
    Sprzedaz(std::shared_ptr<Client> k, std::shared_ptr<Pojazd> p, double cena);

    QString getOpis() const;
    std::shared_ptr<Client> getKlient() const;
    std::shared_ptr<Pojazd> getPojazd() const;
    QDateTime getData() const;
    double getCena() const;
};
