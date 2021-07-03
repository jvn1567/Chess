#include "Knight.h"

Knight::Knight(bool isWhite) : ChessPiece(isWhite) {}

unordered_map<int, int> Knight::getMoves() const {
    unordered_map<int, int> empty;
    return empty;
}

string Knight::getName() const {
    return "Knight";
}