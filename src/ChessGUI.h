/**
 * @file ChessGUI.h
 * @author John Nguyen (https://github.com/jvn1567)
 * @brief This class creates a GUI for a chess game using the
 * Standard Graphics Library by Marty Stepp (https://github.com/stepp/sgl).
 * @version 0.1
 * @date 2021-11-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _ChessGUI_h
#define _ChessGUI_h

#include <string>
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
    static const int PANEL_SIZE = 200; // side panel size, divisible by small image size
    static const int LINE_WIDTH = 4; // thickness of tile highlighters
    static const int TILE_SIZE = WINDOW_SIZE / 8; // equal to large image size
    static const int CAPTURED_SIZE = 25;
    GWindow* window;
    GCanvas* capturedPieces;
    BoardManager* board;
    ChessAI* ai;
    GLabel* lblWinner;
    GButton* btnRestart;
    int capturedRows;

    /**
     * Creates the menu on the right hand side, containing the captured pieces
     * and reset game button.
     */
    void generateMenu();

    /**
     * Creates a filled tile of length and width TILE_SIZE, at the passed-in
     * row and column location and color.
     */
    void fillTile(string color, int row, int col);

    /**
     * Creates an unfilled tile of length and width TILE_SIZE, at the passed-in
     * row and column location and color.
     */
    void drawTile(string color, int row, int col);

    /**
     * Creates the 8x8 tile checkered background for the board.
     */
    void drawBackgroundTile(int row, int col);

    /**
     * Checks whether a tile highlight needs to be drawn on the tile at the
     * passed-in row and column and draws one of the correct color as
     * needed.
     */
    void drawTileHighlight(int row, int col);

    /**
     * Appends items to a string to get the image filename for the passed-in
     * piece.
     */
    string getFilename(ChessPiece* piece, bool isSmall = false) const;

    /**
     * Draws the piece at the passed-in row and column, if one exists there
     * on the board.
     */
    void drawPiece(int row, int col);

    /**
     * Redraws the captured pieces onto the canvas on the right side menu.
     */
    void drawCaptured();

    /**
     * Redraws the entire chess board.
     */
    void redraw();

    /**
     * Restarts the game.
     */
    void startNewGame();

    /**
     * Checks whether the game has ended, and prompts the AI to make a move
     * if the game has not ended.
     */
    void checkGame();

    /**
     * Attempts to select a piece or make a move for the player on click,
     * depending on whether a piece is currently already selected.
     */
    void handleClick(GEvent mouseEvent);

public:
    /**
     * @brief Creates a ChessGUI, which will run a chess game.
     * 
     */
    ChessGUI();
};

#endif