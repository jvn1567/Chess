#include "ChessAI.h"

ChessAI::ChessAI(ChessBoard* board) {
    this->board = board;
}

//recycle for minimax recursion
void ChessAI::weighMoves(int row, int col) {
    ChessPiece* piece = board->getPiece(row, col);
    if (piece != nullptr && !piece->isWhite()) {
        board->selectPiece(row, col);
        unordered_set<Tile, HashTile> moves = board->getMovableTiles();
        for (Tile tile : moves) {
            //weigh board value change
            int startValue = board->evaluateBoard();
            ChessPiece* other = board->getPiece(tile.getRow(), tile.getCol());
            board->setPiece(piece, tile.getRow(), tile.getCol());
            board->setPiece(nullptr, row, col);
            int endValue = board->evaluateBoard();
            board->setPiece(other, tile.getRow(), tile.getCol());
            board->setPiece(piece, row, col);
            //temporary smartening, isCapturable will be deleted
            if (board->isCapturable(false, tile)) {
                endValue -= piece->getValue();
            }
            if (board->isCapturable(false, Tile(row, col))) {
                startValue -= piece->getValue();
            }
            //adds move data
            start.push_back(Tile(row, col));
            end.push_back(tile);
            weight.push_back(startValue - endValue); //want value to decrease
        }
    }
}

void ChessAI::filterMoves() {
    int maxWeight = -999;
    vector<Tile> maxStart;
    vector<Tile> maxEnd;
    for (int i = 0; i < weight.size(); i++) {
        if (weight[i] > maxWeight) {
            maxStart.clear();
            maxEnd.clear();
            maxWeight = weight[i];
            maxStart.push_back(start[i]);
            maxEnd.push_back(end[i]);
        } else if (weight[i] == maxWeight) {
            maxStart.push_back(start[i]);
            maxEnd.push_back(end[i]);
        }
    }
    start = maxStart;
    end = maxEnd;
    weight.clear();
}

#include <iostream>

void ChessAI::makeMove() {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            weighMoves(row, col);
        }
    }
    filterMoves();
    if (start.size() > 0) {
        int index = rand() % start.size();
        board->selectPiece(start[index].getRow(), start[index].getCol());
        board->movePiece(end[index].getRow(), end[index].getCol());
    } else if (board->isCheckedBlack()) {
        board->setWinner("White");
    } else {
        board->setWinner("No one");
    }
    start.clear();
    end.clear();
}