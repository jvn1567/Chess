#include "Pawn.h"

Pawn::Pawn(bool isWhite) : ChessPiece(isWhite) {
    hasMoved = false;
}

unordered_set<Tile, HashTile> Pawn::getMoves(vector<vector<ChessPiece*>>* board,
        int row, int col) const {
    unordered_set<Tile, HashTile> moves;
    int shift = 1;
    if (isWhite()) {
        shift = -shift;
    }
    //returns if pawn is at the enemy end of the board   //HANDLE PROMOTE LATER
    if (isOutOfBounds(row + shift, 0)) {
        return moves;
    }
    //foward moves
    if ((*board)[row + shift][col] == nullptr) {
        Tile movableTile(row + shift, col);
        moves.insert(movableTile);
    }
    if (!hasMoved && (*board)[row + shift * 2][col] == nullptr ) {
        Tile movableTile(row + shift * 2, col);
        moves.insert(movableTile);
    }
    //diagonal captures
    if (!isOutOfBounds(row + shift, col - 1)) {
        if ((*board)[row + shift][col - 1] != nullptr) {
            Tile movableTile(row + shift, col - 1);
            moves.insert(movableTile);
        }
    }
    if (!isOutOfBounds(row + shift, col + 1)) {
        if ((*board)[row + shift][col + 1] != nullptr) {
            Tile movableTile(row + shift, col + 1);
            moves.insert(movableTile);
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