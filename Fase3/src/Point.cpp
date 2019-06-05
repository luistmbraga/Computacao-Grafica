#include "headers/Point.h"

Point::Point(){
	x = 0;
	y = 0;
	z = 0;
}

Point::Point(float q, float t, float w){
	x = q;
	y = t;
	z = w;
}

float Point::getX(){
	return x;
}

float Point::getY(){
	return y;
}

float Point::getZ(){
	return z;
}

void Point::setX(float a){
	x = a;
}

void Point::setY(float a){
	y = a;
}

void Point::setZ(float a){
	z = a;
}

string Point::to_String() {
	string s = to_string(x) + " " + to_string(y) + " " + to_string(z);
	return s;
}

