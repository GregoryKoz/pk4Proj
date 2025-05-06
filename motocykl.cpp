#include "motocykl.h"

Motocykl::Motocykl(const QString& marka, const QString& model, double cena, int moc)
    : Pojazd(marka, model, cena), moc(moc) {}

int Motocykl::getMoc() const {
    return moc;
}

QString Motocykl::getTyp() const {
    return "Motocykl";
}

QString Motocykl::opis() const {
    return QString("%1 %2 | Typ: %3 | Moc: %4 KM | Cena: %5 zl")
    .arg(marka, model, getTyp())
        .arg(moc)
        .arg(cena);
}
