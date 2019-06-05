#include "headers/translate.h"

	Translate::Translate(){
		x = y = z = 0;
	}

	Translate::Translate(float a, float b, float c){
		x = a;
		y = b;
		z = c;
	}

	float Translate::getX(){
		return x;
	}

	float Translate::getY(){
		return y;
	}

	float Translate::getZ(){
		return z;
	}

	void Translate::setX(float a){
		x = a;
	}

	void Translate::setY(float b){
		y = b;
	}

	void Translate::setZ(float c){
		z = c;
	}