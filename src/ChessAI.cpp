#include "ChessAI.h"

ChessAI::ChessAI(ChessBoard* board) {
    this->board = board;
}

int ChessAI::weighPiece(string name) const {
    if (name == "Pawn") {
        return 1;
    } else if (name == "Knight" || name == "Bishop") {
        return 2;
    } else if (name == "Rook") {
        return 3;
    } else {
        return 4;
    }
}

void ChessAI::weighMoves(int row, int col) {
    Tile startTile(row, col);
    ChessPiece* piece = board->getPiece(row, col);
    if (piece != nullptr && !piece->isWhite()) {
        board->selectPiece(row, col);
        unordered_set<Tile, HashTile> moves = board->getMovableTiles();
        for (Tile tile : moves) {
            int moveWeight = 0;
            ChessPiece* other = board->getPiece(tile.getRow(), tile.getCol());
            if (other != nullptr && other->isWhite()) {
                moveWeight += weighPiece(other->getName());
            }
            //adds tiles without allies to possible moves
            if (other == nullptr || other->isWhite()) {
                start.push_back(startTile);
                end.push_back(tile);
                weight.push_back(moveWeight);
            }
        }
    }
}

void ChessAI::filterMoves() {
    int maxWeight = 0;
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
    } else {
        //CHECKMATE
    }
    start.clear();
    end.clear();
}