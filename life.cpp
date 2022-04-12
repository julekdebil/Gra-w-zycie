#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include "life.h"
#include <QtCore>
#include <QtGui>
#include <QDebug>

life::life()                                                                                               //????????????????
{
    L = 200;
    c = 1;
    d = 1;
    init(c);
    rysuj(c);
}

void life::kolejny()
{
    gameoflife(c);
    c=1-c;
    rysuj(c);
}

void life::init(int _c)		//inicjalizacja gry
{
    for(int i=0; i<L; i++) //przechodze po wszystkich elementach (wiersze)
        for (int j = 0; j < L; j++)
        {
           stan[_c][i][j] = 0;
        }

    for(int i=0; i<L; i++) //przechodze po wszystkich elementach (kolumny)
        for (int j = 0; j < L; j++)
        {
            if (rand() / (float)RAND_MAX < 0.15)    //z prawdopodobienstwem 0.15 ustawiam 1, reszta to 0
                stan[_c][i][j] = 1;
            else
                stan[_c][i][j] = 0;
        }
}


void life::rysuj(int _c)            //funkcja rysowania
{
    for (int i = 0; i < L; i++) //przejście po wszystkich elementach wiersze, później kolumny
    for (int j = 0; j < L; j++)
    {
        if(stan[_c][i][j]==1)

            emit tablica (i,j);     //Jeżeli komórka = 1 -> wyemitowany sygnał
    }

}


int life::suma(int _c, int i, int j)    //suma wartości komórek wokół komórki [_c][i][j]
{
    int ip, im, jp, jm;
    if (i < L - 1) ip = i + 1;
        else ip = 0;  //cykliczne warunki ip = i plus im = i minus itd czyli ip to i w prawo im i w lewo itd
    if (i > 0) im = i - 1;
        else im = L - 1;
    if (j < L - 1) jp = j + 1;
        else jp = 0;
    if (j > 0) jm = j - 1l;
        else jm = L - 1;

    //poniżej suma wszystkich komórek wokół (patrzę na 4 wokół)
    return stan[_c][ip][j] + stan[_c][im][j] + stan[_c][i][jp] + stan[_c][i][jm] + stan[_c][ip][jp] + stan[_c][im][jm] + stan[_c][im][jp] + stan[_c][ip][jm];

}




void life::gameoflife(int _c)
{
    if (d==1)

    for (int i = 0; i < L; i++) //przechodze po wszystkich elementach
    for (int j = 0; j < L; j++)

    {
        int s = suma(_c, i, j);

        //Żywa komórka, która ma 2 lub 3 żyjących sąsiadów przeżywa
        if (stan[_c][i][j] && (s == 2 || s == 3))
            stan[1-_c][i][j] = 1;

        //martwa komórka z trzema żywymi sąsiadami ożywa
        else
            if (!stan[_c][i][j] && (s == 3))
                stan[1-_c][i][j] = 1;

            else
                //wszystkie inne umieraja
                stan[1-_c][i][j] = 0;
     }
    else if (d==2)    //to miałoby działać dla wyboru innego trybu - inne warunki, krótsze życie
        for (int i = 0; i < L; i++) //przechodze po wszystkich elementach
        for (int j = 0; j < L; j++)

            {
                int s = suma(_c, i, j);

                //Żywa komórka, która ma 1 lub 4 żyjących sąsiadów umiera
                if (stan[_c][i][j] && (s == 1|| s == 4))
                    stan[1 - _c][i][j] = 0;

                //martwa komórka z trzema żywymi sąsiadami ozywa
                else
                    if (!stan[_c][i][j] && (s == 3))
                        stan[1 - _c][i][j] = 1;

                    else
                        //wszystkie inne umieraą
                        stan[1 - _c][i][j] = 0;
            }

}

//void life::jeden()
//{
//    d = 1;
//}
//void life::dwa()
//{
//    d = 2;
//}

void life::krok()
{
    gameoflife(c);
    c=1-c;
    rysuj(c);

}

void life::getStart()
{

}

void life::getReset()
{
    L = 200;
    c = 1;
    d = 1;
    init(c);
    rysuj(c);

}

void life::wczytaj()    //wczytywanie z pliku
{
    QFile file("C:/Users/Julka/Desktop/life/file.txt"); // wrzucam do tego samego folderu, w którym jest projekt
    QString linia; //string, żeby wpisywać jako tekst
    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    { // metoda open w otwiera plik w trybie tylko do odczytu z zamianą znaków \r\n ma \n
        QTextStream in(&file);
        for (int w=0;w<200;w++) //przejście przez wszystkie wiersze
        {
            linia=in.readLine();
            for (int k=0;k<200;k++) //przed kolumny
            {
                if(linia.at(k)=='1')
                {
                    stan[1][k][w]=1;    // jak przeczyta 1 wstawia 1 itd.

                }
                else if(linia.at(k)=='0')
                {
                    stan[1][k][w]=0;
                }
            }
        }
        file.close();
    }

    rysuj(c);   // dodałam, żeby po wczytaniu od razu się rysowało

}

void life::zapisz() //zapisywanie do pliku
{

    QFile file("C:/Users/Julka/Desktop/life/file.txt");
    QString linia;

    if(file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    { // metoda open w otwiera plik w trybie tylko do odczytu z zamianą znaków \r\n ma \n
        QTextStream out(&file);
        for (int w=0;w<200;w++) //przejscie przez wiersze
        {
            linia.clear();  //czyścimy linię
            for (int k=0;k<200;k++)//przejście przez kolumny
            {
                if(stan[1][k][w]==1)
                {

                    linia+='1'; //kolejna linia = 1, jezeli odczytano 1 itd.
                }
                else if(stan[1][k][w]==0)
                {
                    linia+='0';
                }
            }
            out<<linia<<'\n';   //enter
        }
        file.close();
    }
}
