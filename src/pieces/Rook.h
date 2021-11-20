#ifndef _Rook_h
#define _Rook_h

#include "ChessPiece.h"
using namespace std;

class Rook : public ChessPiece {
private:
public:
    Rook(bool isWhite);
    unordered_set<Tile, HashTile> getMoves(const vector<vector<ChessPiece*>>& board,
            int row, int col) const;
    string getName() const;
    int getValue() const;
};

#endif