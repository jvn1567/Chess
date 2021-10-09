#include "Tile.h"

Tile::Tile(int row, int col) {
    this->row = row;
    this->col = col;
}

int Tile::getRow() const {
    return row;
}

int Tile::getCol() const {
    return col;
}

bool isOutOfBounds(int row, int col) {
    return row < 0 || col < 0 || row >= 8 || col >= 8;
}

bool operator ==(const Tile& tile1, const Tile& tile2) {
    bool equalRow = tile1.getRow() == tile2.getRow();
    bool equalCol = tile1.getCol() == tile2.getCol();
    return equalRow && equalCol;
}

bool operator <(const Tile& tile1, const Tile& tile2) {
    bool lowerRow = tile1.getRow() < tile2.getRow();
    bool equalRow = tile1.getRow() == tile2.getRow();
    bool lowerCol = tile1.getCol() < tile2.getCol();
    return lowerRow || (equalRow && lowerCol);
}

ostream& operator <<(ostream& out, const Tile& tile) {
    out << "(" << tile.getRow() << ", " << tile.getCol() << ")";
    return out;
}