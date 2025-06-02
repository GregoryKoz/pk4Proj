#pragma once

#include <QString>
#include <QDate>

class Serwis {
    QString idKlienta;
    QString vinPojazdu;
    QString opisUsterki;
    QDate dataZgloszenia;
    QDate dataUmowiona;
    bool zakonczone;

public:
    Serwis() = default;

    Serwis(const QString& idKlienta,
           const QString& vinPojazdu,
           const QString& opisUsterki,
           const QDate& dataUmowiona);

    QString getIdKlienta() const;
    QString getVIN() const;
    QString getOpis() const;
    QDate getDataZgloszenia() const;
    QDate getDataUmowiona() const;
    bool czyZakonczone() const;

    void oznaczJakoZakonczone();

    QString zapisz() const;
    bool wczytaj(const QStringList& pola);
};
