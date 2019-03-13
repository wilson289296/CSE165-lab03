#include "dot.h"
using namespace std;

Dot::Dot(){
	x = 0;
	y = 0;
}

Dot::Dot(float new_x, float new_y){
	x = new_x;
	y = new_y;
}

float Dot::getx(){
	return x;
}

float Dot::gety(){
	return y;
}

void Dot::setloc(float newx, float newy){
	x = newx;
	y = newy;
}