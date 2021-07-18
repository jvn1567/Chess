#ifndef _ChessAI_h
#define _ChessAI_h

#include "ChessBoard.h"
using namespace std;

struct ValueTree {
    int value;
    vector<ValueTree*> next;
    ValueTree() {
        value = 0;
    }
};

class ChessAI {
private:
    ChessBoard* board;
    int targetDepth;
    vector<Tile> start;
    vector<Tile> end;
    vector<int> weight;

    void weighMoves(int row, int col);
    void filterMoves();

    int selectMove(int row, int col, int depth, ValueTree* weights);
    void weighBranch(int row, int col, Tile tile, ChessPiece* piece,
            int depth, ValueTree* weights);
    void collapseTree(ValueTree* weights, int depth);

public:
    ChessAI(ChessBoard* board);
    void makeMove();
};

#endif