#include "headers/rotate.h"

	Rotate::Rotate(){
		time = x = y = z = 0;
	}

	Rotate::Rotate(float t, float a, float b, float c){
		time = t;
		x = a;
		y = b;
		z = c;
	}

	float Rotate::getTime(){
		return time;
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

	void Rotate::setTime(float t){
		time = t;
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

	void Rotate::apply() {
		float r, gr;

		if (time != 0) {
			r = glutGet(GLUT_ELAPSED_TIME) % (int)(time * 1000);
			gr = (r * 360) / (time * 1000);
			glRotatef(gr, getX(), getY(), getZ());
		}

	}