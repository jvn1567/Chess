/**
 * @file Knight.h
 * @author John Nguyen (https://github.com/jvn1567)
 * @brief This class represents a Knight chess piece.
 * @version 0.1
 * @date 2021-11-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _Knight_h
#define _Knight_h

#include "ChessPiece.h"
using namespace std;

class Knight : public ChessPiece {
private:
    /**
     * Adds the tile at the passed-in row and column to the
     * passed-in unordered set if it is in-bounds of the board and the
     * Knight can legally move to it.
     */
    void addTile(unordered_set<Tile, HashTile>& moves, int row, int col,
            const vector<vector<ChessPiece*>>& board) const;
public:
    /**
     * @brief Constructor for a Knight object.
     * 
     * @param isWhite true if white, false if black
     */
    Knight(bool isWhite);

    /**
     * @brief Returns an unordered set of tiles this piece can move to.
     * 
     * @param board a 2D vector representing the board state
     * @param row the row this piece is at on the board
     * @param col the column this piece is at on the board
     * @return an unordered set of tiles the piece can move to
     */
    unordered_set<Tile, HashTile> getMoves(const vector<vector<ChessPiece*>>& board,
            int row, int col) const;

    /**
     * @brief Returns the name of this piece.
     * 
     * @return string "Knight"
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