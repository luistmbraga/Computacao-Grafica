#ifndef __GROUP_H__
#define __GROUP_H__

#include <vector>
#include "scale.h"
#include "colour.h"
#include "pontos.h"
#include "rotate.h"
#include "translate.h"
#include "../../../src/headers/Point.h"
#include "headers/light.h"

using namespace std;

class Group {
	int id;
	Rotate* rotation;				// rotação associada ao group
	Translate* translation;			// translação associada ao group
	Scale* scale;					// escala associada ao group
	vector<Light*> lights;          // conjunto de luzes associado ao group
	vector<pontos*> LP;				// pontos, normais e texturas a desenhar associado ao group
	vector<Group*> childs;			// vetor com filhos do tipo Group associado ao group

public:
	Group();
	Group(int);
	int getID();
	Rotate* getRotation();
	Translate* getTranslation();
	Scale* getScale();
	vector<Light*> getLights();
	vector<pontos*> getLP();
	vector<Group*> getChilds();
	void setRotation(Rotate*);
	void setTranslation(Translate*);
	void setScale(Scale*);
	void setPontos(vector<pontos*>);
	void addLight(Light*);
	void addLP(pontos*);
	void addChild(Group*);

};


#endif