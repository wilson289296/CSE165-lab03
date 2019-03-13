#include "board.h"
using namespace std;

Board::Board(){
	//intentionally empty
}

Dot Board::get_vector(int index){
	return dot_list.at(index);
}

void Board::add_dot(float x, float y){
	Dot dot(x, y);
	dot_list.push_back(dot);
}

void Board::erase_at(float x, float y, int boardheight){
	//radius of checking should be 1/64 of height
	float dotxbuffer, dotybuffer; //vars to pull dot location data into
	float eraserradius = (1/64) * boardheight; //calculate radius around dots to erase
	for(i = 0; i <= dot_list.size(); i++){ //iterate through existing list of dots
		dotxbuffer = dot_list.at(i).getx(); //pull dot x data
		dotybuffer = dot_list.at(i).gety(); //pull dot y data
		//erase the dot from dotlist if it's within the radius
		if(dotxbuffer >= (x - eraserradius) && dotxbuffer <= (x + eraserradius) && dotybuffer >= (y - eraserradius) && dotybuffer <= (y + eraserradius)){
			dot_list.erase(i);
		}
	}
}