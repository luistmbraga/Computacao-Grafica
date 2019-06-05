#ifndef __PONTOS_H__
#define __PONTOS_H__

#include <vector>
#include <string>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include "../../../src/headers/Point.h"

using namespace std;

class pontos{
	GLuint buffer, size_buffer;

public:

	pontos();
	pontos(vector<Point*> l);
	void prepare(vector<Point*>);
	void draw();

};




#endif
