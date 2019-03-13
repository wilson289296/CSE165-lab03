#ifndef BOARD_H
#define BOARD_H
#include "dot.h"
#include <vector>

class Board{
	vector<Dot> dot_list;
	
	public:
	Board();
	Dot get_vector(int index); //may or may not need
	void add_dot(float x, float y);
	void erase_at(float x, float y);
	
	


}