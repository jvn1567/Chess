/**
 * @file BoardManager.h
 * @author John Nguyen (https://github.com/jvn1567)
 * @brief This class stores a 2D array containing a chess board and handles
 * the game state.
 * @version 0.1
 * @date 2021-11-22
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#ifndef _BoardManager_h
#define _BoardManager_h

#include <vector>
#include <queue>
#include "ChessPiece.h"
#include "Tile.h"
using namespace std;

class BoardManager {
private:
    vector<vector<ChessPiece*>> board;
    bool whiteIsChecked;
    bool blackIsChecked;
    bool whiteTurn;
    bool selected;
    int boardValue;
    Tile selectedTile;
    string winner;
    unordered_set<Tile, HashTile> movableTiles;
    priority_queue_piece captured;

    /**
     * Resets all game state values to their default start values.
     */
    void resetGameState();

    /**
     * Sets the back row of pieces, including rooks, knights, bishops, and 
     * the king and queen.
     */
    void setBackRow(bool isWhite);

    /**
     * Sets pieces on the board for a standard chess board start.
     */
    void setStartingBoard();

    /**
     * Searches the board for a white king if passed true, black king if false.
     */
    Tile getKingLocation(bool kingIsWhite) const;

    /**
     * Returns true if a piece of the specified side at the passed-in tile
     * can be captured by the enemy on the next turn.
     */
    bool isCapturable(bool isWhite, const Tile& tile) const;

    /**
     * Checks whether any kings are checked by the enemy.
     */
    void checkKings();

    /**
     * Attempts to move the currently selected piece to the passed-in tile,
     * and returns true if the move does not result in a king becoming checked
     * by the enemy. All changes made during this function are undone before
     * returning.
     */
    bool simulateMove(const Tile& tile);

public:

    /**
     * @brief Constructs a BoardManager object.
     * 
     */
    BoardManager();

    /**
     * @brief Resets the game state, deletes all pieces from the board, and sets
     * new pieces at their starting locations.
     * 
     */
    void restartGame();

    /**
     * @brief Gets the piece at the passed-in row and column on the board.
     * 
     * @param row the row to get
     * @param col the column to get
     * @return ChessPiece* the piece at the location on the board.
     */
    ChessPiece* getPiece(int row, int col) const;

    /**
     * @brief Gets the piece at the passed-in tile on the board.
     * 
     * @param tile the tile to get
     * @return ChessPiece* the piece at the location on the board.
     */
    ChessPiece* getPiece(const Tile& tile) const;

    /**
     * @brief Places the passed-in piece at the passed-in row and column
     * on the board.
     * 
     * @param piece the piece to place
     * @param row the row to place
     * @param col the column to place
     */
    void setPiece(ChessPiece* piece, int row, int col);

    /**
     * @brief Places the passed-in piece at the passed-in tile on the board.
     * 
     * @param piece the piece to place
     * @param tile the tile location on the board to place
     */
    void setPiece(ChessPiece* piece, const Tile& tile);

    /**
     * @brief Returns the current total of all pieces on the board.
     * 
     * @return int the total board value
     */
    int getBoardValue() const;

    /**
     * @brief Changes the board value by the passed-in amount.
     * 
     * @param value the amount to add to the board value
     */
    void changeBoardValue(int value);

    /**
     * @brief Returns whether a piece is currently selected.
     * 
     * @return true if selected
     * @return false if no piece is selected
     */
    bool pieceIsSelected() const;

    /**
     * @brief Returns whether the white king is currently checked.
     * 
     * @return true if checked
     * @return false if not checked
     */
    bool isCheckedWhite() const;

    /**
     * @brief Returns whether the black king is currently checked.
     * 
     * @return true if checked
     * @return false if not checked
     */
    bool isCheckedBlack() const;

    /**
     * @brief Returns whether it is currently the white side's turn.
     * 
     * @return true if white's turn
     * @return false if black's turn
     */
    bool isWhiteTurn() const;

    /**
     * @brief Swaps which player's turn it currently is.
     * 
     */
    void changeTurns();

    /**
     * @brief Sets the name of the game's winner.
     * 
     * @param winner a string representing the winner
     */
    void setWinner(string winner);

    /**
     * @brief Gets the winner's name. Returns an empty string if the game
     * has not been won yet.
     * 
     * @return string the name of the winner
     */
    string getWinner() const;

    /**
     * @brief Returns whether the passed-in row and column are the same as
     * that of the currently selected piece/tile.
     * 
     * @param row the row to check
     * @param col the column to check
     * @return true if the location is currently selected
     * @return false if the location is not currently selected
     */
    bool isSelectedPiece(int row, int col) const;

    /**
     * @brief Returns whether the passed-in row and column represent a tile
     * that the currently selected piece can move to.
     * 
     * @param row the row to check
     * @param col the column to check
     * @return true if the location can be moved to by the selected piece
     * @return false if the location cannot be moved to
     */
    bool isMovableTile(int row, int col) const;

    /**
     * @brief Returns an unordered set of tiles that the selected piece can
     * move to.
     * 
     * @return an unordered set of tiles that can be moved to
     */
    unordered_set<Tile, HashTile> getMovableTiles() const;

    /**
     * @brief Returns a priority queue containing the pieces that have been
     * captured this game for both black and white.
     * 
     * @return a priority queue of the captured pieces of both sides.
     */
    priority_queue_piece getCaptured() const;

    /**
     * @brief Attempts to select the piece at the passed-in tile location. If
     * no piece is at the location or the piece belongs to the player who is
     * not taking their turn, the function terminates with no action.
     * 
     * @param tile the tile location to select
     * @param filterMoves a tag for whether to filter moves that will expose
     * a king to being checked
     */
    void selectPiece(const Tile& tile, bool filterMoves = true);

    /**
     * @brief Attempts to move the currently selected piece to the passed-in
     * tile location. If the tile contains another piece of the player that is
     * moving, select that piece instead. Illegal move locations will result
     * in no move being made and the current selected tile becoming deselected.
     * 
     * @param tile the tile to move to
     */
    void tryMove(const Tile& tile);

    /**
     * @brief Moves the currently selected piece ot teh passed-in tile location.
     * The piece is updated if necessary, such as in the case of a pawn making
     * its first move or promoting.
     * 
     * @param tile the tile to move to
     */
    void movePiece(const Tile& tile);

    /**
     * @brief Returns true if the white player has at least one legal move to make.
     * 
     * @return true if white can move
     * @return false if white cannot move
     */
    bool whiteCanMove();
};

#endif