#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "life.h"
#include <QtCore>
#include <QtGui>
#include <QLabel>


MainWindow::MainWindow(QWidget *parent):    //konstruktor
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);      //GUI
    view = new QGraphicsView(this);     //nowy obiekt

    scene = new QGraphicsScene(view);   //widok
    view->setFixedSize(1020,1020);      //pole wyświetlania - wymiary
    scene->setSceneRect(0, 0, 1000,1000);   //wymiary szachownicy

    scene->setBackgroundBrush(Qt::darkMagenta);     //kolory
    view->setScene(scene);

    scene->setItemIndexMethod(QGraphicsScene::NoIndex); //nieindeksowane komórki
    view->show();

    symulacja = 0;  //domyslna wartosc zmiennej symulacja (off)
    predkosc = 1000;    //domyslna predkosc (tutaj raczej okres)
}


MainWindow::~MainWindow()   //destruktor
{
    delete ui;
    delete view;
    delete scene;

}

void MainWindow::tablica(int x,int y)   //tablica kwadratów i dodanie ich do sceny
{

    QGraphicsRectItem *kwadrat = new QGraphicsRectItem(x*5,y*5,5,5);
    kwadrat->setBrush(Qt::magenta);
    scene->addItem(kwadrat);
}

void MainWindow::wymazanie()    //wymazanie aktualnego widoku (żeby się nie dodawały jeden na drugi)
{
    qDeleteAll( scene->items() );
}



void MainWindow::on_pushButtonStart_clicked()
{

    timer.start(predkosc); //timer rusza używając predkości, albo bazowej, albo nadanej suwakiem (okres)

}

void MainWindow::on_pushButton_Reset_clicked()
{
   timer.stop();
   wymazanie();
   emit setReset();
}



void MainWindow::on_horizonpredkosctalScrollBar_valueChanged(int value) //zmiana predkosci za pomoca suwaka i przypisanie jej do zmiennej predkosc
{
    predkosc=value;
    timer.setInterval(predkosc);
}



void MainWindow::on_pushButton_Pauza_clicked()
{
    timer.stop();
}


void MainWindow::on_pushButton_Zapisz_clicked()
{
    emit zapisz();
}




void MainWindow::on_pushButton_Wczytaj_clicked()    //tutaj trzeba wymazać, bo wczytaj rysuje
{
    wymazanie();
    emit wczytaj();
}


//void MainWindow::on_trybclicked(int checked)
//{
//    if(checked)
//    {
//        ui->label -> setText("1");
//       emit jeden();
//    }
//    else
//    {
//        ui->label -> setText("2");
//       emit dwa();
//    }
//}


void kolejny()
{

}

void MainWindow::on_Krok_clicked()
{
    wymazanie();
    emit kolejny();
}

