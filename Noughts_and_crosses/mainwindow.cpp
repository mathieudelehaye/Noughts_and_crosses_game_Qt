#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // Draw labels
    QLabel *noughtsScoreLabel = new QLabel(this);
    noughtsScoreLabel->setText("Noughts score: 2");
    noughtsScoreLabel->setGeometry(60, 65, 300, 80);
    noughtsScoreLabel->setStyleSheet("color: #efefee; font: 21pt 'Roboto'; font-weight: bold;");
    noughtsScoreLabel->show();

    QLabel *crossesScoreLabel = new QLabel(this);
    crossesScoreLabel->setText("Crosses score: 2");
    crossesScoreLabel->setGeometry(325, 65, 300, 80);
    crossesScoreLabel->setStyleSheet("color: #efefee; font: 21pt 'Roboto'; font-weight: bold;");
    crossesScoreLabel->show();

    QLabel *refereeLabel = new QLabel(this);
    refereeLabel->setText("noughts turn!");
    refereeLabel->setGeometry(180,150,300,80);
    refereeLabel->setStyleSheet("color: #efefee; font: 31pt 'Roboto Condensed'; font-weight: normal;");
    refereeLabel->show();

    // Draw buttons
    QPushButton *backButton = new QPushButton("Back", this);
    backButton->setStyleSheet(
        "QPushButton{ background-color: #313131;"
        "border-style: solid;"
        "border-color: #efefee;"
        "border-width: 1px;"
        "border-radius: 30px;"
        "color: #efefee;"
        "font: 18pt 'Roboto';"
        "font-weight: bold; }"
        "QPushButton:hover{ background-color: #efefee;"
        "border-style: solid;"
        "border-color: #efefee;"
        "border-width: 1px;"
        "border-radius: 30px;"
        "color: #313131;"
        "font: 18pt 'Roboto';"
        "font-weight: bold; }"
    );
    backButton->move(20,760);
    backButton->setFixedSize(230,62);
    backButton->show();

    newGameButton = new QPushButton("New game", this);
    newGameButton->setStyleSheet(
        "QPushButton{ background-color: #efefee;"
        "border-style: solid;"
        "border-color: #313131;"
        "border-width: 1px;"
        "border-radius: 30px;"
        "color: #313131;"
        "font: 18pt 'Roboto';"
        "font-weight: bold; }"
        "QPushButton:hover{ background-color: #313131;"
        "border-style: solid;"
        "border-color: #efefee;"
        "border-width: 1px;"
        "border-radius: 30px;"
        "color: #efefee;"
        "font: 18pt 'Roboto';"
        "font-weight: bold; }"
    );
    newGameButton->move(270,760);
    newGameButton->setFixedSize(230,62);
    newGameButton->show();

    // Display images
    QLabel *noughtIconLabel = new QLabel(this);
    QPixmap noughtImage("../../../../Noughts_and_crosses/nought-01.png");
    QPixmap noughtImageIcon = noughtImage.scaled(23, 23);
    noughtIconLabel->setGeometry(30, 92, 23, 23);
    noughtIconLabel->setPixmap(noughtImageIcon);
    noughtIconLabel->show();

    QLabel *crossIconLabel = new QLabel(this);
    QPixmap crossImage("../../../../Noughts_and_crosses/cross-01.png");
    QPixmap crossImageIcon = crossImage.scaled(23, 23);
    crossIconLabel->setGeometry(295, 92, 23, 23);
    crossIconLabel->setPixmap(crossImageIcon);
    crossIconLabel->show();

    // Display game images
    QLabel *noughtGameImageLabel = new QLabel(this);
    QPixmap noughtGameImage = noughtImage.scaled(64, 64);
    noughtGameImageLabel->setGeometry(240, 320, 64, 64);
    noughtGameImageLabel->setPixmap(noughtGameImage);
    noughtGameImageLabel->show();

    QLabel *crossGameImageLabel1 = new QLabel(this);
    QPixmap crossGameImage = crossImage.scaled(64, 64);
    crossGameImageLabel1->setGeometry(240, 440, 64, 64);
    crossGameImageLabel1->setPixmap(crossGameImage);
    crossGameImageLabel1->show();

    QLabel *crossGameImageLabel2 = new QLabel(this);
    crossGameImageLabel2->setGeometry(360, 560, 64, 64);
    crossGameImageLabel2->setPixmap(crossGameImage);
    crossGameImageLabel2->show();

    // Handle button signal
    connect(newGameButton, SIGNAL (released()), this, SLOT (handleButton()));
}

MainWindow::~MainWindow()
{
}

void MainWindow::paintEvent(QPaintEvent *) {

    // Draw game view
    // Main rectangles
    QPainter p(this);
    QPainterPath path;
    path.addRoundedRect(QRectF(20, 67, 490, 660), 12, 12);
    path.moveTo(20, 134); path.lineTo(510, 134);
    p.setPen(QPen(QColor(0xef, 0xef, 0xee), 1));
    p.drawPath(path);

    // Game board
    p.setPen(QPen(QColor(0xef, 0xef, 0xee), 2));
    p.drawLine(90, 412, 440, 412);
    p.drawLine(90, 532, 440, 532);
    p.drawLine(210, 291, 210, 651);
    p.drawLine(330, 291, 330, 651);

}

void MainWindow::handleButton()
 {
//    qDebug() << "Button pressed";
    // change the text
    newGameButton->setText("Example");
 }
