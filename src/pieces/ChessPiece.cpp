#include "ChessPiece.h"

ChessPiece::ChessPiece(bool white) {
    this->white = white;
}

unordered_map<int, int> ChessPiece::getMoves(vector<vector<ChessPiece*>>* board,
        int row, int col) const {
    (void)board;
    (void)row;
    (void)col;
    unordered_map<int, int> empty;
    return empty;
}

string ChessPiece::getName() const {
    return "ChessPiece";
}

bool ChessPiece::isWhite() const {
    return white;
}

bool ChessPiece::isOutOfBounds(int row, int col) const {
    return row < 0 || col < 0 || row >= 8 || col >= 8;
}


void ChessPiece::getLine(vector<vector<ChessPiece*>>* board, int pRow, int pCol,
        unordered_map<int, int>& moves, int rowShift, int colShift) const {
    int row = pRow + rowShift;
    int col = pCol + colShift;
    bool isBlocked = false;
    while (!isOutOfBounds(row, col) && !isBlocked) {
        moves[row] = col;
        isBlocked = (*board)[row][col] == nullptr;
        row += rowShift;
        col += colShift;
    }
}