#ifndef _Rook_h
#define _Rook_h

#include "ChessPiece.h"
using namespace std;

class Rook : public ChessPiece {
private:
public:
    Rook(bool isWhite);
    unordered_map<int, int> getMoves(vector<vector<ChessPiece*>>* board,
            int row, int col) const override;
    string getName() const override;
};

#endif