#include "../headers/BezierPatch.h"
#include "../../src/headers/Struct.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>


using namespace std;

Point BezierPatch::calculaPontos(std::vector<int> patch, std::vector<Point *> pontos, float u, float v) {

#define B(i)    pontos[patch[i]]

	float coef1 = (1 - u)*(1 - u)*(1 - u); 
	float coef2 = 3 * (1 - u)*(1 - u) * u; 
	float coef3 = 3 * (1 - u) * u * u;
	float coef4 = u * u * u;

	float x1 = coef1 * B(0)->getX() + coef2 * B(1)->getX() + coef3 * B(2)->getX() + coef4 * B(3)->getX();
	float x2 = coef1 * B(4)->getX() + coef2 * B(5)->getX() + coef3 * B(6)->getX() + coef4 * B(7)->getX();
	float x3 = coef1 * B(8)->getX() + coef2 * B(9)->getX() + coef3 * B(10)->getX() + coef4 * B(11)->getX();
	float x4 = coef1 * B(12)->getX() + coef2 * B(13)->getX() + coef3 * B(14)->getX() + coef4 * B(15)->getX();

	float y1 = coef1 * B(0)->getY() + coef2 * B(1)->getY() + coef3 * B(2)->getY() + coef4 * B(3)->getY();
	float y2 = coef1 * B(4)->getY() + coef2 * B(5)->getY() + coef3 * B(6)->getY() + coef4 * B(7)->getY();
	float y3 = coef1 * B(8)->getY() + coef2 * B(9)->getY() + coef3 * B(10)->getY() + coef4 * B(11)->getY();
	float y4 = coef1 * B(12)->getY() + coef2 * B(13)->getY() + coef3 * B(14)->getY() + coef4 * B(15)->getY();

	float z1 = coef1 * B(0)->getZ() + coef2 *B(1)->getZ() + coef3 * B(2)->getZ() + coef4 * B(3)->getZ();
	float z2 = coef1 * B(4)->getZ() + coef2 * B(5)->getZ() + coef3 * B(6)->getZ() + coef4 * B(7)->getZ();
	float z3 = coef1 * B(8)->getZ() + coef2 * B(9)->getZ() + coef3 * B(10)->getZ() + coef4 * B(11)->getZ();
	float z4 = coef1 * B(12)->getZ() + coef2 * B(13)->getZ() + coef3 * B(14)->getZ() + coef4 * B(15)->getZ();

	float Coef1 = (1 - v)*(1 - v)*(1 - v);
	float Coef2 = 3 * (1 - v)*(1 - v) * v;
	float Coef3 = 3 * (1 - v) * v * v;
	float Coef4 = v * v * v;
	 
	float x = Coef1 * x1 + Coef2 * x2 + Coef3 * x3 + Coef4 * x4;
	float y = Coef1 * y1 + Coef2 * y2 + Coef3 * y3 + Coef4 * y4;
	float z = Coef1 * z1 + Coef2 * z2 + Coef3 * z3 + Coef4 * z4;

	return Point(x, y, z);
#undef B
}

void BezierPatch::BezierCurve(std::vector<Point> *vertices, std::vector<int> patch, std::vector<Point *> points,
	float u, float v, float intervalo) {

	Point p1 = calculaPontos(patch, points, u, v);
	Point p2 = calculaPontos(patch, points, u, v + intervalo);
	Point p3 = calculaPontos(patch, points, u + intervalo, v);
	Point p4 = calculaPontos(patch, points, u + intervalo, v + intervalo);

	vertices->push_back(p1);
	vertices->push_back(p4);
	vertices->push_back(p2);

	vertices->push_back(p4);
	vertices->push_back(p1);
	vertices->push_back(p3);
}

void BezierPatch::Bezierpatch(int tesselacao, string input, string output) {
	FILE *entrada;
	FILE *saida;
	char path[100];

	strcpy_s(path, "patch_files/");
	strcat_s(path, input.c_str());

	entrada = fopen(path, "r");
	if (entrada == NULL) return;

	char line[512];

	// retira o numero de patches existentes no ficheiro
	fgets(line, 511, entrada);
	int nPatches = atoi(line);

	// retira do ficheiro os indices dos patches
	std::vector<std::vector<int>> patches;
	int t;
	for (int i = 0; i < nPatches; i++) {

		fgets(line, 511, entrada);
		stringstream strstream(line);
		patches.push_back(std::vector<int>());

		while (strstream >> t) {
			patches[i].push_back(t);
			if (strstream.peek() == ',') {
				strstream.ignore();
			}
		}

	}

	// retira do ficheiro o numero de pontos de controlo
	fgets(line, 511, entrada);
	int nPoints = atoi(line);

	std::vector<Point *> pontosControlo;
	float x, y, z;
	for (int i = 0; i < nPoints; i++) {

		fgets(line, 1023, entrada);
		stringstream strstream(line);
		strstream >> x;

		if (strstream.peek() == ',') {
			strstream.ignore();
		}

		strstream >> y;
		if (strstream.peek() == ',') {
			strstream.ignore();
		}

		strstream >> z;
		if (strstream.peek() == ',') {
			strstream.ignore();
		}

		pontosControlo.push_back(new Point(x, y, z));
	}

	fclose(entrada);

	// vector usado para guardar os pontos resultado
	std::vector<Point> resultados;

	// geram-se entao os pontos 
	for (int i = 0; i < nPatches; i++) {
		float u = 0.0;
		float v = 0.0;
		float intervalo = (float) 1.0 / tesselacao;

		for (int j = 0; j < tesselacao; j++) {
			for (int k = 0; k < tesselacao; k++) {
				BezierCurve(&resultados, patches[i], pontosControlo, u, v, intervalo);
				v += intervalo;
			}
			u += intervalo;
			v = 0.0;
		}
	}

	// coloca os resultados no ficheiro 3d destino
	int size = resultados.size();

	strcpy_s(path, "../3dFiles/");
	strcat_s(path, output.c_str());

	saida = fopen(path, "w");
	if (saida == NULL) return;

	fprintf(saida, "%d\n", size);

	size += 1;

	for (int i = 1; i < size; i++) {
		fprintf(saida, "%f %f %f\n", resultados[i].getX(), resultados[i].getY(), resultados[i].getZ());
	}

	fclose(saida);

}


