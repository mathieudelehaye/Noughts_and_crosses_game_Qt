#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Load asset images
    noughtImage = new QPixmap("../../../../Noughts_and_crosses/nought-01.png");
    crossImage = new QPixmap("../../../../Noughts_and_crosses/cross-01.png");

    // Initialize views
    viewToDisplay = 0;
    homeView  = new HomeView(this, crossImage, noughtImage);
    gameView = new GameView(this, crossImage, noughtImage);
    gameView->disable();

    // Handle view signals
    connect(homeView, SIGNAL (leaving(int)), this, SLOT (viewChanged(int)));
    connect(gameView, SIGNAL (leaving(int)), this, SLOT (viewChanged(int)));
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

void MainWindow::viewChanged(int originView) {
    qDebug() << "View changed from view " << originView;

    switch (originView) {
    case 0: // changing from home view
        viewToDisplay = 1;
        homeView->disable();
        gameView->enable();
        break;
    case 1: // changing from game view
        viewToDisplay = 0;
        gameView->disable();
        homeView->enable();
        break;
    }
}
