#include "mainwindow.h"

#include <QApplication>

int main( int argc, char **argv )
{
    QApplication a( argc, argv );

    MainWindow w;

    w.setFixedSize(530, 900);

    a.setStyleSheet("MainWindow { background: #313131; }");

    w.show();

    return a.exec();
}

//    f08113 orange
//b8398e pink
//efefee white
