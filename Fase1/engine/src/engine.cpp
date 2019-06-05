
#include "headers/parser.h"
#include "headers/camera.h"

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif


vector<Point*> LP;     // lista de pontos a desenhar.
Camera camera;         // a camera que esta a ser usada (posicao, para onde esta a olhar..)
int linha = GL_LINE;   // formato da figura.
float rr = 1.0f, gg = 1.0f, bb = 1.0f;  // cores da figura.
int face = GL_CCW;

void help() {
	cout << "*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>HELP<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*" << endl;
	cout << "|                                                                           |" << endl;
	cout << "|   Modo de utilizacao:                                                     |" << endl;
	cout << "|                       engine.exe (ficheiro xml)                           |" << endl;
	cout << "|   Nota: Os ficheiros 3d tem de estar gerados (pelo generator).            |" << endl;
	cout << "|                                                                           |" << endl;
	cout << "|   Exemplo de utilizacao:                                                  |" << endl;
	cout << "|                          engine.exe plane.xml                             |" << endl;
	cout << "|                                                                           |" << endl;
	cout << "|         Teclas:      ->       Respetivas acoes:                           |" << endl;
	cout << "|     (seta cima)      ->  Roda a posicao da camera para cima               |" << endl;
	cout << "|     (seta baixo)     ->  Roda a posicao da camera para baixo              |" << endl;
	cout << "|     (seta esquerda)  ->  Roda a posicao da camera para a esquerda         |" << endl;
	cout << "|     (seta direita)   ->  Roda a posicao da camera para a direita          |" << endl;
	cout << "|             w        ->  Muda a cor da figura para branco                 |" << endl;
	cout << "|             r        ->  Muda a cor da figura para vermelho               |" << endl;
	cout << "|             b        ->  Muda a cor da figura para azul                   |" << endl;
	cout << "|             g        ->  Muda a cor da figura para verde                  |" << endl;
	cout << "|             p        ->  Muda o formato da figura para ponto              |" << endl;
	cout << "|             l        ->  Muda o formato da figura para linha              |" << endl;
	cout << "|             f        ->  Preenche a figura                                |" << endl;
	cout << "|             1        ->  Mostra o exterior                                |" << endl;
	cout << "|             2        ->  Mostra o interior                                |" << endl;
	cout << "|             +        ->  Aproxima a camara do ponto em foco               |" << endl;
	cout << "|             -        ->  Afasta a camara do ponto em foco                 |" << endl;
	cout << "|                                                                           |" << endl;
	cout << "*>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>HELP<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<*" << endl;

}

void changeSize(int w, int h) {

	// Prevent a divide by zero, when window is too short
	// (you cant make a window with zero width).
	if (h == 0)
		h = 1;

	// compute window's aspect ratio 
	float ratio = w * 1.0 / h;

	// Set the projection matrix as current
	glMatrixMode(GL_PROJECTION);
	// Load Identity Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set perspective
	gluPerspective(45.0f, ratio, 1.0f, 1000.0f);

	// return to the model view matrix mode
	glMatrixMode(GL_MODELVIEW);
}

void drawFigure() {
	int size = LP.size();
	int i = 0;
	while (i < size) {
		glBegin(GL_TRIANGLES);
		glVertex3f(LP[i]->getX(), LP[i]->getY(), LP[i]->getZ());
		glVertex3f(LP[i+1]->getX(), LP[i+1]->getY(), LP[i+1]->getZ());
		glVertex3f(LP[i+2]->getX(), LP[i+2]->getY(), LP[i+2]->getZ());
		glEnd();
		i += 3;
	}
}


void renderScene(void) {
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();

	Point* camPos = camera.getCamPosition(); // carrega o ponto em que a camera esta
	Point* lookP = camera.getLookPoint();    // carrega o ponto para onde a camera esta a olhar
	Point* titl = camera.getTitl();		     // carrega o 'up vector'

	gluLookAt(camPos->getX(), camPos->getY(), camPos->getZ(),
		lookP->getX(), lookP->getY(), lookP->getZ(),
		titl->getX(), titl->getY(), titl->getZ());

	glPolygonMode(GL_FRONT_AND_BACK, linha);
	glFrontFace(face);
	glColor3f(rr, gg, bb);
	
	drawFigure(); // desenha a figura pretendida

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {
	switch (c) {
	case 'w': rr = 1.0f; gg = 1.0f; bb = 1.0f; break;

	case 'g': rr = 0.0f; gg = 1.0f; bb = 0.0f; break;
	
	case 'b': rr = 0.0f; gg = 0.0f; bb = 1.0f; break;

	case 'r': rr = 1.0f; gg = 0.0f; bb = 0.0f; break;

	case 'p': linha = GL_POINT; break;

	case 'f': linha = GL_FILL; break;

	case 'l': linha = GL_LINE; break;

	case '1': face = GL_CCW; break;

	case '2': face = GL_CW; break;

	case '-': camera.menosZoom(); break;

	case '+': camera.maisZoom(); break;
	}


}


void processSpecialKeys(int key, int xx, int yy) {
	switch (key) {
	case GLUT_KEY_UP: camera.camUp(); break;

	case GLUT_KEY_DOWN: camera.camDown(); break;

	case GLUT_KEY_LEFT: camera.camLeft(); break;

	case GLUT_KEY_RIGHT: camera.camRight(); break;
	}

}

int main(int argc, char **argv) {
	

	if (argc == 2) {
		if (!strcmp(argv[1], "-h")) { help(); return 0;}
		readXML(argv[1], &LP);
	}
	else { cout << "Nao esta a passar os argumentos corretos! Se precisar de ajuda, execute o comando 'engine.exe -h'" << endl; return 0; }

	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("TrabalhoCG-Fase1-Engine");

	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

	//  OpenGL settings
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}
