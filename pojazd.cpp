#include "pojazd.h"

Pojazd::Pojazd(const QString& vin,const QString& marka, const QString& model, double cena, int rok, int przebieg)
    : vin(vin),marka(marka), model(model), cena(cena), rok(rok), przebieg(przebieg) {}

Pojazd::Pojazd() : vin(""),marka(""), model(""), cena(0), rok(0), przebieg(0){}

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
    return QString("VIN: %1 %2 %3, Cena: %4 zl, Rok: %5, Przebieg: %6 km")
        .arg(vin)
        .arg(marka)
        .arg(model)
        .arg(cena)
        .arg(rok)
        .arg(przebieg);
}
QString Pojazd::getVIN() const{
    return vin;
}
void Pojazd::setVIN(const QString& v){
    vin =v;
}


