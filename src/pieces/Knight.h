#ifndef _Knight_h
#define _Knight_h

#include "ChessPiece.h"
using namespace std;

class Knight : public ChessPiece {
private:
    void addTile(unordered_set<Tile*>& moves, int row, int col) const;
public:
    Knight(bool isWhite);
    unordered_set<Tile*> getMoves(vector<vector<ChessPiece*>>* board,
            int row, int col) const override;
    string getName() const override;
};

#endif