#ifndef __ROTATE_H__
#define __ROTATE_H__

class Rotate {
	float angle;
	float x;
	float y;
	float z;

public:
	Rotate();
	Rotate(float, float, float, float);
	float getAngle();
	float getX();
	float getY();
	float getZ();
	void setAngle(float);
	void setX(float);
	void setY(float);
	void setZ(float);
};


#endif