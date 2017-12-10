/*******************************************************************/
// David Vargas Carrillo
// Informatica Grafica - Practica 3
// Noviembre 2017
//
// Fichero: base.cc
// Declaraciones de los metodos de la clase Base
/*******************************************************************/

#include "base.h"

/*******************************************************************/
//
/*******************************************************************/

Base::Base() {
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

Base::Base(float size) {
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
	BuildPerfilBase(size);
}

/*******************************************************************/
//
/*******************************************************************/

void Base::BuildPerfilBase(float size) {
	// Se vacian los vectores de lados
	lados.clear();
	lados1.clear();
	lados2.clear();

	vertices = {fabs((float)0.0*size),  (float)-5.0*size, fabs((float)0.0*size),	// v0
				fabs((float)3.5*size),  (float)-5.0*size, fabs((float)0.0*size),	// v1
				fabs((float)4.3*size),  (float)-4.5*size, fabs((float)0.0*size),	// v1
				fabs((float)4.0*size),  (float)-4.0*size, fabs((float)0.0*size),	// v2
				fabs((float)3.5*size),  (float)0.0*size,  fabs((float)0.0*size),	// v3
				fabs((float)3.0*size),  (float)2.0*size,  fabs((float)0.0*size),	// v4
				fabs((float)2.0*size),  (float)3.7*size,  fabs((float)0.0*size),	// v5
				fabs((float)1.0*size),  (float)4.7*size,  fabs((float)0.0*size),	// v6
				fabs((float)0.0*size),  (float)5.0*size,  fabs((float)0.0*size)};	// v7

	// La variable de vertices del perfil se ajusta segun lo introducido
	nvertices_perfil = vertices.size() / 3;
}
