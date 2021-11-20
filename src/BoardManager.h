#ifndef _BoardManager_h
#define _BoardManager_h

#include <vector>
#include <queue>
#include "ChessPiece.h"
#include "Tile.h"
using namespace std;

class BoardManager {
private:
    vector<vector<ChessPiece*>> board;
    //game handlers
    bool whiteIsChecked;
    bool blackIsChecked;
    bool whiteTurn;
    bool selected;
    int boardValue;
    Tile selectedTile;
    string winner;
    unordered_set<Tile, HashTile> movableTiles;
    priority_queue_piece captured;
    void resetGameState();
    void setBackRow(bool isWhite);
    void setStartingBoard();
    Tile getKingLocation(bool kingIsWhite) const;
    bool isCapturable(bool isWhite, const Tile& tile) const;
    void checkKings();
    bool simulateMove(const Tile& tile);
public:
    BoardManager();
    void restartGame();
    ChessPiece* getPiece(int row, int col) const;
    ChessPiece* getPiece(const Tile& tile) const;
    void setPiece(ChessPiece* piece, int row, int col);
    void setPiece(ChessPiece* piece, const Tile& tile);
    int getBoardValue() const;
    void changeBoardValue(int value);
    bool pieceIsSelected() const;
    bool isCheckedWhite() const;
    bool isCheckedBlack() const;
    bool isWhiteTurn() const;
    void changeTurns();
    void setWinner(string winner);
    string getWinner() const;
    bool isSelectedPiece(int row, int col) const;
    bool isMovableTile(int row, int col) const;
    unordered_set<Tile, HashTile> getMovableTiles() const;
    priority_queue_piece getCaptured() const;
    void selectPiece(const Tile& tile, bool filterMoves = true);
    void tryMove(const Tile& tile);
    void movePiece(const Tile& tile);
    bool whiteCanMove();
};

#endif