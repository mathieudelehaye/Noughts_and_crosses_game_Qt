#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "homeview.h"
#include "gameview.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);

private:

    // Asssets
    QPixmap * noughtImage, * crossImage;    /* raw images read from file */

    // View management
    int viewToDisplay;  /* 0: home view, 1: game view */
    HomeView * homeView;
    GameView * gameView;
};

#endif // MAINWINDOW_H
