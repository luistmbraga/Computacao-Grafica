#ifndef __TRANSLATE_H__
#define __TRANSLATE_H__

class Translate {
	float x;
	float y;
	float z;

public:
	Translate();
	Translate(float, float, float);
	float getX();
	float getY();
	float getZ();
	void setX(float);
	void setY(float);
	void setZ(float);
};


#endif