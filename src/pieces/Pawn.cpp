#include "Pawn.h"
#include "Queen.h"

Pawn::Pawn(bool isWhite) : ChessPiece(isWhite) {
    hasMoved = false;
}

// pawns promote, so off-board not checked
unordered_set<Tile, HashTile> Pawn::getMoves(const vector<vector<ChessPiece*>>& board,
        int row, int col) const {
    unordered_set<Tile, HashTile> moves;
    // simplified handler for simulated queen promotes
    if (row == 0 || row == 7) {
        getLine(board, row, col, moves, 1, 0); //N
        getLine(board, row, col, moves, 0, 1); //E
        getLine(board, row, col, moves, -1, 0); //S
        getLine(board, row, col, moves, 0, -1); //W
        getLine(board, row, col, moves, 1, 1); //NE
        getLine(board, row, col, moves, -1, 1); //SE
        getLine(board, row, col, moves, -1, -1); //SW
        getLine(board, row, col, moves, 1, -1); //NW
        return moves;
    }
     // handle north/south direction
    int shift = 1;
    if (isWhite()) {
        shift = -shift;
    }
    // foward moves
    if (board[row + shift][col] == nullptr) {
        Tile movableTile(row + shift, col);
        moves.insert(movableTile);
        if (!hasMoved && board[row + shift * 2][col] == nullptr ) {
            Tile movableTile(row + shift * 2, col);
            moves.insert(movableTile);
        }
    }
    // diagonal captures
    if (!isOutOfBounds(row + shift, col - 1)) {
        ChessPiece* other = board[row + shift][col - 1];
        if (other != nullptr && isEnemy(other)) {
            Tile movableTile(row + shift, col - 1);
            moves.insert(movableTile);
        }
    }
    if (!isOutOfBounds(row + shift, col + 1)) {
        ChessPiece* other = board[row + shift][col + 1];
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

void Pawn::setMoved(bool hasMoved) {
    this->hasMoved = hasMoved;
}

bool Pawn::getHasMoved() const {
    return hasMoved;
}