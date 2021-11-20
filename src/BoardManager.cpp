#include "BoardManager.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"

BoardManager::BoardManager() {
    for (int row = 0; row < 8; row++) {
        vector<ChessPiece*> newRow;
        for (int col = 0; col < 8; col++) {
            newRow.push_back(nullptr);
        }
        board.push_back(newRow);
    }
    resetGameState();
    setStartingBoard();
}

void BoardManager::resetGameState() {
    whiteIsChecked = false;
    blackIsChecked = false;
    selected = false;
    selectedTile = Tile();
    whiteTurn = true;
    movableTiles.clear();
    boardValue = 0;
    winner = "";
}

void BoardManager::restartGame(){
    for (int row = 0; row < 8; row++){
        for (int col = 0; col < 8; col++) {
            if (board[row][col] != nullptr) {
                delete board[row][col];
                board[row][col] = nullptr;
            }
        }
    }
    while (!captured.empty()) {
        delete captured.top();
        captured.pop();
    }
    resetGameState();
    setStartingBoard();
}

void BoardManager::setBackRow(bool isWhite) {
    int row;
    isWhite ? row = 7 : row = 0;
    board[row][0] = new Rook(isWhite);
    board[row][1] = new Knight(isWhite);
    board[row][2] = new Bishop(isWhite);
    board[row][3] = new Queen(isWhite);
    board[row][4] = new King(isWhite);
    board[row][5] = new Bishop(isWhite);
    board[row][6] = new Knight(isWhite);
    board[row][7] = new Rook(isWhite);
}

void BoardManager::setStartingBoard() {
    for (int col = 0; col < 8; col ++) {
        board[1][col] = new Pawn(false);
        board[6][col] = new Pawn(true);
    }
    setBackRow(false);
    setBackRow(true);
}

ChessPiece* BoardManager::getPiece(int row, int col) const {
    return board[row][col];
}

ChessPiece* BoardManager::getPiece(const Tile& tile) const {
    return board[tile.row][tile.col];
}

void BoardManager::setPiece(ChessPiece* piece, int row, int col) {
    board[row][col] = piece;
}

void BoardManager::setPiece(ChessPiece* piece, const Tile& tile) {
    board[tile.row][tile.col] = piece;
}

int BoardManager::getBoardValue() const {
    return boardValue;
}

void BoardManager::changeBoardValue(int value) {
    boardValue += value;
}

bool BoardManager::pieceIsSelected() const {
    return selected;
}

bool BoardManager::isCheckedWhite() const {
    return whiteIsChecked;
}

bool BoardManager::isCheckedBlack() const {
    return blackIsChecked;
}

bool BoardManager::isWhiteTurn() const {
    return whiteTurn;
}

void BoardManager::changeTurns() {
    whiteTurn = !whiteTurn;
}

void BoardManager::setWinner(string winner) {
    this->winner = winner;
}

string BoardManager::getWinner() const {
    return winner;
}

bool BoardManager::isSelectedPiece(int row, int col) const {
    return (row == selectedTile.row) && (col == selectedTile.col);
}

bool BoardManager::isMovableTile(int row, int col) const {
    return movableTiles.count(Tile(row, col));
}

unordered_set<Tile, HashTile> BoardManager::getMovableTiles() const {
    return movableTiles;
}

priority_queue_piece BoardManager::getCaptured() const {
    return captured;
}

Tile BoardManager::getKingLocation(bool kingIsWhite) const {
    Tile kingTile;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            ChessPiece* piece = getPiece(row, col);
            if (piece != nullptr && piece->getName() == "King" &&
                    piece->isWhite() == kingIsWhite) {
                kingTile = Tile(row, col);
            }
        }
    }
    return kingTile;
}

bool BoardManager::isCapturable(bool isWhite, const Tile& tile) const {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            ChessPiece* piece = getPiece(row, col);
            if (piece != nullptr && piece->isWhite() != isWhite) {
                unordered_set<Tile, HashTile> temp = piece->getMoves(board, row, col);
                if (temp.count(tile) == 1) {
                    return true;
                }
            }
        }
    }
    return false;
}

void BoardManager::checkKings() {
    Tile whiteKingTile = getKingLocation(true);
    whiteIsChecked = isCapturable(true, whiteKingTile);
    Tile blackKingTile = getKingLocation(false);
    blackIsChecked = isCapturable(false, blackKingTile);
}

bool BoardManager::simulateMove(const Tile& tile) {
    bool whiteWasChecked = whiteIsChecked;
    bool blackWasChecked = blackIsChecked;
    ChessPiece* selectedPiece = getPiece(selectedTile);
    ChessPiece* targetPiece = getPiece(tile);
    setPiece(selectedPiece, tile);
    setPiece(nullptr, selectedTile);
    checkKings();
    bool safe = (whiteTurn && !whiteIsChecked) || (!whiteTurn && !blackIsChecked);
    setPiece(targetPiece, tile);
    setPiece(selectedPiece, selectedTile);
    whiteIsChecked = whiteWasChecked;
    blackIsChecked = blackWasChecked;
    return safe;
}

void BoardManager::selectPiece(const Tile& tile, bool filterMoves) {  
    ChessPiece* piece = getPiece(tile);
    if (piece != nullptr && (piece->isWhite() == whiteTurn)) {
        selectedTile = tile;
        selected = true;
        unordered_set<Tile, HashTile> tempTiles;
        tempTiles = piece->getMoves(board, tile.row, tile.col);
        movableTiles.clear();
        for (Tile tile : tempTiles) {
            if (!filterMoves || simulateMove(tile)) {
                movableTiles.insert(tile);
            }
        }
    }
}

void BoardManager::tryMove(const Tile& tile) {
    ChessPiece* piece = getPiece(tile);
    bool selectedLocation = tile == selectedTile;
    bool alliedPiece = piece != nullptr && piece->isWhite() == whiteTurn;
    bool validLocation = movableTiles.count(tile);
    if (selectedLocation || (!validLocation && !alliedPiece)) {
        selected = false;
    } else if (alliedPiece) {
        selectPiece(tile);
    } else {
        movePiece(tile);
    }
}

void BoardManager::movePiece(const Tile& tile) {
    ChessPiece* pieceToMove = getPiece(selectedTile);
    // pawn status updates and promotes
    if (pieceToMove->getName() == "Pawn") {
        ((Pawn*)pieceToMove)->setMoved(true);
        if (tile.row == 0 || tile.row == 7) {
            boardValue -= pieceToMove->getValue();
            delete pieceToMove;
            pieceToMove = new Queen(pieceToMove->isWhite());
            boardValue += pieceToMove->getValue();
        }
    }
    // handle movement and game status
    ChessPiece* pieceAtLocation = getPiece(tile);
    if (pieceAtLocation != nullptr) {
        boardValue -= pieceAtLocation->getValue();
        captured.push(pieceAtLocation);
    }
    setPiece(pieceToMove, tile);
    setPiece(nullptr, selectedTile);
    selected = false;
    whiteTurn = !whiteTurn;
    checkKings();
}

bool BoardManager::whiteCanMove() {
    selected = true;
    unordered_set<Tile, HashTile> whiteMovable;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            selectedTile = Tile(row, col);
            ChessPiece* piece = getPiece(row, col);
            if (piece != nullptr && piece->isWhite()) {
                unordered_set<Tile, HashTile> tempTiles;
                tempTiles = piece->getMoves(board, row, col);
                for (Tile tile : tempTiles) {
                    if (simulateMove(tile)) {
                        whiteMovable.insert(tile);
                    }
                }
            }
        }
    }
    selected = false;
    return whiteMovable.size() > 0;
}