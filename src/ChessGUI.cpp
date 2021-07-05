#include "ChessBoard.h"
#include "Pawn.h"
#include <iomanip>
#include <string>
#include "gwindow.h"
#include "gbutton.h"
#include "gevent.h"
#include "glabel.h"
using namespace sgl;
using namespace std;

static const int WINDOW_SIZE = 800; //may break if not divisible by 8
static const int TILE_SIZE = WINDOW_SIZE / 8;

//global variables
GWindow* window;
ChessBoard* board;
bool pieceIsSelected;
int selectedRow;
int selectedCol;
unordered_set<Tile*> movableTiles;

void fillTile(string color, int row, int col) {
    window->setColor(color);
    window->fillRect(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE);
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
            fillTile("blue", row, col);
        }
        //highlight moveable tiles
        bool movable = false;
        for (Tile* available : movableTiles) {
            if (available->getCol() == col && available->getRow() == row) {
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
            fillTile("yellow", row, col);
        } else if (movable && containsEnemy) {
            fillTile("red", row, col);
        }
    }
}

void drawPiece(int row, int col) {
    ChessPiece* piece = board->getPiece(row, col);
    if (piece != nullptr) {
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

void handleSelect(int row, int col) {
    ChessPiece* piece = board->getPiece(row, col);
    if (piece != nullptr && piece->isWhite()) {
        selectedRow = row;
        selectedCol = col;
        pieceIsSelected = true;
        //free previous memory
        for (Tile* ptr : movableTiles) {
            delete ptr;
        }
        movableTiles = board->getMoves(row, col);
    redraw();
    }
}

void handleMove(int row, int col) {
    //checks
    ChessPiece* piece = board->getPiece(row, col);
    bool selectedLocation = row == selectedRow && col == selectedCol;
    bool alliedPiece = piece != nullptr && piece->isWhite();
    bool validLocation = false;
    Tile thisTile(row, col);
    for (Tile* tile : movableTiles) {
        if (*tile == thisTile) {
            validLocation = true;
        }
    }
    //filter for behavior
    if (selectedLocation || !validLocation) {
        pieceIsSelected = false;
        redraw();
    } else if (alliedPiece) {
        handleSelect(row, col);
    } else {
        ChessPiece* old = board->getPiece(selectedRow, selectedCol);
        if (old->getName() == "Pawn") {
            ((Pawn*)old)->setMoved();
        }
        board->setPiece(old, row, col);
        board->setPiece(nullptr, selectedRow, selectedCol);
        pieceIsSelected = false;
        redraw();
    }
}

void handleClick(GEvent mouseEvent) {
    int col = mouseEvent.getX() / TILE_SIZE;
    int row = mouseEvent.getY() / TILE_SIZE;
    if (pieceIsSelected && col < 8) {
        handleMove(row, col);
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
    window->setLocation(300, 100);
    window->setBackground("black");
    window->setExitOnClose(true);
    window->setAutoRepaint(false);
    window->setTitle("Chess");
    window->setClickListener(handleClick);
    redraw();
    return 0;
}