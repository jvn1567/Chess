#ifndef _King_h
#define _King_h

#include "ChessPiece.h"
using namespace std;

class King : public ChessPiece {
private:
public:
    King(bool isWhite);
    unordered_set<Tile, HashTile> getMoves(const vector<vector<ChessPiece*>>& board,
            int row, int col) const override;
    string getName() const override;
    int getValue() const override;
};

#endif