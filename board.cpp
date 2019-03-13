#include "board.h"
#include <vector>
#include <iostream>
using namespace std;

Board::Board(){
	//intentionally empty
	mode = 1;
}

Dot Board::get_vector(int index){
	return dot_list.at(index);
}

void Board::add_dot(float x, float y, int color){
	Dot dot(x, y, color);
	dot_list.push_back(dot);
}

void Board::erase_at(float x, float y, int boardheight){
	//radius of checking should be 1/64 of height
	float dotxbuffer, dotybuffer; //vars to pull dot location data into
	float eraserradius = (float)boardheight/6400;//boardheight / 6400; //boardheight/64; //calculate radius around dots to erase
	
	if(dot_list.size() != 0){
		for(unsigned i = 0; i < dot_list.size(); i++){
			dotxbuffer = dot_list.at(i).getx(); //pull dot x data
			dotybuffer = dot_list.at(i).gety(); //pull dot y data
			//cout << "checking for erase: " << dotxbuffer << ", " << dotybuffer << endl;
			if(dotxbuffer >= (x - eraserradius) && dotxbuffer <= (x + eraserradius) && dotybuffer >= (y - eraserradius) && dotybuffer <= (y + eraserradius)){
				dot_list.erase(dot_list.begin() + i);
				//cout << "i = " << i << endl;
				//cout << "size " << dot_list.size() << endl;
			}
		}
	}
}

int Board::get_size(){
	return dot_list.size();
}

void Board::draw_dots(){
	int tempcolor;
	//if(dot_list.size() != 0){
		for(unsigned i = 0; i < dot_list.size(); i++){
			Dot temp = dot_list.at(i);
			tempcolor = temp.get_color();
			cout << "color is: " << tempcolor << endl;
			switch(tempcolor){
				case 1:
					glColor3f(1,0,0);
					break;
				case 2:
					glColor3f(0,1,0);
					break;
				case 3:
					glColor3f(0,0,1);
					break;
				case 4:
					glColor3f(0,0,0);
					break;
			}
			
			glBegin(GL_POINTS);
			glVertex2f(temp.getx(), temp.gety());
			glEnd();
		}
	//}
}

void Board::set_mode(float x, float y){
	//cout << "Received: " << x << ", " << y << endl;
	if(x > -0.995 && x < -0.995 + 0.1 && y > -0.99 && y < -0.89){
		mode = 1;
	}
	if(x > -0.885 && x < -0.885 + 0.1 && y > -0.99 && y < -0.89){
		mode = 2;
	}
	if(x > -0.775 && x < -0.775 + 0.1 && y > -0.99 && y < -0.89){
		mode = 1;
		color = 1;
	}
	if(x > -0.665 && x < -0.665 + 0.1 && y > -0.99 && y < -0.89){
		mode = 1;
		color = 2;
	}
	if(x > -0.555 && x < -0.555 + 0.1 && y > -0.99 && y < -0.89){
		mode = 1;
		color = 3;
	}
	if(x > -0.445 && x < -0.445 + 0.1 && y > -0.99 && y < -0.89){
		mode = 1;
		color = 4;
	}
	cout << "board color is: " << color << endl;
	//cout << "mode switch" << endl;
	
}

int Board::get_mode(){
	return mode;
}

int Board::get_color(){
	return color;
}