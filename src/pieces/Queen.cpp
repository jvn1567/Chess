#include "Queen.h"

Queen::Queen(bool isWhite) : ChessPiece(isWhite) {}

unordered_set<Tile, HashTile> Queen::getMoves(const vector<vector<ChessPiece*>>& board,
        int row, int col) const {
    unordered_set<Tile, HashTile> moves;
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

string Queen::getName() const {
    return "Queen";
}

int Queen::getValue() const {
    return isWhite() ? 9 : -9;
}