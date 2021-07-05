#include "ChessPiece.h"

ChessPiece::ChessPiece(bool white) {
    this->white = white;
}

unordered_set<Tile*> ChessPiece::getMoves(vector<vector<ChessPiece*>>* board,
        int row, int col) const {
    (void)board;
    (void)row;
    (void)col;
    unordered_set<Tile*> moves;
    return moves;
}

string ChessPiece::getName() const {
    return "ChessPiece";
}

bool ChessPiece::isWhite() const {
    return white;
}


void ChessPiece::getLine(vector<vector<ChessPiece*>>* board, int row, int col,
        unordered_set<Tile*>& moves, int rowShift, int colShift) const {
    bool wasBlocked = false;
    bool offBoard = false;
    while (!offBoard && !wasBlocked) {
        row += rowShift;
        col += colShift;
        if (isOutOfBounds(row, col)) {
            offBoard = true;
        } else {
            Tile* movableTile = new Tile(row, col);
            moves.insert(movableTile);
            wasBlocked = (*board)[row][col] != nullptr;
        }
    }
}