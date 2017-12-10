/*******************************************************************/
// David Vargas Carrillo
// Informatica Grafica - Practica 3
// Noviembre 2017
//
// Fichero: base.h
// Definiciones de la estructura y metodos de la clase Base
/*******************************************************************/

#ifndef _BASE_H
#define _BASE_H

#include "revolucion.h"

// Base hereda de Revolucion y define la base del cuerpo

class Base : public Revolucion
{
public:
	// Constructor por defecto
	Base();
	// Crea una base con la dimension dada
	// Recibe:
	// 	size: multiplicador de la dimension de la base
	Base(float size);
	// Construye el perfil con la dimension dada
	// Recibe:
	//	size: multiplicador de la dimension del perfil
	void BuildPerfilBase(float size);
};

#endif
