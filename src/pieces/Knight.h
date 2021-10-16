#ifndef _Knight_h
#define _Knight_h

#include "ChessPiece.h"
using namespace std;

class Knight : public ChessPiece {
private:
    void addTile(unordered_set<Tile, HashTile>& moves, int row, int col,
            const vector<vector<ChessPiece*>>& board) const;
public:
    Knight(bool isWhite);
    unordered_set<Tile, HashTile> getMoves(const vector<vector<ChessPiece*>>& board,
            int row, int col) const override;
    string getName() const override;
    int getValue() const override;
};

#endif