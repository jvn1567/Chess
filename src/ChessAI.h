#ifndef _ChessAI_h
#define _ChessAI_h

#include "BoardManager.h"
using namespace std;

// struct MinimaxNode {
//     Tile start;
//     Tile end;
//     int value;
//     vector<MinimaxNode*> next;
//     MinimaxNode(const Tile& start = Tile(), const Tile& end = Tile(), int value = 0);
// };

// class ChessAI {
// private:
//     BoardManager* board;
//     int targetDepth;
//     int minimax(MinimaxNode*& node, int min, int max, int depth, bool isWhite);
//     int simulateMove(MinimaxNode*& node, int min, int max, int depth, bool isWhite);
// public:
//     ChessAI(BoardManager* board);
//     void makeMove();
// };

// #endif








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