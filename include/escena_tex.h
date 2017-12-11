/*******************************************************************/
// David Vargas Carrillo
// Informatica Grafica - Practica 4
// Diciembre 2017
//
// Fichero: escena_tex.h
// Definiciones de la estructura y metodos de la clase EscenaTex
/*******************************************************************/

#ifndef _ESCENA_TEX_H
#define _ESCENA_TEX_H

#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include "cubo.h"
#include "cargadorBMP.h"

/**
 * EscenaTex representa una escena que contiene objetos con una
 * textura aplicada
 */

class EscenaTex
{
private:
	// Propiedades del tablero
	std::vector<GLfloat> v_tablero;		// vertices del tablero
	std::vector<GLfloat> v_textura;		// vertices de la textura (texels)

	// Imagen a cargar
	CargadorBMP imagen;

public:
	// Constructor por defecto
	// Construye un tablero determinado con con la textura de 0.0 a 1.0 
	EscenaTex();
	// Construye un tablero por defecto con la imagen indicada
	// Recibe:
	// 	imagepath: ruta del archivo BMP a cargar
	EscenaTex(const char * imagepath);

	// Carga la imagen BMP dada por la ruta indicada
	// Recibe:
	// 	imagepath: ruta del archivo BMP a cargar
	void CargarImagen(const char * imagepath);
	// Dibuja la escena
	void Dibujar();
};

#endif
