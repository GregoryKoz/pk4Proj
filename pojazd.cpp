#include "pojazd.h"

Pojazd::Pojazd(const QString& marka, const QString& model, double cena)
    : marka(marka), model(model), cena(cena) {}

Pojazd::~Pojazd() {}

QString Pojazd::getMarka() const {
    return marka;
}

QString Pojazd::getModel() const {
    return model;
}

double Pojazd::getCena() const {
    return cena;
}
