/**
 * @file King.cpp
 * @author John Nguyen (https://github.com/jvn1567)
 * @brief This file implements the King class.
 * @version 0.1
 * @date 2021-11-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "King.h"

King::King(bool isWhite) : ChessPiece(isWhite) {}

unordered_set<Tile, HashTile> King::getMoves(const vector<vector<ChessPiece*>>& board,
        int row, int col) const {
    (void)board;
    unordered_set<Tile, HashTile> moves;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int nRow = row + i;
            int nCol = col + j;
            if (!isOutOfBounds(nRow, nCol) && !(i == 0 && j == 0)) {
                ChessPiece* other = board[nRow][nCol];
                if (other == nullptr || isEnemy(other)) {
                    Tile movableTile(nRow, nCol);
                    moves.insert(movableTile);
                }
            }
        }
    }
    return moves;
}

string King::getName() const {
    return "King";
}

int King::getValue() const {
    return isWhite() ? 100 : -100;
}