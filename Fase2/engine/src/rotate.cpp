#include "headers/rotate.h"

	Rotate::Rotate(){
		angle = x = y = z = 0;
	}

	Rotate::Rotate(float alfa, float a, float b, float c){
		angle = alfa;
		x = a;
		y = b;
		z = c;
	}

	float Rotate::getAngle(){
		return angle;
	}

	float Rotate::getX(){
		return x;
	}

	float Rotate::getY(){
		return y;
	}

	float Rotate::getZ(){
		return z;
	}

	void Rotate::setAngle(float alfa){
		angle = alfa;
	}

	void Rotate::setX(float a){
		x = a;
	}

	void Rotate::setY(float b){
		y = b;
	}

	void Rotate::setZ(float c){
		z = c;
	}