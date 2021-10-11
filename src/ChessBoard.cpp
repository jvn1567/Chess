#include "ChessBoard.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"

ChessBoard::ChessBoard() {
    emptyBoard();
    setStartingBoard();
}

void ChessBoard::emptyBoard() {
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
    movableTiles = new unordered_set<Tile, HashTile>;
    boardValue = 0;
    winner = "";
}

void ChessBoard::setStartingBoard() {
    for (int col = 0; col < 8; col ++) {
        (*board)[1][col] = new Pawn(false);
        (*board)[6][col] = new Pawn(true);
    }
    setBackRow(0, false);
    setBackRow(7, true);
}

ChessPiece* ChessBoard::getPiece(int row, int col) const {
    return (*board)[row][col];
}

void ChessBoard::setPiece(ChessPiece* piece, int row, int col) {
    (*board)[row][col] = piece;
}

int ChessBoard::getBoardValue() const {
    return boardValue;
}

void ChessBoard::changeBoardValue(int value) {
    boardValue += value;
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

bool ChessBoard::isCapturable(bool isWhite, Tile location) const {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            ChessPiece* piece = getPiece(row, col);
            if (piece != nullptr && piece->isWhite() != isWhite) {
                unordered_set<Tile, HashTile> temp = piece->getMoves(board, row, col);
                if (temp.count(location) == 1) {
                    return true;
                }
            }
        }
    }
    return false;
}

void ChessBoard::checkKings() {
    Tile whiteKingTile = getKingLocation(true);
    whiteIsChecked = isCapturable(true, whiteKingTile);
    Tile blackKingTile = getKingLocation(false);
    blackIsChecked = isCapturable(false, blackKingTile);
}

bool ChessBoard::simulateMove(int row, int col) {
    bool whiteWasChecked = whiteIsChecked;
    bool blackWasChecked = blackIsChecked;
    ChessPiece* selectedPiece = getPiece(selectedRow, selectedCol);
    ChessPiece* targetPiece = getPiece(row, col);
    setPiece(selectedPiece, row, col);
    setPiece(nullptr, selectedRow, selectedCol);
    checkKings();
    bool safe = (whiteTurn && !whiteIsChecked) || (!whiteTurn && !blackIsChecked);
    setPiece(targetPiece, row, col);
    setPiece(selectedPiece, selectedRow, selectedCol);
    whiteIsChecked = whiteWasChecked;
    blackIsChecked = blackWasChecked;
    return safe;
}

//change to return set
void ChessBoard::selectPiece(int row, int col) {  
    ChessPiece* piece = getPiece(row, col);
    if (piece != nullptr && (piece->isWhite() == whiteTurn)) {
        selectedRow = row;
        selectedCol = col;
        selected = true;
        unordered_set<Tile, HashTile> tempTiles = piece->getMoves(board, row, col);
        //delete movableTiles;
        movableTiles = new unordered_set<Tile, HashTile>;
        for (Tile tile : tempTiles) {
            if (simulateMove(tile.getRow(), tile.getCol())) {
                movableTiles->insert(tile);
            }
        }
    }
}

//TEMPORARY ai time reducer (bugged)
void ChessBoard::selectPieceAI(int row, int col) {
    ChessPiece* piece = getPiece(row, col);
    selectedRow = row;
    selectedCol = col;
    selected = true;
    unordered_set<Tile, HashTile> tempTiles = piece->getMoves(board, row, col);
    movableTiles = new unordered_set<Tile, HashTile>;
    for (Tile tile : tempTiles) {
        movableTiles->insert(tile);
    }
}

void ChessBoard::movePiece(int row, int col) {
    ChessPiece* pieceToMove = getPiece(selectedRow, selectedCol);
    if (pieceToMove->getName() == "Pawn") {
        ((Pawn*)pieceToMove)->setMoved(true);
        if (row == 0 || row == 7) {
            boardValue -= pieceToMove->getValue();
            delete pieceToMove;
            pieceToMove = new Queen(pieceToMove->isWhite());
            boardValue += pieceToMove->getValue();
        }
    }
    ChessPiece* pieceAtLocation = getPiece(row, col);
    if (pieceAtLocation != nullptr) {
        boardValue -= pieceAtLocation->getValue();
        delete pieceAtLocation;
    }
    setPiece(pieceToMove, row, col);
    setPiece(nullptr, selectedRow, selectedCol);
    selected = false;
    whiteTurn = !whiteTurn;
    checkKings();
}

void ChessBoard::tryMove(int row, int col) {
    //checks
    ChessPiece* piece = getPiece(row, col);
    bool selectedLocation = row == selectedRow && col == selectedCol;
    bool alliedPiece = piece != nullptr && piece->isWhite() == whiteTurn;
    Tile thisTile(row, col);
    bool validLocation = movableTiles->count(thisTile);
    //filter behavior according to checks
    if (selectedLocation || (!validLocation && !alliedPiece)) {
        selected = false;
    } else if (alliedPiece) {
        selectPiece(row, col);
    } else {
        movePiece(row, col);
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

bool ChessBoard::whiteCanMove() const {
    //grab white pieces
    unordered_set<Tile, HashTile> selectablePieces;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            ChessPiece* piece = getPiece(row, col);
            if (piece != nullptr && piece->isWhite()) {
                selectablePieces.insert(Tile(row, col));
            }
        }
    }
    //count possible moves
    int validMoves = 0;
    for (Tile tile : selectablePieces) {
        ChessPiece* piece = getPiece(tile.getRow(), tile.getCol());
        unordered_set<Tile, HashTile> tempTiles;
        tempTiles = piece->getMoves(board, tile.getRow(), tile.getCol());
        validMoves += tempTiles.size();
    }
    return validMoves != 0;
}

bool ChessBoard::isWhiteTurn() const {
    return whiteTurn;
}

void ChessBoard::changeTurns() {
    whiteTurn = !whiteTurn;
}

bool ChessBoard::isSelectedPiece(int row, int col) const {
    return (row == selectedRow) && (col == selectedCol);
}

bool ChessBoard::isMovableTile(int row, int col) const {
    return movableTiles->count(Tile(row, col));
}

unordered_set<Tile, HashTile>* ChessBoard::getMovableTiles() const {
    return movableTiles;
}

void ChessBoard::setWinner(string winner) {
    this->winner = winner;
}

string ChessBoard::getWinner() const {
    return winner;
}