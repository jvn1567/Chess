/**
 * @file Pawn.h
 * @author John Nguyen (https://github.com/jvn1567)
 * @brief This class represents a Pawn chess piece.
 * @version 0.1
 * @date 2021-11-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _Pawn_h
#define _Pawn_h

#include "ChessPiece.h"
using namespace std;

class Pawn : public ChessPiece {
private:
    bool hasMoved;
public:
    /**
     * @brief Constructor for a Pawn object.
     * 
     * @param isWhite true if white, false if black
     */
    Pawn(bool isWhite);

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
     * @return string "Pawn"
     */
    string getName() const;

    /**
     * @brief Returns the value of this piece.
     * 
     * @return int the piece value
     */
    int getValue() const;

    /**
     * @brief Sets the bool indicating whether this pawn has moved at
     * least once.
     * 
     * @param hasMoved true if pawn has moved, false if it has not
     */
    void setMoved(bool hasMoved);

    /**
     * @brief Returns whether this pawn has moved at least once.
     * 
     * @return true if pawn has moved
     * @return false if pawn has not moved
     */
    bool getHasMoved() const;
};

#endif