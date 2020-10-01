#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    viewToDisplay = 0;

    noughtImage = new QPixmap("../../../../Noughts_and_crosses/nought-01.png");
    crossImage = new QPixmap("../../../../Noughts_and_crosses/cross-01.png");

    homeView  = new HomeView(this, crossImage, noughtImage);
    gameView = new GameView(this, crossImage, noughtImage);
    gameView->disable();

}

MainWindow::~MainWindow()
{

    delete noughtImage;

    delete crossImage;

    delete homeView;

    delete gameView;

}

void MainWindow::paintEvent(QPaintEvent *) {

    if(viewToDisplay == 0) {    // Display home view

        homeView->draw(this);

    } else {    // Display game view

        gameView->draw(this);

    }
}
