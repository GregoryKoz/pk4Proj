#ifndef SALON_H
#define SALON_H

#include "klient.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <QString>
#include <vector>
#include <QObject>
#include <ranges>
#include <regex>
#include <algorithm>
#include "Pojazd.h"
#include "osobowy.h"
#include "ciezarowy.h"
#include "motocykl.h"
#include <QTextStream>


class Salon : public QObject
{
    Q_OBJECT
public:
    explicit Salon(QObject *parent = nullptr);
    //klienci
    void dodajKlienta(const Client& klient);
    std::vector<Client>& getKlienci();
    void zapiszKlientow(const std::string& sciezkaPliku) const;
    void wczytajKlientow(const std::string& sciezkaPliku);
    bool usunKlientaPoId(int id);
    //pojazdy
    void wczytajPojazdy(const std::string& sciezkaPliku);
    std::vector<std::shared_ptr<Pojazd>>& getPojazdy();
private:
    std::vector<Client> klienci;
    std::vector<std::shared_ptr<Pojazd>> pojazdy;

signals:
    void klienciWczytani();
};

#endif // SALON_H

