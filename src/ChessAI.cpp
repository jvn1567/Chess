#include "ChessAI.h"
#include "Pawn.h"
#include "Queen.h"
#include <algorithm>

MinimaxNode::MinimaxNode(const Tile& start, const Tile& end, int value) {
    this->start = start;
    this->end = end;
    this->value = value;
}

ChessAI::ChessAI(BoardManager* board) {
    this->board = board;
    targetDepth = 4;
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
                board->selectPiece(Tile(row, col), depth == 0);
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
    // send to minimax
    MinimaxNode* root = new MinimaxNode();
    minimax(root, INT_MIN, INT_MAX, 0, false);
    // filter best moves
    MinimaxNode* bestMove = nullptr;
    int bestValue = INT_MAX; // black AI wants to minimize
    for (MinimaxNode* move : root->next) {
        if (move->value < bestValue) {
            bestValue = move->value;
            bestMove = move;
        }
    }
    // handle game over or tied scores
    if (bestMove != nullptr) {
        board->selectPiece(bestMove->start);
        board->movePiece(bestMove->end);
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
}