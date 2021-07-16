#include "ChessPiece.h"

ChessPiece::ChessPiece(bool white) {
    this->white = white;
}

unordered_set<Tile, HashTile> ChessPiece::getMoves(vector<vector<ChessPiece*>>* board,
        int row, int col) const {
    (void)board;
    (void)row;
    (void)col;
    unordered_set<Tile, HashTile> moves;
    return moves;
}

string ChessPiece::getName() const {
    return "ChessPiece";
}

int ChessPiece::getValue() const {
    return 0;
}

bool ChessPiece::isWhite() const {
    return white;
}

bool ChessPiece::isEnemy(ChessPiece* other) const {
    return other->isWhite() ^ isWhite();
}

void ChessPiece::getLine(vector<vector<ChessPiece*>>* board, int row, int col,
        unordered_set<Tile, HashTile>& moves, int rowShift, int colShift) const {
    bool wasBlocked = false;
    bool offBoard = false;
    while (!offBoard && !wasBlocked) {
        row += rowShift;
        col += colShift;
        offBoard = isOutOfBounds(row, col);
        if (!offBoard) {
            ChessPiece* other = (*board)[row][col];
            if (other == nullptr || isEnemy(other)) {
                Tile movableTile(row, col);
                moves.insert(movableTile);
            }
            wasBlocked = other != nullptr;
        }
    }
}