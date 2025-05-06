#ifndef POJAZD_H
#define POJAZD_H

#include <QString>

class Pojazd {
protected:
    QString marka;
    QString model;
    double cena;

public:
    Pojazd(const QString& marka, const QString& model, double cena);
    virtual ~Pojazd();

    QString getMarka() const;
    QString getModel() const;
    double getCena() const;

    virtual QString getTyp() const = 0;
    virtual QString opis() const = 0;
};

#endif // POJAZD_H
