/**
 * @file Knight.cpp
 * @author John Nguyen (https://github.com/jvn1567)
 * @brief This file implements the Knight class.
 * @version 0.1
 * @date 2021-11-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Knight.h"

Knight::Knight(bool isWhite) : ChessPiece(isWhite) {}

unordered_set<Tile, HashTile> Knight::getMoves(const vector<vector<ChessPiece*>>& board,
        int row, int col) const {
    (void)board;
    unordered_set<Tile, HashTile> moves;
    vector<int> shift = {-2, -1, 1, 2};
    for (int rowShift = 0; rowShift < shift.size(); rowShift++) {
        for (int colShift = 0; colShift < shift.size(); colShift++) {
            if (abs(shift[rowShift]) != abs(shift[colShift])) {
                addTile(moves, row + shift[rowShift], col + shift[colShift], board);
            }
        }
    }
    return moves;
}

string Knight::getName() const {
    return "Knight";
}

int Knight::getValue() const {
    return isWhite() ? 3 : -3;
}

void Knight::addTile(unordered_set<Tile, HashTile>& moves, int row, int col,
        const vector<vector<ChessPiece*>>& board) const {
    if (!isOutOfBounds(row, col)) {
        ChessPiece* other = board[row][col];
        if (other == nullptr || isEnemy(other)) {
            Tile movableTile(row, col);
            moves.insert(movableTile);
        }
    }
}