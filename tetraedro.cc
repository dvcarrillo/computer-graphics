/*******************************************************************/
// David Vargas Carrillo
// Informatica Grafica - Practica 1
// Septiembre 2017
//
// Fichero: tetraedro.cc
// Declaraciones de los metodos de la clase Tetraedro
/*******************************************************************/

#include "tetraedro.h"

Tetraedro::Tetraedro() {
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
}

void Tetraedro::BuildTetraedro(float lado) {
	// Asignacion de valores al vector de vertices
	vertices = {0.0, 0.0, lado,			// v0
				lado, 0.0, -lado,		// v1
				-lado, 0.0, -lado,		// v2
				0.0, lado, 0.0};		// v4

	// Asignacion de valores al vector de lados
	lados = {0, 1, 2,					// l0
			0, 1, 3,					// l1
			0, 2, 3,					// l2
			1, 2, 3};					// l3

	for (int i = 0; i < lados.size(); i += 3) {
		if (i % 2 == 0) {
			lados1.push_back(lados[i]);
			lados1.push_back(lados[i+1]);
			lados1.push_back(lados[i+2]);
		}
		else {
			lados2.push_back(lados[i]);
			lados2.push_back(lados[i+1]);
			lados2.push_back(lados[i+2]);
		}
	}

	for (int i = 0; i < vertices.size(); ++i) {
		if (i % 2 == 0) {
			color1.push_back(255);	// R
			color1.push_back(0);	// G
			color1.push_back(0);	// B
		}
		else {
			color2.push_back(0);	// R
			color2.push_back(255);	// G
			color2.push_back(0);	// B
		}
	}
}