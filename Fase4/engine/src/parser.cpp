#include "headers/parser.h"

int nr_models = 0;
int nr_group = 0;

void parseTranslate(Group* g, XMLElement* e) {
	float x = 0, y = 0, z = 0;										// inicializa as variáveis x, y e z
	float time;
	vector<Point*> v;
	if (e->Attribute("time")) {
		
		time = stof(e->Attribute("time"));
		XMLElement* points = e->FirstChildElement("point");
		
		while (points != nullptr) {

			if (points->Attribute("X")) x = stof(points->Attribute("X"));		// coloca na variável x a componente X associada ao translate
			else x = 0;

			if (points->Attribute("Y")) y = stof(points->Attribute("Y"));		// coloca na variável y a componente Y associada ao translate
			else y = 0;

			if (points->Attribute("Z")) z = stof(points->Attribute("Z"));		// coloca na variável z a componente Z associada ao translate
			else z = 0;

			v.push_back(new Point(x, y, z));
			points = points->NextSiblingElement();
		}
	}

	else time = 0;

	g->setTranslation(new Translate(time, v));									// adiciona ao group essa translação

}

void parseRotate(Group* g, XMLElement* e) {
	float time = 0, x = 0, y = 0, z = 0;							// inicializa as variáveis angle, x, y e z

	if (e->Attribute("time")) time = stof(e->Attribute("time"));	// coloca na variável angle a componente Angle associada ao rotate

	if (e->Attribute("X")) x = stof(e->Attribute("X"));				// coloca na variável x a componente X associada ao rotate

	if (e->Attribute("Y")) y = stof(e->Attribute("Y"));				// coloca na variável y a componente Y associada ao rotate

	if (e->Attribute("Z")) z = stof(e->Attribute("Z"));				// coloca na variável z a componente Z associado ao rotate

	Rotate* rotate = new Rotate(time,x, y, z);						// cria uma instância de rotate com os respetivos valores em angle, x, y e z

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

void parseLight(Group* g, XMLElement* e) {
	float x, y, z;

	if (e->Attribute("posX")) {
		x = stof(e->Attribute("posX"));
	}
	if (e->Attribute("posY")) {
		y = stof(e->Attribute("posY"));
	}
	if (e->Attribute("posZ")) {
		z = stof(e->Attribute("posZ"));
	}

	g->addLight(new Light(true, new Point(x, y, z)));
}


// Faz parser das cores associadas a um dado modelo
void parseMaterial(XMLElement* model, Group* g, string s, vector<Point*> l, vector<Point*> n, vector<Point*> t) {
	Point* diffuse = new Point(0.8, 0.8, 0.8);
	Point* specular = new Point(0, 0, 0);
	Point* emission = new Point(0, 0, 0);
	Point* ambient = new Point(0.2, 0.2, 0.2);
	float shini = 0;
	string a;
	float diffX = 0.8, diffY = 0.8, diffZ = 0.8;
	float specX = 0, specY = 0, specZ = 0;
	float emiX = 0, emiY = 0, emiZ = 0;
	float ambX = 0.2, ambY = 0.2, ambZ = 0.2;
	//float shini = 0;

	if (model->Attribute("diffX")) {
		diffX = stof(model->Attribute("diffX"));
	}
	if (model->Attribute("diffY")) {
		diffY = stof(model->Attribute("diffY"));
	}
	if (model->Attribute("diffZ")) {
		diffZ = stof(model->Attribute("diffZ"));
	}

	if (model->Attribute("specX")) {
		specX = stof(model->Attribute("specX"));
	}
	if (model->Attribute("specY")) {
		specY = stof(model->Attribute("specY"));
	}
	if (model->Attribute("specZ")) {
		specZ = stof(model->Attribute("specZ"));
	}

	if (model->Attribute("emiX")) {
		emiX = stof(model->Attribute("emiX"));
	}
	if (model->Attribute("emiY")) {
		emiY = stof(model->Attribute("emiY"));
	}
	if (model->Attribute("emiZ")) {
		emiZ = stof(model->Attribute("emiZ"));
	}

	if (model->Attribute("ambX")) {
		ambX = stof(model->Attribute("ambX"));
	}
	if (model->Attribute("ambY")) {
		ambY = stof(model->Attribute("ambY"));
	}
	if (model->Attribute("ambZ")) {
		ambZ = stof(model->Attribute("ambZ"));
	}

	if (model->Attribute("shini")) {
		shini = stof(model->Attribute("shini"));
	}

	g->addLP(new pontos(s , l, n, t, new Material(new Point(diffX, diffY, diffZ),
		new Point(specX, specY, specZ), new Point(emiX, emiY, emiZ), new Point(ambX, ambY, ambZ), shini)));

}

// Lê o ficheiro (formato .3d) e devolve o vetor com os pontos lidos desse ficheiro
vector<pontos*> readFile(XMLElement* models, Group *g) {
	vector<string> coord;
	string buffer;
	string linha;
	int index = 0;
	vector<pontos*> resultado;

	for (; models!=nullptr ;models = models->NextSiblingElement()) {
		nr_models++;
		vector<Point*> LP;
		vector<Point*> textures;
		vector<Point*> normals;
		ifstream file(models->Attribute("file"));
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

				for (i = 0; i < nvertices; i++) {
					getline(file, linha);
					if (file.eof()) break;
					stringstream ss(linha);

					while (ss >> buffer) coord.push_back(buffer);

					float x = stof(coord[index]);							// guarda a coordenada x
					float y = stof(coord[index + 1]);						// guarda a coordenada y
					float z = stof(coord[index + 2]);						// guarda a coordenada z

					normals.push_back(new Point(x, y, z));				    // guarda o ponto no vetor de normais
					index += 3;
				}
				for (i = 0; i < nvertices; i++) {
					getline(file, linha);
					if (file.eof()) break;
					stringstream ss(linha);

					while (ss >> buffer) coord.push_back(buffer);

					float x = stof(coord[index]);							// guarda a coordenada x
					float y = stof(coord[index + 1]);						// guarda a coordenada y

					textures.push_back(new Point(x, y, 0));				    // guarda o ponto no vetor de texturas
					index += 3;
				}

			
			float diffX = 0.8, diffY = 0.8, diffZ = 0.8;
			float specX = 0, specY = 0, specZ = 0;
			float emiX = 0, emiY = 0, emiZ = 0;
			float ambX = 0.2, ambY = 0.2, ambZ = 0.2;
			float shini = 0;

			if (models->Attribute("diffX")) {
				diffX = stof(models->Attribute("diffX"));
			}
			if (models->Attribute("diffY")) {
				diffY = stof(models->Attribute("diffY"));
			}
			if (models->Attribute("diffZ")) {
				diffZ = stof(models->Attribute("diffZ"));
			}

			if (models->Attribute("specX")) {
				specX = stof(models->Attribute("specX"));
			}
			if (models->Attribute("specY")) {
				specY = stof(models->Attribute("specY"));
			}
			if (models->Attribute("specZ")) {
				specZ = stof(models->Attribute("specZ"));
			}

			if (models->Attribute("emiX")) {
				emiX = stof(models->Attribute("emiX"));
			}
			if (models->Attribute("emiY")) {
				emiY = stof(models->Attribute("emiY"));
			}
			if (models->Attribute("emiZ")) {
				emiZ = stof(models->Attribute("emiZ"));
			}

			if (models->Attribute("ambX")) {
				ambX = stof(models->Attribute("ambX"));
			}
			if (models->Attribute("ambY")) {
				ambY = stof(models->Attribute("ambY"));
			}
			if (models->Attribute("ambZ")) {
				ambZ = stof(models->Attribute("ambZ"));
			}

			if (models->Attribute("shini")) {
				shini = stof(models->Attribute("shini"));
			}

			if (models->Attribute("texture")) {

				//parseMaterial(models, g, models->Attribute("texture"), LP, normals, textures);
				Material* m = new Material(new Point(diffX, diffY, diffZ), new Point(specX, specY, specZ), new Point(emiX, emiY, emiZ), new Point(ambX, ambY, ambZ), shini);
				resultado.push_back(new pontos(models->Attribute("texture"), LP, normals, textures, new Material(m)));
			}
			else {
				Material* m = new Material(new Point(diffX, diffY, diffZ), new Point(specX, specY, specZ), new Point(emiX, emiY, emiZ), new Point(ambX, ambY, ambZ), shini);
				resultado.push_back(new pontos("", LP, normals, textures, new Material(m)));
				
				//parseMaterial(models, g, "", LP, normals, textures);
			}
		}
		else { cout << "Nao foi possivel abrir o ficheiro 3d (possivelmente nao tera gerado os pontos da figura a desenhar com o 'generator')" << endl; }
	}
	return resultado;
}


//Vai ler e analizar tudo de um dado group e respetivos filhos
void parseGroup(Group* g, XMLElement* e) {

	XMLElement* light = e->FirstChildElement("light");
	for (; light != nullptr; light = light->NextSiblingElement()) {
		parseLight(g, light);
	}

	XMLElement* trans = e->FirstChildElement("translate");
	if (trans != nullptr) parseTranslate(g, trans);				// analisa a translação associada ao respetivo group
	
	XMLElement* rotate = e->FirstChildElement("rotate");
	if (rotate != nullptr) parseRotate(g, rotate);				// analisa a rotação associada ao respetivo group 
	
	XMLElement* scale = e->FirstChildElement("scale");
	if (scale != nullptr) parseScale(g, scale);					// analisa a escala associada ao respetivo group 

	XMLElement* models = e->FirstChildElement("models");
	if (models != nullptr) {									// o modelo (figura) associado ao respetivo group
		models = models->FirstChildElement("model");
		g->setPontos(readFile(models, g));									// irá associar ao vetor de pontos, textura e normais de group os pontos a desenhar futuramente
	}					 
	
	XMLElement* childs = e->FirstChildElement("group");
	if (childs!=nullptr) {												// verifica se o group que está a ser analisado tem filhos
		while (childs != nullptr) {										// enquanto tiver filhos
			Group* child = new Group(++nr_group);					    // inicializa o filho
			g->addChild(child);											// adiciona o filho ao respetivo pai
			if (childs) parseGroup(child, childs);					    // irá fazer 'parse' (analisar) o filho	 
			childs = childs->NextSiblingElement();
		}
	}
}


// lê o XML e devolve o nº de group's desse XML
int readXML(string name, vector<Group*>* LG) {
	XMLDocument doc;
	if (!(doc.LoadFile(name.c_str()))) {
		XMLElement* root = doc.FirstChildElement("scene");
		if (root == nullptr) return 0;
		XMLElement *elemento = root->FirstChildElement("group");		// coloca na variável elemento 
		while (elemento != nullptr) {									// vai analisar todos os group's
			Group* g = new Group(nr_group);			                    // inicializa o group com um respetivo id
			parseGroup(g, elemento);									// analisa tudo o que está dento do group
			LG->push_back(g);											// adiciona o grupo à lista de grupos processados
			elemento = elemento->NextSiblingElement();					// percorre os seus irmãos 
		}
	}

	else {
		cout << "Nao foi possivel realizar a leitura do ficheiro XML (possivelmente porque ele nao existe)! " << endl;
	}

	return nr_models;
}

