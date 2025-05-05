#include "mainwindow.h"
#include "klient.h"
#include <QApplication>
#include "Salon.h"
int main(int argc, char *argv[])
{
    Salon salon;
    salon.wczytajKlientow("C:/Users/Janusz/Desktop/PK4- Laby/pliki do projektu/klienci.txt");
    QApplication a(argc, argv);
    MainWindow w(&salon);
    w.show();
    int result= a.exec();

    salon.zapiszKlientow("C:/Users/Janusz/Desktop/PK4- Laby/pliki do projektu/klienci.txt");
    return result;
}
