/*******************************************************************/
// David Vargas Carrillo
// Informatica Grafica - Practica 4
// Diciembre 2017
//
// Fichero: material.cc
// Declaraciones de los metodos de la clase Material
/*******************************************************************/

#include "material.h"

/*******************************************************************/
//
/*******************************************************************/

Material::Material() {
	mat_emision[0] = 0.0; mat_emision[1] = 0.0;
	mat_emision[2] = 0.0; mat_emision[3] = 0.0;

	mat_ambiente[0] = 0.0; mat_ambiente[1] = 0.0;
	mat_ambiente[2] = 0.0; mat_ambiente[3] = 0.0;

	mat_difuso[0] = 0.0; mat_difuso[1] = 0.0;
	mat_difuso[2] = 0.0; mat_difuso[3] = 0.0;

	mat_especular[0] = 0.0; mat_especular[1] = 0.0;
	mat_especular[2] = 0.0; mat_especular[3] = 0.0;

	brillo = -1.0;
}

/*******************************************************************/
//
/*******************************************************************/

void Material::SetEmision(float emi_r, float emi_g, float emi_b) {
	GLfloat nuevo_memision[4] = {emi_r, emi_g, emi_b, 1.0};
	std::copy(nuevo_memision, nuevo_memision + 4, mat_emision);
}

/*******************************************************************/
//
/*******************************************************************/

void Material::SetAmbiente(float amb_r, float amb_g, float amb_b) {
	GLfloat nuevo_mambiente[4] = {amb_r, amb_g, amb_b, 1.0};
	std::copy(nuevo_mambiente, nuevo_mambiente + 4, mat_ambiente);
}

/*******************************************************************/
//
/*******************************************************************/

void Material::SetDifuso(float dif_r, float dif_g, float dif_b) {
	GLfloat nuevo_mdifuso[4] = {dif_r, dif_g, dif_b, 1.0};
	std::copy(nuevo_mdifuso, nuevo_mdifuso + 4, mat_difuso);
}

/*******************************************************************/
//
/*******************************************************************/

void Material::SetEspecular(float esp_r, float esp_g, float esp_b) {
	GLfloat nuevo_mespecular[4] = {esp_r, esp_g, esp_b, 1.0};
	std::copy(nuevo_mespecular, nuevo_mespecular + 4, mat_especular);
}

/*******************************************************************/
//
/*******************************************************************/

void Material::SetBrillo(float intensidad) {
	if ((intensidad >= 0.0) && (intensidad <= 128.0))
		brillo = intensidad;
	else
		std::cout << "ERROR: valor invalido de brillo para el material\n";
}

/*******************************************************************/
//
/*******************************************************************/

void Material::Enable() {
	// Modifica la emisividad
	if (mat_emision[3] != 0)
		glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, mat_emision);
	// Modifica el color ambiente
	if (mat_ambiente[3] != 0)
		glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambiente);
	// Modifica el color difuso
	if (mat_difuso[3] != 0)
		glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_difuso);
	// Modifica el color especular
	if (mat_especular[3] != 0)
		glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_especular);
	// Modifica el brillo
	if (brillo >= 0.0)
		glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, brillo);
}
