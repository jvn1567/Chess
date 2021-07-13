#ifndef _ChessBoard_h
#define _ChessBoard_h

#include <vector>
#include "ChessPiece.h"
#include "Tile.h"
using namespace std;

class ChessBoard {
private:
    vector<vector<ChessPiece*>>* board;
    bool whiteIsChecked;
    bool blackIsChecked;
    bool selected;
    int selectedRow;
    int selectedCol;
    bool whiteTurn;
    unordered_set<Tile, HashTile> movableTiles;
    void setBackRow(int row, bool isWhite);
    Tile getKingLocation(bool kingIsWhite) const;
    void checkKings();
    bool simulateMove(int row, int col);
    vector<vector<ChessPiece*>>* copyBoard() const;
public:
    ChessBoard();
    void setStartingBoard();
    void tryMove(int row, int col);
    void selectPiece(int row, int col);
    void movePiece(int row, int col);
    bool isCapturable(bool isWhite, Tile location) const;
    bool pieceIsSelected() const;
    bool isCheckedWhite() const;
    bool isWhiteTurn() const;
    bool isSelectedPiece(int row, int col) const;
    bool isMovableTile(int row, int col) const;
    unordered_set<Tile, HashTile> getMovableTiles() const;
    ChessPiece* getPiece(int row, int col) const;
    void setPiece(ChessPiece* piece, int row, int col);
};

#endif