#ifndef _ChessAI_h
#define _ChessAI_h

#include "BoardManager.h"
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
    BoardManager* board;
    int targetDepth;
    vector<Tile> start;
    vector<Tile> end;
    vector<int> weight;
    bool selectMove(int row, int col, int depth, ValueTree* weights, bool isWhite);
    void weighBranch(int row, int col, Tile tile, ChessPiece* piece,
            int depth, ValueTree* weights);
    int minimax(ValueTree* weights, bool minimize);
    void filterMoves();

public:
    ChessAI(BoardManager* board);
    void makeMove();
};

#endif