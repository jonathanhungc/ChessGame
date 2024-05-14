/**
 * Project 1
 * Filename: chessboard.cpp
 * Course: CS341
 * Name: Jonathan Hung
 * UIN: 677555234
 *
 * This project implements a chessboard game, which is composed by different squares (or pieces)
 * that can be moved around the chessboard.
 */

#include "chessboard.h"

/**
 * Method used to get an iterator to the first element of a chessboard.
 * @return An iterator set to the first element of the chessboard
 */
ChessboardIterator Chessboard::begin() { return ChessboardIterator(*this, 0); }

/**
 * Method used to get an iterator to the last element of a chessboard.
 * @return An iterator set to the last element of the chessboard
 */
ChessboardIterator Chessboard::end() { return ChessboardIterator(*this, 64); }

/**
 * Used to print the chessboard, with white pieces at the bottom and black pieces at the top. Uses the iterator
 * to accomplish this.
 */
void Chessboard::print() {

    for (int rows = 0; rows < 8; ++rows) {

        ChessboardIterator iter = this->begin();

        //printf("%d", (64 - (rows + 1) * 8));
        for (int i = 0; i < (64 - ((rows + 1) * 8)); ++i) {
            iter.operator++();
        }

        for (int iterRow = 0; iterRow < 8; ++iterRow) {
//            int x, y;
//            iter.xy(x, y);
//            printf(" %d%d ", x, y); // used for testing. prints the x, y values of the current square
            iter.operator*().print();
            iter.operator++();
        }

        printf("\n");
    }
}
