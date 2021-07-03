#ifndef _Knight_h
#define _Knight_h

#include "ChessPiece.h"
using namespace std;

class Knight : public ChessPiece {
private:
    void addTile(unordered_map<int, int>& moves, int row, int col) const;
public:
    Knight(bool isWhite);
    unordered_map<int, int> getMoves(vector<vector<ChessPiece*>>* board,
            int row, int col) const override;
    string getName() const override;
};

#endif