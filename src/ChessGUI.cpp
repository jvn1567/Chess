#include "gevent.h"
#include "gfont.h"
#include "ChessGUI.h"

ChessGUI::ChessGUI() {
    // GWindow options
    window = new GWindow(WINDOW_SIZE + 200, WINDOW_SIZE); //offset for buttons
    window->setLineWidth(LINE_WIDTH);
    window->setLocation(300, 100);
    window->setBackground("black");
    window->setExitOnClose(true);
    window->setAutoRepaint(false);
    window->setTitle("Chess");
    // other initialization
    generateMenu();
    board = new BoardManager();
    ai = new ChessAI(board);
    window->setClickListener([=](GEvent event){this->handleClick(event);});
    window->setTimerListener(500, [this] {
        checkGame();
    });
    redraw();
}

void ChessGUI::generateMenu() {
    lblWinner = new GLabel();
    lblWinner->setColor("white");
    GFont::changeFontSize(lblWinner, 16);
    btnRestart = new GButton("New Game");
    btnRestart->setClickListener([=](){this->startNewGame();});
    GFont::changeFontSize(btnRestart, 16);
    window->addToRegion(lblWinner, "EAST");
    window->addToRegion(btnRestart, "EAST");
}

void ChessGUI::fillTile(string color, int row, int col) {
    window->setColor(color);
    int tempSize = TILE_SIZE - LINE_WIDTH;
    window->fillRect(col * TILE_SIZE, row * TILE_SIZE, tempSize, tempSize);
}

void ChessGUI::drawTile(string color, int row, int col) {
    window->setColor(color);
    int tempSize = TILE_SIZE - LINE_WIDTH;
    window->drawRect(col * TILE_SIZE, row * TILE_SIZE, tempSize, tempSize);
}

void ChessGUI::drawBackgroundTile(int row, int col) {
    if ((row % 2 == 0) ^ (col % 2 == 0)) {
        fillTile("dark gray", row, col);
    } else {
        fillTile("gray", row, col);
    }
}

void ChessGUI::drawTileHighlight(int row, int col) {
    if (board->pieceIsSelected()) {
        // highlight selected unit
        if (board->isSelectedPiece(row, col)) {
            drawTile("orange", row, col);
        }
        // highlight moveable tiles
        bool movable = board->isMovableTile(row, col);
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

void ChessGUI::drawPiece(int row, int col) {
    ChessPiece* piece = board->getPiece(row, col);
    if (piece != nullptr) {
        // checked king marker
        bool playerKingChecked = board->isWhiteTurn() && board->isCheckedWhite();
        bool isPlayerKing = piece->getName() == "King" && piece->isWhite();
        bool aiKingChecked = !board->isWhiteTurn() && board->isCheckedBlack();
        bool isAiKing = piece->getName() == "King" && !piece->isWhite();
        if ((playerKingChecked && isPlayerKing) || (aiKingChecked && isAiKing)){
            fillTile("red", row, col);
        }
        // draw piece
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

void ChessGUI::startNewGame() {
    board->restartGame();
    lblWinner->setText("");
}

void ChessGUI::checkGame() {
    if (board->getWinner() == "") {
        if (!board->isWhiteTurn()) {
            ai->makeMove();
        }
        if (board->isCheckedWhite() && !board->whiteCanMove()) {
            board->setWinner("Black");
        } else if (!board->isCheckedWhite() && !board->whiteCanMove()) {
            board->setWinner("No one");
        }
    } else {
        lblWinner->setText(board->getWinner() + " wins!");
    }
    redraw();
}

void ChessGUI::handleClick(GEvent mouseEvent) {
    if (board->isWhiteTurn()) {
        int col = mouseEvent.getX() / TILE_SIZE;
        int row = mouseEvent.getY() / TILE_SIZE;
        if (board->pieceIsSelected() && col < 8) {
            board->tryMove(Tile(row, col));
        } else if (col < 8) {
            board->selectPiece(Tile(row, col));
        }
        redraw();
    }
}