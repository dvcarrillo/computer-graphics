#ifndef _ESCENA_H
#define _ESCENA_H

#include <vector>
#include "ejes.h"
#include "objeto3D.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objetoPLY.h"
#include "revolucion.h"
#include "esfera.h"
#include "base.h"
#include "escena_iluminada.h"
#include "escena_tex.h"

class Escena {
private:
// tamaño de los ejes
#define AXIS_SIZE 5000
Ejes ejes;

// variables que definen la posicion de la camara en coordenadas polares
GLfloat Observer_distance;
GLfloat Observer_angle_x;
GLfloat Observer_angle_y;

// variables que controlan la ventana y la transformacion de perspectiva
GLfloat Width,Height,Front_plane,Back_plane;

private:
	void clear_window();
	void draw_axis();
	void draw_objects();

	// Transformación de cámara
	void change_projection();
	void change_observer();

	// Objetos
	int seleccionado;
	// Objeto Cubo
	Cubo cubo3D;
	// Objeto Tetraeedro
	Tetraedro tetra3D;
	// Objeto PLY
	ObjetoPLY objPLY;
	// Peon
	Revolucion peon;
	// Objeto de revolucion
	int vueltas_revolucion;
	// Objeto conjunto
	Objeto3D pinguino;
	float velocidad_mov;
	float velocidad_rot;
	float velocidad_noot;
	// Escena iluminada
	EscenaIluminada es_iluminada;
	// Escena con textura
	EscenaTex es_textura;

public:
    Escena();
	void inicializar(int UI_window_width,int UI_window_height);
	void redimensionar(int newWidth,int newHeight) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	int teclaPulsada(unsigned char Tecla1,int x,int y) ;
	void teclaEspecial(int Tecla1,int x,int y);
};
#endif
