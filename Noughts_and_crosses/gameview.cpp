#include "gameview.h"

GameView::GameView(QWidget * parent, QPixmap * crossImage, QPixmap * noughtImage) {

    // Draw labels
    noughtsScoreLabel = new QLabel(parent);
    noughtsScoreLabel->setGeometry(60, 65, 300, 80);
    noughtsScoreLabel->setStyleSheet("color: #efefee; font: 21pt 'Roboto'; font-weight: bold;");

    crossesScoreLabel = new QLabel(parent);
    crossesScoreLabel->setGeometry(325, 65, 300, 80);
    crossesScoreLabel->setStyleSheet("color: #efefee; font: 21pt 'Roboto'; font-weight: bold;");

    refereeLabel = new QLabel(parent);
    refereeLabel->setGeometry(180,150,300,80);
    refereeLabel->setStyleSheet("color: #efefee; font: 31pt 'Roboto Condensed'; font-weight: normal;");

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

    // Display icon images
    noughtIconLabel = new QLabel(parent);
    QPixmap noughtImageIcon = noughtImage->scaled(23, 23);
    noughtIconLabel->setGeometry(30, 92, 23, 23);
    noughtIconLabel->setPixmap(noughtImageIcon);

    crossIconLabel = new QLabel(parent);
    QPixmap crossImageIcon = crossImage->scaled(23, 23);
    crossIconLabel->setGeometry(295, 92, 23, 23);
    crossIconLabel->setPixmap(crossImageIcon);

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

    // Create game referee and initializ game variables
    referee = new GameReferee();
    winner = 0;
    playerTurn = 1; // cross starts to play
    lastGameStarter = playerTurn;
    gameOver = false;   // start game
    for(int i = 0; i < 2; i++) {
        scoreTally[i] = 0;
    }

    // Handle button signals
    this->connect(backButton, SIGNAL (released()), this, SLOT (handleBackButton()));
    this->connect(newGameButton, SIGNAL (released()), this, SLOT (handleNewGameButton()));
}

GameView::~GameView() {

    delete noughtsScoreLabel;
    delete crossesScoreLabel;
    delete refereeLabel;
    delete backButton;
    delete newGameButton;
    delete noughtIconLabel;
    delete crossIconLabel;
    for(int i = 0; i < 9; i++) {
        delete clickableLabels[i];
    }
    delete noughtGameImage;
    delete crossGameImage;
    delete referee;

}

void GameView::enable() {

    // Show all widgets when switching to the view
    crossesScoreLabel->show();
    noughtsScoreLabel->show();
    crossIconLabel->show();
    noughtIconLabel->show();
    refereeLabel->show();
    newGameButton->show();
    backButton->show();
}

void GameView::disable() {

    // Hide widgets when leaving view
    crossesScoreLabel->hide();
    noughtsScoreLabel->hide();
    crossIconLabel->hide();
    noughtIconLabel->hide();
    refereeLabel->hide();
    newGameButton->hide();
    backButton->hide();
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

    // Draw grid
    p.setPen(QPen(QColor(0xef, 0xef, 0xee), 2));
    p.drawLine(85, 411, 445, 411);
    p.drawLine(85, 531, 445, 531);
    p.drawLine(210, 291, 210, 651);
    p.drawLine(330, 291, 330, 651);

    // Update grid images
    updateGrid();

    // Check if a player has won
    int previousWinnerValue = winner;
    winner = referee->checkForWinnerOrDraw(currentSlotSymbols);
    if(winner != previousWinnerValue) {
        qDebug() << "Winner: " << winner;
        gameOver = true;
        switch (winner) {
        case 1:
            refereeLabel->setText("crosses won!");
            scoreTally[0]++;
            break;
        case 2:
            refereeLabel->setText("noughts won!");
            scoreTally[1]++;
            break;
        case 3:
            refereeLabel->setText("it's a draw!");
            break;
        }
    }

    // Display game labels
    noughtsScoreLabel->setText("Noughts score: " + QString::number(scoreTally[1]));
    crossesScoreLabel->setText("Crosses score: " + QString::number(scoreTally[0]));

    // Do not display turn if game over
    if (!gameOver) {
        switch (playerTurn) {
        case 1: // cross plays
            refereeLabel->setText("crosses turn!");
            break;
        case 2: // nought plays
            refereeLabel->setText("noughts turn!");
            break;
        }
    }
}

void GameView::updateGrid() {
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
}

void GameView::handleBackButton() {
    qDebug() << "Back Button pressed";

    // clear the grid
    for(int i = 0; i < 0; i++) {
        currentSlotSymbols[i] = playerTurn;
    }

    // clear the tally scores
    scoreTally[0] = 0;
    scoreTally[1] = 0;

    // reinitialize game variables
    winner = 0;
    playerTurn = 1; // cross starts to play
    lastGameStarter = playerTurn;
    gameOver = false;
    for(int i = 0; i < 2; i++) {
        scoreTally[i] = 0;
    }

    emit leaving(1);    // 1: leaving game view
}

void GameView::handleNewGameButton() {
    qDebug() << "New Game Button pressed";

    // clear the grid
    for(int i = 0; i < 9; i++) {
        currentSlotSymbols[i] = 0;
    }
    updateGrid();

    // player who played second in the previous game starts the new game
    playerTurn = 3 - lastGameStarter;
    lastGameStarter = playerTurn;

    // reinitialize game variables
    winner = 0;
    gameOver = false;
 }

void GameView::slotClicked(int xPos, int yPos) {
//    qDebug()<< "label clicked at " << xPos + 60 << ", " << yPos + 60;
    int slotIndex = ((yPos - 291) / 120) * 3 + (xPos - 85) / 120;

    // If not gameover and clicked slot empty, then change slot value and player turn
    if( !gameOver && currentSlotSymbols[slotIndex] == 0) {
        currentSlotSymbols[slotIndex] = playerTurn;

        playerTurn = 3 - playerTurn;
        //    qDebug() << "slot with index" << slotIndex << " changed to " << currentSlotSymbols[slotIndex] << " and player to " << playerTurn;
    }
}
