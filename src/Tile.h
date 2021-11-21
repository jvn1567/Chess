/**
 * @file Tile.h
 * @author John Nguyen (https://github.com/jvn1567)
 * @brief This struct represents a single tile on a chess board.
 * @version 0.1
 * @date 2021-11-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _Tile_h
#define _Tile_h

#include <iostream>
using namespace std;

struct Tile {
    int row;
    int col;
    /**
     * @brief Constructs a Tile object.
     * 
     * @param row the row value
     * @param col the column value
     */
    Tile(int row = 0, int col = 0); 
};

/**
 * @brief Returns whether the location is on the chess board, which has
 * rows and column values from 0 to 7, inclusive.
 * 
 * @param row the row to check
 * @param col the column to check
 * @return true if the location is within bounds of the chess board
 * @return false if the location is outside the chess board
 */
bool isOutOfBounds(int row, int col);

/**
 * Operator overloads for Tile.
 */
bool operator ==(const Tile& tile1, const Tile& tile2);
bool operator <(const Tile& tile1, const Tile& tile2);
ostream& operator <<(ostream& out, const Tile& tile);

/**
 * @brief Hash function for a Tile object.
 * 
 */
struct HashTile {
    size_t operator()(const Tile& tile) const;
};

#endif