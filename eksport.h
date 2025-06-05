#pragma once
#include <vector>
#include <QString>
#include <QStringList>
#include <QFile>
#include "sprzedaz.h"
#include "serwis.h"
class Eksport {
public:
    static void podsumujSprzedaz(const std::vector<Sprzedaz>& sprzedane);
    static void pojazdyKlienta(const std::vector<Sprzedaz>& sprzedane, const QString& id, const QString& imie, const QString& nazwisko);
    static void serwisyKlienta(const std::vector<Serwis>& serwisy, const QString& id, const QString& imie, const QString& nazwisko);
    static void serwisyPojazdu(const std::vector<Serwis>& serwisy, const QString& vin);

private:
    static const std::string sciezkaFolderu;
    static bool otworzPlikDoZapisu(QFile& file, const std::string& katalog, const std::string& nazwaPliku);
};
