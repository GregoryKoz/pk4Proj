#ifndef OSOBOWY_H
#define OSOBOWY_H

#include "pojazd.h"

class Osobowy : public Pojazd {
    int iloscPasazerow;

public:
    Osobowy(const QString& marka, const QString& model, double cena, int iloscPasazerow);

    int getIloscPasazerow() const;
    QString getTyp() const override;
    QString opis() const override;
};

#endif // OSOBOWY_H
