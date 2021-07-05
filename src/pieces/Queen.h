#ifndef _Queen_h
#define _Queen_h

#include "ChessPiece.h"
using namespace std;

class Queen : public ChessPiece {
private:
public:
    Queen(bool isWhite);
    unordered_set<Tile*> getMoves(vector<vector<ChessPiece*>>* board,
            int row, int col) const override;
    string getName() const override;
};

#endif