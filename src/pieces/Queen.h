#ifndef _Queen_h
#define _Queen_h

#include "ChessPiece.h"
using namespace std;

class Queen : public ChessPiece {
private:
public:
    Queen(bool isWhite);
    unordered_set<Tile, HashTile> getMoves(const vector<vector<ChessPiece*>>& board,
            int row, int col) const;
    string getName() const;
    int getValue() const;
};

#endif