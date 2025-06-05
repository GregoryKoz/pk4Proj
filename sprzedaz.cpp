#include "Sprzedaz.h"

Sprzedaz::Sprzedaz(const QString& vin, const QString& typPojazdu,
                   const QString& marka, const QString& model,
                   int rokProdukcji, int przebieg, const QString& cechaSpecyficzna,
                   const QString& imieKlienta, const QString& nazwiskoKlienta,
                   const QString& idKlienta, double cenaSprzedazy, const QString& data)
    : vin(vin), typPojazdu(typPojazdu), marka(marka), model(model),
    rokProdukcji(rokProdukcji), przebieg(przebieg), cechaSpecyficzna(cechaSpecyficzna),
    imieKlienta(imieKlienta), nazwiskoKlienta(nazwiskoKlienta), idKlienta(idKlienta),
    cenaSprzedazy(cenaSprzedazy), data(data) {}
void Sprzedaz::zapisz(QTextStream& out) const {
    out.setRealNumberNotation(QTextStream::FixedNotation);
    out.setRealNumberPrecision(2);

    out << vin << ";" << typPojazdu << ";" << marka << ";" << model << ";"
        << rokProdukcji << ";" << przebieg << ";" << cechaSpecyficzna << ";"
        << imieKlienta << ";" << nazwiskoKlienta << ";" << idKlienta << ";"
        << QString::number(cenaSprzedazy, 'f', 2) << ";" << data << "\n";
}

bool Sprzedaz::wczytaj(const QStringList& dane) {
    if (dane.size() != 12)
        return false;

    vin = dane[0];
    typPojazdu = dane[1];
    marka = dane[2];
    model = dane[3];
    rokProdukcji = dane[4].toInt();
    przebieg = dane[5].toInt();
    cechaSpecyficzna = dane[6];
    imieKlienta = dane[7];
    nazwiskoKlienta = dane[8];
    idKlienta = dane[9];
    cenaSprzedazy = dane[10].toDouble();
    data = dane[11];
    return true;
}

// Gettery
QString Sprzedaz::getVIN() const { return vin; }
QString Sprzedaz::getTypPojazdu() const { return typPojazdu; }
QString Sprzedaz::getMarka() const { return marka; }
QString Sprzedaz::getModel() const { return model; }
int Sprzedaz::getRokProdukcji() const { return rokProdukcji; }
int Sprzedaz::getPrzebieg() const { return przebieg; }
QString Sprzedaz::getImieKlienta() const { return imieKlienta; }
QString Sprzedaz::getNazwiskoKlienta() const { return nazwiskoKlienta; }
QString Sprzedaz::getIdKlienta() const { return idKlienta; }
double Sprzedaz::getCenaSprzedazy() const { return cenaSprzedazy; }
QString Sprzedaz::getData() const { return data; }
QString Sprzedaz::getCechaSpecyficzna() const {
    return cechaSpecyficzna;
}
