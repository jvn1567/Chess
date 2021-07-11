#include "ChessBoard.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"

ChessBoard::ChessBoard() {
    board = new vector<vector<ChessPiece*>>;
    for (int row = 0; row < 8; row++) {
        vector<ChessPiece*> newRow;
        for (int col = 0; col < 8; col++) {
            newRow.push_back(nullptr);
        }
        board->push_back(newRow);
    }
    whiteIsChecked = false;
    blackIsChecked = false;
    selected = false;
    selectedRow = 0;
    selectedCol = 0;
    whiteTurn = true;
}

vector<vector<ChessPiece*>>* ChessBoard::copyBoard() const {
    vector<vector<ChessPiece*>>* copy = new vector<vector<ChessPiece*>>;
    for (int row = 0; row < 8; row++) {
        vector<ChessPiece*> newRow;
        for (int col = 0; col < 8; col++) {
            ChessPiece* piece = getPiece(row, col);
            newRow.push_back(piece);
        }
        copy->push_back(newRow);
    }
    return copy;
}

void ChessBoard::setStartingBoard() {
    for (int col = 0; col < 8; col ++) {
        (*board)[1][col] = new Pawn(false);
        (*board)[6][col] = new Pawn(true);
    }
    setBackRow(0, false);
    setBackRow(7, true);
}

void ChessBoard::setBackRow(int row, bool isWhite) {
    (*board)[row][0] = new Rook(isWhite);
    (*board)[row][1] = new Knight(isWhite);
    (*board)[row][2] = new Bishop(isWhite);
    (*board)[row][3] = new Queen(isWhite);
    (*board)[row][4] = new King(isWhite);
    (*board)[row][5] = new Bishop(isWhite);
    (*board)[row][6] = new Knight(isWhite);
    (*board)[row][7] = new Rook(isWhite);
}

unordered_set<Tile, HashTile> ChessBoard::getMoves(int row, int col) const {
    unordered_set<Tile, HashTile> moves = (*board)[row][col]->getMoves(board, row, col);
    return moves;
}

Tile ChessBoard::getKingLocation(bool kingIsWhite) const {
    int kingRow = 0;
    int kingCol = 0;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            ChessPiece* piece = getPiece(row, col);
            if (piece != nullptr && piece->getName() == "King" &&
                    piece->isWhite() == kingIsWhite) {
                kingRow = row;
                kingCol = col;
            }
        }
    }
    Tile kingTile(kingRow, kingCol);
    return kingTile;
}

bool ChessBoard::kingIsChecked(bool kingIsWhite, Tile kingLocation) const {
    unordered_set<Tile, HashTile> enemyMoves;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            ChessPiece* piece = getPiece(row, col);
            if (piece != nullptr && piece->isWhite() != kingIsWhite) {
                unordered_set<Tile, HashTile> temp = getMoves(row, col);
                for (Tile tile : temp) {
                    enemyMoves.insert(tile);
                }
            }
        }
    }
    return enemyMoves.count(kingLocation);
}

void ChessBoard::checkKings() {
    Tile whiteKing = getKingLocation(true);
    whiteIsChecked = kingIsChecked(true, whiteKing);
    Tile blackKing = getKingLocation(false);
    blackIsChecked = kingIsChecked(false, blackKing);
}

bool ChessBoard::simulateMove(Tile start, Tile end, bool whiteTurn) {
    vector<vector<ChessPiece*>>* oldBoard = copyBoard();
    ChessPiece* oldPiece = getPiece(start);
    bool whiteWasChecked = whiteIsChecked;
    bool blackWasChecked = blackIsChecked;
    setPiece(oldPiece, end);
    setPiece(nullptr, start);
    checkKings();
    bool checked = (whiteTurn && !whiteIsChecked) || (!whiteTurn && !blackIsChecked);
    board = oldBoard;
    oldBoard = nullptr;
    whiteIsChecked = whiteWasChecked;
    blackIsChecked = blackWasChecked;
    return checked;
}

void ChessBoard::selectPiece(int row, int col) {
    ChessPiece* piece = getPiece(row, col);
    if (piece != nullptr && piece->isWhite()) {
        selectedRow = row;
        selectedCol = col;
        selected = true;
        unordered_set<Tile, HashTile> tempMovableTiles = getMoves(row, col);
        movableTiles.clear();
        Tile selected(selectedRow, selectedCol);
        for (Tile tile : tempMovableTiles) {
            if (simulateMove(selected, tile, whiteTurn)) {
                movableTiles.insert(tile);
            }
        }
    }
}

void ChessBoard::movePiece(int row, int col) {
    ChessPiece* old = getPiece(selectedRow, selectedCol);
    if (old->getName() == "Pawn") {
        ((Pawn*)old)->setMoved();
    }
    setPiece(old, row, col);
    setPiece(nullptr, selectedRow, selectedCol);
    selected = false;
}

void ChessBoard::tryMove(int row, int col) {
    //checks
    ChessPiece* piece = getPiece(row, col);
    bool selectedLocation = row == selectedRow && col == selectedCol;
    bool alliedPiece = piece != nullptr && piece->isWhite();
    bool validLocation = false;
    Tile thisTile(row, col);
    if (movableTiles.count(thisTile)) {
        validLocation = true;
    }
    //filter behavior according to checks
    if (selectedLocation || (!validLocation && !alliedPiece)) {
        selected = false;
    } else if (alliedPiece) {
        selectPiece(row, col);
    } else {
        Tile selected(selectedRow, selectedCol);
        Tile goal(row, col);
        bool moveGood = simulateMove(selected, goal, whiteTurn);
        if (moveGood) {
            movePiece(row, col);
            checkKings();
        }
    }
}

bool ChessBoard::pieceIsSelected() const {
    return selected;
}

bool ChessBoard::isCheckedWhite() const {
    return whiteIsChecked;
}

bool ChessBoard::isCheckedBlack() const {
    return blackIsChecked;
}

bool ChessBoard::isWhiteTurn() const {
    return whiteTurn;
}

int ChessBoard::getSelectedRow() const {
    return selectedRow;
}

int ChessBoard::getSelectedCol() const {
    return selectedCol;
}

ChessPiece* ChessBoard::getPiece(int row, int col) const {
    return (*board)[row][col];
}

ChessPiece* ChessBoard::getPiece(Tile location) const {
    return (*board)[location.getRow()][location.getCol()];
}

unordered_set<Tile, HashTile> ChessBoard::getMovableTiles() const {
    return movableTiles;
}

void ChessBoard::setPiece(ChessPiece* piece, int row, int col) {
    (*board)[row][col] = piece;
}

void ChessBoard::setPiece(ChessPiece* piece, Tile location) {
    (*board)[location.getRow()][location.getCol()] = piece;
}