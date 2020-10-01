#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QPainterPath>
#include <QPushButton>
#include <QLabel>
#include <QObject>

#include "gamereferee.h"
#include "clickablelabel.h"

class GameView : public QObject
{
    Q_OBJECT

public:
    GameView(QWidget *, QPixmap*, QPixmap*);
    void draw(QWidget *);

private slots:
    void handleBackButton();
    void handleNewGameButton();
    void slotClicked(int, int);

private:
    QLabel * noughtsScoreLabel, * crossesScoreLabel, *  refereeLabel;  /* game labels */
    QPixmap * noughtGameImage, * crossGameImage;    /* resized game images */
    QPushButton *newGameButton;
    QPushButton *backButton;
    GameReferee *referee;
    int winner; /* 1: no winner, 1: cross wins, 2: nought wins, 3: draw */
    int playerTurn; /* 1: cross, 2: nought */
    int scoreTally[2];
    ClickableLabel* clickableLabels[9];
    int currentSlotSymbols[9];  /* Slot symbols: 0: empty, 1: cross, 2: nought */
};

#endif // GAMEVIEW_H
