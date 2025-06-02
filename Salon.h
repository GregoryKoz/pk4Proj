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
#include <QUuid>
#include "sprzedaz.h"
#include "serwis.h"  // upewnij się, że masz #include na górze pliku

class Salon : public QObject
{
    Q_OBJECT
public:
    explicit Salon(QObject *parent = nullptr);
    //klienci
    void dodajKlienta(const std::shared_ptr<Client>& klient);
    std::vector<std::shared_ptr<Client>>& getKlienci();
    void zapiszKlientow(const std::string& sciezkaPliku) const;
    void wczytajKlientow(const std::string& sciezkaPliku);
    bool usunKlientaPoId(int id);
    //pojazdy
    void wczytajPojazdy(const std::string& sciezkaPliku);
    std::vector<std::shared_ptr<Pojazd>>& getPojazdy();
    void zapiszPojazdyDoPliku(const std::string& sciezkaPliku);
    void dodajPojazd(const std::shared_ptr<Pojazd>& pojazd);
    bool vinIstnieje(const QString& vin) const;
    QString wygenerujUnikalnyVIN();
    bool usunPojazdPoVIN(const QString& vin);
    std::shared_ptr<Pojazd> znajdzPojazdPoVIN(const QString& vin);
    void zamienPojazd(const QString& vin, std::shared_ptr<Pojazd> nowy);
    //sprzedaz
    void sprzedajPojazd(std::shared_ptr<Pojazd> pojazd, std::shared_ptr<Client> klient, double cena);
    const std::vector<Sprzedaz>& getSprzedaze() const;
    void zapiszSprzedazDoPliku(const std::string& sciezkaPliku) const;
    void wczytajSprzedazZPliku(const std::string& sciezkaPliku);
    //serwis
    void dodajSerwis(const Serwis& s);
    bool zakonczSerwisPoVIN(const QString& vin);
    void zapiszSerwisyDoPliku(const std::string& sciezka) const;
    void wczytajSerwisyZPliku(const std::string& sciezka);
    const std::vector<Serwis>& getSerwisy() const;
private:
    std::vector<std::shared_ptr<Client>> klienci;
    std::vector<std::shared_ptr<Pojazd>> pojazdy;
    std::vector<Sprzedaz> sprzedane;
    std::vector<Serwis> serwisy;

signals:
    void klienciWczytani();
};

#endif // SALON_H

