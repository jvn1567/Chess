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
    bool kingIsChecked(bool kingIsWhite, Tile kingLocation) const;
    void checkKings();
    bool simulateMove(Tile start, Tile end, bool whiteTurn);
    void movePiece(int row, int col);
    vector<vector<ChessPiece*>>* copyBoard() const;
public:
    ChessBoard();
    void setStartingBoard();
    unordered_set<Tile, HashTile> getMoves(int row, int col) const;
    void tryMove(int row, int col);
    void selectPiece(int row, int col);
    bool pieceIsSelected() const;
    bool isCheckedWhite() const;
    bool isCheckedBlack() const;
    bool isWhiteTurn() const;
    int getSelectedRow() const;
    int getSelectedCol() const;
    ChessPiece* getPiece(int row, int col) const;
    ChessPiece* getPiece(Tile location) const;
    unordered_set<Tile, HashTile> getMovableTiles() const;
    void setPiece(ChessPiece* piece, int row, int col);
    void setPiece(ChessPiece* piece, Tile location);
};

#endif