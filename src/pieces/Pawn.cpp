#include "Pawn.h"

Pawn::Pawn(bool isWhite) : ChessPiece(isWhite) {
    hasMoved = false;
}

//pawns promote, so off-board not checked
unordered_set<Tile, HashTile> Pawn::getMoves(vector<vector<ChessPiece*>>* board,
        int row, int col) const {
    unordered_set<Tile, HashTile> moves;
    //handle north/south direction
    int shift = 1;
    if (isWhite()) {
        shift = -shift;
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
        ChessPiece* other = (*board)[row + shift][col - 1];
        if (other != nullptr && isEnemy(other)) {
            Tile movableTile(row + shift, col - 1);
            moves.insert(movableTile);
        }
    }
    if (!isOutOfBounds(row + shift, col + 1)) {
        ChessPiece* other = (*board)[row + shift][col + 1];
        if (other != nullptr && isEnemy(other)) {
            Tile movableTile(row + shift, col + 1);
            moves.insert(movableTile);
        }
    }
    return moves;
}

string Pawn::getName() const {
    return "Pawn";
}

int Pawn::getValue() const {
    return isWhite() ? 1 : -1;
}

void Pawn::setMoved() {
    hasMoved = true;
}