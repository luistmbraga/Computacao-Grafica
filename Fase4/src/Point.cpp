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


Point* Point::calcula_Normal() {
	float normal_value;

	normal_value = sqrt(x * x + y * y + z * z);
	x = x / normal_value;
	y = y / normal_value;
	z = z / normal_value;

	return new Point(x, y, z);
}

string Point::to_String() {
	string s = to_string(x) + " " + to_string(y) + " " + to_string(z);
	return s;
}

