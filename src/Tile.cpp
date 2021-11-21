/**
 * @file Tile.cpp
 * @author John Nguyen (https://github.com/jvn1567)
 * @brief This file implements the Tile class.
 * @version 0.1
 * @date 2021-11-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "Tile.h"

Tile::Tile(int row, int col) {
    this->row = row;
    this->col = col;
}

bool isOutOfBounds(int row, int col) {
    return row < 0 || col < 0 || row >= 8 || col >= 8;
}

bool operator ==(const Tile& tile1, const Tile& tile2) {
    bool equalRow = tile1.row == tile2.row;
    bool equalCol = tile1.col == tile2.col;
    return equalRow && equalCol;
}

bool operator <(const Tile& tile1, const Tile& tile2) {
    bool lowerRow = tile1.row < tile2.row;
    bool equalRow = tile1.row == tile2.row;
    bool lowerCol = tile1.col < tile2.col;
    return lowerRow || (equalRow && lowerCol);
}

ostream& operator <<(ostream& out, const Tile& tile) {
    out << "(" << tile.row << ", " << tile.col << ")";
    return out;
}

size_t HashTile::operator()(const Tile& tile) const {
    size_t temp = hash<int>()(tile.row * 10 + tile.col);
    return temp;
}