#include "Rook.h"

Rook::Rook(bool isWhite) : ChessPiece(isWhite) {}

unordered_set<Tile, HashTile> Rook::getMoves(vector<vector<ChessPiece*>>* board,
        int row, int col) const {
    unordered_set<Tile, HashTile> moves;
    getLine(board, row, col, moves, 1, 0); //N
    getLine(board, row, col, moves, 0, 1); //E
    getLine(board, row, col, moves, -1, 0); //S
    getLine(board, row, col, moves, 0, -1); //W
    return moves;
}

string Rook::getName() const {
    return "Rook";
}

int Rook::getValue() const {
    return isWhite() ? 5 : -5;
}