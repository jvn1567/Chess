#include "ChessAI.h"
#include "Pawn.h"
#include "Queen.h"
#include <algorithm>

//BORROWED TIMING CODE
#include <sys/time.h>
typedef unsigned long long timestamp_t;
static timestamp_t get_timestamp () {
    struct timeval now;
    gettimeofday (&now, NULL);
    return  now.tv_usec + (timestamp_t)now.tv_sec * 1000000;
}

MinimaxNode::MinimaxNode(const Tile& start, const Tile& end, int value) {
    this->start = start;
    this->end = end;
    this->value = value;
}

ChessAI::ChessAI(BoardManager* board) {
    this->board = board;
    targetDepth = 3;
}

void ChessAI::clearChildren(MinimaxNode*& node, int depth) {
    if (depth > 0) {
        for (int i = 0; i < node->next.size(); i++) {
            delete node->next[i];
        }
        node->next.clear();
    }
}

int ChessAI::minimax(MinimaxNode*& node, int alpha, int beta, int depth, bool isWhite) {
    if (depth == targetDepth) {
        node->value = board->getBoardValue();
        return board->getBoardValue();
    }
    int limit = isWhite ? INT_MIN : INT_MAX;
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            ChessPiece* piece = board->getPiece(row, col);
            if ((piece != nullptr) && (piece->isWhite() == isWhite)) {
                board->selectPiece(Tile(row, col));
                for (Tile end : board->getMovableTiles()) {
                    int size = node->next.size();
                    node->next.push_back(new MinimaxNode(Tile(row, col), end));
                    int moveValue = simulateMove(node->next[size], alpha, beta, depth, isWhite);
                    if (isWhite) {
                        limit = max(limit, moveValue);
                        alpha = max(alpha, moveValue);
                    } else {
                        limit = min(limit, moveValue);
                        beta = min(beta, moveValue);
                    }
                    if (alpha >= beta) {
                        clearChildren(node, depth);
                        node->value = limit;
                        return limit;
                    }
                }
            }
        }
    }
    clearChildren(node, depth);
    node->value = limit;
    return limit;
}

int ChessAI::simulateMove(MinimaxNode*& node, int alpha, int beta, int depth, bool isWhite) {
    ChessPiece* piece = board->getPiece(node->start);
    ChessPiece* target = board->getPiece(node->end);
    // stop recursion on game over
    if (target != nullptr && target->getName() == "King") {
        return board->getBoardValue() - target->getValue();
    }
    // store original state for pawns
    ChessPiece* thisTemp = piece;
    bool makesFirstMove = false;
    bool getsPromoted = false;
    bool isPawn = piece->getName() == "Pawn";
    bool promotableBlack = node->start.row == 6 && !piece->isWhite();
    bool promotableWhite = node->start.row == 1 && piece->isWhite();
    if (isPawn && (promotableBlack || promotableWhite)) {
        getsPromoted = true;
        board->changeBoardValue(-piece->getValue());
        piece = new Queen(piece->isWhite());
        board->changeBoardValue(piece->getValue());
    } else if (isPawn && !((Pawn*)piece)->getHasMoved()) { //start tile
        makesFirstMove = true;
        ((Pawn*)piece)->setMoved(true);
    }
    // make move and recurse
    if (target != nullptr) {
        board->changeBoardValue(-target->getValue());
    }
    board->setPiece(piece, node->end);
    board->setPiece(nullptr, node->start);
    board->changeTurns();
    int limit = minimax(node, alpha, beta, depth + 1, !isWhite);
    // undo move and pawn promotes
    if (getsPromoted) {
        board->changeBoardValue(-piece->getValue());
        delete piece;
        piece = thisTemp;
        board->changeBoardValue(piece->getValue());
    }
    if (target != nullptr) {
        board->changeBoardValue(target->getValue());
    }
    board->setPiece(target, node->end);
    board->setPiece(piece, node->start);
    board->changeTurns();
    if (makesFirstMove) {
        ((Pawn*)piece)->setMoved(false);
    }
    return limit;
}

void ChessAI::makeMove() {
    timestamp_t t0 = get_timestamp();

    // send to minimax
    MinimaxNode* root = new MinimaxNode();
    minimax(root, INT_MIN, INT_MAX, 0, false);
    // filter best moves
    vector<MinimaxNode*> bestMoves;
    int bestValue = INT_MAX; // black AI wants to minimize
    for (MinimaxNode* move : root->next) {
        if (move->value < bestValue) {
            bestValue = move->value;
            bestMoves.clear();
            bestMoves.push_back(move);
        } else if (move->value == bestValue) {
            bestMoves.push_back(move);
        }
    }
    // handle game over or tied scores
    if (bestMoves.size() > 0) {
        int index = 0;
        board->selectPiece(bestMoves[index]->start);
        board->movePiece(bestMoves[index]->end);
    } else if (board->isCheckedBlack()) {
        board->setWinner("White");
    } else {
        board->setWinner("No one");
    }
    // free nodes
    for (int i = 0; i < root->next.size(); i++) {
        delete root->next[i];
    }
    delete root;

    timestamp_t t1 = get_timestamp();
    double secs = (t1 - t0) / 1000000.0L;
    cout << secs << endl;
}














// ChessAI::ChessAI(BoardManager* board) {
//     vector<Tile> start;
//     vector<Tile> end;
//     vector<int> weight;
//     this->board = board;
//     targetDepth = 3; //change on difficulty?
// }

// #include <iostream>

// bool ChessAI::selectMove(int row, int col, int depth, ValueTree* weights, bool isWhite) {
//     //handle coordinates
//     if (row == 8) {
//         return true;
//     }
//     if (col == 8) {
//         return selectMove(row + 1, 0, depth, weights, isWhite);
//     }
//     //max depth, put weight on leaf
//     if (depth == targetDepth) {
//         weights->value = board->getBoardValue(); //TODO: return weight to compare and place on parent node
//         return true;
//     }
//     //non-max depth, explore all branches
//     ChessPiece* piece = board->getPiece(row, col);
//     if (piece != nullptr) {
//         if (piece->isWhite() == isWhite) {
//             board->selectPiece(Tile(row, col));
//             unordered_set<Tile, HashTile> moves = board->getMovableTiles();
//             for (Tile tile : moves) {
//                 if (depth == 0) {
//                     start.push_back(Tile(row, col));
//                     end.push_back(tile);
//                 }
//                 weighBranch(row, col, tile, piece, depth, weights);
//             }
//         }
//     }
//     return selectMove(row, col + 1, depth, weights, isWhite);
// }

// void ChessAI::weighBranch(int row, int col, Tile tile, ChessPiece* piece,
//          int depth, ValueTree* weights) {
//     ChessPiece* other = board->getPiece(tile);
//     //special pawn handler
//     ChessPiece* thisTemp = piece;
//     bool makesFirstMove = false;
//     bool getsPromoted = false;
//     bool isPawn = piece->getName() == "Pawn";
//     bool promotableBlack = row == 6 && !piece->isWhite();
//     bool promotableWhite = row == 1 && piece->isWhite();
//     if (isPawn && (promotableBlack || promotableWhite)) {
//         getsPromoted = true;
//         board->changeBoardValue(-piece->getValue());
//         piece = new Queen(piece->isWhite());
//         board->changeBoardValue(piece->getValue());
//     } else if (isPawn && !((Pawn*)piece)->getHasMoved()) { //start tile
//         makesFirstMove = true;
//         ((Pawn*)piece)->setMoved(true);
//     }
//     //make move and recurse
//     if (other != nullptr) {
//         board->changeBoardValue(-other->getValue());
//     }
//     board->setPiece(piece, tile);
//     board->setPiece(nullptr, row, col);
//     board->changeTurns();
//     ValueTree* next = new ValueTree();
//     weights->next.push_back(next);
//     selectMove(0, 0, depth + 1, weights->next[weights->next.size() - 1], !piece->isWhite());
//     //undo move and pawn promotes
//     if (getsPromoted) {
//         board->changeBoardValue(-piece->getValue());
//         delete piece;
//         piece = thisTemp;
//         board->changeBoardValue(piece->getValue());
//     }
//     if (other != nullptr) {
//         board->changeBoardValue(other->getValue());
//     }
//     board->setPiece(other, tile);
//     board->setPiece(piece, row, col);
//     board->changeTurns();
//     if (makesFirstMove) {
//         ((Pawn*)piece)->setMoved(false);
//     }
// }

// int ChessAI::minimax(ValueTree* weights, bool minimize) {
//     int size = weights->next.size();
//     if (size == 0) {
//         return weights->value;
//     }
//     int limit = minimax(weights->next[0], !minimize);
//     for (int i = 1; i < size; i++) {
//         int current = minimax(weights->next[i], !minimize);
//         if ((minimize && (current < limit)) || (!minimize && (current > limit))) {
//             limit = current;
//         }
//     }
//     weights->value = limit;
//     return limit;
// }

// void ChessAI::filterMoves() {
//     int minWeight = 9999;
//     vector<Tile> minStart;
//     vector<Tile> minEnd;
//     for (int i = 0; i < weight.size(); i++) {
//         if (weight[i] < minWeight) {
//             minStart.clear();
//             minEnd.clear();
//             minWeight = weight[i];
//             minStart.push_back(start[i]);
//             minEnd.push_back(end[i]);
//         } else if (weight[i] == minWeight) {
//             minStart.push_back(start[i]);
//             minEnd.push_back(end[i]);
//         }
//     }
//     start = minStart;
//     end = minEnd;
//     weight.clear();
// }

// void ChessAI::makeMove() {
//     timestamp_t t0 = get_timestamp();

//     ValueTree* weights = new ValueTree();
//     selectMove(0, 0, 0, weights, false);

//     timestamp_t t1 = get_timestamp();
//     double secs = (t1 - t0) / 1000000.0L;
//     cout << secs << endl;

//     minimax(weights, true);
//     for (int i = 0; i < weights->next.size(); i++) {
//         weight.push_back(weights->next[i]->value);
//     }
//     filterMoves();

//     //pick random move if many equal valued moves and handle checkmate
//     if (start.size() > 0) {
//         int index = rand() % start.size();
//         board->selectPiece(start[index]);
//         board->movePiece(end[index]);
//     } else if (board->isCheckedBlack()) {
//         board->setWinner("White");
//     } else {
//         board->setWinner("No one");
//     }
//     delete weights;
//     weights = nullptr;
//     start.clear();
//     end.clear();
// }