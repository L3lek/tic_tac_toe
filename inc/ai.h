#pragma once
#include "board.h"


class ai: public Board{
int x, y;
int depth;

public:
ai(int depth_limit):depth(depth_limit){};
int minimax(Board board, int depth, int alpha, int beta, bool player);
void move(Board board);
int getx() const { return x; }
int gety() const { return y; }

};