#include "Eksport.h"
#include <filesystem>
#include <QTextStream>
#include <QDebug>

namespace fs = std::filesystem;

const std::string Eksport::sciezkaFolderu = "C:/Users/Janusz/Desktop/PK4- Laby/pliki do projektu/Eksporty";

bool Eksport::otworzPlikDoZapisu(QFile& file, const std::string& katalog, const std::string& nazwaPliku) {
    fs::create_directories(katalog);
    fs::path pelnaSciezka = fs::path(katalog) / nazwaPliku;
    file.setFileName(QString::fromStdString(pelnaSciezka.string()));
    return file.open(QIODevice::WriteOnly | QIODevice::Text);
}

void Eksport::podsumujSprzedaz(const std::vector<Sprzedaz>& sprzedane) {
    QFile file;
    if (!otworzPlikDoZapisu(file, sciezkaFolderu, "podsumowaniesprzedazy.txt")) {
        qWarning() << "Nie mozna otworzyc pliku do zapisu";
        return;
    }

    QTextStream out(&file);
    out.setRealNumberNotation(QTextStream::FixedNotation);
    out.setRealNumberPrecision(2);

    double suma = 0;
    for (const auto& s : sprzedane)
        suma += s.getCenaSprzedazy();

    out << "Podsumowanie sprzedazy:\n";
    out << "Liczba transakcji: " << sprzedane.size() << "\n";
    out << "Laczna kwota: " << suma << " zl\n";
}

void Eksport::pojazdyKlienta(const std::vector<Sprzedaz>& sprzedane, const QString& id, const QString& imie, const QString& nazwisko) {
    QFile file;
    std::string nazwa = "POJAZDY_" + imie.toStdString() + "_" + nazwisko.toStdString() + ".txt";
    if (!otworzPlikDoZapisu(file, sciezkaFolderu, nazwa)) return;

    QTextStream out(&file);
    out.setRealNumberNotation(QTextStream::FixedNotation);
    out.setRealNumberPrecision(2);

    for (const auto& s : sprzedane) {
        if (s.getIdKlienta() == id) {
            out << s.getVIN() << ";" << s.getMarka() << ";" << s.getModel() << ";" << s.getCenaSprzedazy() << ";" << s.getData() << "\n";
        }
    }
}

void Eksport::serwisyKlienta(const std::vector<Serwis>& serwisy, const QString& id, const QString& imie, const QString& nazwisko) {
    QFile file;
    std::string nazwa = "SERWISY_" + imie.toStdString() + "_" + nazwisko.toStdString() + ".txt";
    if (!otworzPlikDoZapisu(file, sciezkaFolderu, nazwa)) return;

    QTextStream out(&file);
    for (const auto& s : serwisy) {
        if (s.getIdKlienta() == id) {
            out << s.getVIN() << ";" << s.getOpis() << ";" << s.getDataUmowiona().toString("yyyy-MM-dd") << ";" << (s.czyZakonczone() ? "Zakonczony" : "W toku") << "\n";
        }
    }
}

void Eksport::serwisyPojazdu(const std::vector<Serwis>& serwisy, const QString& vin) {
    QFile file;
    std::string nazwa = "SERWISY_" + vin.toStdString() + ".txt";
    if (!otworzPlikDoZapisu(file, sciezkaFolderu, nazwa)) return;

    QTextStream out(&file);
    for (const auto& s : serwisy) {
        if (s.getVIN() == vin) {
            out << s.getIdKlienta() << ";" << s.getOpis() << ";" << s.getDataUmowiona().toString("yyyy-MM-dd") << ";" << (s.czyZakonczone() ? "Zakonczony" : "W toku") << "\n";
        }
    }
}
