#include "headers/parser.h"

int nr_group = 0;

void parseTranslate(Group* g, XMLElement* e) {
	float x = 0, y = 0, z = 0;										// inicializa as variáveis x, y e z

	if (e->Attribute("X")) x = stof(e->Attribute("X"));				// coloca na variável x a componente X associada ao translate

	if (e->Attribute("Y")) y = stof(e->Attribute("Y"));				// coloca na variável y a componente Y associada ao translate

	if (e->Attribute("Z")) z = stof(e->Attribute("Z"));				// coloca na variável z a componente Z associada ao translate

	Translate* translate = new Translate(x, y, z);					// cria uma instância de translate com os respetivos valores em x, y e z

	g->setTranslation(translate);									// adiciona ao group essa translação

}

void parseRotate(Group* g, XMLElement* e) {
	float angle = 0, x = 0, y = 0, z = 0;							// inicializa as variáveis angle, x, y e z

	if (e->Attribute("Angle")) angle = stof(e->Attribute("Angle"));	// coloca na variável angle a componente Angle associada ao rotate

	if (e->Attribute("X")) x = stof(e->Attribute("X"));				// coloca na variável x a componente X associada ao rotate

	if (e->Attribute("Y")) y = stof(e->Attribute("Y"));				// coloca na variável y a componente Y associada ao rotate

	if (e->Attribute("Z")) z = stof(e->Attribute("Z"));				// coloca na variável z a componente Z associado ao rotate

	Rotate* rotate = new Rotate(angle,x, y, z);						// cria uma instância de rotate com os respetivos valores em angle, x, y e z

	g->setRotation(rotate);											// adiciona ao group essa rotação
}

void parseScale(Group* g, XMLElement* e) {
	float x = 0, y = 0, z = 0;										// inicializa as variáveis x, y e z

	if (e->Attribute("X")) x = stof(e->Attribute("X"));				// coloca na variável x a componente X associado ao scale

	if (e->Attribute("Y")) y = stof(e->Attribute("Y"));				// coloca na variável y a componente Y associado ao scale

	if (e->Attribute("Z")) z = stof(e->Attribute("Z"));				// coloca na variável z a componente Z associado ao scale

	Scale* scale = new Scale(x, y, z);								// cria uma instância de scale com os respetivos valores em x, y e z

	g->setScale(scale);												// adiciona ao group essa escala
}

void parseColour(Group* g, XMLElement* e) {
	float x = 0, y = 0, z = 0;										// inicializa as variáveis x, y e z

	if (e->Attribute("X")) x = stof(e->Attribute("X"));				// coloca na variável x a componente X associado à cor

	if (e->Attribute("Y")) y = stof(e->Attribute("Y"));				// coloca na variável y a componente Y associado à cor

	if (e->Attribute("Z")) z = stof(e->Attribute("Z"));				// coloca na variável z a componente Z associado à cor

	Colour* colour = new Colour(x, y, z);							// cria uma instância de colour com os respetivos valores em x, y e z

	g->setColour(colour);											// adiciona ao group essa cor
}



// Lê o ficheiro (formato .3d) e devolve o vetor com os pontos lidos desse ficheiro
vector<Point*> readFile(string name) {
	vector<string> coord;
	string buffer;
	string linha;
	int index = 0;
	
	vector<Point*> LP;
	ifstream file(name);
	if (file.is_open()) {
		getline(file, linha);										// Guarda a primeira linha que corresponde ao nº de vértices presentes no ficheiro a ler.
		int nvertices = atoi(linha.c_str());
		int i;
		for (i = 0; i < nvertices; i++) {
			getline(file, linha);									// percorre as linhas dos ficheiros
			stringstream ss(linha);
			while (ss >> buffer) coord.push_back(buffer);           // percorrer as coordenadas dos vértices em cada linha
			
			float x = stof(coord[index]);							// guarda a coordenada x
			float y = stof(coord[index + 1]);						// guarda a coordenada y
			float z = stof(coord[index + 2]);						// guarda a coordenada z
			LP.push_back(new Point(x, y, z));						// guarda o ponto no vetor de pontos
		    index += 3; 
		}
	}
	else { cout << "Nao foi possivel abrir o ficheiro 3d (possivelmente nao tera gerado os pontos da figura a desenhar com o 'generator')" << endl; }

	return LP;
}


//Vai ler e analizar tudo de um dado group e respetivos filhos
void parseGroup(Group* g, XMLElement* e) {

	XMLElement* trans = e->FirstChildElement("translate");
	if (trans != nullptr) parseTranslate(g, trans);				// analisa a translação associada ao respetivo group
	
	XMLElement* rotate = e->FirstChildElement("rotate");
	if (rotate != nullptr) parseRotate(g, rotate);				// analisa a rotação associada ao respetivo group 
	
	XMLElement* scale = e->FirstChildElement("scale");
	if (scale != nullptr) parseScale(g, scale);					// analisa a escala associada ao respetivo group 
	
	XMLElement* colour = e->FirstChildElement("colour");		
	if (colour != nullptr) parseColour(g, colour);				// analisa a cor associada ao respetivo group

	XMLElement* models = e->FirstChildElement("models");
	if (models != nullptr) {									// o modelo (figura) associado ao respetivo group
		models = models->FirstChildElement("model");
		while(models!=nullptr) {
			g->setLP((readFile(models->Attribute("file"))));					// irá associar ao vetor de pontos de group os pontos a desenhar futuramente
			models = models->NextSiblingElement();
		}
	}					 

	XMLElement* childs = e->FirstChildElement("group");
	if (childs!=nullptr) {												// verifica se o group que está a ser analisado tem filhos
		while (childs != nullptr) {										// enquanto tiver filhos
			nr_group++;													// incrementa o número de group's
			Group* child = new Group();									// inicializa o filho
			g->addChild(child);											// adiciona o filho ao respetivo pai
			if (childs) parseGroup(child, childs);					    // irá fazer 'parse' (analisar) o filho	 
			childs = childs->NextSiblingElement();
		}
	}
}


// lê o XML e devolve o nº de group's desse XML
int readXML(string name, vector<Group*>* LG) {
	XMLDocument doc;
	//string path = "xml/" + name;
	if (!(doc.LoadFile(name.c_str()))) {
		XMLElement* root = doc.FirstChildElement("scene");
		if (root == nullptr) return 0;
		XMLElement *elemento = root->FirstChildElement("group");		// coloca na variável elemento 
		while (elemento != nullptr) {									// vai analisar todos os group's
			nr_group++;													// incrementa o número de group's
			Group* g = new Group();			                            // inicializa o group com um respetivo id
			parseGroup(g, elemento);									// analisa tudo o que está dento do group
			LG->push_back(g);											// adiciona o grupo à lista de grupos processados
			elemento = elemento->NextSiblingElement();					// percorre os seus irmãos 
		}
	}

	else {
		cout << "Nao foi possivel realizar a leitura do ficheiro XML (possivelmente porque ele nao existe)! " << endl;
	}
	return nr_group;
}

