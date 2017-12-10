/*******************************************************************/
// David Vargas Carrillo
// Informatica Grafica - Practica 4
// Diciembre 2017
//
// Fichero: luz.h
// Definiciones de la estructura y metodos de la clase Luz
/*******************************************************************/

#ifndef _LUZ_H
#define _LUZ_H

#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "cubo.h"

/**
 * Luz comprende una fuente de iluminacion en una escena
 */

class Luz
{
private:
	// Componentes posicionales
	// Valores para type: 1.0 luz posicional, 0.0 luz direccional
	GLfloat posicion[4];			// pX, pY, pZ, type
	GLfloat direccion[4];			// vX, vY, vZ, type
	int type;						// 0 o 1

	// Propiedades
	int numero_luz;					// Numero de la luz respecto a OpenGL
	int modo_sombreado;				// 0 sombreado plano, 1 sombreado de Goraud
	GLfloat color_difuso[4];		// difR, difB, difG
	GLfloat color_especular[4];		// espR, espB, espG
	GLfloat color_ambiente[4];		// ambR, ambG, ambB

public:
	// Constructor por defecto
	// Construye una luz posicional en el origen sin color
	Luz();
	// Constructor con numero de luz
	// Recibe:
	// 	num: numero de la luz en OpenGL
	Luz(int num);

	// Modificadores de propiedades
	// Crea una luz posicional
	void SetPosicion(float pos_x, float pos_y, float pos_z);
	// Crea una luz direccional
	void SetDireccion(float vec_x, float vec_y, float vec_z);
	void SetColorDifuso(float dif_r, float dif_g, float dif_b);
	void SetColorEspecular(float esp_r, float esp_g, float esp_b);
	void SetColorAmbiente(float amb_r, float amb_g, float amb_b);
	void SetNumeroLuz(int num);
	// Modifica el modo de sombreado de la figura
	void CambiarModoSombreado();

	// Activa la luz en OpenGL dada por el numero definido en numero_luz
	void Enable();
	// Desactiva la luz en OpenGL dada por el numero definido en numero_luz
	void Disable();

	// Funciones de testeo
	// Imprime por pantalla la informacion actual de la luz
	void ImprimeInformacion();
	// Dibuja un cubo en la posicion de la luz
	void DibujaPosicion();
};

#endif
