#ifndef HOMEVIEW_H
#define HOMEVIEW_H

#include <QWidget>
#include <QDebug>
#include <QPainter>
#include <QPainterPath>
#include <QPushButton>
#include <QLabel>
#include <QObject>

class HomeView : public QObject
{
    Q_OBJECT
public:
    HomeView(QWidget *, QPixmap*, QPixmap*);
    ~HomeView();
    void enable();
    void disable();
    void draw(QWidget *);

private slots:
    void handleStartButton();

private:
    QLabel * noughtsWordLabel, * crossesWordLabel, *  plusSignLabel, * noughtIconLabel, * crossIconLabel;  /* title labels */
    QPushButton *startButton;
};

#endif // HOMEVIEW_H
