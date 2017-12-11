/*******************************************************************/
// David Vargas Carrillo
// Informatica Grafica - Practica 4
// Octubre 2017
//
// Fichero: objeto3D.h
// Definiciones de la estructura y metodos de la clase objeto3D
/*******************************************************************/

#ifndef _OBJETO_3D_H
#define _OBJETO_3D_H

#include <GL/gl.h>
#include <GL/glut.h>
#include <vector>
#include <iostream>
#include <file_ply_stl.h>

#include "vertex.h"
#include "material.h"

/**
* Objeto3D representa un objeto en el plano 3D, definido por una lista
* de vertices y una lista de caras o triangulos
*/

class Objeto3D
{
protected:
	// Relativo a la geometria y toponomia de la figura
	std::vector<GLfloat> vertices;
	std::vector<GLuint> lados;

	// Parametros propios del modo ajedrez
	std::vector<GLuint> lados1;
	std::vector<GLuint> lados2;
	std::vector<GLfloat> color1;
	std::vector<GLfloat> color2;

	// Vectores de normales
	std::vector<GLfloat> n_vertices;
	std::vector<GLfloat> n_lados;

	// Propiedades de la figura
	bool puntos, alambre, solido, ajedrez;

	// Propiedades de color
	float color_r, color_g, color_b;

	// Parametros de transformaciones
	float tras_x, tras_y, tras_z;	// Traslacion
	float rota_x, rota_y, rota_z;	// Rotacion
	float esca_x, esca_y, esca_z;	// Escalado

	// Movimiento y animacion
	bool rot_cuerpo, noot, mov_pingu;
	float LIM_MIN_MOVIMIENTO;
	float LIM_MAX_MOVIMIENTO;
	float MAGNITUD_PASO;
	float posicion_movimiento;
	bool adelante;

	// Material propio del objeto
	Material *material;
public:
	// Arbol de objetos
	std::vector<Objeto3D*> child;
	// Constructor por defecto
	Objeto3D();
	// Constructor de copia
	Objeto3D(Objeto3D &obj3D);

	// Agrega un objeto al vector de hijos
	void AddObjeto(Objeto3D *obj3D);
	// Calcula las normales de caras del objeto
	// Se deberia llamar a esta funcion una vez definidos lados y vertices
	void CalcularNormales();

	// Establece las transformaciones
	// Recibe:
	//	traslacion_?: parametros de traslacion
	//	rotacion_?: parametros de rotacion
	//	escalado_?: parametros de escalado
	void SetTransformaciones(float t_x, float t_y, float t_z,
							float r_x, float r_y, float r_z,
							float e_x, float e_y, float e_z);
	// Funcion para configurar el modo de dibujado del objeto
	// Recibe MODO DE DIBUJADO:
	//	p: modo por puntos
	//	f: modo solido
	//	c: modo ajedrez
	//	l (y cualquier otro caracter): alambre
	void SetModoDibujado(char modo);
	// Establece el color de la figura
	// Recibe:
	//	{r, g, b}: intensidad de color en R, G o B
	void SetColor(float r, float g, float b);
	// Establece el material del objeto
	// Recibe:
	// 	*mat: puntero a objeto de la clase material
	void SetMaterial(Material *mat);
	// Activa el material del objeto
	void EnableMaterial();

	// Funcion de dibujado de la figura actual
	void Dibujar();
	// Dibujado con un color solido
	void DibujarSolido(float r, float g, float b);
	// Funcion de dibujado jerarquico
	// Aplica transformaciones, dibuja la figura actual y sus hijos
	void DibujadoJerarquico();

	// Activar animaciones (propio de la animacion de pinguino)
	void EnableRotacion(float v);
	void EnableDesplazamiento(float v);
	void EnableNoot(float v);
};

#endif