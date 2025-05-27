#include "pojazd.h"

Pojazd::Pojazd(const QString& marka, const QString& model, double cena, int rok, int przebieg)
    : marka(marka), model(model), cena(cena), rok(rok), przebieg(przebieg) {}

Pojazd::Pojazd() : marka(""), model(""), cena(0), rok(0), przebieg(0){}

QString Pojazd::getMarka() const {
    return marka;
}

QString Pojazd::getModel() const {
    return model;
}

double Pojazd::getCena() const {
    return cena;
}
int Pojazd::getRok() const{
    return rok;
}
int Pojazd::getPrzebieg() const{
    return przebieg;
}

QString Pojazd::opisbazowy() const{
    return QString("%1 %2, Cena: %3 zl, Rok: %4, Przebieg: %5 km")
        .arg(marka)
        .arg(model)
        .arg(cena)
        .arg(rok)
        .arg(przebieg);
}

