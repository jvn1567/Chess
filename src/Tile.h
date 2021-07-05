#ifndef _Tile_h
#define _Tile_h

class Tile {
private:
    int row;
    int col;
public: 
    Tile(int row, int col);
    int getRow() const;
    int getCol() const;
};
bool isOutOfBounds(int row, int col);
bool operator ==(const Tile& tile1, const Tile& tile2);

#endif