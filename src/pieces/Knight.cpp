#include "Knight.h"

Knight::Knight(bool isWhite) : ChessPiece(isWhite) {}

unordered_set<Tile*> Knight::getMoves(vector<vector<ChessPiece*>>* board,
        int row, int col) const {
    (void)board;
    unordered_set<Tile*> moves;
    vector<int> shift = {-2, -1, 1, 2};
    for (int rowShift = 0; rowShift < shift.size(); rowShift++) {
        for (int colShift = 0; colShift < shift.size(); colShift++) {
            if (abs(shift[rowShift]) != abs(shift[colShift])) {
                addTile(moves, row + shift[rowShift], col + shift[colShift]);
            }
        }
    }
    return moves;
}

string Knight::getName() const {
    return "Knight";
}

void Knight::addTile(unordered_set<Tile*>& moves, int row, int col) const {
    if (!isOutOfBounds(row, col)) {
        Tile* movableTile = new Tile(row, col);
        moves.insert(movableTile);
    }
}