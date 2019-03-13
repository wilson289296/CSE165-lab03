#ifndef BOARD_H
#define BOARD_H
#include "dot.h"
#include <vector>
#include "freeglut.h"

class Board{
	std::vector<Dot> dot_list;
	//mode 1: draw, mode 2: erase
	int mode;
	int color;
	
	public:
	Board();
	Dot get_vector(int index); //may or may not need
	void add_dot(float x, float y, int color);
	void erase_at(float x, float y, int boardheight);
	int get_size();
	void draw_dots();
	void set_mode(float x, float y);
	int get_mode();
	int get_color();
	
	


};
#endif