#include "headers/pontos.h"



pontos::pontos() {
}

pontos::pontos(string s, vector<Point*> l, vector<Point*> n, vector<Point*> t, Material* m){
	size_buffer[0] = l.size();
	size_buffer[1] = t.size();
	size_buffer[2] = n.size();
	prepare(l, n, t);
	if (s!="") {
		loadTexture(s);
	}
	colour = m;
}

void pontos::loadTexture(string s) {
	unsigned int t, tw, th;
	unsigned char *texData;

	//ilInit();

	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ilGenImages(1, &t);
	ilBindImage(t);
	ilLoadImage((ILstring) s.c_str());
	tw = ilGetInteger(IL_IMAGE_WIDTH);
	th = ilGetInteger(IL_IMAGE_HEIGHT);
	ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	texData = ilGetData();

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tw, th, 0, GL_RGBA, GL_UNSIGNED_BYTE, texData);
	//glBindTexture(GL_TEXTURE_2D, 0);
}

Material* pontos::getColour() {
	return colour;
}

void pontos::setColour(Material* c) {
	colour = c;
}


void pontos::prepare(vector<Point*> l, vector<Point*> n, vector<Point*> t) {
	float *vertex, *textur, *normal;

	glewInit();

	vertex = (float *) malloc(sizeof(float) * size_buffer[0] * 3);
	textur = (float *) malloc(sizeof(float) * size_buffer[1] * 3);
	normal = (float *) malloc(sizeof(float) * size_buffer[2] * 3);

	for (size_t i = 0; i < size_buffer[0]; i++) {
		vertex[i*3] = l[i]->getX();
		vertex[i*3 +1] = l[i]->getY();
		vertex[i*3 +2] = l[i]->getZ();
	}
	
	for(size_t i = 0; i < size_buffer[1]; i++){
		textur[i * 3] = t[i]->getX();
		textur[i * 3 + 1] = t[i]->getY();
	}

	for (size_t i = 0; i < size_buffer[2]; i++) {
		normal[i * 3] = n[i]->getX();
		normal[i * 3 + 1] = n[i]->getY();
		normal[i * 3 + 2] = n[i]->getZ();
	}
	int nr = 3;

	//if (!size_buffer[1]){
		//glGenBuffers(1, &buffer[0]);
	//}
	//else {
		glGenBuffers(3, buffer);
	//}

	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size_buffer[0] * 3 , vertex, GL_STATIC_DRAW);

	//if (!size_buffer[1]) {
		glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size_buffer[2] * 3, normal, GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * size_buffer[1] * 2, textur, GL_STATIC_DRAW);
	//}

	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	

	free(vertex);
	free(textur);
	free(normal);
}

void pontos::draw() {
	colour->draw();
	glBindBuffer(GL_ARRAY_BUFFER, buffer[0]);
	glVertexPointer(3, GL_FLOAT, 0, 0);

	if (size_buffer[2]) {
		glBindBuffer(GL_ARRAY_BUFFER, buffer[2]);
		glNormalPointer(GL_FLOAT, 0, 0);
	}

	if (size_buffer[1]) {
		glBindBuffer(GL_ARRAY_BUFFER, buffer[1]);
		glTexCoordPointer(2, GL_FLOAT, 0, 0);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
	
	glEnable(GL_LIGHTING);
	glDrawArrays(GL_TRIANGLES, 0, size_buffer[0] *3);
	glDisable(GL_LIGHTING);
	glBindTexture(GL_TEXTURE_2D, 0);

}