/**
 * Project 1
 * Filename: chessboard.h
 * Course: CS341
 * Name: Jonathan Hung
 * UIN: 677555234
 *
 * This project implements a chessboard game, which is composed by different squares (or pieces)
 * that can be moved around the chessboard.
 */

#include <iostream>
#include <iterator>
#include <cmath>
using namespace std;

/**
 * Color of the piece
 */
enum Color {
    White,
    Black,
    None
};

/**
 * Types of pieces
 */
enum Piece {
    Rook,
    Knight,
    Bishop,
    Queen,
    King,
    Pawn,
    Space
};

/**
 * Class for a square. This is what composes the chessboard
 */
class Square {
private:
    Color color;
    Piece piece;
    bool occupied;

public:

    /**
     * Default constructor, unoccupied square
     */
    Square() {
        color = None;
        piece = Space;
        occupied = false; }

    /**
     * Parameter constructor. It takes a color and a piece to set values
     * @param c The color for the piece
     * @param p The type of piece
     */
    Square(Color c, Piece p) { // an occupied square
        color = c;
        piece = p;
        occupied = true;
    }

    /**
     * Getter for a square. It takes arguments by reference a copies instance members
     * @param o The occupied member
     * @param c The color member
     * @param p The piece member
     */
    void get(bool &o, Color &c, Piece &p) {
        o = occupied;
        c = color;
        p = piece;
    }

    /**
     * Getter for occupied member
     * @return The occupied member
     */
    bool getOccupied() { return occupied; }

    /**
     * Getter for color member
     * @return The color member
     */
    Color getColor() { return color; }

    /**
     * Used to print a single square, depending on the color and piece
     */
    void print() {
        if (occupied) {
            if (color == White) {
                switch (piece) {
                    case Rook:
                        printf("wR ");
                        break;
                    case Knight:
                        printf("wN ");
                        break;
                    case Bishop:
                        printf("wB ");
                        break;
                    case Queen:
                        printf("wQ ");
                        break;
                    case King:
                        printf("wK ");
                        break;
                    case Pawn:
                        printf("wP ");
                        break;
                }
            }

            if (color == Black) {
                switch (piece) {
                    case Rook:
                        printf("bR ");
                        break;
                    case Knight:
                        printf("bN ");
                        break;
                    case Bishop:
                        printf("bB ");
                        break;
                    case Queen:
                        printf("bQ ");
                        break;
                    case King:
                        printf("bK ");
                        break;
                    case Pawn:
                        printf("bP ");
                        break;
                }
            }

        } else {
            printf(" . "); // a blank square
        }
    }
};

class ChessboardIterator;

/**
 * The chessboard class creates a 8x8 chessboard, creates and stores all the pieces for the chessboard,
 * and contains several methods to manipulate the chessboard.
 */
class Chessboard {
    // make the container iterator friendly
    typedef ChessboardIterator iterator;

private:
    Square chessboard[8][8]; // the chessboard with squares

public:
    friend class ChessboardIterator;

    Chessboard() {} // Square does all the initialization

    /**
     * Getter for a square in the chessboard
     * @param x The x coordinate of the square
     * @param y The y coordinate of the square
     * @return The square specified from the chessboard
     */
    Square square(int x, int y) { return chessboard[x][y]; }

    // Iterator initializers for starts/end of iterator
    ChessboardIterator begin();
    ChessboardIterator end();

    /**
     * Place a piece on the coordinates (x,y). Also checks that input arguments are valid, and if it's possible
     * to add the piece
     * @param x The x coordinate for the piece
     * @param y The y coordinate for the piece
     * @param c The color for the piece
     * @param p The type of piece
     * @return 1 if placing was successful, a negative number otherwise
     */
    int place(int x, int y, Color c, Piece p) {

        // checking exceptions
        if (x < 0 || x > 7)
            return -1;

        if (y < 0 || y > 7)
            return -2;

        if (chessboard[x][y].getOccupied())
            return -3;

        if (c != White && c != Black)
            return -4;

        if (p != Rook && p != Knight && p != Bishop && p != Queen && p != King && p != Pawn)
            return -5;

        chessboard[x][y] = Square(c, p);

        return 1;
    }

    /**
     * Getter for a piece on the chessboard, based on the (x,y) coordinates. It takes reference arguments
     * to copy the specified piece's color and type of piece
     * @param x The x coordinate of the piece
     * @param y The y coordinate of the piece
     * @param c The color used to copy instance member
     * @param p The piece used to copy instance member
     * @return
     */
    int get(int x, int y, Color &c, Piece &p) {

        if (x < 0 || x > 7)
            return -1;

        if (y < 0 || y > 7)
            return -2;

        if (!chessboard[x][y].getOccupied())
            return -3;

        bool temp;

        chessboard[x][y].get(temp, c, p);

        return 1;
    }

    /**
     * Used to check if a move is possible or not, checking the path from a point to another is obstructed or clear.
     * It is used as a helper method for move().
     * @param fromX The x coordinate of the piece to move
     * @param fromY The y coordinate of the piece to move
     * @param toX The x coordinate to move to
     * @param toY The y coordinate to move to
     * @return False if there is an obstructing piece, true if the moving path is clear
     */
    bool legalMove(int fromX, int fromY, int toX, int toY) {

        if ((toX - fromX) == 0 && (toY - fromY) == 0)
            return false;

        int diffX = 0;
        int diffY = 0;

        if (toX > fromX)
            diffX = 1;
        if (toX < fromX)
            diffX = -1;

        if (toY > fromY)
            diffY = 1;
        if (toY < fromY)
            diffY = -1;

        int pivotX = fromX + diffX;
        int pivotY = fromY + diffY;

        // Check squares between "from" point and "to" point
        while (pivotX != toX && pivotY != toY) {

            if (chessboard[pivotX][pivotY].getOccupied())
                return false;

            pivotX += diffX;
            pivotY += diffY;

            if (pivotX == 8 || pivotY == 8)
                return false;
        }

        return true;
    }

    /**
     * Used to move a piece from one position (x,y) to another, calling helper functions legalMove() to check for paths.
     * @param fromX The x coordinate of the piece to move
     * @param fromY The y coordinate of the piece to move
     * @param toX The x coordinate to move to
     * @param toY The y coordinate to move to
     * @return 1 if a move was successful, a negative number otherwise
     */
    int move(int fromX, int fromY, int toX, int toY) {

        // checking exceptions
        if (fromX < 0 || fromX > 7)
            return -1;

        if (fromY < 0 || fromY > 7)
            return -2;

        if (toX < 0 || toX > 7)
            return -3;

        if (toY < 0 || toY > 7)
            return -4;

        if (!chessboard[fromX][fromY].getOccupied())
            return -5;


        if (chessboard[fromX][fromY].getColor() == chessboard[toX][toY].getColor())
            return -6;

        bool occupied;
        Color color;
        Piece piece;

        chessboard[fromX][fromY].get(occupied, color, piece);

//        printf("------------------------------\n"); //for debugging
//        print();
//        printf("fromX=%d fromY=%d\n", fromX, fromY);
//        printf("toX=%d toY=%d\n", toY, toY);


        // checking what kind of piece is to move
        if (piece == Rook) {
            //printf("Rook\n");
            if (((fromX - toX) != 0 && (fromY - toY) != 0) || ((fromX - toX) == 0 && (fromY - toY) == 0) ||
                !legalMove(fromX, fromY, toX, toY))
                return -7;
        }

        if (piece == Knight) {
            //printf("Knight\n");
            //(abs(fromX - toX) != 2 && abs(fromY - toY) != 1) && (abs(fromY - toY) != 2 && abs(fromX - toX) != 1)
            if (!((abs(fromX - toX) == 2 && abs(fromY - toY) == 1) || (abs(fromY - toY) == 2 && abs(fromX - toX) == 1)))
                return -7;
        }

        if (piece == Bishop) {
            //printf("Bishop\n");
            if (abs(fromX - toX) != abs(fromY - toY))
                return -7;
        }

        if (piece == Queen) {
            //printf("Queen\n");
            if (!legalMove(fromX, fromY, toX, toY))
                return -7;
        }

        if (piece == King) {
            //printf("King\n");
            if (abs(fromX - toX) > 1 || abs(fromY - toY) > 1)
                return -7;
        }

        if (piece == Pawn) {
            //printf("Pawn\n");
            if (color == White) {
                if (((toY - fromY) != 1 && (toX - fromX != 0)) || !((toY - fromY) == 1 && (abs(toX - fromX) == 1)))
                    return -7;
            } else {
                if (((toY - fromY) != -1 && (toX - fromX != 0)) || !((toY - fromY) == -1 && (abs(toX - fromX) == 1)))
                    return -7;
            }
        }

        // make move
        chessboard[toX][toY] = chessboard[fromX][fromY];
        chessboard[fromX][fromY] = Square();

        return 1;
    }


    void print();
};

/**
 * Used to iterate over a chessboard object.
 */
class ChessboardIterator {
private:
    int position; // a number in [0..63]. Used to designate the current position of the iterator
    Chessboard & chessboard; // the chessboard to iterate

public:
    /**
     * Constructor for an iterator.
     * @param board The board used to iterate
     * @param pos The designated positon for the iterator
     */
    ChessboardIterator(Chessboard &board, int pos) : chessboard(board) { // start out with an empty board
        position = pos;
    }

    /**
     * Breaks the position of the iterator into x and y
     * @param x The x value used to copy
     * @param y The y value used to copy
     */
    void xy(int &x, int &y) {
        x = position % 8;
        y = position / 8;
    }

    /**
     * Pointer to current element in the iterator
     * @return The square object in the chessboard the iterator points to
     */
    Square operator*() {
        return chessboard.square(position % 8, position / 8);
    }

    /**
     * Increment operator. It runs the position from one element to the next
     * @return The current element pointed by the iterator
     */
    ChessboardIterator &operator++() {
        position++;
        return *this;
    }

    /**
     * Checks if two iterators are the same
     * @param a The iterator to compare to
     * @return 1 if iterators are different, 0 otherwise
     */
    int operator!=(ChessboardIterator &a) {
        if (a.position != this->position)
            return 1;
        else
            return 0;
    }
};
