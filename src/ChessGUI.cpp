#include "ChessBoard.h"
#include "Pawn.h"
#include <string>
#include <unordered_set>
#include "gwindow.h"
#include "gbutton.h"
#include "gevent.h"
#include "glabel.h"
using namespace sgl;
using namespace std;

static const int WINDOW_SIZE = 800; //may break if not divisible by 8
static const int LINE_WIDTH = 4;
static const int TILE_SIZE = WINDOW_SIZE / 8;

//global variables
GWindow* window;
ChessBoard* board;
//tile selection status and location for player
bool pieceIsSelected;
int selectedRow;
int selectedCol;
//turn tracker, king status and location
bool whiteTurn;
bool whiteIsChecked;
bool blackIsChecked;
unordered_set<Tile, HashTile> movableTiles;

void fillTile(string color, int row, int col) {
    window->setColor(color);
    int tempSize = TILE_SIZE - LINE_WIDTH;
    window->fillRect(col * TILE_SIZE, row * TILE_SIZE, tempSize, tempSize);
}

void drawTile(string color, int row, int col) {
    window->setColor(color);
    int tempSize = TILE_SIZE - LINE_WIDTH;
    window->drawRect(col * TILE_SIZE, row * TILE_SIZE, tempSize, tempSize);
}

void drawBackgroundTile(int row, int col) {
    if ((row % 2 == 0) ^ (col % 2 == 0)) {
        fillTile("dark gray", row, col);
    } else {
        fillTile("gray", row, col);
    }
}

void drawTileHighlight(int row, int col) {
    if (pieceIsSelected) {
        //highlight selected unit
        if (row == selectedRow && col == selectedCol) {
            drawTile("orange", row, col);
        }
        //highlight moveable tiles
        bool movable = false;
        for (Tile available : movableTiles) {
            if (available.getCol() == col && available.getRow() == row) {
                movable = true;
            }
        }
        bool isOccupied = false;
        bool containsEnemy = false;
        ChessPiece* piece = board->getPiece(row, col);
        if (piece != nullptr) {
            isOccupied = true;
            containsEnemy = !(piece->isWhite());
        }
        if (movable && !isOccupied) {
            drawTile("yellow", row, col);
        } else if (movable && containsEnemy) {
            drawTile("red", row, col);
        }
    }
}

void drawPiece(int row, int col) {
    ChessPiece* piece = board->getPiece(row, col);
    if (piece != nullptr) {
        bool isChecked = (whiteTurn && whiteIsChecked && piece->isWhite()) ||
                (!whiteTurn && blackIsChecked && !piece->isWhite());
        if (piece->getName() == "King" && isChecked) {
            fillTile("red", row, col);
        }
        string filename = "";
        if (piece->isWhite()) {
            filename += "White";
        } else {
            filename += "Black";
        }
        filename += piece->getName();
        filename += ".png";
        window->drawImage(filename, col * TILE_SIZE, row * TILE_SIZE);
    }
}

void redraw() {
    for (int row = 0; row < 8; row ++) {
        for (int col = 0; col < 8; col++) {
            drawBackgroundTile(row, col);
            drawTileHighlight(row, col);
            drawPiece(row, col);
        }
    }
    window->repaint();
}

Tile getKingLocation(bool kingIsWhite) {
    int kingRow = 0;
    int kingCol = 0;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            ChessPiece* piece = board->getPiece(row, col);
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

bool kingIsChecked(bool kingIsWhite, Tile kingLocation) {
    unordered_set<Tile, HashTile> enemyMoves;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            ChessPiece* piece = board->getPiece(row, col);
            if (piece != nullptr && piece->isWhite() != kingIsWhite) {
                unordered_set<Tile, HashTile> temp = board->getMoves(row, col);
                for (Tile tile : temp) {
                    enemyMoves.insert(tile);
                }
            }
        }
    }
    return enemyMoves.count(kingLocation);
}

void checkKings() {
    Tile whiteKing = getKingLocation(true);
    whiteIsChecked = kingIsChecked(true, whiteKing);
    Tile blackKing = getKingLocation(false);
    blackIsChecked = kingIsChecked(false, blackKing);
}

bool simulateMove(int row, int col) {
    ChessBoard* oldBoard = new ChessBoard(*board);
    ChessPiece* oldPiece = board->getPiece(selectedRow, selectedCol);
    bool whiteWasChecked = whiteIsChecked;
    bool blackWasChecked = blackIsChecked;
    board->setPiece(oldPiece, row, col);
    board->setPiece(nullptr, selectedRow, selectedCol);
    checkKings();
    bool checked = (whiteTurn && !whiteIsChecked) || (!whiteTurn && !blackIsChecked);
    board = oldBoard;
    oldBoard = nullptr;
    whiteIsChecked = whiteWasChecked;
    blackIsChecked = blackWasChecked;
    return checked;
}

void handleSelect(int row, int col) {
    ChessPiece* piece = board->getPiece(row, col);
    if (piece != nullptr && piece->isWhite()) {
        selectedRow = row;
        selectedCol = col;
        pieceIsSelected = true;
        unordered_set<Tile, HashTile> tempMovableTiles = board->getMoves(row, col);
        movableTiles.clear();
        for (Tile tile : tempMovableTiles) {
            if (simulateMove(tile.getRow(), tile.getCol())) {
                movableTiles.insert(tile);
            }
        }
        redraw();
    }
}

void movePiece(int row, int col) {
    ChessPiece* old = board->getPiece(selectedRow, selectedCol);
    if (old->getName() == "Pawn") {
        ((Pawn*)old)->setMoved();
    }
    board->setPiece(old, row, col);
    board->setPiece(nullptr, selectedRow, selectedCol);
    pieceIsSelected = false;
}

void tryMove(int row, int col) {
    //checks
    ChessPiece* piece = board->getPiece(row, col);
    bool selectedLocation = row == selectedRow && col == selectedCol;
    bool alliedPiece = piece != nullptr && piece->isWhite();
    bool validLocation = false;
    Tile thisTile(row, col);
    if (movableTiles.count(thisTile)) {
        validLocation = true;
    }
    //filter behavior according to checks
    if (selectedLocation || !validLocation) {
        pieceIsSelected = false;
        redraw();
    } else if (alliedPiece) {
        handleSelect(row, col);
    } else {
        bool moveGood = simulateMove(row, col);
        if (moveGood) {
            movePiece(row, col);
            checkKings();
            redraw();
        }
    }
}

void handleClick(GEvent mouseEvent) {
    int col = mouseEvent.getX() / TILE_SIZE;
    int row = mouseEvent.getY() / TILE_SIZE;
    if (pieceIsSelected && col < 8) {
        tryMove(row, col);
    } else if (col < 8) {
        handleSelect(row, col);
    }
}

int main() {
    //general initialization
    window = new GWindow(WINDOW_SIZE + 200, WINDOW_SIZE); //offset for buttons
    board = new ChessBoard();
    board->setStartingBoard();
    pieceIsSelected = false;
    selectedRow = 0;
    selectedCol = 0;
    whiteIsChecked = false;
    blackIsChecked = false;
    whiteTurn = true;
    //GWindow options
    window->setLineWidth(LINE_WIDTH);
    window->setLocation(300, 100);
    window->setBackground("black");
    window->setExitOnClose(true);
    window->setAutoRepaint(false);
    window->setTitle("Chess");
    window->setClickListener(handleClick);
    redraw();
    return 0;
}