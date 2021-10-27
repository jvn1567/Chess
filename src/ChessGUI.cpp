#include <unordered_set>
#include "gevent.h"
#include "gfont.h"
#include "ChessGUI.h"

ChessGUI::ChessGUI() {
    // GWindow options
    window = new GWindow(WINDOW_SIZE + PANEL_SIZE + 10, WINDOW_SIZE); // padding for edge
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
    // captured pieces box
    int piecesPerRow = PANEL_SIZE / CAPTURED_SIZE;
    capturedRows = 0;
    int pieces = 0;
    while (pieces < 15) { // maxiumum all pieces but king captured for 15 total
        capturedRows++;
        pieces += piecesPerRow;
    }
    capturedPieces = new GCanvas(PANEL_SIZE, CAPTURED_SIZE * capturedRows * 2);
    capturedPieces->setBackground("white");
    capturedPieces->setAutoRepaint(false);
    window->addToRegion(capturedPieces, "east");
    // reset button and winner label
    lblWinner = new GLabel();
    lblWinner->setColor("white");
    GFont::changeFontSize(lblWinner, 16);
    btnRestart = new GButton("New Game");
    btnRestart->setClickListener([=](){this->startNewGame();});
    GFont::changeFontSize(btnRestart, 16);
    window->addToRegion(lblWinner, "east");
    window->addToRegion(btnRestart, "east");
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

string ChessGUI::getFilename(ChessPiece* piece, bool isSmall) const {
    string filename = "";
    if (piece->isWhite()) {
        filename += "White";
    } else {
        filename += "Black";
    }
    filename += piece->getName();
    if (isSmall) {
        filename += "S";
    }
    filename += ".png";
    return filename;
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
        window->drawImage(getFilename(piece), col * TILE_SIZE, row * TILE_SIZE);
    }
}

void ChessGUI::drawCaptured() {
    capturedPieces->clear();
    priority_queue_piece captured = board->getCaptured();
    int size = captured.size();
    int whitePosition = 0;
    int blackPosition = 0;
    for (int i = 0; i < size; i++) {
        ChessPiece* piece = captured.top();
        captured.pop();
        string filename = getFilename(piece, true);
        if (piece->isWhite()) {
            int xPos = whitePosition % PANEL_SIZE;
            int yPos = ((whitePosition / PANEL_SIZE) * CAPTURED_SIZE);
            capturedPieces->drawImage(filename, xPos, yPos);
            whitePosition += CAPTURED_SIZE;
        } else {
            int xPos = blackPosition % PANEL_SIZE;
            int yPos = (((blackPosition / PANEL_SIZE) + capturedRows) * CAPTURED_SIZE);
            capturedPieces->drawImage(filename, xPos, yPos);
            blackPosition += CAPTURED_SIZE;
        }
    }
    capturedPieces->repaint();
}

void ChessGUI::redraw() {
    window->clearCanvas();
    for (int row = 0; row < 8; row ++) {
        for (int col = 0; col < 8; col++) {
            drawBackgroundTile(row, col);
            drawTileHighlight(row, col);
            drawPiece(row, col);
        }
    }
    drawCaptured();
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