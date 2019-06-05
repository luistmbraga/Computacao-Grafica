#include "headers/Struct.h"

//Construtor vazio
Struct::Struct(){
}

//Construtor parametrizado
Struct::Struct(vector<Point*> L, vector<Point*> norm, vector<Point*> text) {
	LP = L;
	normal = norm;
	textura = text;
}

//Devolve a lista de pontos da figura
vector<Point*> Struct::getLP() {
	return LP;
}
	
//Dada uma lista de pontos, associa esses pontos à lista de pontos da figura
void Struct::setLP(vector<Point*> L) {
	LP = L;
}

//Dada uma lista de pontos, associa esses pontos á lista de pontos das normais
void Struct::setNormal(vector<Point*> l) {
	normal = l;
}

//Devolve a lista de pontos das normais
vector<Point*> Struct::getNormal() {
	return normal;
}

//Associa uma lista de pontos à lista de pontos da textura
void Struct::setTextura(vector<Point*> l) {
	textura = l;
}

//Devolve a lista de pontos da textura
vector<Point*> Struct::getTextura(){
	return textura;
}


//Responsavel por gerar os pontos dos (2) triângulos pertencentes ao plano.
void Struct::genPlane(float size)
{
	float h = size/2;
	
	LP.push_back(new Point(-h, 0, h));
	LP.push_back(new Point(h, 0, h));
	LP.push_back(new Point(-h, 0, -h));
	LP.push_back(new Point(-h, 0, -h));
	LP.push_back(new Point(h, 0, h));
	LP.push_back(new Point(h, 0, -h));

	normal.push_back(new Point(0, 1, 0));
	normal.push_back(new Point(0, 1, 0));
	normal.push_back(new Point(0, 1, 0));
	normal.push_back(new Point(0, 1, 0));
	normal.push_back(new Point(0, 1, 0));
	normal.push_back(new Point(0, 1, 0));

	textura.push_back(new Point(0, 1, 0));
	textura.push_back(new Point(1, 1, 0));
	textura.push_back(new Point(0, 0, 0));
	textura.push_back(new Point(0, 0, 0));
	textura.push_back(new Point(1, 1, 0));
	textura.push_back(new Point(1, 0, 0));
}

//Responsavel por gerar os pontos dos triângulos relativos ao cilindro.
void Struct::genCylinder(float radius, float height, int slices) {
	float beta = atan(radius / height);
	float alfa = (float) (2 * (M_PI / slices));
	float tex = 1 / slices;

	for (int i = 0; i < slices; i++) {
		float x0 = sin((i + 1)*alfa)*radius;
		float x1 = sin(i*alfa)*radius;
		float z0 = cos((i + 1)*alfa)*radius;
		float z1 = cos(i*alfa)*radius;

		// base inferior
		normal.push_back(new Point(0, -1, 0));
		normal.push_back(new Point(0, -1, 0));
		normal.push_back(new Point(0, -1, 0));

		LP.push_back(new Point(x0, -height / 2, z0));
		LP.push_back(new Point(x1, -height / 2, z1));
		LP.push_back(new Point(0.0f, -height / 2, 0.0f));

		// base superior
		normal.push_back(new Point(0, 1, 0));
		normal.push_back(new Point(0, 1, 0));
		normal.push_back(new Point(0, 1, 0));

		LP.push_back(new Point(0.0f, height / 2, 0.0f));
		LP.push_back(new Point(x1, height / 2, z1));
		LP.push_back(new Point(x0, height / 2, z0));
		
		// rolo
		normal.push_back(new Point(sin((i + 1)*alfa), 0, cos((i + 1)*alfa)));
		normal.push_back(new Point(sin((i + 1)*alfa), 0, cos((i + 1)*alfa)));
		normal.push_back(new Point(sin(i*alfa), 0, cos(i*alfa)));

		LP.push_back(new Point(x0, -height / 2, z0));
		LP.push_back(new Point(x0, height / 2, z0));
		LP.push_back(new Point(x1, height / 2, z1));
		
		normal.push_back(new Point(sin(i*alfa), 0, cos(i * alfa)));
		normal.push_back(new Point(sin((i + 1)*alfa), 0, cos((i + 1)*alfa)));
		normal.push_back(new Point(sin(i*alfa), 0, cos(i*alfa)));
		
		LP.push_back(new Point(x1, -height / 2, z1));
		LP.push_back(new Point(x0, -height / 2, z0));
		LP.push_back(new Point(x1, height / 2, z1));
	}
}

float xxx = 0, yyy = 0, zzz = 0;

// Responsavel por gerar os pontos dos triangulos relativos a esfara.
void Struct::genSphere(float radius, int slices, int stacks) {

	float beta = (float) (M_PI) / stacks; //angulo beta
	float alfa = (float) (2 * M_PI) / slices; //angulo alfa

	float texDivX = 1 / slices;
	float texDivY = 1 / stacks;

	float texX1 = 0;
	float texX2 = texDivX;

	float texY1, texY2;

	//para cada slice percorrem-se as respectivas stacks
	for (int i = 0; i < slices; i++, texX1 += texDivX, texX2 += texDivX) {

		//calculam-se os pontos por slice
		for (int j = 0; j < stacks; j++) {


			//só foram consideradas 
			// expressões que se repitam mais do que uma 
			// vez por "if"
			//porque, salvo certas excepções, 
			// o mesmo "if" é executado uma vez por ciclo
			float x1 = radius * cos((j + 1)*beta);
			float x2 = radius * cos(i*alfa)*sin((j + 1)*beta);
			float x3 = radius * sin(i*alfa)*sin((j + 1)*beta);
			float x4 = radius * cos((j + 1)*beta);
			float x5 = radius * cos((i + 1)*alfa)*sin((j + 2)*beta);
			float x6 = radius * cos((j + 2)*beta);
			float x7 = radius * sin((i + 1)*alfa)*sin((j + 2)*beta);

			//começa-se a construir a esfera por cima
			//j = 0 corresponde ao topo (polo norte) da esfera 
			//porque como podemos ver (0,radius,0)
			//o que indica que estamos no topo
			if (j == 0) {
				texY1 = 1;							// como estamos no topo, o valor é máximo
				texY2 = 1 - texDivY;			     // logo abaixo do topo, será este o valor 

				LP.push_back(new Point(0+xxx, radius+yyy, 0+zzz));
				normal.push_back(new Point(0, 1, 0));
				textura.push_back(new Point(texX1 + texDivX/2, texY1, 0));

				LP.push_back(new Point(radius*cos((i + 1)*alfa)*sin((j + 1)*beta)+xxx, x1+yyy, radius*sin((i + 1)*alfa)*sin((j + 1)*beta) +zzz));
				normal.push_back( (new Point( radius*cos((i + 1)*alfa)*sin((j + 1)*beta)  ,  x1   , radius*sin((i + 1)*alfa)*sin((j + 1)*beta)  ))->calcula_Normal());
				textura.push_back(new Point(texX2, texY2, 0));


				LP.push_back(new Point(x2+xxx, x1+yyy, x3+zzz));
				normal.push_back((new Point(x2, x1, x3))->calcula_Normal());
				textura.push_back(new Point(texX1, texY2, 0));
			}

			//estamos no polo sul da esfera
			if (j == stacks - 1) {

					//definic~ao dos pontos de refer^encia nesta
					//regiao
					texY1 = texDivY;
					texY2 = 0;

				LP.push_back(new Point(0+xxx, -radius+yyy, 0+zzz));
				normal.push_back(new Point(0, -1, 0));
				LP.push_back(new Point(x2 + radius*cos(i*alfa)*sin(beta) + xxx, -(radius*cos(beta)) + yyy, x3 + radius*sin(i*alfa)*sin(beta) + zzz));
				Point* p = new Point(x2 + radius * cos(i*alfa)*sin(beta), -(radius*cos(beta)), x3 + radius * sin(i*alfa)*sin(beta));
				normal.push_back( p->calcula_Normal() );
				LP.push_back(new Point(radius*cos((i + 1)*alfa)*sin((j + 1)*beta) + radius*cos((i + 1)*alfa)*sin(beta) + xxx,
										-(radius * cos(beta)) + yyy, 
										radius*sin((i + 1)*alfa)*sin((j + 1)*beta) + radius * sin((i + 1)*alfa)*sin(beta) + zzz));
				normal.push_back((new Point(radius*cos((i + 1)*alfa)*sin((j + 1)*beta) + radius * cos((i + 1)*alfa)*sin(beta),
					-(radius * cos(beta)),
					radius*sin((i + 1)*alfa)*sin((j + 1)*beta) + radius * sin((i + 1)*alfa)*sin(beta)))->calcula_Normal());

					//raciocnio analogo a regi~ao topo
					textura.push_back(new Point(texX1 + texDivX / 2, texY2, 0));
					textura.push_back(new Point(texX1, texY1, 0));
					textura.push_back(new Point(texX2, texY1, 0));

			}//para os níveis intermedios entre os polos
			else {

				LP.push_back(new Point(radius*cos((i + 1)*alfa)*sin((j + 1)*beta) + xxx, x4+yyy, radius*sin((i + 1)*alfa)*sin((j + 1)*beta)+zzz));
				normal.push_back((new Point(radius*cos((i + 1)*alfa)*sin((j + 1)*beta), x4, radius*sin((i + 1)*alfa)*sin((j + 1)*beta)))->calcula_Normal());
				LP.push_back(new Point(x5+xxx, x6+yyy, x7+zzz));
				normal.push_back((new Point(x5, x6, x7))->calcula_Normal());
				LP.push_back(new Point(x2+xxx, x4+yyy, x3+zzz));
				normal.push_back((new Point(x2, x4, x3))->calcula_Normal());

				LP.push_back(new Point(x2+xxx, x4+yyy, x3+zzz));
				normal.push_back((new Point(x2, x4, x3))->calcula_Normal());
				LP.push_back(new Point(x5+xxx, x6+yyy,x7+zzz));
				normal.push_back((new Point(x5, x6, x7))->calcula_Normal());
				LP.push_back(new Point(radius*cos(i*alfa)*sin((j + 2)*beta)+xxx, x6+yyy, radius*sin(i*alfa)*sin((j + 2)*beta)+zzz));
				normal.push_back((new Point(radius*cos(i*alfa)*sin((j + 2)*beta) , x6 , radius*sin(i*alfa)*sin((j + 2)*beta) ))->calcula_Normal());

					//Triangulo lateral
					textura.push_back(new Point(texX2, texY1, 0));
					textura.push_back(new Point(texX2, texY2, 0));
					textura.push_back(new Point(texX1, texY1, 0));

					//Triangulo complementar ao anterior
					textura.push_back(new Point(texX1, texY1, 0));
					textura.push_back(new Point(texX2, texY2, 0));
					textura.push_back(new Point(texX1, texY2, 0));
			}
		}
	}
}

void Struct::genCone(float radius, float height, int slices, int stacks) {
	float alfa = (float) (2 * M_PI) / slices; //angulo alfa
	float alturaStack = height / stacks; // altura de uma stack 
	float tangenteBeta = height / radius;

	float alturaBaixo = 0; //altura parte de baixo
	float alturaCima; //altura parte de cima
	float raio2; //raio do circulo superior

	//um slice pode ser resumido em quatro pontos 
	//ligados entre a camada superior e inferior
	//   __
	//  /\/
	//   
	float x1, x2, x3, x4, z1, z2, z3, z4;

		//variaveis que representam um "passo" na textura
		float texDivY = 1.0 / stacks, texDivX = 1.0 / slices;

		//pontos de referencia da textura
		float texYcima = 0 + texDivY, texYbaixo = 0;
		float texXesq, texXdir;

	float alfaI;
	float alfaIMais1;

	//este ciclo exterior trata das camadas
	//o que faz com que o cone seja
	//desenhado por "andares" 
	//que convergem no topo do cilindro
	for (int j = 1; j <= stacks; j++, texXesq += texDivX, texXdir += texDivX) {
		alturaCima = alturaStack * j;
		raio2 = (height - alturaCima) / tangenteBeta;

		//este ciclo foca-se num slice particular
		//portanto, quando 
		for (int i = 1; i <= slices + 1; i++) {

			alfaI = alfa * i;
			alfaIMais1 = alfa * (i + 1);

			x1 = radius * sin(alfaI);
			z1 = radius * cos(alfaI);

			x2 = radius * sin(alfaIMais1);
			z2 = radius * cos(alfaIMais1);

			x3 = raio2 * sin(alfaI);
			z3 = raio2 * cos(alfaI);

			x4 = raio2 * sin(alfaIMais1);
			z4 = raio2 * cos(alfaIMais1);

			if (j == 1) {

				//triangulo da base
				LP.push_back(new Point(0, 0, 0));
				normal.push_back(new Point(0, -1, 0));
				LP.push_back(new Point(x2, 0, z2));
				normal.push_back(new Point(0, -1, 0));
				LP.push_back(new Point(x1, 0, z1));
				normal.push_back(new Point(0, -1, 0));

				//triangulos do lado
				LP.push_back(new Point(x1, 0, z1));
				normal.push_back(new Point(sin(alfaI), 0, cos(alfaI)));
				LP.push_back(new Point(x2, 0, z2));
				normal.push_back(new Point(sin(alfaIMais1), 0, cos(alfaIMais1)));
				LP.push_back(new Point(x3, alturaCima, z3));
				normal.push_back((new Point( x3, alturaCima , z3))->calcula_Normal());

				LP.push_back(new Point(x2, 0, z2));
				normal.push_back(new Point(sin(alfaIMais1), 0, cos(alfaIMais1)));
				LP.push_back(new Point(x4, alturaCima, z4));
				normal.push_back((new Point(x4, alturaCima, z4))->calcula_Normal());
				LP.push_back(new Point(x3, alturaCima, z3));
				normal.push_back((new Point(x4, alturaCima, z4))->calcula_Normal());


					//vertice inferior do triangulo (media das
					//distancias)
					textura.push_back(new Point(texXesq + texDivX / 2, texYbaixo, 0));
					textura.push_back(new Point(texXdir, texYcima, 0));
					textura.push_back(new Point(texXesq, texYcima, 0));

					// lados
					textura.push_back(new Point(texXesq, texYbaixo, 0));
					textura.push_back(new Point(texXdir, texYbaixo, 0));
					textura.push_back(new Point(texXesq, texYcima, 0));

					textura.push_back(new Point(texXdir, texYbaixo, 0));
					textura.push_back(new Point(texXdir, texYcima, 0));
					textura.push_back(new Point(texXesq, texYcima, 0));

			}// estamos no topo do cone
			else if (j == stacks) {

				//um unico triangulo no topo (por slice)
				LP.push_back(new Point(x1, alturaBaixo, z1));
				normal.push_back((new Point(x1, alturaBaixo, z1))->calcula_Normal());
				LP.push_back(new Point(x2, alturaBaixo, z2));
				normal.push_back((new Point(x2, alturaBaixo, z2))->calcula_Normal());
				LP.push_back(new Point(0, height, 0));
				normal.push_back(new Point(0, 1, 0));

					textura.push_back(new Point(texXesq, texYbaixo, 0));
					textura.push_back(new Point(texXdir, texYbaixo, 0));
					textura.push_back(new Point(texXesq + texDivX / 2, texYcima, 0));
			}
			else {
				//se nao estivermos no topo ou na base estamos a desenhar os lados do cone

				//triangulos relativos aos lados do cone		
				LP.push_back(new Point(x1, alturaBaixo, z1));
				normal.push_back((new Point(x1, alturaBaixo, z1))->calcula_Normal());
				LP.push_back(new Point(x2, alturaBaixo, z2));
			    normal.push_back((new Point(x2, alturaBaixo, z2))->calcula_Normal());
				LP.push_back(new Point(x3, alturaCima, z3));
				normal.push_back((new Point(x3, alturaCima, z3))->calcula_Normal());
		
				LP.push_back(new Point(x2, alturaBaixo, z2));
				normal.push_back((new Point(x2, alturaBaixo, z2))->calcula_Normal());
				LP.push_back(new Point(x4, alturaCima, z4));
				normal.push_back((new Point(x4, alturaCima, z4))->calcula_Normal());
				LP.push_back(new Point(x3, alturaCima, z3));
				normal.push_back((new Point(x3, alturaCima, z3))->calcula_Normal());

					textura.push_back(new Point(texXesq, texYbaixo, 0));
					textura.push_back(new Point(texXdir, texYbaixo, 0));
					textura.push_back(new Point(texXesq, texYcima, 0));

					textura.push_back(new Point(texXdir, texYbaixo, 0));
					textura.push_back(new Point(texXdir, texYcima, 0));
					textura.push_back(new Point(texXesq, texYcima, 0));
			}
		}

		//subimos de patamar
		alturaBaixo = alturaCima;
		//consequentemente tambem muda o circulo da base
		radius = raio2;
	}
}


void Struct:: genBox(float cX, float cY, float cZ, int div){
    
    
    
    float x = cX/2;
    float y = cY/2;
    float z = cZ/2;
    
    float pX = (float)cX/div;
    float pY = (float)cY/div;
    float pZ = (float)cZ/div;
    
	// Calculo dos pontos que identificam as faces da textura
	float texY1 = cZ / ((cZ * 2) + cY);
	float texY2 = (cZ + cY) / ((cZ * 2) + cY);
	
	float texX1 = (cZ) / ((cZ * 2) + (cX * 2));
	float texX2 = (cZ + x) / ((cZ * 2) + (cX * 2));
	float texX3 = ((cZ * 2) + cX) / ((cZ * 2) + (cX * 2));
    
	// Calculo das divis~oes da textura
	float texDivX = (cX / ((cZ * 2) + (cX * 2))) / float(div);
	float texDivY = (cY / ((cZ * 2) + cY)) / float(div);
	float texDivZ = (cZ / ((cZ * 2) + (cX * 2))) / float(div);


    for(int i=0;i<div;i++){
        for(int j=0;j<div;j++){
            //Face da frente
            LP.push_back(new Point(-x + (j*pX),-y + (i*pY),z));
			normal.push_back(new Point(0, 0, 1));
            LP.push_back(new Point((-x+pX) + (j*pX),-y + (i*pY),z));
			normal.push_back(new Point(0, 0, 1));
            LP.push_back(new Point(-x + (j*pX),(-y+pY) + (i*pY),z));
			normal.push_back(new Point(0, 0, 1));
            
            
            LP.push_back(new Point(-x + (j*pX),(-y+pY) + (i*pY),z));
			normal.push_back(new Point(0, 0, 1));
            LP.push_back(new Point((-x+pX) + (j*pX),-y + (i*pY),z));
			normal.push_back(new Point(0, 0, 1));
            LP.push_back(new Point((-x+pX) + (j*pX),(-y+pY) + (i*pY),z));
			normal.push_back(new Point(0, 0, 1));
            
				// Comecar na posicao de texX1 e ir aumentando um
				//"passo" de cada vez.Por outro lado comeca - se
				//	no texY2 e diminui - se um "passo"
		
				textura.push_back(new Point(texX1 + (j*texDivX), texY2 - (i*texDivY), 0));
				textura.push_back(new Point(texX1 + (j*texDivX), (texY2 - texDivY) - (i*texDivY), 0));
				textura.push_back(new Point((texX1 + texDivX) + (j*texDivX),(texY2 - texDivY) - (i*texDivY), 0));

				// Triangulo complementar ao anterior
				textura.push_back(new Point(texX1 + (j*texDivX), texY2 - (i*texDivY), 0));
				textura.push_back(new Point((texX1 + texDivX) + (j*texDivX), (texY2 - texDivY) - (i*texDivY), 0));
				textura.push_back(new Point((texX1 + texDivX) + (j*texDivX), texY2 - (i*texDivY), 0));

            //Face traseira
            
            LP.push_back(new Point(-x + (j*pX),-y + (i*pY),-z));
			normal.push_back(new Point(0, 0, -1));
            LP.push_back(new Point(-x + (j*pX),(-y+pY) + (i*pY),-z));
			normal.push_back(new Point(0, 0, -1));
            LP.push_back(new Point((-x+pX) + (j*pX),-y + (i*pY),-z));
			normal.push_back(new Point(0, 0, -1));
            
            
            LP.push_back(new Point(-x + (j*pX),(-y+pY) + (i*pY),-z));
			normal.push_back(new Point(0, 0, -1));
            LP.push_back(new Point((-x+pX) + (j*pX),(-y+pY) + (i*pY),-z));
			normal.push_back(new Point(0, 0, -1));
            LP.push_back(new Point((-x+pX) + (j*pX),-y + (i*pY),-z));
			normal.push_back(new Point(0, 0, -1));

				// Comecar na posic~ao final, 1, e ir diminuindo um
				//"passo" de cada vez.Por outro lado comeca - se
				//	no texY2 e diminui - se um "passo"
				textura.push_back(new Point((1 - texDivX) - (j*texDivX), (texY2 - texDivY) - (i*texDivY), 0));
				textura.push_back(new Point(1 - (j*texDivX), (texY2 - texDivY) - (i*texDivY), 0));
				textura.push_back(new Point(1 - (j*texDivX), texY2 - (i*texDivY), 0));
            
				// Tri^angulo complementar ao anterior
				textura.push_back(new Point((1 - texDivX) - (j*texDivX), (texY2 - texDivY) - (i*texDivY), 0));
				textura.push_back(new Point(1 - (j*texDivX), texY2 - (i*texDivY), 0));
				textura.push_back(new Point((1 - texDivX) - (j*texDivX), texY2 - (i*texDivY), 0));

            //Face direita
            LP.push_back(new Point(x,-y + (i*pY),-z + (j*pZ)));
			normal.push_back(new Point(1, 0, 0));
            LP.push_back(new Point(x,(-y+pY) + (i*pY),-z +(j*pZ)));
			normal.push_back(new Point(1, 0, 0));
            LP.push_back(new Point(x,-y + (i*pY),(-z+pZ) + (j*pZ)));
			normal.push_back(new Point(1, 0, 0));
            
            
            LP.push_back(new Point(x,(-y+pY) + (i*pY),-z + (j*pZ)));
			normal.push_back(new Point(1, 0, 0));
            LP.push_back(new Point(x,(-y+pY) + (i*pY),(-z+pZ) + (j*pZ)));
			normal.push_back(new Point(1, 0, 0));
            LP.push_back(new Point(x,-y + (i*pY),(-z+pZ) + (j*pZ)));
			normal.push_back(new Point(1, 0, 0));

				// Comecar na posic~ao de texX2 e ir aumentando um
				//"passo" de cada vez, em Z.Por outro lado
				//	comeca - se no texY2 e diminui - se um "passo".
				textura.push_back(new Point(texX2 + (j*texDivZ), (texY2 - texDivY) - (i*texDivY), 0));
				textura.push_back(new Point((texX2 + texDivZ) - (j*texDivX), (texY2 - texDivY) - (i*texDivY), 0));
				textura.push_back(new Point(texX2 + (j*texDivZ), texY2 - (i*texDivY), 0));
            
				// Tri^angulo complementar ao anterior
				textura.push_back(new Point((texX2 + texDivZ) + (j*texDivZ), (texY2 - texDivY) - (i*texDivY), 0));
				textura.push_back(new Point((texX2 + texDivZ) + (j*texDivX), texY2 - (i*texDivY), 0));
				textura.push_back(new Point(texX2 + (j*texDivZ), texY2 - (i*texDivY), 0));
            
            //Face esquerda
            LP.push_back(new Point(-x,-y + (i*pY),-z + (j*pZ)));
			normal.push_back(new Point(-1, 0, 0));
            LP.push_back(new Point(-x,-y + (i*pY),(-z+pZ) + (j*pZ)));
			normal.push_back(new Point(-1, 0, 0));
            LP.push_back(new Point(-x,(-y+pY) + (i*pY),-z +(j*pZ)));
			normal.push_back(new Point(-1, 0, 0));
            
            
            LP.push_back(new Point(-x,(-y+pY) + (i*pY),-z + (j*pZ)));
			normal.push_back(new Point(-1, 0, 0));
            LP.push_back(new Point(-x,-y + (i*pY),(-z+pZ) + (j*pZ)));
			normal.push_back(new Point(-1, 0, 0));
            LP.push_back(new Point(-x,(-y+pY) + (i*pY),(-z+pZ) + (j*pZ)));
			normal.push_back(new Point(-1, 0, 0));
            
				// Comecar na posic~ao inicial, 0, (tendo em conta
				// que esta face utiliza a variavel Z) e ir
				//aumentando um "passo" de cada vez.Por outro
				//	lado comeca - se no texY2 e diminui - se um
				//	"passo".
			
				textura.push_back(new Point((j*texDivZ), texY2 - (i*texDivY), 0));
				textura.push_back(new Point(j*texDivZ, (texY2 - texDivY) - (i*texDivY), 0));
				textura.push_back(new Point(texDivZ + (j*texDivZ), (texY2 - texDivY) - (i*texDivY), 0));

				// Tri^angulo complementar ao anterior
				textura.push_back(new Point((j*texDivZ), texY2 - (i*texDivY), 0));
				textura.push_back(new Point(texDivZ + (j*texDivZ), (texY2 - texDivY) - (i*texDivY), 0));
				textura.push_back(new Point(texDivZ + (j*texDivZ), texY2 - (i*texDivY), 0));

            //Topo
            LP.push_back(new Point(-x + (j*pX),y,-z + (i*pZ)));
			normal.push_back(new Point(1, 0, 0));
            LP.push_back(new Point(-x + (j*pX),y,(-z+pZ) + (i*pZ)));
			normal.push_back(new Point(1, 0, 0));
            LP.push_back(new Point((-x+pX) + (j*pX),y,-z + (i*pZ)));
			normal.push_back(new Point(1, 0, 0));

            
            LP.push_back(new Point(-x + (j*pX),y,(-z+pZ) + (i*pZ)));
			normal.push_back(new Point(1, 0, 0));
            LP.push_back(new Point((-x+pX) + (j*pX),y,(-z+pZ) + (i*pZ)));
			normal.push_back(new Point(1, 0, 0));
            LP.push_back(new Point((-x+pX) + (j*pX),y,-z + (i*pZ)));
			normal.push_back(new Point(1, 0, 0));

				// Comecar na posic~ao de texX1 e ir aumentando um
				//"passo" de cada vez.Por outro lado comeca - se
				//	na posicao final e diminui - se um "passo", em
				//	Z.
				textura.push_back(new Point(texX1 + (j*texDivX), 1 - (i*texDivZ), 0));
				textura.push_back(new Point(texX1 + (j*texDivX), (1 - texDivZ) - (i*texDivZ), 0));
				textura.push_back(new Point((texX1 + texDivX) + (j*texDivX), (1 - texDivZ) - (i*texDivZ), 0));

				// Tri^angulo complementar ao anterior
				textura.push_back(new Point(texX1 + (j*texDivX), 1 - (i*texDivZ), 0));
				textura.push_back(new Point((texX1 + texDivX) + (j*texDivX), (1 - texDivZ) - (i*texDivZ), 0));
				textura.push_back(new Point((texX1 + texDivX) + (j*texDivX), 1 - (i*texDivZ), 0));

            //Base
            LP.push_back(new Point(-x + (j*pX),-y,-z + (i*pZ)));
			normal.push_back(new Point(-1, 0, 0));
            LP.push_back(new Point((-x+pX) + (j*pX),-y,-z + (i*pZ)));
			normal.push_back(new Point(-1, 0, 0));
            LP.push_back(new Point(-x + (j*pX),-y,(-z+pZ) + (i*pZ)));
			normal.push_back(new Point(-1, 0, 0));
            
            
            LP.push_back(new Point(-x + (j*pX),-y,(-z+pZ) + (i*pZ)));
			normal.push_back(new Point(-1, 0, 0));
            LP.push_back(new Point((-x+pX) + (j*pX),-y,-z + (i*pZ)));
			normal.push_back(new Point(-1, 0, 0));
            LP.push_back(new Point((-x+pX) + (j*pX),-y,(-z+pZ) + (i*pZ)));
			normal.push_back(new Point(-1, 0, 0));

				// Comecar na posic~ao de texX1 e ir aumentando um
				//"passo" de cada vez.Por outro lado comeca - se
				//	no texY1 e diminui - se um "passo", em Z.
				textura.push_back(new Point(texX1 + (j*texDivX), (texY1 - texDivZ) - (i*texDivZ), 0));
				textura.push_back(new Point(texX1 + (j*texDivX), texY1 - (i*texDivZ), 0));
				textura.push_back(new Point((texX1 + texDivX) + (j*texDivX), texY1 - (i*texDivZ), 0));
            
				// Tri^angulo complementar ao anterior
				textura.push_back(new Point(texX1 + (j*texDivX), (texY1 - texDivZ) - (i*texDivZ), 0));
				textura.push_back(new Point((texX1 + texDivX) + (j*texDivX), texY1 - (i*texDivZ), 0));
				textura.push_back(new Point((texX1 + texDivX) + (j*texDivX), (texY1 - texDivZ) - (i*texDivZ), 0));
        }
    }
    
}


void Struct::genTorus(float tamanhoCoroa, float raio, int faces, int aneis) {

	float lado = (float) (2 * M_PI) / faces;
	float anel =  (float) (2 * M_PI) / aneis;

		//variaveis que representam um "passo" na textura
		float texX = 1.0 / aneis;
		float texY = 1.0 / faces;
	

	for (int i = 0; i < aneis; i++) {
		
		float cosI = (float) cos(i * anel);
		float sinI = (float) sin(i * anel);
		float cosIanel = (float) cos(i * anel + anel);
		float sinIanel = (float) sin(i * anel + anel);

		for (int j = 0; j < faces + 1; j++) {

			float jj = j * lado;
			float jjUm = (j + 1)*lado;

			float tcos = tamanhoCoroa * cos(jj) + raio;
			float tsin = tamanhoCoroa * sin(jj);

			float tcosUm = tamanhoCoroa * (cos(jjUm)) + raio;
			float tsinUm = tamanhoCoroa * sin(jjUm);

			LP.push_back(new Point(cosI*tcos, sinI*tcos, tsin));
			normal.push_back((new Point(cosI*tcos, sinI*tcos, tsin))->calcula_Normal());
			LP.push_back(new Point(cosIanel*tcos, sinIanel*tcos, tsin));
			normal.push_back((new Point(cosIanel*tcos, sinIanel*tcos, tsin))->calcula_Normal());
			LP.push_back(new Point(cosI*tcosUm, sinI*tcosUm, tsinUm));
			normal.push_back((new Point(cosI*tcosUm, sinI*tcosUm, tsinUm))->calcula_Normal());
			
			LP.push_back(new Point(cosI*tcosUm, sinI*tcosUm, tsinUm));
			normal.push_back((new Point(cosI*tcosUm, sinI*tcosUm, tsinUm))->calcula_Normal());
			LP.push_back(new Point(cosIanel*tcos, sinIanel*tcos, tsin));
			normal.push_back((new Point(cosIanel*tcos, sinIanel*tcos, tsin))->calcula_Normal());
			LP.push_back(new Point(cosIanel*tcosUm, sinIanel*tcosUm, tsinUm));
			normal.push_back((new Point(cosIanel*tcosUm, sinIanel*tcosUm, tsinUm))->calcula_Normal());

				textura.push_back(new Point(texX*i, texY*j, 0));
				textura.push_back(new Point(texX*(i + 1), texY*j, 0));
				textura.push_back(new Point(texX*i, texY*(j + 1), 0));

				//triangulo complementar ao anterior
				textura.push_back(new Point(texX*i, texY*(j + 1), 0));
				textura.push_back(new Point(texX*(i + 1), texY*j, 0));
				textura.push_back(new Point(texX*(i + 1), texY*(j + 1), 0));

		}
	}
}

void Struct::genCintura(float tamanhoCoroa, float raio, int faces, int aneis) {

	float lado = (float)(2 * M_PI) / faces;
	float anel = (float)(2 * M_PI) / aneis;


	for (int i = 0; i < aneis; i++) {


		float cosI = (float)cos(i * anel);
		float sinI = (float)sin(i * anel);
		float cosIanel = (float)cos(i * anel + anel);
		float sinIanel = (float)sin(i * anel + anel);

		for (int j = 0; j < faces + 1; j++) {

			float jj = j * lado;
			float jjUm = (j + 1)*lado;

			float tcos = tamanhoCoroa * cos(jj) + raio;
			float tsin = tamanhoCoroa * sin(jj);

			float tcosUm = tamanhoCoroa * (cos(jjUm)) + raio;
			float tsinUm = tamanhoCoroa * sin(jjUm);

			//(float radius, int slices, int stacks)
			float radius = (float) 0.01; int slices = 4; int stacks = 2;

			//LP.push_back(new Point(cosI*tcos, sinI*tcos, tsin));
			xxx = cosI*tcos; yyy = sinI*tcos; zzz = tsin;
			genSphere(radius, slices, stacks);

			//LP.push_back(new Point(cosIanel*tcos, sinIanel*tcos, tsin));
			xxx = cosIanel * tcos; yyy = sinIanel * tcos;
			genSphere(radius, slices, stacks);
			//LP.push_back(new Point(cosI*tcosUm, sinI*tcosUm, tsinUm));
			xxx = cosI * tcosUm; yyy = sinI * tcosUm; zzz = tsinUm;
			genSphere(radius, slices,stacks);
			//LP.push_back(new Point(cosI*tcosUm, sinI*tcosUm, tsinUm));
			xxx = cosI * tcosUm; yyy = sinI * tcosUm;
			genSphere(radius, slices, stacks);
			//LP.push_back(new Point(cosIanel*tcos, sinIanel*tcos, tsin));
			xxx = cosIanel * tcos; yyy = sinIanel * tcos; zzz = tsin;
			genSphere(radius, slices, stacks);
			//LP.push_back(new Point(cosIanel*tcosUm, sinIanel*tcosUm, tsinUm));
			xxx = cosIanel * tcosUm; yyy = sinIanel * tcosUm; zzz = tsinUm;
			genSphere(radius, slices, stacks);
		}
	}
}


