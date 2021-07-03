#include "Knight.h"

Knight::Knight(bool isWhite) : ChessPiece(isWhite) {}

unordered_map<int, int> Knight::getMoves(vector<vector<ChessPiece*>>* board,
        int row, int col) const {
    (void)board;
    unordered_map<int, int> moves;
    vector<int> shift = {-2, -1, 1, 2};
    for (int rowShift = 0; rowShift < shift.size(); rowShift++) {
        for (int colShift = 0; colShift < shift.size(); colShift++) {
            addTile(moves, row + rowShift, col + colShift);
        }
    }
    return moves;
}

string Knight::getName() const {
    return "Knight";
}

void Knight::addTile(unordered_map<int, int>& moves, int row, int col) const {
    if (!isOutOfBounds(row, col) && abs(row) != abs(col)) {
        moves[row] = col;
    }
}