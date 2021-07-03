#ifndef _ChessPiece_h
#define _ChessPiece_h

#include <unordered_map>
#include <vector>
using namespace std;

class ChessPiece {
private:
    bool isWhite;
public:
    ChessPiece(bool isWhite);
    virtual unordered_map<int, int> getMoves() const;
    virtual string getName() const;
};

#endif