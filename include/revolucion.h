/*******************************************************************/
// David Vargas Carrillo
// Informatica Grafica - Practica 2
// Octubre 2017
//
// Fichero: revolucion.h
// Definiciones de la estructura y metodos de la clase Revolucion
/*******************************************************************/

#ifndef _REVOLUCION_H
#define _REVOLUCION_H

#include "objeto3D.h"
#include <cmath>

// Revolucion hereda de Objeto3D y define una figura de revolucion

class Revolucion : public Objeto3D
{
protected:
	// Numero de vertices del perfil de la figura
	int nvertices_perfil;
	// Variable que almacena si las tapas estan activadas
	bool hay_tapas;
public:
	// Crea una figura de revolucion vacia
	Revolucion();
	// Construye el perfil de la figura con puntos en el plano Y
	// Recibe: 
	// 	size: multiplicador de dimension de la figura
	void BuildPeon(float size);
	// Crea un nuevo perfil a partir de la rotacion del original en el eje Y
	// Recibe:
	// 	angle: angulo de rotacion en radianes
	void RotarPerfil_Y(float angle);
	// Construye la figura de revolucion
	// Recibe:
	// 	num_vueltas: vueltas de la revolucion de la figura
	void BuildFigura(int num_vueltas);
	// Construye las tapas de la figura
	void BuildTapas();
	// Elimina las tapas de la figura
	void DeleteTapas();
};

#endif
