#include "headers/material.h"

Material::Material() {

}

Material::Material(Material* m) {
	float* d = (float*) m->getDiffuse();
	diffuse[0] = d[0];
	diffuse[1] = d[1];
	diffuse[2] = d[2];
	diffuse[3] = d[3];

	float* s = m->getSpecular();
	specular[0] = s[0];
	specular[1] = s[1];
	specular[2] = s[2];
	specular[3] = s[3];

	float* e = m->getEmission();
	emission[0] = e[0];
	emission[1] = e[1];
	emission[2] = e[2];
	emission[3] = e[3];
	
	float* a = m->getAmbient();
	ambient[0] = a[0];
	ambient[1] = a[1];
	ambient[2] = a[2];
	ambient[3] = a[3];
	
	shini = m->getShini();
}

Material::Material(Point* diff, Point* specul, Point* emiss, Point* amb, float shin) {
	
	diffuse[0] = diff->getX();
	diffuse[1] = diff->getY(); 
	diffuse[2] = diff->getZ();
	diffuse[3] = 1;
	
	specular[0] = specul->getX();
	specular[1] = specul->getY();
	specular[2] = specul->getZ();
	specular[3] = 1;
	
	emission[0] = emiss->getX();
	emission[1] = emiss->getY();
	emission[2] = emiss->getZ();
	emission[3] = 1;

	ambient[0] = amb->getX();
	ambient[1] = amb->getY();
	ambient[2] = amb->getZ();
	ambient[3] = 1;

	shini = shin;
}
float* Material::getDiffuse() {
	return diffuse;
}
float* Material::getSpecular() {
	return specular;
}
float* Material::getEmission() {
	return emission;
}
float* Material::getAmbient() {
	return ambient;
}
float Material::getShini() {
	return shini;
}

void Material::draw() {
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shini);
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, emission);
}