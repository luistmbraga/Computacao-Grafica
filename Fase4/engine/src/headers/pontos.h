#ifndef __PONTOS_H__
#define __PONTOS_H__

#include <vector>
#include <string>
#include <stdlib.h>
#include <GL/glew.h>
#include <GL/glut.h>
#include <IL/il.h>
#include "../../../src/headers/Point.h"
#include "headers/material.h"

using namespace std;

class pontos{
	GLuint buffer[3], size_buffer[3];
	Material* colour;
	GLuint texture;


public:

	pontos();
	pontos(string s, vector<Point*>, vector<Point*> , vector<Point*>, Material*);
	Material* getColour();
	void setColour(Material*);
	void loadTexture(string s);
	void prepare(vector<Point*>, vector<Point*>, vector<Point*>);
	void draw();

};




#endif
