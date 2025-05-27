#include "osobowy.h"

Osobowy::Osobowy(const QString& marka, const QString& model, double cena, int rok, int przebieg, int liczbaMiejsc)
    : Pojazd(marka, model, cena, rok, przebieg), liczbaMiejsc(liczbaMiejsc) {}

Osobowy::Osobowy() : Pojazd() {}

int Osobowy::getliczbaMiejsc() const {
    return liczbaMiejsc;
}

QString Osobowy::getTyp() const {
    return "Osobowy";
}

void Osobowy::wczytaj(const QStringList& dane) {
    if (dane.size() >= 6) {
        marka = dane[0];
        model = dane[1];
        cena = dane[2].toDouble();
        rok = dane[3].toInt();
        przebieg = dane[4].toInt();
        liczbaMiejsc = dane[5].toInt();
    }
}
void Osobowy::wypisz(QTextStream& dane){
    dane << marka << model << cena << rok << przebieg << liczbaMiejsc;
}
QString Osobowy::getOpis() const{
    return Pojazd::opisbazowy() + QString(", Ilość miejsc: %1").arg(liczbaMiejsc);
}
