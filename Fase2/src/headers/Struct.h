#ifndef STRUCT_H__
#define STRUCT_H__

#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>
#include <vector>
#include "Point.h"

using namespace std;

class Struct {
	vector<Point*> LP; // lista de pontos

public:
	Struct();
	Struct(vector<Point*>);
	vector<Point*> getLP();
	void setLP(vector<Point*>);
	void genPlane(float);
	void genCylinder(float, float, int);
	void genSphere(float, int, int);
	void genCone(float , float , int , int );
	void genBox(float, float, float, int);
	void genTorus(float, float, int, int);
	void genCintura(float, float, int, int);
};

#endif
