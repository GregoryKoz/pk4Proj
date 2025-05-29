#ifndef DODAJPOJAZDDIALOG_H
#define DODAJPOJAZDDIALOG_H

#include <QDialog>
#include <memory>
#include "Pojazd.h"

class DodajPojazdDialog : public QDialog {
    Q_OBJECT
public:
    explicit DodajPojazdDialog(QWidget* parent = nullptr) : QDialog(parent) {}
    virtual ~DodajPojazdDialog() = default;

    virtual std::shared_ptr<Pojazd> getPojazd() const = 0;
};

#endif // DODAJPOJAZDDIALOG_H
