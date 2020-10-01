#include "homeview.h"

HomeView::HomeView(QWidget * parent, QPixmap * crossImage, QPixmap * noughtImage) {

    // Draw labels
    noughtsWordLabel = new QLabel(parent);
    noughtsWordLabel->setText("noughts");
    noughtsWordLabel->setGeometry(52, 270, 300, 80);
    noughtsWordLabel->setStyleSheet("color: #f08113; font: 58pt 'Roboto Condensed'; font-weight: normal;");

    plusSignLabel = new QLabel(parent);
    plusSignLabel->setText("+");
    plusSignLabel->setGeometry(252, 275, 300, 80);
    plusSignLabel->setStyleSheet("color: #efefee; font: 48pt 'Roboto Condensed'; font-weight: normal;");

    crossesWordLabel = new QLabel(parent);
    crossesWordLabel->setText("crosses");
    crossesWordLabel->setGeometry(293, 270, 300, 80);
    crossesWordLabel->setStyleSheet("color: #b8398e; font: 58pt 'Roboto Condensed'; font-weight: normal;");

    // Draw button
    startButton = new QPushButton("Start game", parent);
    startButton->setStyleSheet(
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
    startButton->move(80,760);
    startButton->setFixedSize(370,62);

    // Display icon images
    noughtIconLabel = new QLabel(parent);
    QPixmap noughtImageIcon = noughtImage->scaled(46, 46);
    noughtIconLabel->setGeometry(195, 433, 46, 46);
    noughtIconLabel->setPixmap(noughtImageIcon);

    crossIconLabel = new QLabel(parent);
    QPixmap crossImageIcon = crossImage->scaled(46, 46);
    crossIconLabel->setGeometry(290, 433, 46, 46);
    crossIconLabel->setPixmap(crossImageIcon);

    // Handle button signals
    connect(startButton, SIGNAL (released()), this, SLOT (handleStartButton()));
}

HomeView::~HomeView() {

    delete noughtsWordLabel;
    delete plusSignLabel;
    delete crossesWordLabel;
    delete startButton;
    delete noughtIconLabel;
    delete crossIconLabel;

}

void HomeView::enable() {

    // Show all widgets when switching to the view
    noughtsWordLabel->show();
    plusSignLabel->show();
    crossesWordLabel->show();
    startButton->show();
    noughtIconLabel->show();
    crossIconLabel->show();

}

void HomeView::disable() {

    // Hide widgets when leaving view
    noughtsWordLabel->hide();
    plusSignLabel->hide();
    crossesWordLabel->hide();
    startButton->hide();
    noughtIconLabel->hide();
    crossIconLabel->hide();
}


void HomeView::draw(QWidget * parent) {

    // Draw home view graphics
    QPainter p(parent);
    p.setPen(QPen(QColor(0xef, 0xef, 0xee), 2));
    p.drawLine(265, 413, 265, 493);

}

void HomeView::handleStartButton() {
    qDebug() << "Start Button pressed";
    emit leaving(0);    // 0: leaving home view
}
