#ifndef DOT_H
#define DOT_H

class Dot{
	float x;
	float y;
	
	public:
	Dot();
	Dot(float new_x, float new_y);
	float getx();
	float gety();
	void setloc(float x, float y, int boardheight);	//may or may not be necessary
}