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

class Salon : public QObject
{
    Q_OBJECT
public:
    explicit Salon(QObject *parent = nullptr);

    void dodajKlienta(const Client& klient);
    std::vector<Client>& getKlienci();
    void zapiszKlientow(const std::string& sciezkaPliku) const;
    void wczytajKlientow(const std::string& sciezkaPliku);
    bool usunKlientaPoId(int id);
private:
    std::vector<Client> klienci;
signals:
    void klienciWczytani();
};

#endif // SALON_H

