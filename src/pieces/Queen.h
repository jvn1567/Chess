#ifndef _Queen_h
#define _Queen_h

#include "ChessPiece.h"
using namespace std;

class Queen : public ChessPiece {
private:
public:
    Queen(bool isWhite);
    unordered_map<int, int> getMoves() const override;
    string getName() const override;
};

#endif