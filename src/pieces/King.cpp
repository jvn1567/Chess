#include "King.h"

King::King(bool isWhite) : ChessPiece(isWhite) {}

unordered_map<int, int> King::getMoves(vector<vector<ChessPiece*>>* board,
        int row, int col) const {
    (void)board;
    unordered_map<int, int> empty;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int nRow = row + i;
            int nCol = col + i;
            if (!isOutOfBounds(nRow, nCol) && !(i == 0 && j == 0)) {
                empty[nRow] = nCol;
            }
        }
    }
    return empty;
}

string King::getName() const {
    return "King";
}