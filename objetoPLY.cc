/*******************************************************************/
// David Vargas Carrillo
// Informatica Grafica - Practica 2
// Octubre 2017
//
// Fichero: objetoPLY.cc
// Declaraciones de los metodos de la clase ObjetoPLY
/*******************************************************************/

#include "objetoPLY.h"

/*******************************************************************/
//
/*******************************************************************/

ObjetoPLY::ObjetoPLY() {
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

/*******************************************************************/
//
/*******************************************************************/

void ObjetoPLY::LeerFigura(string archivo) {
	_file_ply figura_ply;
	vector<_vertex3f> temp_vertices;
  	vector<_vertex3i> temp_triangles;

	if (figura_ply.open(archivo)) {
		figura_ply.read(temp_vertices, temp_triangles);
	}
	else std::cerr << "Error al leer el fichero" << std::endl;

	for (int i = 0; i < temp_vertices.size(); ++i)
	{
		vertices.push_back(5 * temp_vertices[i].x);
		vertices.push_back(5 * temp_vertices[i].y);
		vertices.push_back(5 * temp_vertices[i].z);
	}

	// Ya que tenemos todos los vertices, creamos los vectores de color
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

	for (int i = 0; i < temp_triangles.size(); ++i)
	{
		lados.push_back(temp_triangles[i]._0);
		lados.push_back(temp_triangles[i]._1);
		lados.push_back(temp_triangles[i]._2);
		if (i % 2 == 0) {
			lados1.push_back(temp_triangles[i]._0);
			lados1.push_back(temp_triangles[i]._1);
			lados1.push_back(temp_triangles[i]._2);
		}
		else {
			lados2.push_back(temp_triangles[i]._0);
			lados2.push_back(temp_triangles[i]._1);
			lados2.push_back(temp_triangles[i]._2);
		}
	}
}
