/*******************************************************************/
// David Vargas Carrillo
// Informatica Grafica - Practica 3
// Noviembre 2017
//
// Fichero: esfera.cc
// Declaraciones de los metodos de la clase Esfera
/*******************************************************************/

#include "esfera.h"

/*******************************************************************/
//
/*******************************************************************/

Esfera::Esfera() {
	vertices = {};
	lados = {};
	lados1 = {};
	lados2 = {};
	color1 = {};
	color2 = {};
	puntos = false;
	alambre = false;
	solido = true;
	ajedrez = false;
	nvertices_perfil = 0;
	hay_tapas = true;	// no se necesitan
}

/*******************************************************************/
//
/*******************************************************************/

Esfera::Esfera(float size) {
	vertices = {};
	lados = {};
	lados1 = {};
	lados2 = {};
	color1 = {};
	color2 = {};
	puntos = false;
	alambre = false;
	solido = true;
	ajedrez = false;
	nvertices_perfil = 0;
	hay_tapas = true;	// no se necesitan
	BuildPerfilEsfera(size);
}

/*******************************************************************/
//
/*******************************************************************/

void Esfera::BuildPerfilEsfera(float size) {
	// Se vacia el vector de vertices
	vertices.clear();
	// Se vacian los vectores de lados
	lados.clear();
	lados1.clear();
	lados2.clear();

	// Precision de la semicircunferencia
	float prec = 10.0;
	
	for (int i = 0; i <= prec; ++i)
	{
		// Angulo de rotacion en el dibujado
		float angle = M_PI * (i / prec);
		// Posicionamiento del punto
		float x = sin(angle) * size;
		float y = cos(angle) * size;
		float z = 0.0;
		// Introduccion en el vector
		vertices.push_back(x);
		vertices.push_back(y);
		vertices.push_back(z);
	}

	// La variable de vertices del perfil se ajusta segun lo introducido
	nvertices_perfil = vertices.size() / 3;
}
