#include "gameview.h"

GameView::GameView(QWidget * parent, QPixmap * crossImage, QPixmap * noughtImage) {

    noughtsScoreLabel = new QLabel(parent);
    noughtsScoreLabel->setGeometry(60, 65, 300, 80);
    noughtsScoreLabel->setStyleSheet("color: #efefee; font: 21pt 'Roboto'; font-weight: bold;");
    noughtsScoreLabel->show();

    crossesScoreLabel = new QLabel(parent);
    crossesScoreLabel->setGeometry(325, 65, 300, 80);
    crossesScoreLabel->setStyleSheet("color: #efefee; font: 21pt 'Roboto'; font-weight: bold;");
    crossesScoreLabel->show();

    refereeLabel = new QLabel(parent);
    refereeLabel->setGeometry(180,150,300,80);
    refereeLabel->setStyleSheet("color: #efefee; font: 31pt 'Roboto Condensed'; font-weight: normal;");
    refereeLabel->show();

    // Draw buttons
    backButton = new QPushButton("Back", parent);
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

    newGameButton = new QPushButton("New game", parent);
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

    // Display icon images
    QLabel *noughtIconLabel = new QLabel(parent);
    noughtImage = new QPixmap("../../../../Noughts_and_crosses/nought-01.png");
    QPixmap noughtImageIcon = noughtImage->scaled(23, 23);
    noughtIconLabel->setGeometry(30, 92, 23, 23);
    noughtIconLabel->setPixmap(noughtImageIcon);
    noughtIconLabel->show();

    QLabel *crossIconLabel = new QLabel(parent);
    crossImage = new QPixmap("../../../../Noughts_and_crosses/cross-01.png");
    QPixmap crossImageIcon = crossImage->scaled(23, 23);
    crossIconLabel->setGeometry(295, 92, 23, 23);
    crossIconLabel->setPixmap(crossImageIcon);
    crossIconLabel->show();

    // Add clickable areas
    for(int i = 0; i < 9; i++) {
        clickableLabels[i] = new ClickableLabel(parent);
        int x_coordinate = i % 3;
        int y_coordinate = i  / 3;
        clickableLabels[i]->setGeometry(85 + x_coordinate * 120, 291 + y_coordinate * 120, 120, 120);
        clickableLabels[i]->setAlignment (Qt::AlignCenter);
        this->connect(clickableLabels[i], SIGNAL(clicked(int, int)), this, SLOT(slotClicked(int, int)));
    }

    // Reset slot symbols
    for(int i = 0; i < 9; i++) {
        currentSlotSymbols[i] = 0;
    }

    // Resize images to be displayed in game
    noughtGameImage = new QPixmap(noughtImage->scaled(64, 64));
    crossGameImage = new QPixmap(crossImage->scaled(64, 64));

    // Create game referee and game variables
    referee = new GameReferee();
    winner = 0;
    playerTurn = 1;
    for(int i = 0; i < 2; i++) {
        scoreTally[i] = 0;
    }

    // Handle button signals
    this->connect(backButton, SIGNAL (released()), this, SLOT (handleBackButton()));
    this->connect(newGameButton, SIGNAL (released()), this, SLOT (handleNewGameButton()));
}

void GameView::draw(QWidget * parent) {

    // Draw game view
    // Main rectangles
    QPainter p(parent);
    QPainterPath path;
    path.addRoundedRect(QRectF(20, 67, 490, 660), 12, 12);
    path.moveTo(20, 134); path.lineTo(510, 134);
    p.setPen(QPen(QColor(0xef, 0xef, 0xee), 1));
    p.drawPath(path);

    // Game board
    p.setPen(QPen(QColor(0xef, 0xef, 0xee), 2));
    p.drawLine(85, 411, 445, 411);
    p.drawLine(85, 531, 445, 531);
    p.drawLine(210, 291, 210, 651);
    p.drawLine(330, 291, 330, 651);

    // Display game images
    for(int i = 0; i < 9; i++) {
        switch(currentSlotSymbols[i]) {

        case 1: // cross symbol in slot
            clickableLabels[i]->setPixmap(*crossGameImage);
            break;
        case 2: // nought symbol in slot
            clickableLabels[i]->setPixmap(*noughtGameImage);
            break;
        default:
            clickableLabels[i]->clear();
        }
    }

    // Check if a player has won
    int previousWinnerValue = winner;
    winner = referee->checkForWinnerOrDraw(currentSlotSymbols);
    if(winner != previousWinnerValue) {
        qDebug() << "Winner is: " << winner;
    }

    // Display game labels
    noughtsScoreLabel->setText("Noughts score: " + QString::number(scoreTally[0]));
    crossesScoreLabel->setText("Crosses score: " + QString::number(scoreTally[1]));
    refereeLabel->setText("noughts turn!");

}

void GameView::handleBackButton() {
    qDebug() << "Back Button pressed";
//    backButton->setText("BB");
}

void GameView::handleNewGameButton() {
    qDebug() << "New Game Button pressed";
//    newGameButton->setText("NGB");
 }

void GameView::slotClicked(int xPos, int yPos) {
//    qDebug()<< "label clicked at " << xPos + 60 << ", " << yPos + 60;
    int slotIndex = ((yPos - 291) / 120) * 3 + (xPos - 85) / 120;
    currentSlotSymbols[slotIndex] ++;
    if(currentSlotSymbols[slotIndex] >= 3) {
        currentSlotSymbols[slotIndex] = 0;
    }
//    qDebug() << slotIndex << ": " << currentSlotSymbols[slotIndex];
}
