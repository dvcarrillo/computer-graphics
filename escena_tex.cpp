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
// Devuelve un valor entre 0 y 1 segun los parametros de entrada
/*******************************************************************/

float NormalizarTexel (float min, float max, float value) {
	float minimo = min;
	float maximo = max;

	if (min > max) {
		float aux = maximo;
		maximo = minimo;
		minimo = aux;
	}

	return ((value - minimo) / (maximo - minimo));
}

/*******************************************************************/
//
/*******************************************************************/

EscenaTex::EscenaTex() {
	float min_x = -40.0f, max_x = 40.0f;
	float min_y = 40.0f, max_y = -40.0f;

	// Dimension X (desde 0 hasta 40)
	for (float x = -40.0f; x < 40.0f; x += 10.0f) {
		// Dimension Y (desde 0 hasta 40)
		for (float y = 40.0f; y > -40.0f; y -= 10.0f) {
			// vertice 1
			v_tablero.push_back(x);
			v_tablero.push_back(y);
			v_textura.push_back(NormalizarTexel(min_x, max_x, x));
			v_textura.push_back(NormalizarTexel(min_y, max_y, y));

			// vertice 2
			v_tablero.push_back(x + 10.0f);
			v_tablero.push_back(y);
			v_textura.push_back(NormalizarTexel(min_x, max_x, x + 10.0f));
			v_textura.push_back(NormalizarTexel(min_y, max_y, y));

			// vertice 3
			v_tablero.push_back(x + 10.0f);
			v_tablero.push_back(y - 10.0f);
			v_textura.push_back(NormalizarTexel(min_x, max_x, x + 10.0f));
			v_textura.push_back(NormalizarTexel(min_y, max_y, y - 10.0f));

			// vertice 4
			v_tablero.push_back(x);
			v_tablero.push_back(y - 10.0f);
			v_textura.push_back(NormalizarTexel(min_x, max_x, x));
			v_textura.push_back(NormalizarTexel(min_y, max_y, y - 10.0f));
		}
	}
}

/*******************************************************************/
//
/*******************************************************************/

EscenaTex::EscenaTex(const char * imagepath) {
	float min_x = -40, max_x = 40;
	float min_y = 40, max_y = -40;

	// Dimension X (desde 0 hasta 40)
	for (int x = -40; x < 40; x += 5) {
		// Dimension Y (desde 0 hasta 40)
		for (int y = 40; y > -40; y -= 5) {
			// vertice 1
			v_tablero.push_back(x);
			v_tablero.push_back(y);
			v_textura.push_back(NormalizarTexel(min_x, max_x, x));
			v_textura.push_back(NormalizarTexel(min_y, max_y, y));

			// vertice 2
			v_tablero.push_back(x + 5);
			v_tablero.push_back(y);
			v_textura.push_back(NormalizarTexel(min_x, max_x, x + 5));
			v_textura.push_back(NormalizarTexel(min_y, max_y, y));

			// vertice 3
			v_tablero.push_back(x + 5);
			v_tablero.push_back(y + 5);
			v_textura.push_back(NormalizarTexel(min_x, max_x, x + 5));
			v_textura.push_back(NormalizarTexel(min_y, max_y, y + 5));

			// vertice 4
			v_tablero.push_back(x);
			v_tablero.push_back(y + 5);
			v_textura.push_back(NormalizarTexel(min_x, max_x, x));
			v_textura.push_back(NormalizarTexel(min_y, max_y, y + 5));
		}
	}
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

	glDrawArrays(GL_QUADS, 0, v_tablero.size());

	glDisableClientState(GL_VERTEX_ARRAY);
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_TEXTURE_2D);
}
