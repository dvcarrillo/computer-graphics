/*******************************************************************/
// David Vargas Carrillo
// Informatica Grafica - Practica 3
// Noviembre 2017
//
// Fichero: esfera.h
// Definiciones de la estructura y metodos de la clase Esfera
/*******************************************************************/

#ifndef _ESFERA_H
#define _ESFERA_H

#include "revolucion.h"

// Esfera hereda de Revolucion

class Esfera : public Revolucion
{
public:
	// Constructor vacio
	Esfera();
	// Crea una esfera con la dimension dada
	// Recibe:
	// 	size: multiplicador de la dimension de la esfera
	Esfera(float size);
	// Construye el perfil con la dimension dada
	// Recibe:
	//	size: multiplicador de la dimension del perfil
	void BuildPerfilEsfera(float size);
};

#endif
