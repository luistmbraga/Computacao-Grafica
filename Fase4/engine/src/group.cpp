#include "headers/group.h"

Group::Group(){
	rotation = new Rotate();
	translation = new Translate();
	scale = new Scale();
}	

Group::Group(int i) {
	id = i;
	rotation = new Rotate();
	translation = new Translate();
	scale = new Scale();
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

vector<Light*> Group::getLights() {
	return lights;
}

vector<pontos*> Group::getLP() {
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

void Group::setPontos(vector<pontos*> p) {
	LP = p;
}

void Group::addLight(Light* l) {
	lights.push_back(l);
}

void Group::addLP(pontos* p) {
	LP.push_back(p);
}

void Group::addChild(Group* g) {
	childs.push_back(g);
}