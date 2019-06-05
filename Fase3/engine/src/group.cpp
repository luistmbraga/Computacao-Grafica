#include "headers/group.h"

Group::Group(){
	rotation = new Rotate();
	translation = new Translate();
	scale = new Scale();
	colour = new Colour();
}	

Group::Group(int i) {
	id = i;
	rotation = new Rotate();
	translation = new Translate();
	scale = new Scale();
	colour = new Colour();
}

int Group::getID() {
	return id;
}

Rotate* Group::getRotation() {
	return rotation;
}

Translate* Group::getTranslation() {
	return translation;
}

Scale* Group::getScale() {
	return scale;
}

Colour* Group::getColour() {
	return colour;
}

pontos Group::getLP() {
	return LP;
}

vector<Group*> Group::getChilds() {
	return childs;
}

void Group::setRotation(Rotate* r) {
	rotation = r;
}
void Group::setTranslation(Translate* t) {
	translation = t;
}

void Group::setScale(Scale* s) {
	scale = s;
}

void Group::setColour(Colour* c) {
	colour = c;
}

void Group::setLP(vector<Point*> l) {
	printf("\n antes inicializar vetor");
	LP = pontos(l);
	printf("\n depois inicializar vetor");
}

void Group::addChild(Group* g) {
	childs.push_back(g);
}