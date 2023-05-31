#pragma once
#include <vector>

class Board{
	int size;
	int max_row;
	bool turn;
	char pl_symbol, ai_symbol;
	std::vector<std::vector<char>> area;

	public:
	Board(){};
	Board(int size, int max_row, char player);
	void print() const;
	void set(int x, int y);
	void remove(int x, int y);
	void reset();
	int get_size();
	int game_result()const;
	bool full_board();
	bool occupied(int x, int y);
	bool player_turn(){return turn;}
	void change_turn(bool player){player ? turn = 1 : turn = 0; }


};