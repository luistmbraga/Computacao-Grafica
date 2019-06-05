#include "headers/colour.h"

	Colour::Colour(){
		rr = gg = bb = 0.5;
	}

	Colour::Colour(float a, float b, float c){
		rr = a;
		gg = b;
		bb = c;
	}

	float Colour::getRR(){
		return rr;
	}

	float Colour::getGG(){
		return gg;
	}

	float Colour::getBB(){
		return bb;
	}

	void Colour::setRR(float a){
		rr = a;
	}

	void Colour::setGG(float b){
		gg = b;
	}

	void Colour::setBB(float c){
		bb = c;
	}