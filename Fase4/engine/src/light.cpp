#include "headers/light.h"


Light::Light() {
	point = true;
	p = new Point(0, 0, 0);
}

Light::Light(bool b, Point* r) {
	point = b;
	p = r;
}

bool Light::getType() {
	return point;
}
Point* Light::getPoint() {
	return p;
}
void Light::setType(bool type){
	point = type;

}
void Light::setPoint(Point* ponto) {
	p = ponto;
}

void Light::draw() {
	GLfloat ambient[4] = { 0.1,0.1,0.1, 1 };
	GLfloat diffuse[4] = { 1, 1, 1, 0 };
	GLfloat position[4] = { p->getX(), p->getY() , p->getZ(), (float) point };

	// light position
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	// light colors
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
}