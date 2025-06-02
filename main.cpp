#include "mainwindow.h"
#include "klient.h"
#include <QApplication>
#include "Salon.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Salon* salon = new Salon();

    salon->wczytajKlientow("C:/Users/Janusz/Desktop/PK4- Laby/pliki do projektu/klienci.txt");
    salon->wczytajPojazdy("C:/Users/Janusz/Desktop/PK4- Laby/pliki do projektu/pojazdy.txt");
    salon->wczytajSprzedazZPliku("C:/Users/Janusz/Desktop/PK4- Laby/pliki do projektu/sprzedaz.txt");
    salon->wczytajSerwisyZPliku("C:/Users/Janusz/Desktop/PK4- Laby/pliki do projektu/serwisy.txt");
    MainWindow w(salon);
    w.show();

    int result = a.exec();

    salon->zapiszKlientow("C:/Users/Janusz/Desktop/PK4- Laby/pliki do projektu/klienci.txt");
    salon->zapiszPojazdyDoPliku("C:/Users/Janusz/Desktop/PK4- Laby/pliki do projektu/pojazdy.txt");
    salon->zapiszSprzedazDoPliku("C:/Users/Janusz/Desktop/PK4- Laby/pliki do projektu/sprzedaz.txt");
    salon->zapiszSerwisyDoPliku("C:/Users/Janusz/Desktop/PK4- Laby/pliki do projektu/serwisy.txt");
    delete salon;

    return result;
}
