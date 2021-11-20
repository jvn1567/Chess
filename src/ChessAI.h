#ifndef _ChessAI_h
#define _ChessAI_h

#include "BoardManager.h"
using namespace std;

struct MinimaxNode {
    Tile start;
    Tile end;
    int value;
    vector<MinimaxNode*> next;
    MinimaxNode(const Tile& start = Tile(), const Tile& end = Tile(), int value = 0);
};

class ChessAI {
private:
    BoardManager* board;
    int targetDepth;
    int minimax(MinimaxNode*& node, int alpha, int beta, int depth, bool isWhite);
    int simulateMove(MinimaxNode*& node, int alpha, int beta, int depth, bool isWhite);
    void clearChildren(MinimaxNode*& node, int depth);
public:
    ChessAI(BoardManager* board);
    void makeMove();
};

#endif