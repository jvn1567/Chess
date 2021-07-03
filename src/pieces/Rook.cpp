#include "Rook.h"

Rook::Rook(bool isWhite) : ChessPiece(isWhite) {}

unordered_map<int, int> Rook::getMoves() const {
    unordered_map<int, int> empty;
    return empty;
}

string Rook::getName() const {
    return "Rook";
}