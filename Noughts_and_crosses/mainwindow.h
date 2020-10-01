#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintEvent>
#include <QPainter>
#include <QPainterPath>
#include <QPen>
#include <QColor>
#include <QLabel>
#include <QPushButton>
#include <QPixmap>
#include <QDebug>

#include "clickablelabel.h"
#include "gamereferee.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *);

private slots:
    void handleBackButton();
    void handleNewGameButton();
    void slotClicked(int, int);

private:
    QPixmap * noughtImage, * crossImage;    /* raw images read from file */
    QPixmap * noughtGameImage, * crossGameImage;    /* resized game images */
    QLabel * noughtsScoreLabel, * crossesScoreLabel, *  refereeLabel;  /* game labels */
    QPushButton *newGameButton;
    QPushButton *backButton;
    GameReferee *referee;
    int winner; /* 1: no winner, 1: cross wins, 2: nought wins, 3: draw */
    int playerTurn; /* 1: cross, 2: nought */
    int scoreTally[2];
    ClickableLabel* clickableLabels[9];
    int currentSlotSymbols[9];  /* Slot symbols: 0: empty, 1: cross, 2: nought */
};

#endif // MAINWINDOW_H
