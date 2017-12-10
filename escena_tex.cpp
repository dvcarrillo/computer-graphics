/*******************************************************************/
// David Vargas Carrillo
// Informatica Grafica - Practica 4
// Diciembre 2017
//
// Fichero: escena_tex.cc
// Declaraciones de los metodos de la clase EscenaTex
/*******************************************************************/

#include "escena_tex.h"

/*******************************************************************/
//
/*******************************************************************/

EscenaTex::EscenaTex() {
	v_tablero = {-40, 	-40,
				40, 	-40,
				40, 	40,
				-40, 	40};
	v_textura = {0.0,	1.0,
				1.0, 	1.0,
				1.0,	0.0,
				0.0,	0.0};
}

/*******************************************************************/
//
/*******************************************************************/

EscenaTex::EscenaTex(const char * imagepath) {
	v_tablero = {-40, 	-40,
				40, 	-40,
				40, 	40,
				-40, 	40};
	v_textura = {0.0,	1.0,
				1.0, 	1.0,
				1.0,	0.0,
				0.0,	0.0};
	CargarImagen(imagepath);
}

/*******************************************************************/
//
/*******************************************************************/

void EscenaTex::CargarImagen(const char * imagepath) {
	imagen.LoadBMP(imagepath);
}

/*******************************************************************/
//
/*******************************************************************/

void EscenaTex::Dibujar() {
	glColor3f(1.0, 1.0, 1.0);
	// Se crea una textura OpenGL
	GLuint textureID;
	glGenTextures(1, &textureID);

	// Se ata la nueva textura
	glBindTexture(GL_TEXTURE_2D, textureID);

	// Se le pasa la imagen a OpenGL
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imagen.GetWidth(),
		imagen.GetHeight(), 0, GL_BGR, GL_UNSIGNED_BYTE, imagen.GetData());
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	// Se activa la textura
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState (GL_TEXTURE_COORD_ARRAY_EXT);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glVertexPointer(2, GL_FLOAT, 0, &v_tablero[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &v_textura[0]);

	glDrawArrays(GL_QUADS, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}
