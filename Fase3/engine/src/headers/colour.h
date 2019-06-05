#ifndef __COLOUR_H__
#define __COLOUR_H__

class Colour {
	float rr;
	float gg;
	float bb;

public:
	Colour();
	Colour(float, float, float);
	float getRR();
	float getGG();
	float getBB();
	void setRR(float);
	void setGG(float);
	void setBB(float);
};


#endif