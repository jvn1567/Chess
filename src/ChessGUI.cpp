#include "ChessGUI.h"
#include <iomanip>
#include <string>
#include "gthread.h"
#include "gwindow.h"
#include "gbutton.h"
#include "gevent.h"
#include "glabel.h"
#include "gobjects.h"
#include "gradiobutton.h"
#include "gtextfield.h"

//mouse listener handlers don't work as member functions, prototyping here
void processMouseEvent(GEvent mouseEvent);
void selectPiece();

//click handler function prototype
actionFunc funcClick = nullptr;

ChessGUI::ChessGUI() {
    //general initialization
    window = new GWindow(WINDOW_SIZE + 200, WINDOW_SIZE); //offset for buttons
    board = new ChessBoard();
    selected = false;
    board->setStartingBoard();
    window->setLocation(300, 100);
    window->setBackground("black");
    window->setExitOnClose(true);
    window->setAutoRepaint(false);
    window->setTitle("Chess");
    window->setMouseListener(processMouseEvent);
    redraw();
}

ChessBoard* ChessGUI::getBoard() const {
    return board;
}

bool ChessGUI::pieceIsSelected() const {
    return selected;
}

void ChessGUI::redraw() {
    for (int row = 0; row < 8; row ++) {
        for (int col = 0; col < 8; col++) {
            drawBackgroundTile(row, col);
            drawTileHighlight(row, col);
            drawPiece(row, col);
        }
    }
    window->repaint();
}

void ChessGUI::fillTile(string color, int row, int col) {
    window->setColor(color);
    window->fillRect(col * TILE_SIZE, row * TILE_SIZE, TILE_SIZE, TILE_SIZE);
}

void ChessGUI::drawBackgroundTile(int row, int col) {
    if ((row % 2 == 0) ^ (col % 2 == 0)) {
        fillTile("dark gray", row, col);
    } else {
        fillTile("gray", row, col);
    }
}

void ChessGUI::drawTileHighlight(int row, int col) {
    if (selected) {
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
        }
    }
}

void ChessGUI::drawPiece(int row, int col) {
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

void processMouseEvent(GEvent mouseEvent) {
    int col = mouseEvent.getX() / TILE_SIZE;
    int row = mouseEvent.getY() / TILE_SIZE;
    //funcClick(row, col);
}

void setClickFunction(actionFunc func) {
    funcClick = func;
}

void selectPiece() {
    
}