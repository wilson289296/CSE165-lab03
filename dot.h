#ifndef DOT_H
#define DOT_H

class Dot{
	float x;
	float y;
	int color;
	//1 = r, 2 = g, 3 = b, 4 = black; 
	
	public:
	Dot();
	Dot(float new_x, float new_y, int color);
	float getx();
	float gety();
	int get_color();
	//void setloc(float x, float y);	//may or may not be necessary
};
#endif