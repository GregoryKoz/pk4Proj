#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void onAddClientClicked();

private:
    Ui::MainWindow *ui;
    Salon* salon;
};

#endif // MAINWINDOW_H
