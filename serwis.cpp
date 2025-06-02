#include "serwis.h"

Serwis::Serwis(const QString& idKlienta,
               const QString& vinPojazdu,
               const QString& opisUsterki,
               const QDate& dataUmowiona)
    : idKlienta(idKlienta),
    vinPojazdu(vinPojazdu),
    opisUsterki(opisUsterki),
    dataZgloszenia(QDate::currentDate()),
    dataUmowiona(dataUmowiona),
    zakonczone(false) {}

QString Serwis::getIdKlienta() const { return idKlienta; }
QString Serwis::getVIN() const { return vinPojazdu; }
QString Serwis::getOpis() const { return opisUsterki; }
QDate Serwis::getDataZgloszenia() const { return dataZgloszenia; }
QDate Serwis::getDataUmowiona() const { return dataUmowiona; }
bool Serwis::czyZakonczone() const { return zakonczone; }

void Serwis::oznaczJakoZakonczone() { zakonczone = true; }

QString Serwis::zapisz() const {
    return QString("%1;%2;%3;%4;%5;%6")
    .arg(idKlienta)
        .arg(vinPojazdu)
        .arg(opisUsterki)
        .arg(dataZgloszenia.toString("yyyy-MM-dd"))
        .arg(dataUmowiona.toString("yyyy-MM-dd"))
        .arg(zakonczone ? "1" : "0");
}

bool Serwis::wczytaj(const QStringList& pola) {
    if (pola.size() != 6) return false;

    idKlienta = pola[0];
    vinPojazdu = pola[1];
    opisUsterki = pola[2];
    dataZgloszenia = QDate::fromString(pola[3], "yyyy-MM-dd");
    dataUmowiona = QDate::fromString(pola[4], "yyyy-MM-dd");
    zakonczone = (pola[5] == "1");

    return true;
}
