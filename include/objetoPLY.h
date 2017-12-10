/*******************************************************************/
// David Vargas Carrillo
// Informatica Grafica - Practica 2
// Octubre 2017
//
// Fichero: objetoPLY.h
// Definiciones de la estructura y metodos de la clase ObjetoPLY
/*******************************************************************/

#ifndef _OBJETO_PLY_H
#define _OBJETO_PLY_H

#include "objeto3D.h"

 /**
 * ObjetoPLY es una clase que hereda de Objeto3D y representa una
 * figura 3D cargada mediante un fichero PLY
 */

class ObjetoPLY : public Objeto3D
{
public:
	// Constructor por defecto
	// Crea un objeto 3D vacio
	ObjetoPLY();
	// Carga el fichero PLY indicado y construye una figura 3D
	// a partir del mismo
	// Recibe: ruta del fichero PLY
	void LeerFigura(string archivo);
};

#endif