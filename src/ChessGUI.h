#ifndef _ChessGUI_h
#define _ChessGUI_h

#include <string>
#include <unordered_set>
#include "gwindow.h"
#include "gcanvas.h"
#include "gbutton.h"
#include "glabel.h"
#include "ChessAI.h"
#include "BoardManager.h"
using namespace sgl;
using namespace std;

class ChessGUI {
private:
    static const int WINDOW_SIZE = 800; // may break if not divisible by 8
    static const int PANEL_SIZE = 200; // preferred divisible by small image size
    static const int LINE_WIDTH = 4; // thickness of tile highlighters
    static const int TILE_SIZE = WINDOW_SIZE / 8; // equal to large image size
    static const int CAPTURED_SIZE = 25;
    GWindow* window;
    GCanvas* capturedPieces;
    BoardManager* board;
    ChessAI* ai;
    GLabel* lblWinner;
    GButton* btnRestart;
    void generateMenu();
    void fillTile(string color, int row, int col);
    void drawTile(string color, int row, int col);
    void drawBackgroundTile(int row, int col);
    void drawTileHighlight(int row, int col);
    string getFilename(ChessPiece* piece, bool isSmall = false) const;
    void drawPiece(int row, int col);
    void drawCaptured();
    void redraw();
    void startNewGame();
    void checkGame();
    void handleClick(GEvent mouseEvent);
public:
    ChessGUI();
};

#endif