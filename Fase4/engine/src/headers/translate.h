#ifndef __TRANSLATE_H__
#define __TRANSLATE_H__

#include<vector>
#include "../../../src/headers/Point.h"
#include <GL/glut.h>

class Translate {
	float tempo;
	vector<Point*> trans;
	vector<Point*> curve;

public:
	Translate();
	Translate(float, vector<Point*>);
	float getTempo();
	vector<Point*> getCurve();
	vector<Point*> getTrans();
	void setTempo(float);
	void setTrans(vector<Point*>);
	void setCurve(vector<Point*>);
	void getCatmullRomPoint(float, int*, float*, vector<Point*>);
	void getGlobalCatmullRomPoint(float, float *, vector<Point*>);
	void drawCurve();
	void drawCatmullRomCurve();
	void draw();

};


#endif