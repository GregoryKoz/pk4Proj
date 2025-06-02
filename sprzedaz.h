#pragma once

#include <QString>
#include <QStringList>
#include <QTextStream>

class Sprzedaz {
private:
    QString vin;
    QString typPojazdu;

    // Dane pojazdu
    QString marka;
    QString model;
    int rokProdukcji;
    int przebieg;
    QString cechaSpecyficzna;

    // Dane klienta
    QString imieKlienta;
    QString nazwiskoKlienta;
    QString idKlienta;

    double cenaSprzedazy;
    QString data;

public:
    Sprzedaz() = default;

    Sprzedaz(const QString& vin, const QString& typPojazdu,
             const QString& marka, const QString& model,
             int rokProdukcji, int przebieg, const QString& cechaSpecyficzna,
             const QString& imieKlienta, const QString& nazwiskoKlienta,
             const QString& idKlienta, double cenaSprzedazy, const QString& data);
    void zapisz(QTextStream& out) const;
    bool wczytaj(const QStringList& dane);

    // Gettery
    QString getVIN() const;
    QString getTypPojazdu() const;
    QString getMarka() const;
    QString getModel() const;
    int getRokProdukcji() const;
    int getPrzebieg() const;
    double getPojemnoscSilnika() const;
    QString getImieKlienta() const;
    QString getNazwiskoKlienta() const;
    QString getIdKlienta() const;
    double getCenaSprzedazy() const;
    QString getData() const;
    QString getCechaSpecyficzna() const;
};
