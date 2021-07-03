#ifndef _ChessBoard_h
#define _ChessBoard_h

#include <vector>
#include <unordered_map>
#include "ChessPiece.h"
using namespace std;

class ChessBoard {
private:
    vector<vector<ChessPiece*>>* board;
    void setBackRow(int row, bool isWhite);
public:
    ChessBoard();
    void setStartingBoard();
    unordered_map<int, int> getMoves(int row, int col) const;
    ChessPiece* getPiece(int row, int col) const;
    void setPiece(ChessPiece* piece, int row, int col);
};

#endif