#include "Bishop.h"

Bishop::Bishop(bool isWhite) : ChessPiece(isWhite) {}

unordered_set<Tile, HashTile> Bishop::getMoves(vector<vector<ChessPiece*>>* board,
        int row, int col) const {
    unordered_set<Tile, HashTile> moves;
    getLine(board, row, col, moves, 1, 1); //NE
    getLine(board, row, col, moves, -1, 1); //SE
    getLine(board, row, col, moves, -1, -1); //SW
    getLine(board, row, col, moves, 1, -1); //NW
    return moves;
}

string Bishop::getName() const {
    return "Bishop";
}

int Bishop::getValue() const {
    return isWhite() ? 3 : -3;
}