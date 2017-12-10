/*******************************************************************/
// David Vargas Carrillo
// Informatica Grafica - Practica 4
// Diciembre 2017
//
// Fichero: material.h
// Definiciones de la estructura y metodos de la clase Material
/*******************************************************************/
#ifndef _MATERIAL_H
#define _MATERIAL_H

#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

/**
 * Material define los parametros de un material aplicable a un
 * objeto
 */

class Material
{
private:							// Valores RGB
	GLfloat mat_emision[4];			// emiR, emiG, emiB
	GLfloat mat_ambiente[4];		// ambR, ambG, ambB
	GLfloat mat_difuso[4];			// difR, difB, difG
	GLfloat mat_especular[4];		// espR, espB, espG
	float brillo;					// Entre 0.0 y 128.0
public:
	// Constructor por defecto
	// Crea un material con todas las propiedades a cero
	Material();

	// Modificadores de las propiedades
	void SetEmision(float emi_r, float emi_g, float emi_b);
	void SetAmbiente(float amb_r, float amb_g, float amb_b);
	void SetDifuso(float dif_r, float dif_g, float dif_b);
	void SetEspecular(float esp_r, float esp_g, float esp_b);
	void SetBrillo(float intensidad);

	// Activa el material en OpenGL
	void Enable();
};

#endif
