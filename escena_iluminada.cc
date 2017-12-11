/*******************************************************************/
// David Vargas Carrillo
// Informatica Grafica - Practica 4
// Diciembre 2017
//
// Fichero: escena_iluminada.cc
// Declaraciones de los metodos de la clase EscenaIluminada
/*******************************************************************/

#include "escena_iluminada.h"

/*******************************************************************/
//
/*******************************************************************/

EscenaIluminada::EscenaIluminada() {
	pos_x_actual = -15.0;
	dir_x_actual = 1.0;
	dir_z_actual = 0.0;
	pos_adelante = true;
	dir_adelante = true;

	// Construccion de objetos
	beethoven.LeerFigura("./read_ply/beethoven.ply");
	beethoven.CalcularNormales();

	// Construccion de la luz
	// Luz 1 posicional
	luz1.SetNumeroLuz(1);
	luz1.SetPosicion(pos_x_actual, 20.0, 25.0);
	luz1.SetColorAmbiente(0.2, 0.2, 0.2);
	luz1.SetColorDifuso(0.2, 0.8, 1.0);
	luz1.SetColorEspecular(1.0, 1.0, 1.0);

	// Luz 2 direccional
	luz2.SetNumeroLuz(2);
	luz2.SetDireccion(dir_x_actual, 0.0, dir_x_actual);
	luz2.SetColorAmbiente(0.2, 0.2, 0.2);
	luz2.SetColorDifuso(1.0, 0.0, 1.0);
	luz2.SetColorEspecular(1.0, 1.0, 1.0);

	// Construccion de los materiales
	material1 = new Material();
	material2 = new Material();
	material3 = new Material();

	// Configuracion de cada uno de ellos
	// La activacion de Emision y Ambiente impide que la figura
	// refleje el color de la luz

	material1->SetEmision(0.0, 0.0, 0.0);
	material1->SetAmbiente(0.0, 0.0, 0.0);
	material1->SetEspecular(0.8, 0.8, 0.8);
	material1->SetBrillo(20);

	material2->SetEmision(0.5, 0.5, 0.0);
	material2->SetAmbiente(0.0, 0.0, 0.0);
	material2->SetEspecular(0.5, 0.5, 0.5);
	material2->SetBrillo(20);

	material3->SetEmision(0.8, 0.8, 0.8);
	material3->SetAmbiente(0.0, 0.0, 0.0);
	material3->SetEspecular(0.5, 0.5, 0.5);
	material3->SetBrillo(30);

	// No se asigna ningun material por defecro
	mat_seleccionado = 0;
	
	estado = 1;
}

/*******************************************************************/
//
/*******************************************************************/

EscenaIluminada::~EscenaIluminada() {
	if (material1 != NULL) delete[] material1;
	if (material2 != NULL) delete[] material2;
	if (material3 != NULL) delete[] material3;
	material1 = NULL;
	material2 = NULL;
	material3 = NULL;
}

/*******************************************************************/
//
/*******************************************************************/

void EscenaIluminada::SetModoDibujado(char modo) {
	beethoven.SetModoDibujado(modo);
}

/*******************************************************************/
//
/*******************************************************************/

void EscenaIluminada::DibujarEscena() {
	glEnable(GL_NORMALIZE);

	//glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER,GL_TRUE);
	// glClearColor (0.0, 0.0, 0.0, 0.0);

	// Activacion de las luces
	if (estado == 1) {
		luz1.Enable();
		// luz1.DibujaPosicion();
		luz2.Enable();
	}

	// Activacion del material
	if (mat_seleccionado != 0)
		beethoven.EnableMaterial();

	// Dibujado de los objetos presentes en la escena
	beethoven.Dibujar();

	// Desactivacion de las luces
	if (estado == 1) {
		luz1.Disable();
		luz2.Disable();
	}
}

/*******************************************************************/
//
/*******************************************************************/

void EscenaIluminada::MoverLuz1() {
	if (pos_adelante)
		pos_x_actual += 1.0;
	else
		pos_x_actual -= 1.0;

	if (pos_x_actual >= LIM_MIN_POSICION_LUZ)
		pos_adelante = false;
	else if (pos_x_actual <= LIM_MAX_POSICION_LUZ)
		pos_adelante = true;

	std::cout << "Posicion luz 1: " << pos_x_actual << std::endl; 
	luz1.SetPosicion(pos_x_actual, 20.0, 25.0);
}

/*******************************************************************/
//
/*******************************************************************/

void EscenaIluminada::MoverLuz2() {
	if (dir_adelante) {
		dir_x_actual -= 0.1;
		dir_z_actual += 0.1;
	} else {
		dir_x_actual += 0.1;
		dir_z_actual -= 0.1;
	}

	if (dir_x_actual <= LIM_MIN_DIRECCION_LUZ)
		dir_adelante = false;
	else if (dir_x_actual >= LIM_MAX_DIRECCION_LUZ)
		dir_adelante = true;

	std::cout << "Posicion luz 2: " << dir_x_actual;
	std::cout << " " << dir_z_actual << std::endl; 
	luz2.SetDireccion(dir_x_actual, 0.0, dir_z_actual);
}

/*******************************************************************/
//
/*******************************************************************/
void EscenaIluminada::SetMaterial(int num) {
	switch (num) {
		case 0:
			mat_seleccionado = 0;
			break;
		case 1:
			mat_seleccionado = 1;
			beethoven.SetMaterial(material1);
			break;
		case 2:
			mat_seleccionado = 2;
			beethoven.SetMaterial(material2);
			break;
		case 3:
			mat_seleccionado = 3;
			beethoven.SetMaterial(material3);
			break;
		default:
			std::cout << "ERROR: material seleccionado invalido\n";
	}
}

/*******************************************************************/
//
/*******************************************************************/

void EscenaIluminada::InterruptorLuces() {
	(estado == 1) ? estado = 0 : estado = 1;
}

/*******************************************************************/
//
/*******************************************************************/

void EscenaIluminada::InterruptorSombreado() {
	luz1.CambiarModoSombreado();
	luz2.CambiarModoSombreado();
}
