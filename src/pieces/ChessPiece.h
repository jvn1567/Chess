#ifndef _ChessPiece_h
#define _ChessPiece_h

#include <unordered_set>
#include <vector>
#include "Tile.h"
using namespace std;

class ChessPiece {
private:
    bool white;
public:
    ChessPiece(bool white);
    virtual unordered_set<Tile, HashTile> getMoves(vector<vector<ChessPiece*>>* board,
            int row, int col) const;
    virtual string getName() const;
    bool isWhite() const;
    void getLine(vector<vector<ChessPiece*>>* board, int row, int col,
            unordered_set<Tile, HashTile>& moves, int rowShift, int colShift) const;
};

#endif