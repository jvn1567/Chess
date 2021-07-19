#include "ChessAI.h"
#include "Pawn.h"
#include "Queen.h"

ChessAI::ChessAI(ChessBoard* board) {
    this->board = board;
    targetDepth = 3; //change on difficulty?
}

#include <iostream>

bool ChessAI::selectMove(int row, int col, int depth, ValueTree* weights, bool isWhite) {
    //handle coordinates
    if (row == 8) {
        return true;
    }
    if (col == 8) {
        return selectMove(row + 1, 0, depth, weights, isWhite);
    }
    //max depth, put weight on leaf
    if (depth == targetDepth) {
        weights->value = board->evaluateBoard();
        return true;
    }
    //non-max depth, explore all branches
    ChessPiece* piece = board->getPiece(row, col);
    if (piece != nullptr) {
        if (piece->isWhite() == isWhite) {
            board->selectPiece(row, col);
            unordered_set<Tile, HashTile> moves = board->getMovableTiles();
            for (Tile tile : moves) {
                if (depth == 0) {
                    start.push_back(Tile(row, col));
                    end.push_back(tile);
                }
                weighBranch(row, col, tile, piece, depth, weights);
            }
        }
    }
    return selectMove(row, col + 1, depth, weights, isWhite);
}

void ChessAI::weighBranch(int row, int col, Tile tile, ChessPiece* piece,
         int depth, ValueTree* weights) {
    ChessPiece* other = board->getPiece(tile.getRow(), tile.getCol());
    //special pawn handler
    ChessPiece* thisTemp = piece;
    bool makesFirstMove = false;
    bool getsPromoted = false;
    bool isPawn = piece->getName() == "Pawn";
    bool promotableBlack = row == 6 && !piece->isWhite();
    bool promotableWhite = row == 1 && piece->isWhite();
    if (isPawn && (promotableBlack || promotableWhite)) {
        getsPromoted = true;
        piece = new Queen(piece->isWhite());
    } else if (isPawn && !((Pawn*)piece)->getHasMoved()) { //start tile
        makesFirstMove = true;
        ((Pawn*)piece)->setMoved(true);
    }
    //make move and recurse
    board->setPiece(piece, tile.getRow(), tile.getCol());
    board->setPiece(nullptr, row, col);
    board->changeTurns();
    ValueTree* next = new ValueTree();
    weights->next.push_back(next);
    selectMove(0, 0, depth + 1, weights->next[weights->next.size() - 1], !piece->isWhite());
    //undo move and pawn promotes
    if (getsPromoted) {
        delete piece;
        piece = thisTemp;
    }
    board->setPiece(other, tile.getRow(), tile.getCol());
    board->setPiece(piece, row, col);
    board->changeTurns();
    if (makesFirstMove) {
        ((Pawn*)piece)->setMoved(false);
    }
}

int ChessAI::minimax(ValueTree* weights, bool minimize) {
    int size = weights->next.size();
    //leaf
    if (size == 0) {
        return weights->value;
    }
    //branches
    int limit = minimax(weights->next[0], !minimize);
    for (int i = 1; i < size; i++) {
        int current = minimax(weights->next[i], !minimize);
        if ((minimize && (current < limit)) || (!minimize && (current > limit))) {
            limit = current;
        }
    }
    weights->value = limit;
    return limit;
}

void ChessAI::filterMoves() {
    int maxWeight = -9999;
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
    cout << "   MAX: " << maxWeight << endl;
    weight.clear();
}

void ChessAI::makeMove() {
    ValueTree* weights = new ValueTree();
    selectMove(0, 0, 0, weights, true);
    minimax(weights, false);
    for (int i = 0; i < weights->next.size(); i++) {
        weight.push_back(weights->next[i]->value);
    }
    filterMoves();
    //pick random move if many equal valued moves and handle checkmate
    if (start.size() > 0) {
        int index = rand() % start.size();
        board->selectPiece(start[index].getRow(), start[index].getCol());
        board->movePiece(end[index].getRow(), end[index].getCol());
    } else if (board->isCheckedBlack()) {
        board->setWinner("White");
    } else {
        board->setWinner("No one");
    }
    delete weights;
    weights = nullptr;
    start.clear();
    end.clear();
}