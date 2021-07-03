#ifndef _Bishop_h
#define _Bishop_h

#include "ChessPiece.h"
using namespace std;

class Bishop : public ChessPiece {
private:
public:
    Bishop(bool isWhite);
    unordered_map<int, int> getMoves() const override;
    string getName() const override;
};

#endif