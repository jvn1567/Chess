#ifndef _ChessPiece_h
#define _ChessPiece_h

#include <unordered_map>
#include <vector>
using namespace std;

class ChessPiece {
private:
    bool white;
public:
    ChessPiece(bool white);
    virtual unordered_map<int, int> getMoves(vector<vector<ChessPiece*>>* board,
            int row, int col) const;
    virtual string getName() const;
    bool isWhite() const;
    bool isOutOfBounds(int row, int col) const;
    void getLine(vector<vector<ChessPiece*>>* board, int pRow, int pCol,
            unordered_map<int, int>& moves, int rowShift, int colShift) const;
};

#endif