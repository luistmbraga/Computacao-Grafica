#include "headers/translate.h"

Translate::Translate(){
}

Translate::Translate(float time, vector<Point*> v){
	tempo = time;
	trans = v;
}

float Translate::getTempo() {
	return tempo;
}

vector<Point*> Translate::getTrans() {
	return trans;
}

vector<Point*> Translate::getCurve() {
	return curve;
}

void Translate::setTempo(float t) {
	tempo = t;
}

void Translate::setTrans(vector<Point*> l) {
	trans = l;
}

void Translate::setCurve(vector<Point*> v) {
	curve = v;
}

void Translate::getCatmullRomPoint(float t, int* indices, float* res, vector<Point*> tr) {
	float novo[4];
	float ttt, tt;
	int ind1, ind2, ind3, ind4;
	Point p0, p1, p2, p3;

	res[0] = res[1] = res[2] = 0.0;
	ttt = t * t * t;
	tt = t * t;

	float m[4][4] = { { -0.5f, 1.5f, -1.5f, 0.5f },
					 { 1.0f, -2.5f, 2.0f, -0.5f },
					 { -0.5f, 0.0f, 0.5f, 0.0f },
					 { 0.0f, 1.0f, 0.0f, 0.0f } };


	novo[0] = ttt * m[0][0] + tt * m[1][0] + t * m[2][0] + m[3][0];
	novo[1] = ttt * m[0][1] + tt * m[1][1] + t * m[2][1] + m[3][1];
	novo[2] = ttt * m[0][2] + tt * m[1][2] + t * m[2][2] + m[3][2];
	novo[3] = ttt * m[0][3] + tt * m[1][3] + t * m[2][3] + m[3][3];

	ind1 = indices[0];
	ind2 = indices[1];
	ind3 = indices[2];
	ind4 = indices[3];

	p0 = (*tr[ind1]);
	p1 = (*tr[ind2]);
	p2 = (*tr[ind3]);
	p3 = (*tr[ind4]);

	res[0] = novo[0] * p0.getX() + novo[1] * p1.getX() + novo[2] * p2.getX() + novo[3] * p3.getX();
	res[1] = novo[0] * p0.getY() + novo[1] * p1.getY() + novo[2] * p2.getY() + novo[3] * p3.getY();
	res[2] = novo[0] * p0.getZ() + novo[1] * p1.getZ() + novo[2] * p2.getZ() + novo[3] * p3.getZ();

}




void Translate::getGlobalCatmullRomPoint(float t, float *res, vector<Point*> tr) {

	int indices[4];

	int tam = tr.size();
	float gt = t * tam;
	int index = floor(gt);    // floor arredonda para o menor ou maior inteiro
	gt = gt - index;

	// indices armazenam os pontos
	indices[0] = (index + tam - 1) % tam;
	indices[1] = (indices[0] + 1) % tam;
	indices[2] = (indices[1] + 1) % tam;
	indices[3] = (indices[2] + 1) % tam;

	getCatmullRomPoint(gt, indices, res, tr);
}


void Translate::drawCurve() {

	float res[3];

	for (float t = 0; t < 1; t += 0.01) {

		getGlobalCatmullRomPoint(t, res, trans);
		curve.push_back(new Point(res[0], res[1], res[2]));
	}

}

void Translate::drawCatmullRomCurve() {
	int tam = curve.size();
	float p[3];

	glBegin(GL_LINE_LOOP);

	for (int i = 0; i < tam; i++) {
		p[0] = curve[i]->getX();
		p[1] = curve[i]->getY();
		p[2] = curve[i]->getZ();
		glVertex3fv(p);
	}

	glEnd();
}

void normalize(float *a) {

	float l = sqrt(a[0] * a[0] + a[1] * a[1] + a[2] * a[2]);
	a[0] = a[0] / l;
	a[1] = a[1] / l;
	a[2] = a[2] / l;
}

void cross(float *a, float *b, float *res) {

	res[0] = a[1] * b[2] - a[2] * b[1];
	res[1] = a[2] * b[0] - a[0] * b[2];
	res[2] = a[0] * b[1] - a[1] * b[0];
}


void curveRotation(float *der, float *up) {

	float left[3];

	cross(der, up, left);
	cross(left, der, up);

	normalize(der);
	normalize(up);
	normalize(left);

	float m[4][4] = { {der[0], der[1], der[2], 0},
					  {up[0], up[1], up[2], 0},
					  {left[0], left[1], left[2], 0},
					  {0.0f,0.0f,0.0f, 1}
	};
	glMultMatrixf((float*)m);
}


void Translate::draw() {
	float te, gt;
	float res[3];
	float deriv[3];
	float up[3];

	if (tempo != 0 && trans.size() != 0) {
		te = glutGet(GLUT_ELAPSED_TIME) % (int)(tempo * 1000);
		gt = te / (tempo * 1000);
		drawCurve();
		drawCatmullRomCurve();
		getGlobalCatmullRomPoint(gt, res, trans);
		curve.clear();
		glTranslatef(res[0], res[1], res[2]);
		curveRotation(deriv, up);
	}
}