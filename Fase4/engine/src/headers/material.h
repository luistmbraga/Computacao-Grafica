#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "../../../src/headers/Point.h"
#include <GL/glut.h>

class Material {
	float diffuse[4];            // por omissão {0.8,0.8,0.8,1}
	float specular[4];			 // por omissão {0,0,0,1}
	float emission[4];			 // por omissão {0,0,0,1}
	float ambient[4];			 // por omissão {0.2,0.2,0.2,1}
	float shini;			     // por omissão 0

public:
	Material();
	Material(Point* diff, Point* specular, Point* emission, Point* ambient, float shin);
	Material(Material*);
	float* getDiffuse();
	float* getSpecular();
	float* getEmission();
	float* getAmbient();
	float getShini();
	void draw();
	
};


#endif