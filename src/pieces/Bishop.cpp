#include "Bishop.h"

Bishop::Bishop(bool isWhite) : ChessPiece(isWhite) {}

unordered_map<int, int> Bishop::getMoves() const {
    unordered_map<int, int> empty;
    return empty;
}

string Bishop::getName() const {
    return "Bishop";
}