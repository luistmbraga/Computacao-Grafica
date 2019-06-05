#ifndef __LIGHT_H__
#define __LIGHT_H__


#include "../../../src/headers/Point.h"
#include <GL/glut.h>



class Light {
	bool point;          // 1 -> é ponto
	Point* p;			 // posX, posY, posZ

public:
	Light();
	Light(bool, Point*);
	bool getType();
	Point* getPoint();
	void setType(bool type);
	void setPoint(Point* p);
	void draw();
	
};
#endif 