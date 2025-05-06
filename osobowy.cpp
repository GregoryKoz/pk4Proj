#include "osobowy.h"

Osobowy::Osobowy(const QString& marka, const QString& model, double cena, int iloscPasazerow)
    : Pojazd(marka, model, cena), iloscPasazerow(iloscPasazerow) {}

int Osobowy::getIloscPasazerow() const {
    return iloscPasazerow;
}

QString Osobowy::getTyp() const {
    return "Osobowy";
}

QString Osobowy::opis() const {
    return QString("%1 %2 | Typ: %3 | Pasazerowie: %4 | Cena: %5 zl")
    .arg(marka, model, getTyp())
        .arg(iloscPasazerow)
        .arg(cena);
}
