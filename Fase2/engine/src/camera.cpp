#include "headers/camera.h"

float deslA = float(2 * (M_PI) / 16.0);
float deslB = float((M_PI) / 10.0);


// responsavel por inicializar a camera.
Camera::Camera() {
	camPosition = new Point(160, 160, 160);
	lookPoint = new Point(140.0, 0.0, 0.0);
	titl = new Point(0.0f, 1.0f, 0.0f);
	alfa = beta = 0.0;
	atualizaDist();
}

// Atualiza a camera conforme os valores de alfa, beta e dist.
void Camera::atualizaCamPosition() {
	float x = dist * cos(beta)*sin(alfa);  // calcula o novo valor de x para a posicao da camera.
	float y = dist * sin(beta);			   // calcula o novo valor de y para a posicao da camera.
	float z = dist * cos(beta)*cos(alfa);  // calcula o novo valor de z para a posicao da camera.

	setCamPosition(x, y, z);		// atualiza a posicao da camera.
}

void Camera::atualizaDist() {

	float Cx = camPosition->getX();
	float Cy = camPosition->getY();
	float Cz = camPosition->getZ();
	float LookPx = lookPoint->getX();
	float LookPy = lookPoint->getY();
	float LookPz = lookPoint->getZ();

	dist = sqrt(pow(Cx-LookPx,2) + pow(Cy-LookPy,2) + pow(Cz-LookPz,2));
	atualizaCamPosition();
}


//responsavel pela rotacao da posicao da camara para a esquerda.
void Camera::camUp() {
	beta += deslB;

	if (beta >= M_PI / 2) beta = float(M_PI / 2 - 0.001); // beta < pi/2

	atualizaCamPosition();
}

//responsavel pela rotacao da posicao da camara para baixo.
void Camera::camDown() {
	beta -= deslB;

	if (beta <= -M_PI / 2) beta = float(-M_PI / 2 + 0.001); //  beta > -pi/2

	atualizaCamPosition();
}

//responsavel pela rotacao da posicao da camara para a esquerda.
void Camera::camLeft() {
	alfa -= deslA;
	
	atualizaCamPosition();
}

//responsavel pela rotacao da posicao da camara para a direita.
void Camera::camRight() {
	alfa += deslA;

	atualizaCamPosition();
}

void Camera::FocusUp() {
	float y = lookPoint->getY()+1;
	lookPoint->setY(y);
	//atualizaDist();
	camPosition->setY(camPosition->getY() + 1);
}
void Camera::FocusDown() {
	float y = lookPoint->getY()-1;
	lookPoint->setY(y);
	camPosition->setY(camPosition->getY() - 1);
	//atualizaDist();
}
void Camera::FocusLeft() {
	float x = lookPoint->getX() - 1;
	lookPoint->setX(x);
	camPosition->setX(camPosition->getX() - 1);
	//atualizaDist();
}
void Camera::FocusRight() {
	float x = lookPoint->getX() + 1;
	lookPoint->setX(x);
	camPosition->setX(camPosition->getX() + 1);
	//atualizaDist();
}

//aproxima a camera do ponto a que esta a olhar.
void Camera::maisZoom() {
	dist -= 30.0f;
	
	atualizaCamPosition();
}

//afasta a camara do ponto a que esta a olhar.
void Camera::menosZoom() {
	dist += 30.0f;
	
	atualizaCamPosition();
}

// Devolve a posicao da camera.
Point* Camera::getCamPosition() {
	return camPosition;
}

// Devolve o ponto para o qual a camera esta a olhar.
Point* Camera::getLookPoint() {
	return lookPoint;
}

//Devolve o ponto do titl.
Point* Camera::getTitl() {
	return titl;
}

// Dadas as coordenadas, coloca a camera nessa posicao.
void Camera::setCamPosition(float x, float y, float z) {
	camPosition->setX(x);
	camPosition->setY(y);
	camPosition->setZ(z);
}

// Dadas as coordenadas, coloca a camera olhar para essas mesmas coordendas.
void Camera::setLookPoint(float x, float y, float z) {
	lookPoint->setX(x);
	lookPoint->setY(y);
	lookPoint->setZ(z);
}

// Dadas as coordenadas, atualiza o titl.
void Camera::setTitl(float x, float y, float z) {
	titl->setX(x);
	titl->setY(y);
	titl->setZ(z);
}