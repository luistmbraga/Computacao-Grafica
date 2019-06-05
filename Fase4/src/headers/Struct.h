#ifndef STRUCT_H__
#define STRUCT_H__

#define _USE_MATH_DEFINES

#include <math.h>
#include <iostream>
#include <vector>
#include "Point.h"

using namespace std;

class Struct {
	vector<Point*> LP;		 // lista de pontos
	vector<Point*> normal;   // lista de pontos das normais
	vector<Point*> textura;  // lista de pontos das texturas

public:
	Struct();
	Struct(vector<Point*>, vector<Point*>, vector<Point*>);
	vector<Point*> getLP();
	vector<Point*> getNormal();
	vector<Point*> getTextura();
	void setLP(vector<Point*>);
	void setNormal(vector<Point*>);
	void setTextura(vector<Point*>);
	void genPlane(float);
	void genCylinder(float, float, int);
	void genSphere(float, int, int);
	void genCone(float , float , int , int );
	void genBox(float, float, float, int);
	void genTorus(float, float, int, int);
	void genCintura(float, float, int, int);
};

#endif
