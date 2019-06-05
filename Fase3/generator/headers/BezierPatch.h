#ifndef __BEZIERPATCH_H__
#define __BEZIERPATCH_H__

#include <vector>
#include "../../src/headers/Point.h"

using namespace std;

class BezierPatch {

	public:
		
		void Bezierpatch(int tesselacao, string input, string output);
		void BezierCurve(std::vector<Point> *vertices, std::vector<int> patch, std::vector<Point *> points,
			float u, float v, float intervalo);
		Point calculaPontos(std::vector<int> patch, std::vector<Point *> pontos, float u, float v);
};

#endif