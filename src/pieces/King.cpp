#include "King.h"

King::King(bool isWhite) : ChessPiece(isWhite) {}

unordered_set<Tile, HashTile> King::getMoves(vector<vector<ChessPiece*>>* board,
        int row, int col) const {
    (void)board;
    unordered_set<Tile, HashTile> moves;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int nRow = row + i;
            int nCol = col + j;
            if (!isOutOfBounds(nRow, nCol) && !(i == 0 && j == 0)) {
                Tile movableTile(nRow, nCol);
                moves.insert(movableTile);
            }
        }
    }
    return moves;
}

string King::getName() const {
    return "King";
}