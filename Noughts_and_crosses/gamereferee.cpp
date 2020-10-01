#include "gamereferee.h"

GameReferee::GameReferee()
{

}

int GameReferee::checkForWinnerOrDraw(int gameboardSlots[9]) {

    int winner = 0; // 1: no winner, 1: cross wins, 2: nought wins, 3: draw

    // Check if board is full
    bool isBoardFull = true;
    for(int i = 0; i < 9; i++) {

        if(gameboardSlots[i] == 0) {

            isBoardFull = false;
            break;

        }
    }

    //Check if there is a winner
    if( gameboardSlots[0] != 0 &&
        ((gameboardSlots[0] == gameboardSlots[1] && gameboardSlots[1] == gameboardSlots[2]) ||
        (gameboardSlots[0] == gameboardSlots[3] && gameboardSlots[3] == gameboardSlots[6]) ||
        (gameboardSlots[0] == gameboardSlots[4] && gameboardSlots[4] == gameboardSlots[8]))) {

        winner = gameboardSlots[0];

    } else if ( gameboardSlots[4] != 0 &&
                ((gameboardSlots[1] == gameboardSlots[4] && gameboardSlots[4] == gameboardSlots[7]) ||
                (gameboardSlots[3] == gameboardSlots[4] && gameboardSlots[4] == gameboardSlots[5]) ||
                (gameboardSlots[2] == gameboardSlots[4] && gameboardSlots[4] == gameboardSlots[6]))) {

        winner = gameboardSlots[4];

    } else if ( gameboardSlots[8] != 0 &&
                ((gameboardSlots[2] == gameboardSlots[5] && gameboardSlots[5] == gameboardSlots[8]) ||
                (gameboardSlots[6] == gameboardSlots[7] && gameboardSlots[7] == gameboardSlots[8]))) {

        winner = gameboardSlots[8];

    } else if (isBoardFull) {

        winner = 3; // draw

    }

    return winner;
}
