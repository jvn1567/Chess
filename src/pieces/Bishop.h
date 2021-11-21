/**
 * @file Bishop.h
 * @author John Nguyen (https://github.com/jvn1567)
 * @brief This class represents a Bishop chess piece.
 * @version 0.1
 * @date 2021-11-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _Bishop_h
#define _Bishop_h

#include "ChessPiece.h"
using namespace std;

class Bishop : public ChessPiece {
public:
    /**
     * @brief Constructor for a Bishop chess piece.
     * 
     * @param isWhite true if the piece is white, false if black
     */
    Bishop(bool isWhite);

    /**
     * @brief Returns the tiles that this piece can move to.
     * 
     * @param board the 2D vector containing the board state
     * @param row the row this piece is currently at on the board
     * @param col the column this piece is currently at on the board
     * @return unordered_set<Tile, HashTile> a set of tiles the piece can move to
     */
    unordered_set<Tile, HashTile> getMoves(const vector<vector<ChessPiece*>>& board,
            int row, int col) const;

    /**
     * @brief Returns a string representing the piece.
     * 
     * @return the string "Bishop"
     */
    string getName() const;

    /**
     * @brief Returns the value of this piece.
     * 
     * @return the value of this piece
     */
    int getValue() const;
};

#endif