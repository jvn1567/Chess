/**
 * @file Rook.h
 * @author John Nguyen (https://github.com/jvn1567)
 * @brief This class represents a Rook chess piece.
 * @version 0.1
 * @date 2021-11-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _Rook_h
#define _Rook_h

#include "ChessPiece.h"
using namespace std;

class Rook : public ChessPiece {
public:
    /**
     * @brief Constructor for a Rook object.
     * 
     * @param isWhite true if white, false if black
     */
    Rook(bool isWhite);

    /**
     * @brief Returns an unordered set of tiles this piece can move to.
     * 
     * @param board a 2D vector representing the board state
     * @param row the row this piece is at on the board
     * @param col the column this piece is at on the board
     * @return an unordered set of tiles this piece can move to
     */
    unordered_set<Tile, HashTile> getMoves(const vector<vector<ChessPiece*>>& board,
            int row, int col) const;

    /**
     * @brief Returns the name of this piece.
     * 
     * @return string "Rook"
     */
    string getName() const;

    /**
     * @brief Returns the value of this piece.
     * 
     * @return int the value of this piece
     */
    int getValue() const;
};

#endif