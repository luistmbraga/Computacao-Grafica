#ifndef __GROUP_H__
#define __GROUP_H__

#include <vector>
#include "rotate.h"
#include "translate.h"
#include "scale.h"
#include "colour.h"
#include "../../../src/headers/Point.h"

using namespace std;

class Group {
	Rotate* rotation;				// rotação associada ao group
	Translate* translation;			// translação associada ao group
	Scale* scale;					// escala associada ao group
	Colour* colour;					// cor associada ao group
	vector<Point*> LP;				// vetor de pontos a desenhar associado ao group
	vector<Group*> childs;			// vetor com filhos do tipo Group associado ao group

public:
	Group();
	Rotate* getRotation();
	Translate* getTranslation();
	Scale* getScale();
	Colour* Group::getColour();
	vector<Point*> getLP();
	vector<Group*> getChilds();
	void setRotation(Rotate*);
	void setTranslation(Translate*);
	void setScale(Scale*);
	void setColour(Colour*);
	void setLP(vector<Point*>);
	void addChild(Group*);

};


#endif