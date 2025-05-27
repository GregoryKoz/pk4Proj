#ifndef OSOBOWY_H
#define OSOBOWY_H

#include "pojazd.h"

class Osobowy : public Pojazd {
    int liczbaMiejsc;

public:
    Osobowy(const QString& marka, const QString& model, double cena, int rok, int przebieg, int liczbaMiejsc);
    Osobowy();
    int getliczbaMiejsc() const;
    QString getTyp() const override;
    void wypisz(QTextStream &dane) override;
    void wczytaj(const QStringList& dane) override;
    QString getOpis() const override;

};

#endif // OSOBOWY_H
