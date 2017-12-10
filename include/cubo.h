/*******************************************************************/
// David Vargas Carrillo
// Informatica Grafica - Practica 1
// Septiembre 2017
//
// Fichero: cubo.h
// Definiciones de la estructura y metodos de la clase Cubo
/*******************************************************************/

#ifndef _CUBO_3D
#define _CUBO_3D

#include "objeto3D.h"


/**
* Cubo es una clase que hereda de Objeto3D y representa un cubo en
* el espacio 3D
*/

class Cubo : public Objeto3D
{
public:
	// Constructor por defecto
	// Crea un cubo con unos atributos predefinidos
	Cubo();
	// Construye un cubo con la longitud de lado dada
	void BuildCubo(float lado);
};

#endif