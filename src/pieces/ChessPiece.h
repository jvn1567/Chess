#ifndef _ChessPiece_h
#define _ChessPiece_h

#include <unordered_set>
#include <vector>
#include <queue>
#include "Tile.h"
using namespace std;

class ChessPiece {
private:
    bool white;
protected:
    void getLine(const vector<vector<ChessPiece*>>& board, int row, int col,
            unordered_set<Tile, HashTile>& moves, int rowShift, int colShift) const;
    bool isEnemy(ChessPiece* other) const;
public:
    ChessPiece(bool white);
    virtual unordered_set<Tile, HashTile> getMoves(const vector<vector<ChessPiece*>>& board,
            int row, int col) const = 0;
    virtual string getName() const = 0;
    virtual int getValue() const = 0;
    bool isWhite() const;
    virtual ~ChessPiece();
};

struct PieceCompare {
    bool operator()(const ChessPiece* left, const ChessPiece* right);
};

typedef priority_queue<ChessPiece*, vector<ChessPiece*>, PieceCompare> priority_queue_piece;

#endif