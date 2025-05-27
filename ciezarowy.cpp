#include "ciezarowy.h"

Ciezarowy::Ciezarowy(const QString& marka, const QString& model, double cena, int rok, int przebieg, double ladownosc)
    : Pojazd(marka, model, cena, rok, przebieg), ladownosc(ladownosc) {}

Ciezarowy::Ciezarowy() : Pojazd() {}
double Ciezarowy::getLadownosc() const {
    return ladownosc;
}

QString Ciezarowy::getTyp() const {
    return "Ciezarowy";
}

void Ciezarowy::wczytaj(const QStringList& dane) {
    if (dane.size() >= 6) {
        marka = dane[0];
        model = dane[1];
        cena = dane[2].toDouble();
        rok = dane[3].toInt();
        przebieg = dane[4].toInt();
        ladownosc = dane[5].toDouble();
    }
}
void Ciezarowy::wypisz(QTextStream& dane){
    dane << marka << model << cena << rok << przebieg << ladownosc;
}
QString Ciezarowy::getOpis() const{
    return Pojazd::opisbazowy() + QString(", Ladowność: %1 kg").arg(ladownosc);
}

