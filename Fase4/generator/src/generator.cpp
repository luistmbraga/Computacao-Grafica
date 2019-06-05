#include "../../src/headers/Struct.h"
#include "../headers/BezierPatch.h"
#include <iostream>
#include <fstream>

using namespace std;

// Responsável por guardar os pontos, normais e texturas gerados num documento.
void saveFile(Struct *p, string nomeF) {
	fstream(file);
	file.open("../3dFiles/" + nomeF, fstream::out);
	
	if (file.is_open()) { // verifica se foi aberto
		vector<Point*> v = p->getLP();
		vector<Point*> normal = p->getNormal();
		vector<Point*> textura = p->getTextura();

		file << to_string(v.size()) << endl;                 // coloca o tamanho da lista de pontos no ficheiro

		for (vector<Point*>::iterator it = v.begin(); it != v.end(); ++it) { //percorre a lista de pontos toda, escrevendo cada ponto no ficheiro
			file << (*it)->to_String() << endl; 
		}
		
		for (vector<Point*>::iterator it = normal.begin(); it != normal.end(); ++it) { //percorre a lista das normais toda, escrevendo cada ponto no ficheiro
			file << (*it)->to_String() << endl;
		}

		for (vector<Point*>::iterator it = textura.begin(); it != textura.end(); ++it) { //percorre a lista das texturas toda, escrevendo cada ponto no ficheiro
			file << (*it)->to_String() << endl;
		}

		file.close(); // fecha o ficheiro
	}
	else { cout << "Nao se conseguiu abrir o ficheiro." << endl; }
}


void help() {
	cout << "*---------------------------------HELP---------------------------------*" << endl;
	cout << "|                                                                      |" << endl;
	cout << "|            Modo de utlizacao:                                        |" << endl;
	cout << "| $ generator.exe figura [argumentos] ficheiro(.3d)                    |" << endl;
	cout << "|                                                                      |" << endl;
	cout << "|         Figuras:                                                     |" << endl;
	cout << "|               -plane :                                               |" << endl;
	cout << "|                     argumentos:                                      |" << endl;
	cout << "|                            -tamanho.                                 |" << endl;
	cout << "|               -box :                                                 |" << endl;
	cout << "|                     argumentos :                                     |" << endl;
	cout << "|                            -X Y Z divisoes(opcional).                |" << endl;
	cout << "|               -sphere :                                              |" << endl;
	cout << "|                     argumentos:                                      |" << endl;
	cout << "|                            -Raio Fatias Pilhas                       |" << endl;
	cout << "|               -cone :                                                |" << endl;
	cout << "|                     argumentos:                                      |" << endl;
	cout << "|                            - Raio Altura Fatias Pilhas.              |" << endl;
	cout << "|               -cylinder :                                            |" << endl;
	cout << "|                     argumentos:                                      |" << endl;
	cout << "|                            -Raio Altura Fatias.                      |" << endl;
	cout << "|                                                                      |" << endl;
	cout << "|               -torus :                                               |" << endl;
	cout << "|                     argumentos:                                      |" << endl;
	cout << "|                            -TamanhoCoroa RaioExterior Stacks Aneis   |" << endl;
	cout << "|                                                                      |" << endl;
	cout << "|               -cintura de asteroides :                               |" << endl;
	cout << "|                     argumentos:                                      |" << endl;
	cout << "|                            -TamanhoCoroa RaioExterior Faces  Aneis   |" << endl;
	cout << "|                                                                      |" << endl;
	cout << "|               -bezierPatch :                                               |" << endl;
	cout << "|                     argumentos:                                      |" << endl;
	cout << "|                            - NivelTesselacao ficheiroPatch           |" << endl;
	cout << "|                                                                      |" << endl;
	cout << "|         Exemplo de utilizacao:                                       |" << endl;
	cout << "|           $ generator.exe sphere 1 10 10 sphere.3d                   |" << endl;
	cout << "|                                                                      |" << endl;
	cout << "*---------------------------------HELP---------------------------------*" << endl;
} 


int main(int argc, char* argv[]) {

	if (argc >= 2) {

		//comando help
		if (strcmp(argv[1], "-h") == 0) {
			help();
			return 0;
		}

		Struct* p = new Struct();
		string nomeF;

		//gera pontos do plano
		if (strcmp(argv[1], "plane") == 0 && argc == 4) {
			float dim = stof(argv[2]);
			nomeF = argv[3];
			p->genPlane(dim);
			saveFile(p, nomeF);
			return 0;
		}

		if (strcmp(argv[1], "cylinder") == 0 && argc == 6) {
			float radius = stof(argv[2]);
			float height = stof(argv[3]);
			int slices = (int)atoi(argv[4]);
			nomeF = argv[5];
			p->genCylinder(radius, height, slices);
			saveFile(p, nomeF);
			return 0;
		}

		if (strcmp(argv[1], "sphere") == 0 && argc == 6) {
			float radius = stof(argv[2]);
			int slices = atoi(argv[3]);
			int stack = atoi(argv[4]);
			nomeF = argv[5];
			p->genSphere(radius, slices, stack);
			saveFile(p, nomeF);
			return 0;
		}


		//desenha box
		if (strcmp(argv[1], "box") == 0 && argc > 5) {
			float x = stof(argv[2]);
			float y = stof(argv[3]);
			float z = stof(argv[4]);

			if (argc == 6) { p->genBox(x, y, z, 1); nomeF = argv[5]; }

			if (argc == 7) {
				int divisions = atoi(argv[5]);
				p->genBox(x, y, z, divisions);
				nomeF = argv[6];
			}
			saveFile(p, nomeF);

			return 0;
		}

		if (strcmp(argv[1], "torus") == 0 && argc == 7) {

			float raioIn = stof(argv[2]);
			float raioEx = stof(argv[3]);
			int sides = atoi(argv[4]);
			int rings = atoi(argv[5]);

			p->genTorus(raioIn, raioEx, sides, rings);

			nomeF = argv[6];

			saveFile(p, nomeF);

			return 0;
		}

		//le o ficheiro de patch e produz a figura
		if (strcmp(argv[1], "bezierPatch") == 0 && argc == 5) {

			int tess = atoi(argv[2]); // nivel de tesselação
			string input_file = argv[3]; // ficheiro do patch
			string output_file = argv[4];

			BezierPatch bp;

			bp.Bezierpatch(tess, input_file, output_file);

			return 0;
		}

		//desenha cintura de asteroides
		if (strcmp(argv[1], "cintura") == 0 && argc == 7) {

			float raioIn = stof(argv[2]);
			float raioEx = stof(argv[3]);
			int sides = atoi(argv[4]);
			int rings = atoi(argv[5]);

			p->genCintura(raioIn, raioEx, sides, rings);

			nomeF = argv[6];

			saveFile(p, nomeF);

			return 0;
		}

		//desenha cone
		if (strcmp(argv[1], "cone") == 0 && argc == 7) {
			float radius = stof(argv[2]);
			float height = stof(argv[3]);
			int slices = atoi(argv[4]);
			int stack = atoi(argv[5]);
			nomeF = argv[6];

			p->genCone(radius,height,slices,stack);
			saveFile(p, nomeF);
			return 0;
		}
		else { cout << "Nao tem argumentos suficientes ou figura nao existe" << endl; }
		
	}
	
	else{
		cout << "Nao tem argumentos suficientes! Se precisar de ajuda execute 'generator.exe -h'" << endl; 
		return 0;
	}
}
