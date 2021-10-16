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
    virtual unordered_set<Tile, HashTile> getMoves(const vector<vector<ChessPiece*>>& board,
            int row, int col) const = 0;
    virtual string getName() const;
    virtual int getValue() const;
    bool isWhite() const;
    bool isEnemy(ChessPiece* other) const;
    void getLine(const vector<vector<ChessPiece*>>& board, int row, int col,
            unordered_set<Tile, HashTile>& moves, int rowShift, int colShift) const;
    virtual ~ChessPiece();
};

#endif