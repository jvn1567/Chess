#include "Pawn.h"

Pawn::Pawn(bool isWhite) : ChessPiece(isWhite) {
    hasMoved = false;
}

unordered_map<int, int> Pawn::getMoves() const {
    unordered_map<int, int> empty;
    return empty;
}

string Pawn::getName() const {
    return "Pawn";
}

void Pawn::setMoved() {
    hasMoved = true;
}