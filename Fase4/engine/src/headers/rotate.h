#ifndef __ROTATE_H__
#define __ROTATE_H__

#include <GL/glut.h>

class Rotate {
	float time;
	float x;
	float y;
	float z;

public:
	Rotate();
	Rotate(float, float, float, float);
	float getTime();
	float getX();
	float getY();
	float getZ();
	void setTime(float);
	void setX(float);
	void setY(float);
	void setZ(float);
	void apply();
};


#endif