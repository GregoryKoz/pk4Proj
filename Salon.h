#ifndef SALON_H
#define SALON_H

#include "klient.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <QString>
#include <vector>

class Salon{
public:
    void dodajKlienta(const Client& klient);
    const std::vector<Client>& getKlienci() const;
    void zapiszKlientow(const std::string& sciezkaPliku) const;
    void wczytajKlientow(const std::string& sciezkaPliku);
private:
    std::vector<Client> klienci;

};

#endif // SALON_H

