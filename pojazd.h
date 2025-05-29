#ifndef POJAZD_H
#define POJAZD_H

#include <QString>
#include <QTextStream>
#include <QStringList>

class Pojazd {
protected:
    QString marka;
    QString model;
    double cena;
    int rok;
    int przebieg;
    QString vin;

public:
    Pojazd();
    Pojazd(const QString& vin,const QString& marka, const QString& model, double cena, int rok, int przebieg);
    virtual ~Pojazd() = default;

    QString getMarka() const;
    QString getModel() const;
    double getCena() const;
    int getRok() const;
    int getPrzebieg() const;
    virtual QString getTyp() const = 0;
    virtual void wypisz(QTextStream& dane) = 0;
    virtual void wczytaj(const QStringList& dane) = 0;
    QString opisbazowy() const;
    virtual QString getOpis() const = 0;
    QString getVIN() const;
    virtual QString zapisz() const = 0;
    void setVIN(const QString& v);

};

#endif // POJAZD_H
