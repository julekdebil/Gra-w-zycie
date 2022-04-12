#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QObject>

// Biblioteki wyświetlanie
#include <QMainWindow>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QLabel>

// Biblioteka dla timera
#include <QTimer>

//biblioteki  do zapisu w pliku
#include <QFile>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow  //deklaracja klasy
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);  //konstruktor
    ~MainWindow();  // destruktor

    /**
     * Metoda odpowiadająca za stworzenie macierzy kwadratów i narysowanie ich
     */
    void tablica (int x,int y);
    /**
     * Metoda odpowiadająca za wymazanie narysowanego stanu macierzy
     */
    void wymazanie ();
    QTimer timer;   //obsluguje timer
    QFile file;     // obsluguje plik

private:
    Ui::MainWindow *ui;
    QGraphicsView *view;
    QGraphicsScene *scene;
    int suwak;
    int start;
    int reset;
    bool symulacja;
    int predkosc;


 /**
 * prywatne sloty - przyciśniete przyciski itd
 */
private slots:
     void on_pushButton_Reset_clicked();
     void on_pushButtonStart_clicked();
     void on_horizonpredkosctalScrollBar_valueChanged(int value);
     void on_pushButton_Zapisz_clicked();
     void on_pushButton_Pauza_clicked();
     void on_pushButton_Wczytaj_clicked();
     void on_spinBox_valueChanged(int arg1);
/**
* sygnaly wychodzace na zewnątrz klasy
*/


     void on_trybclicked(int checked);


     void on_label_linkActivated(const QString &link);

     void on_Krok_clicked();

public: signals:

     void setStart();
     void setReset();
     void wczytaj();
     void kolejny();
     void zapisz();
     void jeden();
     void dwa();

};


#endif
