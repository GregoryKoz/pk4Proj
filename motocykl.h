#ifndef MOTOCYKL_H
#define MOTOCYKL_H

#include "pojazd.h"

class Motocykl : public Pojazd {
    int moc;

public:
    Motocykl(const QString& marka, const QString& model, double cena, int moc);

    int getMoc() const;
    QString getTyp() const override;
    QString opis() const override;
};

#endif // MOTOCYKL_H
