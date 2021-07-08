#ifndef _Tile_h
#define _Tile_h

#include <unordered_set>
#include <functional>
using namespace std;

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
bool operator <(const Tile& tile1, const Tile& tile2);

struct HashTile {
    size_t operator()(const Tile& tile) const {
        size_t temp = hash<int>()(tile.getRow() * 10 + tile.getCol());
        return temp;
    }
};

#endif