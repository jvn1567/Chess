/**
 * @file ChessPiece.h
 * @author John Nguyen (https://github.com/jvn1567)
 * @brief This class provides functionality for specific chess
 * piece objects.
 * @version 0.1
 * @date 2021-11-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _ChessPiece_h
#define _ChessPiece_h

#include <unordered_set>
#include <vector>
#include <queue>
#include "Tile.h"
using namespace std;

class ChessPiece {
private:
    bool white;
protected:
    /**
     * Adds tiles to the passed-in set of tiles that the chess piece
     * at the passed-in row and column can move to that fall along the straight
     * horizontal/vertical or diagonal line specified by rowShift and colShift.
     * 
     * rowShift and colShift are both between -1 and 1, inclusive
     */
    void getLine(const vector<vector<ChessPiece*>>& board, int row, int col,
            unordered_set<Tile, HashTile>& moves, int rowShift, int colShift) const;

    /**
     * Returns whether the passed-in piece belongs to the enemy of this one.
     */
    bool isEnemy(ChessPiece* other) const;
    
    /**
     * Constructor for a ChessPiece object.
     */
    ChessPiece(bool white);
public:
    /**
     * @brief Returns a set of tiles this piece can move to.
     * 
     * @param board a 2D vector representing the board state
     * @param row the row this piece is at on the board
     * @param col the column this piece is at on the board
     * @return an unordered set of tiles this piece can move to
     */
    virtual unordered_set<Tile, HashTile> getMoves(const vector<vector<ChessPiece*>>& board,
            int row, int col) const = 0;

    /**
     * @brief Returns the name of this piece's type.
     * 
     * @return a string representing the type of piece this is
     */
    virtual string getName() const = 0;

    /**
     * @brief Returns the value of this piece.
     * 
     * @return int the value of this piece
     */
    virtual int getValue() const = 0;

    /**
     * @brief Returns whether this piece belongs to the white player.
     * 
     * @return true if white
     * @return false if black
     */
    bool isWhite() const;
};

/**
 * @brief Allows pieces to be compared for use in a priority queue.
 * 
 */
struct PieceCompare {
    bool operator()(const ChessPiece* left, const ChessPiece* right);
};

typedef priority_queue<ChessPiece*, vector<ChessPiece*>, PieceCompare> priority_queue_piece;

#endif