#include "motocykl.h"

Motocykl::Motocykl(const QString& vin, const QString& marka, const QString& model, double cena, int rok, int przebieg, int moc)
    : Pojazd(vin, marka, model, cena, rok, przebieg), moc(moc) {}

Motocykl::Motocykl(): Pojazd() {}
int Motocykl::getMoc() const {
    return moc;
}

QString Motocykl::getTyp() const {
    return "Motocykl";
}

void Motocykl::wczytaj(const QStringList& dane) {
    if (dane.size() >= 7) {
        vin = dane[0];
        marka = dane[1];
        model = dane[2];
        cena = dane[3].toDouble();
        rok = dane[4].toInt();
        przebieg = dane[5].toInt();
        moc = dane[6].toInt();
    }
}
void Motocykl::wypisz(QTextStream& dane){
    dane << marka << model << cena << rok << przebieg << moc;
}
QString Motocykl::getOpis() const{
    return Pojazd::opisbazowy() + QString(", Moc: %1 KM").arg(moc);
}
QString Motocykl::zapisz() const {
    return QString("Motocykl;%1;%2;%3;%4;%5;%6;%7")
    .arg(vin).arg(marka).arg(model).arg(cena)
        .arg(rok).arg(przebieg).arg(moc);
}
