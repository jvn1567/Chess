#ifndef _Tile_h
#define _Tile_h

#include <unordered_set>
#include <functional>
#include <iostream>
using namespace std;

struct Tile {
    int row;
    int col;
    Tile(int row = 0, int col = 0); 
};
bool isOutOfBounds(int row, int col);
bool operator ==(const Tile& tile1, const Tile& tile2);
bool operator <(const Tile& tile1, const Tile& tile2);
ostream& operator <<(ostream& out, const Tile& tile);

struct HashTile {
    size_t operator()(const Tile& tile) const;
};

#endif