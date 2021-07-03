#ifndef _ChessPiece_h
#define _ChessPiece_h

#include <unordered_map>
using namespace std;

class ChessPiece {
private:
public:
    unordered_map<int, int> getMoves() const;
};

#endif