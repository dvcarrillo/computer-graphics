#ifdef _WIN32
#include <windows.h>
#endif
#include <cstdio>
#include <iostream>
#include <GL/gl.h>
#include <GL/glut.h>
#include "escena.h"

//**************************************************************************
// Imprime informacion sobre la practica en pantalla
//***************************************************************************

void ImprimeInformacion() {
	std::cout << "***********************************************************************\n";
	std::cout << "* DAVID VARGAS CARRILLO (github.com/dvcarrillo)\n";
	std::cout << "* PRACTICAS DE INFORMATICA GRAFICA, curso 2017 - 2018\n";
	std::cout << "* UNIVERSIDAD DE GRANADA\n";
	std::cout << "* Mostrando practicas 1 - 4\n*\n";
	std::cout << "* INSTRUCCIONES:\n";
	std::cout << "* 1. Seleccion de figuras:\n";
	std::cout << "* \t1: Visualizar tetraedro\n";
	std::cout << "* \t2: Visualizar cubo\n";
	std::cout << "* \t3: Visualizar objeto leido de un PLY: beethoven\n";
	std::cout << "* \t4: Visualizar objeto de revolucion: peon\n";
	std::cout << "* \t5: Visualizar objeto animado: pinguino\n";
	std::cout << "* \t6: Visualizar objeto iluminado\n";
	std::cout << "* \t7: Visualizar tablero con textura\n";
	std::cout << "* 2. Modos de visualizacion:\n";
	std::cout << "* \tf: Visualizar en modo solido\n";
	std::cout << "* \tl: Visualizar en modo alambre\n";
	std::cout << "* \tp: Visualizar en modo puntos\n";
	std::cout << "* \tp: Visualizar en modo ajedrez\n";
	std::cout << "* 3. Operaciones con el objeto animado:\n";
	std::cout << "* \tm/M: Activar desplazamiento del objeto y cambiar velocidad\n";
	std::cout << "* \tn/N: Activar rotacion del objeto y cambiar velocidad\n";
	std::cout << "* \tn/N: Activar escalado del objeto y cambiar velocidad\n";
	std::cout << "* 4. Operaciones con el objeto iluminado\n";
	std::cout << "* \ti: Activar/desactivar iluminacion\n";
	std::cout << "* \ts: Alternar entre sobreado plano y sombreado de Goraud\n";
	std::cout << "* \tg: Mover luz 1\n";
	std::cout << "* \th: Mover luz 2\n";
	std::cout << "* \tt: Activar material 1\n";
	std::cout << "* \ty: Activar material 2\n";
	std::cout << "* \tu: Activar material 3\n";
	std::cout << "***********************************************************************\n\n";
}

//**************************************************************************
// Constructor de Escena
//***************************************************************************

Escena::Escena(){
    Front_plane=50;
    Back_plane=2000;
    Observer_distance = 2*Front_plane;
    Observer_angle_x = Observer_angle_y=0;
    ejes.changeAxisSize(5000);
   
   	ImprimeInformacion();
    seleccionado = 0;
    // Construccion de las figuras basicas
    cubo3D.BuildCubo(10);
	tetra3D.BuildTetraedro(20);

    // Construccion de la figura por PLY
   	objPLY.LeerFigura("./read_ply/beethoven.ply");

   	// Construccion del peon
   	peon.BuildPeon(20);
   	peon.BuildFigura(15);
   	peon.BuildTapas();

   	// CONSTRUCCION DE PINGUINO
   	velocidad_mov = 0.05;
   	velocidad_rot = 0.05;
   	velocidad_noot = 0.005;
   	pinguino.EnableDesplazamiento(velocidad_mov);
   	// Declaracion de las partes de las que consta
	Base* cuerpo = new Base();
	Base* pico = new Base();
	Cubo* pie1 = new Cubo();
	Cubo* pie2 = new Cubo();
	Tetraedro* brazo1 = new Tetraedro();
	Tetraedro* brazo2 = new Tetraedro();
	Esfera* ojo1 = new Esfera();
	Esfera* ojo2 = new Esfera();

	// Inicializacion de los objetos
	// Cuerpo
	cuerpo->BuildPerfilBase(1.0);
	cuerpo->BuildFigura(15.0);
	cuerpo->SetColor(0.0f, 0.0f, 0.0f);
	cuerpo->SetTransformaciones(0.0f, 5.0f, 0.0f,
								0.0f, 0.0f, 0.0f,
								5.0f, 5.0f, 5.0f);
	cuerpo->EnableRotacion(velocidad_rot);
	pinguino.AddObjeto(cuerpo);

	// Pico
	pico->BuildPerfilBase(1.0);
	pico->BuildFigura(10.0);
	pico->SetColor(120.0f, 0.0f, 0.0f);
	pico->SetTransformaciones(0.0f, 35.0f, 25.0f,
							90.0f, 0.0f, 0.0f,
							0.8f, 0.8f, 0.8f);
	pico->EnableNoot(velocidad_noot);
	pinguino.child[0]->AddObjeto(pico);

	// Pies
	pie1->BuildCubo(1.0);
	pie1->SetColor(120.0f, 90.0f, 0.0f);
	pie1->SetTransformaciones(2.0f, -0.5f, 1.0f,
							0.0f, 0.0f, 0.0f,
							5.0f, 1.5f, 10.0f);
	pinguino.AddObjeto(pie1);
	pie2->BuildCubo(1.0);
	pie2->SetColor(120.0f, 90.0f, 0.0f);
	pie2->SetTransformaciones(-2.0f, -0.5f, 1.0f,
							0.0f, 0.0f, 0.0f,
							5.0f, 1.5f, 10.0f);
	pinguino.AddObjeto(pie2);

	// Brazos
	brazo1->BuildTetraedro(1.0);
	brazo1->SetColor(60.0f, 60.0f, 60.0f);
	brazo1->SetTransformaciones(4.5f, 4.0f, 0.0f,
							90.0f, 0.0f, 0.0f,
							3.0f, 5.0f, 30.0f);
	pinguino.child[0]->AddObjeto(brazo1);
	brazo2->BuildTetraedro(1.0);
	brazo2->SetColor(60.0f, 60.0f, 60.0f);
	brazo2->SetTransformaciones(-4.5f, 4.0f, 0.0f,
							90.0f, 0.0f, 0.0f,
							3.0f, 5.0f, 30.0f);
	pinguino.child[0]->AddObjeto(brazo2);

	// Ojos
	ojo1->BuildPerfilEsfera(1.0);
	ojo1->BuildFigura(10.0);
	ojo1->SetColor(120.0f, 120.0f, 120.0f);
	ojo1->SetTransformaciones(1.5f, 17.0f, 7.0f,
							0.0f, 0.0f, 0.0f,
							2.0f, 2.0f, 2.0f);
	pinguino.child[0]->AddObjeto(ojo1);
	ojo2->BuildPerfilEsfera(1.0);
	ojo2->BuildFigura(10.0);
	ojo2->SetColor(120.0f, 120.0f, 120.0f);
	ojo2->SetTransformaciones(-1.5f, 17.0f, 7.0f,
							0.0f, 0.0f, 0.0f,
							2.0f, 2.0f, 2.0f);
	pinguino.child[0]->AddObjeto(ojo2);

	es_textura.CargarImagen("./bmp/lena.bmp");
}

void Escena::inicializar(int UI_window_width,int UI_window_height) {

	glClearColor(1,1,1,1);// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable(GL_DEPTH_TEST);	// se habilita el z-bufer

	this->change_projection();
	Width=UI_window_width/10;
	Height=UI_window_height/10;
	glViewport(0,0,UI_window_width,UI_window_height);

}

//**************************************************************************
// Funcion que dibuja objetos en la escena
//***************************************************************************
void Escena::draw_objects() {
	if (seleccionado == 0) tetra3D.Dibujar();
	else if (seleccionado == 1) cubo3D.Dibujar();
	else if (seleccionado == 2) objPLY.Dibujar();
	else if (seleccionado == 3) peon.Dibujar();
	else if (seleccionado == 4) pinguino.DibujadoJerarquico();
	else if (seleccionado == 5) es_iluminada.DibujarEscena();
	else if (seleccionado == 6) es_textura.Dibujar();
}


void Escena::dibujar() {

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
	draw_axis();
	draw_objects();
}

int Escena::teclaPulsada(unsigned char Tecla1,int x,int y) {
    std::cout << "Tecla " << Tecla1<< std::endl;
	if (toupper(Tecla1)=='Q') return 1;
	else if (toupper(Tecla1)=='P') {
		std::cout << "Modo seleccionado: Puntos\n";
		if (seleccionado == 0) tetra3D.SetModoDibujado('p');
		else if (seleccionado == 1) cubo3D.SetModoDibujado('p');
		else if (seleccionado == 2) objPLY.SetModoDibujado('p');
		else if (seleccionado == 3) peon.SetModoDibujado('p');
		else if (seleccionado == 4) pinguino.SetModoDibujado('p');
		else if (seleccionado == 5) es_iluminada.SetModoDibujado('p');
	}
	else if (toupper(Tecla1)=='L') {
		std::cout << "Modo seleccionado: Lineas\n";
		if (seleccionado == 0) tetra3D.SetModoDibujado('l');
		else if (seleccionado == 1) cubo3D.SetModoDibujado('l');
		else if (seleccionado == 2) objPLY.SetModoDibujado('l');
		else if (seleccionado == 3) peon.SetModoDibujado('l');
		else if (seleccionado == 4) pinguino.SetModoDibujado('l');
		else if (seleccionado == 5) es_iluminada.SetModoDibujado('l');
	}
	else if (toupper(Tecla1)=='F') {
		std::cout << "Modo seleccionado: Relleno\n";
		if (seleccionado == 0) tetra3D.SetModoDibujado('f');
		else if (seleccionado == 1) cubo3D.SetModoDibujado('f');
		else if (seleccionado == 2) objPLY.SetModoDibujado('f');
		else if (seleccionado == 3) peon.SetModoDibujado('f');
		else if (seleccionado == 4) pinguino.SetModoDibujado('f');
		else if (seleccionado == 5) es_iluminada.SetModoDibujado('f');
	}
	else if (toupper(Tecla1)=='C') {
		std::cout << "Modo seleccionado: Ajedrez\n";
		if (seleccionado == 0) tetra3D.SetModoDibujado('c');
		else if (seleccionado == 1) cubo3D.SetModoDibujado('c');
		else if (seleccionado == 2) objPLY.SetModoDibujado('c');
		else if (seleccionado == 3) peon.SetModoDibujado('c');
		else if (seleccionado == 4) pinguino.SetModoDibujado('c');
		else if (seleccionado == 5)
			cout << "No es posible activar ajedrez en la escena iluminada\n";
	}
	else if (toupper(Tecla1)=='1') {
		std::cout << "Dibujando objeto Cubo\n";
		seleccionado = 0;
	}
	else if (toupper(Tecla1)=='2') {
		std::cout << "Dibujando objeto Tetraedro\n";
		seleccionado = 1;
	}
	else if (toupper(Tecla1)=='3') {
		std::cout << "Dibujando objeto PLY cargado\n";
		seleccionado = 2;
	}
	else if (toupper(Tecla1)=='4') {
		std::cout << "Dibujando objeto de revolucion\n";
		seleccionado = 3;
	}
	else if (toupper(Tecla1)=='5') {
		std::cout << "Dibujando objeto jerarquico\n";
		seleccionado = 4;
	}
	else if (toupper(Tecla1)=='6') {
		std::cout << "Dibujando escena iluminada\n";
		seleccionado = 5;
	}
	else if (toupper(Tecla1)=='7') {
		std::cout << "Dibujando tablero con textura\n";
		seleccionado = 6;
	}
	else if ((Tecla1)=='M') {
		std::cout << "Desplazando Pingu ++...\n";
		velocidad_mov += 0.01;
		pinguino.EnableDesplazamiento(velocidad_mov);
	}
	else if ((Tecla1)=='m') {
		std::cout << "Desplazando Pingu --...\n";
		if (velocidad_mov - 0.01 > 0) velocidad_mov -= 0.01;
		pinguino.EnableDesplazamiento(velocidad_mov);
	}
	else if ((Tecla1)=='N') {
		std::cout << "Rotando cuerpo ++...\n";
		velocidad_rot += 0.01;
		pinguino.child[0]->EnableRotacion(velocidad_rot);
	}
	else if ((Tecla1)=='n') {
		std::cout << "Rotando cuerpo --...\n";
		if (velocidad_rot - 0.01 > 0) velocidad_rot-= 0.01;
		pinguino.child[0]->EnableRotacion(velocidad_rot);
	}
	else if ((Tecla1)=='B') {
		std::cout << "NOOT NOOT ++...\n";
		velocidad_noot += 0.001;
		pinguino.child[0]->child[0]->EnableNoot(velocidad_noot);
	}
	else if ((Tecla1)=='b') {
		std::cout << "NOOT NOOT --...\n";
		if (velocidad_noot - 0.01 > 0) velocidad_noot -= 0.001;
		pinguino.child[0]->child[0]->EnableNoot(velocidad_noot);
	}
	else if ((Tecla1)=='i') {
		std::cout << "Modificando estado de luces...\n";
		es_iluminada.InterruptorLuces();
	}
	else if ((Tecla1)=='s') {
		std::cout << "Modificando modo de sombreado...\n";
		es_iluminada.InterruptorSombreado();
	}
	else if ((Tecla1)=='g') {
		std::cout << "Moviendo luz 1...\n";
		es_iluminada.MoverLuz1();
	}
	else if ((Tecla1)=='h') {
		std::cout << "Moviendo luz 2...\n";
		es_iluminada.MoverLuz2();
	}
	else if ((Tecla1)=='t') {
		std::cout << "Activando material 1...\n";
		es_iluminada.SetMaterial(1);
	}
	else if ((Tecla1)=='y') {
		std::cout << "Activando material 2...\n";
		es_iluminada.SetMaterial(2);
	}
	else if ((Tecla1)=='u') {
		std::cout << "Activando material 3...\n";
		es_iluminada.SetMaterial(3);
	}
	else {
		return 0;
	}
	return 0;
}

void Escena::teclaEspecial(int Tecla1,int x,int y) {
switch (Tecla1){
	case GLUT_KEY_LEFT:Observer_angle_y--;break;
	case GLUT_KEY_RIGHT:Observer_angle_y++;break;
	case GLUT_KEY_UP:Observer_angle_x--;break;
	case GLUT_KEY_DOWN:Observer_angle_x++;break;
	case GLUT_KEY_PAGE_UP:Observer_distance*=1.2;break;
	case GLUT_KEY_PAGE_DOWN:Observer_distance/=1.2;break;
	}

	std::cout << Observer_distance << std::endl;
}


//**************************************************************************
// Funcion para definir la transformación de proyeccion
//***************************************************************************

void Escena::change_projection()  {
glMatrixMode(GL_PROJECTION);
glLoadIdentity();
glFrustum(-Width,Width,-Height,Height,Front_plane,Back_plane);
}


void Escena::redimensionar(int newWidth,int newHeight) {
change_projection();
Width=newWidth/10;
Height=newHeight/10;
glViewport(0,0,newWidth,newHeight);
}


//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************



void Escena::change_observer() {

// posicion del observador
glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
glTranslatef(0,0,-Observer_distance);
glRotatef(Observer_angle_x,1,0,0);
glRotatef(Observer_angle_y,0,1,0);
}


//**************************************************************************
// Funcion que dibuja los ejes utilizando la primitiva grafica de lineas
//***************************************************************************

void Escena::draw_axis()
{
ejes.draw();
}
