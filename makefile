
output: main.o chessboard.o
	g++ main.o chessboard.o -o project-1

main.o: main.cpp
	g++ -c main.cpp

chessboard.o: chessboard.cpp chessboard.h
	g++ -c chessboard.cpp

clean:
	rm main.o chessboard.o project-1