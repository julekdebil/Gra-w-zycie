#include "mainwindow.h"
#include "life.h"

#include <QApplication>
#include <QObject>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;   //typu mainwindow
    life l;         //ob. typu life
    w.show();

    //poniżej łączenia sygnalu ze slotem z obiektu l wysyłany sygnał do l, tam slot
    // & bo adresy (operator wyłuskania zwraca adres)
    QObject::connect(&l, &life::tablica, &w, &MainWindow::tablica);
    QObject::connect(&w, &MainWindow::setStart, &l, &life::getStart);
    QObject::connect(&w, &MainWindow::setReset, &l, &life::getReset);
    QObject::connect(&w, &MainWindow::wczytaj, &l, &life::wczytaj);
    QObject::connect(&w, &MainWindow::kolejny, &l, &life::kolejny);
    QObject::connect(&w, &MainWindow::zapisz, &l, &life::zapisz);
    //QObject::connect(&w, &MainWindow::jeden, &l, &life::jeden);
    //QObject::connect(&w, &MainWindow::dwa, &l, &life::dwa);


    l.rysuj(1); //rysuję stan początkowy

    // powiązanie wymazania i kroku z timerem
    QObject::connect(&w.timer, &QTimer::timeout, &w, &MainWindow::wymazanie);
    QObject::connect(&w.timer, &QTimer::timeout, &l, &life::krok);


    return a.exec();    //petla - aż exit
}




