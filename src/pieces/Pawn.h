#ifndef _Pawn_h
#define _Pawn_h

#include "ChessPiece.h"
using namespace std;

class Pawn : public ChessPiece {
private:
    bool hasMoved;
public:
    Pawn(bool isWhite);
    unordered_set<Tile, HashTile> getMoves(const vector<vector<ChessPiece*>>& board,
            int row, int col) const;
    string getName() const;
    int getValue() const;
    void setMoved(bool hasMoved);
    bool getHasMoved() const;
};

#endif