#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    viewToDisplay = 1;

    homeView  = new HomeView(this, crossImage, noughtImage);

    gameView = new GameView(this, crossImage, noughtImage);

}

MainWindow::~MainWindow()
{
}

void MainWindow::paintEvent(QPaintEvent *) {

    if(viewToDisplay == 0) {    // Display home view

//        drawHomeView();

    } else {    // Display game view

        gameView->draw(this);

    }
}
