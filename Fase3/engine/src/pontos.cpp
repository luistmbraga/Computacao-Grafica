#include "headers/pontos.h"



pontos::pontos() {
}

pontos::pontos(vector<Point*> l) {
	size_buffer = l.size();
	prepare(l);
}

void pontos::prepare(vector<Point*> l) {
	float *vertex;
	glewInit();
	vertex = (float *) malloc(sizeof(float) * size_buffer * 3);
	for (size_t i = 0; i < size_buffer; i++) {
		vertex[i*3] = l[i]->getX();
		vertex[i*3 +1] = l[i]->getY();
		vertex[i*3 +2] = l[i]->getZ();
	}
	
	glGenBuffers(1, &buffer); 
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size_buffer * 3 , vertex, GL_STATIC_DRAW);

	free(vertex);
}

void pontos::draw() {
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, size_buffer);
}