#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "../../../src/headers/Point.h"
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;

class Camera {
	Point* camPosition; // posicao de onde a camara se encontra.
	Point* lookPoint;   // posicao para onde a camara esta a olhar.
	Point* titl;        // 'up vector'.
	float alfa;        // determina a posicao da camera.
	float beta;		   // determina a posicao da camera.
	float dist;        // distancia entre a posicao da camera e o ponto a que a mesma esta a olhar.

public:
	Camera();
	void atualizaCamPosition();
	void atualizaDist();
	void camUp();
	void camDown();
	void camLeft();
	void camRight();
	void FocusUp();
	void FocusDown();
	void FocusLeft();
	void FocusRight();
	void maisZoom();
	void menosZoom();
	Point* getCamPosition();
	Point* getLookPoint();
	Point* getTitl();
	void setCamPosition(float, float, float);
	void setLookPoint(float, float, float);
	void setTitl(float, float, float);
	
};

#endif