#ifndef CIEZAROWY_H
#define CIEZAROWY_H

#include "pojazd.h"

class Ciezarowy : public Pojazd {
    double ladownosc;

public:
    Ciezarowy(const QString& marka, const QString& model, double cena, int rok, int przebieg, double ladownosc);
    Ciezarowy();
    double getLadownosc() const;
    QString getTyp() const override;
    void wypisz(QTextStream &dane) override;
    void wczytaj(const QStringList& dane) override;
    QString getOpis() const override;
};

#endif // CIEZAROWY_H
