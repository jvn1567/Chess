/**
 * @file ChessAI.h
 * @author John Nguyen (https://github.com/jvn1567)
 * @brief This file implements a chess AI, which uses a minimax algorithm.
 * @version 0.1
 * @date 2021-11-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _ChessAI_h
#define _ChessAI_h

#include "BoardManager.h"
using namespace std;

/**
 * @brief This class is a node for a move tree, and contains the start tile, end
 * tile, and move value for this node's move, and a vector containing all the
 * moves that can be made next turn.
 * 
 */
struct MinimaxNode {
    Tile start;
    Tile end;
    int value;
    vector<MinimaxNode*> next;
    MinimaxNode(const Tile& start = Tile(), const Tile& end = Tile(), int value = 0);
};

/**
 * @brief This class contains a chess AI, which selects moves using
 * a minimax algorithm.
 * 
 */
class ChessAI {
private:
    static const int TARGET_DEPTH = 4;
    BoardManager* board;

    /**
     * Creates a tree of moves and uses alpha-beta pruning to reduce the number
     * of moves searched. The tree will self-delete all moves when calculations
     * finish, excluding the top layer of moves that must be selected from to
     * make this turn.
     */
    int minimax(MinimaxNode*& node, int alpha, int beta, int depth, bool isWhite);

    /**
     * Simulates a move from the passed-in node's data, then continues the
     * recursion by calling minmax again. All changes to the board are then
     * undone after the move value limit is returned from minimax.
     */
    int simulateMove(MinimaxNode*& node, int alpha, int beta, int depth, bool isWhite);

    /**
     * Deletes all child nodes from the passed-in node if its depth is greater
     * than the first move layer (depth 0).
     */
    void clearChildren(MinimaxNode*& node, int depth);

public:
    /**
     * @brief Creates a ChessAI using the board state stored in the passed-in
     * BoardManager object.
     * 
     * @param board the BoardManager object handling the chess board and game state
     */
    ChessAI(BoardManager* board);
    void makeMove();
};

#endif