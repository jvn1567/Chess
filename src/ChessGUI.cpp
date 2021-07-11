#include "ChessBoard.h"
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
    if (board->pieceIsSelected()) {
        //highlight selected unit
        if (row == board-> getSelectedRow() && col == board->getSelectedCol()) {
            drawTile("orange", row, col);
        }
        //highlight moveable tiles
        bool movable = false;
        unordered_set<Tile, HashTile> movableTiles = board->getMovableTiles();
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
        bool playerKingChecked = board->isWhiteTurn() && board->isCheckedWhite();
        bool pieceIsPlayerKing = piece->getName() == "King" && piece->isWhite();
        if (playerKingChecked && pieceIsPlayerKing) {
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

void handleClick(GEvent mouseEvent) {
    int col = mouseEvent.getX() / TILE_SIZE;
    int row = mouseEvent.getY() / TILE_SIZE;
    if (board->pieceIsSelected() && col < 8) {
        board->tryMove(row, col);
    } else if (col < 8) {
        board->selectPiece(row, col);
    }
    redraw();
}

int main() {
    //general initialization
    window = new GWindow(WINDOW_SIZE + 200, WINDOW_SIZE); //offset for buttons
    board = new ChessBoard();
    board->setStartingBoard();
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