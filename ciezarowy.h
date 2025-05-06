#ifndef CIEZAROWY_H
#define CIEZAROWY_H

#include "pojazd.h"

class Ciezarowy : public Pojazd {
    double ladownosc;

public:
    Ciezarowy(const QString& marka, const QString& model, double cena, double ladownosc);

    double getLadownosc() const;
    QString getTyp() const override;
    QString opis() const override;
};

#endif // CIEZAROWY_H
