#ifndef _ChessAI_h
#define _ChessAI_h

#include "ChessBoard.h"
using namespace std;

class ChessAI {
private:
    ChessBoard* board;
    vector<Tile> start;
    vector<Tile> end;
    vector<int> weight;
    void weighMoves(int row, int col);
    void filterMoves();
public:
    ChessAI(ChessBoard* board);
    void makeMove();
};

#endif