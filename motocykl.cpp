#include "motocykl.h"

Motocykl::Motocykl(const QString& marka, const QString& model, double cena, int rok, int przebieg, int moc)
    : Pojazd(marka, model, cena, rok, przebieg), moc(moc) {}

Motocykl::Motocykl(): Pojazd() {}
int Motocykl::getMoc() const {
    return moc;
}

QString Motocykl::getTyp() const {
    return "Motocykl";
}

void Motocykl::wczytaj(const QStringList& dane) {
    if (dane.size() >= 6) {
        marka = dane[0];
        model = dane[1];
        cena = dane[2].toDouble();
        rok = dane[3].toInt();
        przebieg = dane[4].toInt();
        moc = dane[5].toInt();
    }
}
void Motocykl::wypisz(QTextStream& dane){
    dane << marka << model << cena << rok << przebieg << moc;
}
QString Motocykl::getOpis() const{
    return Pojazd::opisbazowy() + QString(", Moc: %1 KM").arg(moc);
}
