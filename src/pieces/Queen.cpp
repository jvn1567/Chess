#include "Queen.h"

Queen::Queen(bool isWhite) : ChessPiece(isWhite) {}

unordered_map<int, int> Queen::getMoves() const {
    unordered_map<int, int> empty;
    return empty;
}

string Queen::getName() const {
    return "Queen";
}