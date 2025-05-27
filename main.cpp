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
    MainWindow w(salon);
    w.show();

    int result = a.exec();

    salon->zapiszKlientow("C:/Users/Janusz/Desktop/PK4- Laby/pliki do projektu/klienci.txt");
    delete salon;

    return result;
}
