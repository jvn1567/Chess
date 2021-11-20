#include <cmath>
#include "ChessPiece.h"

ChessPiece::ChessPiece(bool white) {
    this->white = white;
}

bool ChessPiece::isWhite() const {
    return white;
}

bool ChessPiece::isEnemy(ChessPiece* other) const {
    return other->isWhite() ^ isWhite();
}

void ChessPiece::getLine(const vector<vector<ChessPiece*>>& board, int row, int col,
        unordered_set<Tile, HashTile>& moves, int rowShift, int colShift) const {
    bool wasBlocked = false;
    bool offBoard = false;
    while (!offBoard && !wasBlocked) {
        row += rowShift;
        col += colShift;
        offBoard = isOutOfBounds(row, col);
        if (!offBoard) {
            ChessPiece* other = board[row][col];
            if (other == nullptr || isEnemy(other)) {
                Tile movableTile(row, col);
                moves.insert(movableTile);
            }
            wasBlocked = other != nullptr;
        }
    }
}

ChessPiece::~ChessPiece() {}

// largest value first, first alphabetical name if tied
bool PieceCompare::operator()(const ChessPiece* left, const ChessPiece* right) {
    if (abs(left->getValue()) == abs(right->getValue())) {
        return left->getName() > right->getName();
    } else {
        return abs(left->getValue()) < abs(right->getValue());
    }
}