#include "ChessPiece.h"

ChessPiece::ChessPiece(bool isWhite) {
    this->isWhite = isWhite;
}

unordered_map<int, int> ChessPiece::getMoves() const {
    unordered_map<int, int> empty;
    return empty;
}

string ChessPiece::getName() const {
    return "ChessPiece";
}