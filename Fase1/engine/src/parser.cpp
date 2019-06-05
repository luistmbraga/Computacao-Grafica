#include "headers/parser.h"


void readFile(string name, vector<Point*>* LP) {
	vector<string> coord;
	string buffer;
	string linha;
	int index = 0;

	ifstream file(name);
	if (file.is_open()) {

		getline(file, linha);                   // Guarda a primeira linha que corresponde ao nº de vértices presentes no ficheiro a ler.
		int nvertices = atoi(linha.c_str());
		for (int i = 0; i < nvertices; i++) {
			getline(file, linha);           // percorre as linhas dos ficheiros
			stringstream ss(linha);
			while (ss >> buffer) coord.push_back(buffer);            // percorrer as coordenadas dos vértices em cada linha
			
			float x = stof(coord[index]);             // guarda a coordenada x
			float y = stof(coord[index + 1]);	      // guarda a coordenada y
			float z = stof(coord[index + 2]);		  // guarda a coordenada z
			LP->push_back(new Point(x, y, z));		  // guarda o ponto no vetor de pontos
		    index += 3;
		}
	}
	else { cout << "Nao foi possivel abrir o ficheiro 3d (possivelmente nao tera gerado os pontos da figura a desenhar com o 'generator')" << endl; }
}

void readXML(string name, vector<Point*>* LP) {
	XMLDocument doc;
	string s;
	string path = "xml/" + name;
	if (!(doc.LoadFile(path.c_str()))) {
		XMLElement* root = doc.FirstChildElement("scene");
		if (root == nullptr) return;
		XMLElement *elemento = root->FirstChildElement("model");
		while (elemento != nullptr) {
			s = elemento->Attribute("file");
			readFile(s, LP);
			elemento = elemento->NextSiblingElement();
		}
	}
	else {
		cout << "Nao foi possivel realizar a leitura do ficheiro XML (possivelmente porque ele nao existe)! " << endl;
	}
	return;
}

