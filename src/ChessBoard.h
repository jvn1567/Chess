#ifndef _ChessBoard_h
#define _ChessBoard_h

#include <vector>
#include "ChessPiece.h"
#include "Tile.h"
using namespace std;

class ChessBoard {
private:
    vector<vector<ChessPiece*>>* board;
    void setBackRow(int row, bool isWhite);
public:
    ChessBoard();
    ChessBoard(const ChessBoard& oldBoard);
    void setStartingBoard();
    unordered_set<Tile, HashTile> getMoves(int row, int col) const;
    ChessPiece* getPiece(int row, int col) const;
    void setPiece(ChessPiece* piece, int row, int col);
};

#endif