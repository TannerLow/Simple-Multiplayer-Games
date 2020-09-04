#pragma once
#include <string>

class TicTacToe
{
private:
	char board[10] = "         ";

public:
	TicTacToe() {}
	~TicTacToe() {}

	bool choosePlayer1() const;
	bool makePlay(int position, char piece);
	void getBoard(char* out) const;
	void setBoard(char* newBoard);

	static void display(char* board);
};

