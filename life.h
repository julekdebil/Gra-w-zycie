#ifndef LIFE_H
#define LIFE_H
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QtAlgorithms>
#include <QObject>
#include <QTimer>
#include <QFile>
#include <QString>


/**
 *W poniższym pliku deklaruję zmienne i funkcje z klasy life
 */

class life:public QObject //klasa dziedziczy po QObject
{
    Q_OBJECT

private:
      //zmienna trybu
    int c;  // ktora tablica?
    int L;
    int stan[2][200][200]; //wybieram wymiar macierzy

protected:
     int d = 1;

public:



    life();

    /**
     * @brief Metoda inicjalizująca macierz zmiennych
     */
    void init(int _c);
    /**
     * @brief Metoda wyświetlająca stan macierzy
     */
    void rysuj(int _c);
    /**
     * @brief Metoda sumująca wartość komórek wokół danej komórki
     * @return suma wartości komórek wokół
     */
    int suma(int _c, int i, int j);
    /**
     * @brief Metoda zawierająca logikę zmian wartości macierzy
     */
    void gameoflife(int _c);    // gra
    //void tryb(int d);   //wybrany tryb gry



public: signals:
    void tablica (int x,int y);

public slots:
    /**
     * Kolejne kroki
     */
    void krok();
    /**
     * odbiór sygnału start
     */
    void getStart();
    /**
     * odbiór sygnału reset
     */
    void getReset();
    /**
     * Metoda odpowiadająca za wczytanie macierzy z pliku
     */
    void wczytaj();
    /**
     * Metoda odpowiadająca za zapisanie macierzy do pliku
     */
    void zapisz();
    //void jeden();
    //void dwa();
    void kolejny();

};

#endif // LIFE_H
