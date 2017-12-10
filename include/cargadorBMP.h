/*******************************************************************/
// David Vargas Carrillo
// Informatica Grafica - Practica 4
// Diciembre 2017
//
// Fichero: cargadorBMP.h
// Definiciones de la estructura y metodos de la clase CargadorBMP
/*******************************************************************/

#ifndef _CARGADOR_BMP_H
#define _CARGADOR_BMP_H

#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>

/**
 * CargadorBMP es una clase encargada de cargar y procesar imagenes
 * en formato BMP
 */

class CargadorBMP
{
private:
	// Variables para la lectura del encabezado del archivo
	unsigned char header[54];	// Cada fichero BMP empieza con un header de 54 bytes
	unsigned int dataPos;		// Posicion en el dichero donde empiezan los datos
	unsigned int width, height;
	unsigned int imageSize;		// width * height * 3

	// Informacion de color
	unsigned char * data;
public:
	// Constructor por defecto
	CargadorBMP();
	// Destructor
	~CargadorBMP();

	// Metodos GET
	unsigned int GetWidth();
	unsigned int GetHeight();
	unsigned int GetImageSize();
	unsigned char * GetData();

	// Funcion para cargar la imagen
	// Recibe:
	// 	imagepath: ruta de la imagen a cargar
	// Devuelve:
	// 	estado de la carga
	GLuint LoadBMP(const char * imagepath);
};

#endif
