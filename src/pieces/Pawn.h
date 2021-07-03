#ifndef _Pawn_h
#define _Pawn_h

#include "ChessPiece.h"
using namespace std;

class Pawn : public ChessPiece {
private:
    bool hasMoved;
public:
    Pawn(bool isWhite);
    unordered_map<int, int> getMoves() const override;
    string getName() const override;
    void setMoved();
};

#endif