#include "King.h"

King::King(bool isWhite) : ChessPiece(isWhite) {}

unordered_map<int, int> King::getMoves() const {
    unordered_map<int, int> empty;
    return empty;
}

string King::getName() const {
    return "King";
}