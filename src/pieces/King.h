/**
 * @file King.h
 * @author John Nguyen (https://github.com/jvn1567)
 * @brief This class represents a King chess piece.
 * @version 0.1
 * @date 2021-11-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _King_h
#define _King_h

#include "ChessPiece.h"
using namespace std;

class King : public ChessPiece {
public:
    /**
     * @brief Constructor for a King object.
     * 
     * @param isWhite true if white, false if black
     */
    King(bool isWhite);

    /**
     * @brief Returns a set containing the tiles this piece can move to.
     * 
     * @param board a 2D vector representing the board state
     * @param row the row this piece is at on the board
     * @param col the column this piece is at on the board
     * @return an unordered set of tiles containing the movable tiles
     */
    unordered_set<Tile, HashTile> getMoves(const vector<vector<ChessPiece*>>& board,
            int row, int col) const;

    /**
     * @brief Returns the name of this piece.
     * 
     * @return string "King"
     */
    string getName() const;

    /**
     * @brief Returns the value of this piece.
     * 
     * @return int the piece value
     */
    int getValue() const;
};

#endif