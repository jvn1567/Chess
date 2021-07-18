#ifndef _Pawn_h
#define _Pawn_h

#include "ChessPiece.h"
using namespace std;

class Pawn : public ChessPiece {
private:
    bool hasMoved;
public:
    Pawn(bool isWhite);
    unordered_set<Tile, HashTile> getMoves(vector<vector<ChessPiece*>>* board,
            int row, int col) const override;
    string getName() const override;
    int getValue() const override;
    void setMoved(bool hasMoved);
};

#endif