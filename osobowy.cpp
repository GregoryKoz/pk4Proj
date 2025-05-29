#include "osobowy.h"

Osobowy::Osobowy(const QString& vin,const QString& marka, const QString& model, double cena, int rok, int przebieg, int liczbaMiejsc)
    : Pojazd(vin, marka, model, cena, rok, przebieg), liczbaMiejsc(liczbaMiejsc) {}

Osobowy::Osobowy() : Pojazd() {}

int Osobowy::getliczbaMiejsc() const {
    return liczbaMiejsc;
}

QString Osobowy::getTyp() const {
    return "Osobowy";
}

void Osobowy::wczytaj(const QStringList& dane) {
    if (dane.size() >= 7) {
        vin = dane[0];
        marka = dane[1];
        model = dane[2];
        cena = dane[3].toDouble();
        rok = dane[4].toInt();
        przebieg = dane[5].toInt();
        liczbaMiejsc = dane[6].toInt();
    }
}
void Osobowy::wypisz(QTextStream& dane){
    dane << marka << model << cena << rok << przebieg << liczbaMiejsc;
}
QString Osobowy::getOpis() const{
    return Pojazd::opisbazowy() + QString(", Ilość miejsc: %1").arg(liczbaMiejsc);
}
QString Osobowy::zapisz() const {
    return QString("Osobowy;%1;%2;%3;%4;%5;%6;%7")
    .arg(vin).arg(marka).arg(model).arg(cena)
        .arg(rok).arg(przebieg).arg(liczbaMiejsc);
}
