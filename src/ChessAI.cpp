#include "ChessAI.h"
#include "Pawn.h"
#include "Queen.h"

ChessAI::ChessAI(ChessBoard* board) {
    this->board = board;
    targetDepth = 3; //change on difficulty?
}

#include <iostream>

int ChessAI::selectMove(int row, int col, int depth, ValueTree* weights) {
    //cout << "SELECT MOVE -- "  << "Row: " << row << "   Col: " << col << "   Depth: " << depth << endl;
    //handle coordinates
    if (row == 8) {
        return 1;
    }
    if (col == 8) {
        return selectMove(row + 1, 0, depth, weights);
    }
    //max depth
    if (depth == targetDepth) {
        weights->value = -board->evaluateBoard();
        return 1;
    }
    //non-max depth
    ChessPiece* piece = board->getPiece(row, col);
    if (piece != nullptr && !piece->isWhite()) {
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
    return selectMove(row, col + 1, depth, weights);
}

void ChessAI::weighBranch(int row, int col, Tile tile, ChessPiece* piece,
         int depth, ValueTree* weights) {
    //cout << "WEIGH BRANCH -- "  << "Row: " << row << "   Col: " << col << "   Depth: " << depth;
    ChessPiece* other = board->getPiece(tile.getRow(), tile.getCol());
    //special pawn handler
    ChessPiece* thisTemp = piece;
    bool makesFirstMove = false;
    bool getsPromoted = false;
    if (piece->getName() == "Pawn" && row == 6) { //before promote tile
        getsPromoted = true;
        piece = new Queen(piece->isWhite());
    } else if (piece->getName() == "Pawn" && row == 1) { //start tile
        makesFirstMove = true;
        ((Pawn*)piece)->setMoved(true);
    }
    //make move and recurse
    board->setPiece(piece, tile.getRow(), tile.getCol());
    board->setPiece(nullptr, row, col);
    ValueTree* next = new ValueTree();
    weights->next.push_back(next);
    selectMove(0, 0, depth + 1, weights->next[weights->next.size() - 1]);
    //undo move and pawn promotes
    if (getsPromoted) {
        delete piece;
        piece = thisTemp;
    }
    board->setPiece(other, tile.getRow(), tile.getCol());
    board->setPiece(piece, row, col);
    if (makesFirstMove) {
        ((Pawn*)piece)->setMoved(false);
    }
}

void ChessAI::collapseTree(ValueTree* node, int depth) {
    (void)depth;
    for (int i = 0; i < node->next.size(); i++) {
        int total2 = 0;
        for (int j = 0; j < node->next[i]->next.size(); j++) {
            int total3 = 0;
            for (int k = 0; k < node->next[i]->next[j]->next.size(); k++) {
                total3 += node->next[i]->next[j]->next[k]->value;
                delete node->next[i]->next[j]->next[k];
                node->next[i]->next[j]->next[k] = nullptr;
            }
            if (node->next[i]->next[j]->next.size() > 0) {
                total2 += (total3 / node->next[i]->next[j]->next.size());
            }
            node->next[i]->next[j]->next.clear();
            delete node->next[i]->next[j];
            node->next[i]->next[j] = nullptr;
        }
        if (node->next[i]->next.size() > 0) {
            cout << total2 << " " << node->next[i]->next.size();
            cout << total2 / node->next[i]->next.size() << endl;
            weight.push_back(total2 / node->next[i]->next.size());
        } else {
            weight.push_back(0);
        }
        node->next[i]->next.clear();
        delete node->next[i];
        node->next[i] = nullptr;
    }
    node->next.clear();

    /*if (depth > 0) {
        for (int i = 0; i < node->next.size(); i++) {
            collapseTree(node->next[i], depth - 1);
        }
    } else {
        int total = 0;
        for (int i = 0; i < node->next.size(); i++) {
            total += node->next[i]->value;
        }
        if (node->next.size() > 0) {
            node->value = total / node->next.size();
        } else {
            node->value = 0;
        }
    }*/
}

//OLD SINGLE LAYER DEPTH AI
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
            if (board->isCapturable(false, tile)) {
                endValue -= piece->getValue();
            }
            board->setPiece(other, tile.getRow(), tile.getCol());
            board->setPiece(piece, row, col);
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
    weight.clear();
    cout << "MAX WEIGHT: " << maxWeight << endl;
}

void ChessAI::makeMove() {
    /*for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            weighMoves(row, col);
        }
    }
    filterMoves();*/
    
    ValueTree* weights = new ValueTree();
    selectMove(0, 0, 0, weights);
    collapseTree(weights, 0);
    for (int i = 0; i < weights->next.size(); i++) {
        weight.push_back(weights->next[i]->value);
    }
    filterMoves();
    
    if (start.size() > 0) {
        int index = rand() % start.size();
        board->selectPiece(start[index].getRow(), start[index].getCol());
        board->movePiece(end[index].getRow(), end[index].getCol());

        cout << start[index].getRow() << ", " << start[index].getCol() << " : " << end[index].getRow() << ", " << end[index].getCol() << endl;

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