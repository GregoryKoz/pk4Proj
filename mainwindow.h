#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QAction>
#include <QMainWindow>
#include <vector>
#include "klient.h"
#include "Salon.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(Salon* salonPtr, QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_stackedWidget_currentChanged(int arg1);
    void on_btnDodajKlienta_clicked();

private:
    Ui::MainWindow *ui;
    Salon* salon;
};

#endif // MAINWINDOW_H
