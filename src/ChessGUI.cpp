#include "ChessBoard.h"
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
unordered_map<int, int> movableTiles;

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
            cout << pieceIsSelected << endl;
            fillTile("blue", row, col);
        }
        //highlight moveable tiles
        try {
            int col2 = movableTiles.at(row);
            bool movable = col == col2;
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
        } catch (exception ex) {
            //do nothing
            (void)ex;
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
        movableTiles = board->getMoves(row, col);
    redraw();
    }
}

void handleMove(int row, int col) {
    pieceIsSelected = false;
    redraw();
}

void handleClick(GEvent mouseEvent) {
    int col = mouseEvent.getX() / TILE_SIZE;
    int row = mouseEvent.getY() / TILE_SIZE;
    if (pieceIsSelected) {
        handleMove(row, col);
    } else {
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
    cout << "check1" << endl;
    redraw();
    cout << "check2" << endl;
    return 0;
}