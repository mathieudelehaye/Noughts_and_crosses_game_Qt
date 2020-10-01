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
    ~GameView();
    void enable();
    void disable();
    void draw(QWidget *);

private slots:
    void handleBackButton();
    void handleNewGameButton();
    void slotClicked(int, int);

signals:
    void leaving(int);

private:
    QLabel * noughtsScoreLabel, * crossesScoreLabel, *  refereeLabel, * noughtIconLabel, * crossIconLabel;  /* game labels */
    QPixmap * noughtGameImage, * crossGameImage;    /* resized game images */
    QPushButton *newGameButton;
    QPushButton *backButton;
    GameReferee *referee;
    int winner; /* 0: no winner, 1: cross wins, 2: nought wins, 3: draw */
    int playerTurn; /* 1: cross, 2: nought */
    int lastGameStarter;    /* player who has started the previous game */
    bool gameOver;
    int scoreTally[2];
    ClickableLabel* clickableLabels[9];
    int currentSlotSymbols[9];  /* Slot symbols: 0: empty, 1: cross, 2: nought */
    void updateGrid();    /* update image in grid */
};

#endif // GAMEVIEW_H
