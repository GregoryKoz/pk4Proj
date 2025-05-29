#include "ciezarowy.h"

Ciezarowy::Ciezarowy(const QString& vin, const QString& marka, const QString& model, double cena, int rok, int przebieg, double ladownosc)
    : Pojazd(vin, marka, model, cena, rok, przebieg), ladownosc(ladownosc) {}

Ciezarowy::Ciezarowy() : Pojazd() {}
double Ciezarowy::getLadownosc() const {
    return ladownosc;
}

QString Ciezarowy::getTyp() const {
    return "Ciezarowy";
}

void Ciezarowy::wczytaj(const QStringList& dane) {
    if (dane.size() >= 7) {
        vin = dane[0];
        marka = dane[1];
        model = dane[2];
        cena = dane[3].toDouble();
        rok = dane[4].toInt();
        przebieg = dane[5].toInt();
        ladownosc = dane[6].toInt();
    }
}
void Ciezarowy::wypisz(QTextStream& dane){
    dane << marka << model << cena << rok << przebieg << ladownosc;
}
QString Ciezarowy::getOpis() const{
    return Pojazd::opisbazowy() + QString(", Ladowność: %1 kg").arg(ladownosc);
}
QString Ciezarowy::zapisz() const {
    return QString("Ciezarowy;%1;%2;%3;%4;%5;%6;%7")
    .arg(vin).arg(marka).arg(model).arg(cena)
        .arg(rok).arg(przebieg).arg(ladownosc);
}
