#include "headers/scale.h"

	Scale::Scale(){
		x = y = z = 1;
	}

	Scale::Scale(float a, float b, float c){
		x = a;
		y = b;
		z = c;
	}

	float Scale::getX(){
		return x;
	}

	float Scale::getY(){
		return y;
	}

	float Scale::getZ(){
		return z;
	}

	void Scale::setX(float a){
		x = a;
	}

	void Scale::setY(float b){
		y = b;
	}

	void Scale::setZ(float c){
		z = c;
	}