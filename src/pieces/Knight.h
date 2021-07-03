#ifndef _Knight_h
#define _Knight_h

#include "ChessPiece.h"
using namespace std;

class Knight : public ChessPiece {
private:
public:
    Knight(bool isWhite);
    unordered_map<int, int> getMoves() const override;
    string getName() const override;
};

#endif