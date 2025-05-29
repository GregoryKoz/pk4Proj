#ifndef MOTOCYKL_H
#define MOTOCYKL_H

#include "pojazd.h"

class Motocykl : public Pojazd {
    int moc;

public:
    Motocykl(const QString& vin, const QString& marka, const QString& model, double cena, int rok, int przebieg, int moc);
    Motocykl();
    int getMoc() const;
    QString getTyp() const override;
    void wypisz(QTextStream &dane) override;
    void wczytaj(const QStringList& dane) override;
    QString getOpis() const override;
    QString zapisz() const override;
};

#endif // MOTOCYKL_H
