#include "ciezarowy.h"

Ciezarowy::Ciezarowy(const QString& marka, const QString& model, double cena, double ladownosc)
    : Pojazd(marka, model, cena), ladownosc(ladownosc) {}

double Ciezarowy::getLadownosc() const {
    return ladownosc;
}

QString Ciezarowy::getTyp() const {
    return "Ciezarowy";
}

QString Ciezarowy::opis() const {
    return QString("%1 %2 | Typ: %3 | Ladownosc: %4 kg | Cena: %5 zl")
    .arg(marka, model, getTyp())
        .arg(ladownosc)
        .arg(cena);
}
