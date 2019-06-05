#include "headers/group.h"

Group::Group(){
	rotation = new Rotate();
	translation = new Translate();
	scale = new Scale();
	colour = new Colour();
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

vector<Point*> Group::getLP() {
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
	LP = l;
}

void Group::addChild(Group* g) {
	childs.push_back(g);
}