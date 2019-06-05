#include "headers/parser.h"
#include "headers/camera.h"


int nr_groups = 0;
vector<Group*> LG;											// groups a desenhar
Camera camera;												// a camera que esta a ser usada (posicao, para onde esta a olhar..)
int linha = GL_LINE;										// formato da figura.
int face = GL_CCW;
int timebase = 0, frame = 0;
int n_models = 0;

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


// responsável por desenhar um determinado group
void drawGroup(Group* g){
	Translate* trans = g->getTranslation();										// faz 'get' da translação associada a este group
	Rotate* rotat = g->getRotation();											// faz 'get' da rotação associada a este group
	Scale* scale = g->getScale();												// faz 'get' da escala associada a este group
	Colour* colour = g->getColour();											// faz 'get' da cor associada a este group
	
	vector<Group*> childs = g->getChilds();									    // vetor com os respetivos filhos deste group
	int size = childs.size();													// quantos groups filhos temos nesse vetor

	glColor3f(colour->getRR(), colour->getGG(), colour->getBB());				// pinta o objeto com a cor associada
	glPushMatrix();

	trans->draw();																// efetua a translação associada
	rotat->apply();																// efetua a rotação associada
	glScalef(scale->getX(), scale->getY(), scale->getZ());						// efetua o escalonamento associado

	g->getLP().draw();													        // desenha figura do group
		for (int i = 0; i < size; i++) {										// percorrer a lista de filhos
			drawGroup(childs[i]);											    // chama recursivamente a função para desenhar cada filho
		}

	glPopMatrix();

}

void drawGroups() {
	int size = LG.size();										// quantos groups 'principais' se tem no vetor de groups
	for (int i = 0; i < size; i++) {							// percorre esses groups principais todos
		drawGroup(LG[i]);										// desenha cada um deles
	}
}

void displayFPS() {
	int time;
	char title[20];
	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);
	if (time - timebase > 1000) {
		float fps = frame * 1000.0 / (time - timebase);
		timebase = time;
		frame = 0;
		sprintf_s(title, "Engine | %.2f FPS", fps);
		glutSetWindowTitle(title);
	}
}

void renderScene(void) {
	// clear buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// set the camera
	glLoadIdentity();

	Point* camPos = camera.getCamPosition();								// carrega o ponto em que a camera esta
	Point* lookP = camera.getLookPoint();									// carrega o ponto para onde a camera esta a olhar
	Point* titl = camera.getTitl();											// carrega o 'up vector'

	gluLookAt(camPos->getX(), camPos->getY(), camPos->getZ(),
		lookP->getX(), lookP->getY(), lookP->getZ(),
		titl->getX(), titl->getY(), titl->getZ());

	glPolygonMode(GL_FRONT_AND_BACK, linha);
	glFrontFace(face);
	
	if(n_models > 0) drawGroups();										 // desenha todos os groups	
	
	displayFPS();

	// End of frame
	glutSwapBuffers();
}


void processKeys(unsigned char c, int xx, int yy) {
	switch (c) {

	case 'p': linha = GL_POINT; break;

	case 'f': linha = GL_FILL; break;

	case 'l': linha = GL_LINE; break;
	
	case 'w': camera.FocusUp(); break;

	case 'd': camera.FocusRight(); break;

	case 's': camera.FocusDown(); break;

	case 'a': camera.FocusLeft(); break;

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

void initGlut() {
	// OpenGL settings 
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	glEnableClientState(GL_VERTEX_ARRAY);

}



int main(int argc, char **argv) {
	
	// init GLUT and the window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("TrabalhoCG-Fase3-Engine");
	
	if (argc == 2) {
		if (!strcmp(argv[1], "-h")) { help(); return 0;}
		initGlut();
		n_models = readXML(argv[1], &LG);
	}
	else { cout << "Nao esta a passar os argumentos corretos! Se precisar de ajuda, execute o comando 'engine.exe -h'" << endl; return 0; }

	


	// Required callback registry 
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);

	// Callback registration for keyboard processing
	glutKeyboardFunc(processKeys);
	glutSpecialFunc(processSpecialKeys);

	//  OpenGL settings
	//initGlut();
	//glewInit();

	// enter GLUT's main cycle
	glutMainLoop();

	return 1;
}
