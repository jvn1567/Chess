#include "ChessBoard.h"
#include "King.h"
#include "Queen.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Pawn.h"

ChessBoard::ChessBoard() {
    board = new vector<vector<ChessPiece*>>;
    for (int row = 0; row < 8; row++) {
        vector<ChessPiece*> newRow;
        for (int col = 0; col < 8; col++) {
            newRow.push_back(nullptr);
        }
        board->push_back(newRow);
    }
}

void ChessBoard::setStartingBoard() {
    for (int col = 0; col < 8; col ++) {
        (*board)[1][col] = new Pawn(false);
        (*board)[6][col] = new Pawn(true);
    }
    setBackRow(0, false);
    setBackRow(7, true);
}

void ChessBoard::setBackRow(int row, bool isWhite) {
    (*board)[row][0] = new Rook(isWhite);
    (*board)[row][1] = new Knight(isWhite);
    (*board)[row][2] = new Bishop(isWhite);
    (*board)[row][3] = new Queen(isWhite);
    (*board)[row][4] = new King(isWhite);
    (*board)[row][5] = new Bishop(isWhite);
    (*board)[row][6] = new Knight(isWhite);
    (*board)[row][7] = new Rook(isWhite);
}

ChessPiece* ChessBoard::getPiece(int row, int col) const {
    return (*board)[row][col];
}

void ChessBoard::setPiece(ChessPiece* piece, int row, int col) {
    (*board)[row][col] = piece;
}