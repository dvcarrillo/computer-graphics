/*******************************************************************/
// David Vargas Carrillo
// Informatica Grafica - Practica 1
// Septiembre 2017
//
// Fichero: cubo.cc
// Declaraciones de los metodos de la clase Cubo
/*******************************************************************/

#include "cubo.h"

Cubo::Cubo() {
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

void Cubo::BuildCubo(float lado) {
	// Asignacion de valores al vector de vertices
	vertices = {-lado, 0.0, lado,		// v0
				lado, 0.0, lado,		// v1
				-lado, 2*lado, lado,	// v2
				lado, 2*lado, lado,		// v3
				-lado, 0.0, -lado,		// v4
				lado, 0.0, -lado,		// v5
				-lado, 2*lado, -lado,	// v6
				lado, 2*lado, -lado};	// v7

	// Asignacion de valores al vector de lados
	lados = {4, 7, 6,			// l6 Cara trasera
			5, 7, 4,			// l7

			1, 5, 7,			// l5 Cara derecha
			1, 7, 3,			// l4 

			0, 4, 1,			// l8 Cara inferior
			1, 4, 5,			// l9

			2, 6, 4,			// l10 Cara izquierda
			0, 2, 4,			// l11

			2, 3, 7,			// l2 Cara superior
			2, 7, 6,			// l3

			0, 1, 2,			// l0 Cara delantera
			1, 3, 2				// l1
			};

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

