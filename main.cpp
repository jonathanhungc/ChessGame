/**
 * Project 1
 * Filename: main.cpp
 * Course: CS341
 * Name: Jonathan Hung
 * UIN: 677555234
 *
 * This project implements a chessboard game, which is composed by different squares (or pieces)
 * that can be moved around the chessboard.
 */

#include "chessboard.h"
#include <iostream>

int main() {
    std::cout << "Hello World!\n";
    Chessboard chessboard;

    chessboard.place(0, 0, White, Rook);
    chessboard.place(1, 0, White, Knight);
    chessboard.place(2, 0, White, Bishop);
    chessboard.place(3, 0, White, Queen);
    chessboard.place(4, 0, White, King);
    chessboard.place(5, 0, White, Bishop);
    chessboard.place(6, 0, White, Knight);
    chessboard.place(7, 0, White, Rook);
    for (int i = 0; i < 8; i++) {
        chessboard.place(i, 1, White, Pawn);
    }
    chessboard.place(0, 7, Black, Rook);
    chessboard.place(1, 7, Black, Knight);
    chessboard.place(2, 7, Black, Bishop);
    chessboard.place(3, 7, Black, Queen);
    chessboard.place(4, 7, Black, King);
    chessboard.place(5, 7, Black, Bishop);
    chessboard.place(6, 7, Black, Knight);
    chessboard.place(7, 7, Black, Rook);
    for (int i = 0; i < 8; i++) {
        chessboard.place(i, 6, Black, Pawn);
    }
    chessboard.print();
    cout << "***********Testing get************" << endl;
    Color co;
    Piece p;
    cout << "Testing get illegal x cood: " << chessboard.get(8, 0, co, p) << endl;
    cout << "Testing get illegal y cood: " << chessboard.get(0, 8, co, p) << endl;
    cout << "Testing get occupied square: " << chessboard.get(3, 0, co, p)
         << endl;
    cout << "Testing get unoccupied square: " << chessboard.get(0, 2, co, p)
         << endl;
    cout << "***********Testing place************" << endl;
    Color coPlace = (Color)3;
    Piece piPlace = (Piece)6;
    cout << "Testing place illegal x cood: "
         << chessboard.place(87, 8, coPlace, piPlace) << endl;
    cout << "Testing place illegal y cood: "
         << chessboard.place(0, 8, coPlace, piPlace) << endl;
    cout << "Testing place square occupied: "
         << chessboard.place(0, 0, coPlace, piPlace) << endl;
    cout << "Testing place illegal color: "
         << chessboard.place(0, 2, coPlace, piPlace) << endl;
    coPlace = (Color)0;
    cout << "Testing place illegal piece: "
         << chessboard.place(0, 2, coPlace, piPlace) << endl;
    piPlace = (Piece)3;
    cout << "Testing place everything ok: "
         << chessboard.place(0, 2, coPlace, piPlace) << endl;
    chessboard.print();
}

