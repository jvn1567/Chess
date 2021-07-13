#include "ChessAI.h"

ChessAI::ChessAI(ChessBoard* board) {
    this->board = board;
}

int ChessAI::weighPiece(string name) const {
    if (name == "Pawn") {
        return 1;
    } else if (name == "Knight" || name == "Bishop") {
        return 3;
    } else if (name == "Rook") {
        return 5;
    } else { //Queen
        return 8;
    }
}

void ChessAI::weighMoves(int row, int col) {
    ChessPiece* piece = board->getPiece(row, col);
    if (piece != nullptr && !piece->isWhite()) {
        board->selectPiece(row, col);
        unordered_set<Tile, HashTile> moves = board->getMovableTiles();
        //weigh risk of losing piece by staying
        int stayRisk;
        if (board->isCapturable(false, Tile(row, col))) {
            stayRisk = weighPiece(piece->getName());
        }
        for (Tile tile : moves) {
            //weigh capture value of any piece at the tile
            int moveWeight = stayRisk;
            ChessPiece* other = board->getPiece(tile.getRow(), tile.getCol());
            if (other != nullptr && other->isWhite()) {
                moveWeight += weighPiece(other->getName());
            }
            //weigh risk of losing the piece after moving to the tile
            board->setPiece(piece, tile.getRow(), tile.getCol());
            if (board->isCapturable(false, Tile(tile.getRow(), tile.getCol()))) {
                moveWeight -= weighPiece(piece->getName());
            }
            board->setPiece(other, tile.getRow(), tile.getCol());
            //adds move data of tiles not occupied by allies
            if (other == nullptr || other->isWhite()) {
                start.push_back(Tile(row, col));
                end.push_back(tile);
                weight.push_back(moveWeight);
            }
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
    } else {
        //HANDLE CHECKMATE PLACEHOLDER
        cout << "CHECKMATE" << endl;
    }
    start.clear();
    end.clear();
}