#ifndef _ChessBoard_h
#define _ChessBoard_h

#include <vector>
#include "ChessPiece.h"
#include "Tile.h"
using namespace std;

class ChessBoard {
private:
    vector<vector<ChessPiece*>>* board;
    //game handlers
    bool whiteIsChecked;
    bool blackIsChecked;
    bool selected;
    int selectedRow;
    int selectedCol;
    bool whiteTurn;
    string winner;
    unordered_set<Tile, HashTile>* movableTiles;
    int boardValue;
    void setBackRow(int row, bool isWhite);
    Tile getKingLocation(bool kingIsWhite) const;
    void checkKings();
    bool simulateMove(int row, int col);
    vector<vector<ChessPiece*>>* copyBoard() const;
public:
    ChessBoard();
    void emptyBoard();
    void setStartingBoard();
    unordered_set<Tile, HashTile>* getMovableTiles() const;
    ChessPiece* getPiece(int row, int col) const;
    void setPiece(ChessPiece* piece, int row, int col);
    int getBoardValue() const;
    void changeBoardValue(int value);


    //maybe offload
    void tryMove(int row, int col);
    void selectPiece(int row, int col); //change to return set
    void movePiece(int row, int col);

    void selectPieceAI(int row, int col);


    //to delete
    bool isCapturable(bool isWhite, Tile location) const;


    //offload to board manager
    bool pieceIsSelected() const;
    bool isCheckedWhite() const;
    bool isCheckedBlack() const;
    bool whiteCanMove() const;
    bool isWhiteTurn() const;
    void changeTurns();
    bool isSelectedPiece(int row, int col) const;
    bool isMovableTile(int row, int col) const;
    void setWinner(string winner);
    string getWinner() const;
};

#endif