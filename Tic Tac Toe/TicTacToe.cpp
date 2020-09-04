#define _CRT_SECURE_NO_WARNINGS
#include "TicTacToe.h"
#include <cstdlib>
#include <ctime>
#include <iostream>


//Essentially a coin toss for who goes first
bool TicTacToe::choosePlayer1() const{
	std::srand(std::time(0));
	return rand() % 2;
}

bool TicTacToe::makePlay(int position, char piece) {
	position--;
	if (position > 8 or position < 0 or board[position] != ' ') return false;
	board[position] = piece;
	return true;
}

void TicTacToe::getBoard(char* out) const {
	strcpy(out, board);
}

void TicTacToe::setBoard(char* newBoard) {
	strncpy(board, newBoard, 9);
}

void TicTacToe::display(char* board) {
	for (int i = 0; i < 8; i++) {
		std::cout << board[i] << (i % 3 == 2 ? "\n" : " | ");
		if (i % 3 == 2) {
			std::cout << "---------" << std::endl;
		}
	}
	std::cout << board[8] << std::endl << std::endl;
}
