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
	void change_turn(bool player){player ? turn =1 : turn=0;}
	void print() const;
	void set(int x, int y);
	void remove(int x, int y);
	void reset();
	int get_size();
	int game_result()const;
	bool full_board();
	bool occupied(int x, int y);
	bool player_turn(){return turn;}
	char get_pl_symbol(){return pl_symbol;}
	char get_ai_symbol(){return ai_symbol;}
	void set_turn(bool whose_turn){turn = whose_turn;}

};