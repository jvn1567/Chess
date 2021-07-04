#ifndef _ChessGUI_h
#define _ChessGUI_h

#include "gwindow.h"
#include "gevent.h"
#include "ChessBoard.h"
using namespace sgl;
using namespace std;

typedef void (*actionFunc)(int, int);

static const int WINDOW_SIZE = 800; //may break if not divisible by 8
static const int TILE_SIZE = WINDOW_SIZE / 8;

class ChessGUI {
private:
    GWindow* window;
    ChessBoard* board;
    bool selected;
    unordered_map<int, int> movableTiles;
    void redraw();
    void fillTile(string color, int row, int col);
    void drawBackgroundTile(int row, int col);
    void drawTileHighlight(int row, int col);
    void drawPiece(int row, int col);
public:
    ChessGUI();
    ChessBoard* getBoard() const;
    bool pieceIsSelected() const; 
};

#endif