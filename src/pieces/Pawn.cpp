#include "Pawn.h"

Pawn::Pawn(bool isWhite) : ChessPiece(isWhite) {
    hasMoved = false;
}

unordered_map<int, int> Pawn::getMoves(vector<vector<ChessPiece*>>* board,
        int row, int col) const {
    unordered_map<int, int> moves;
    int shift = 1;
    if (isWhite()) {
        shift = -shift;
    }
    //foward moves
    if ((*board)[row + shift][col] == nullptr) {
        moves[row + shift] = col;
    }
    if ((*board)[row + shift * 2][col] == nullptr && !hasMoved) {
        moves[row + shift * 2] = col;
    }
    //diagonal captures
    if (!isOutOfBounds(row, col - 1)) {
        if ((*board)[row + shift][col - 1] == nullptr) {
            moves[row + shift] = col - 1;
        }
    }
    if (!isOutOfBounds(row, col + 1)) {
        if ((*board)[row + shift][col + 1] == nullptr) {
            moves[row + shift] = col + 1;
        }
    }
    return moves;
}

string Pawn::getName() const {
    return "Pawn";
}

void Pawn::setMoved() {
    hasMoved = true;
}