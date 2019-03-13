#include "dot.h"
using namespace std;

Dot::Dot(){
	x = 0;
	y = 0;
}

Dot::Dot(float new_x, float new_y, int new_color){
	x = new_x;
	y = new_y;
	color = new_color;
}

float Dot::getx(){
	return x;
}

float Dot::gety(){
	return y;
}

int Dot::get_color(){
	return color;
}
/*void Dot::setloc(float newx, float newy){
	x = newx;
	y = newy;
}*/