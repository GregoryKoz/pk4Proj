#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QAction>
#include <QMainWindow>
#include <vector>
#include "klient.h"
#include "Salon.h"
#include <regex>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(Salon* salon, QWidget *parent = nullptr);
    ~MainWindow();
    void odswiezListeKlientow();
    void odswiezListePojazdow();

private slots:

    void on_stackedWidget_currentChanged(int arg1);
    void on_btnDodajKlienta_clicked();
    void on_btnUsunKlienta_clicked();
    void on_btnWyszukaj_clicked();
    void on_btnEdytujKlienta_clicked();
    void on_btnStronaKlient_clicked();
    void on_btnStronaPojazd_clicked();
    void on_btnStronaRaport_clicked();
    void on_btnStronaSprzedaz_clicked();
    void on_btnStronaSerwis_clicked();
private:
    Ui::MainWindow *ui;
    Salon* salon;
};

#endif // MAINWINDOW_H
