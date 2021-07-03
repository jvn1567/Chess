#include "ChessPiece.h"
#include "ChessBoard.h"
#include "King.h"
#include "Queen.h"
#include <iostream>

int main() {
    //testing
    ChessPiece* queen = new Queen(true);
    cout << queen->getName() << endl;
    ChessBoard* board = new ChessBoard();
    board->setStartingBoard();
    ChessPiece* king = board->getPiece(0, 4);
    cout << king->getName() << endl;
    ChessPiece* pawn = board->getPiece(1, 4);
    cout << pawn->getName() << endl;
    return 0;
}