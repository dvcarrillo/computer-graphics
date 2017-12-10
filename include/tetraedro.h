/*******************************************************************/
// David Vargas Carrillo
// Informatica Grafica - Practica 1
// Septiembre 2017
//
// Fichero: tetraedro.h
// Definiciones de la estructura y metodos de la clase Tetraedro
/*******************************************************************/

#ifndef _TETRAEDRO_3D
#define _TETRAEDRO_3D

#include "objeto3D.h"

/**
* Tetraedro es una clase que hereda de Objeto3D y representa un
* tetraedro en el espacio 3D
*/

class Tetraedro : public Objeto3D
{
public:
	// Constructor por defecto
	// Crea un tetraedro con unos atributos predefinidos
	Tetraedro();
	// Construye un tetraedro con la longitud de lado dada
	void BuildTetraedro(float lado);
};

#endif