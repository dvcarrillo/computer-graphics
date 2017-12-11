/*******************************************************************/
// David Vargas Carrillo
// Informatica Grafica - Practica 4
// Diciembre 2017
//
// Fichero: cargadorBMP.cc
// Declaraciones de los metodos de la clase CargadorBMP
/*******************************************************************/

#include "cargadorBMP.h"

/*******************************************************************/
//
/*******************************************************************/

CargadorBMP::CargadorBMP() {
	width = 0;
	height = 0;
	dataPos = 0;
	imageSize = 0;
}

/*******************************************************************/
//
/*******************************************************************/

CargadorBMP::~CargadorBMP() {
	if (data != NULL) delete[] data;
	data = NULL;
}

/*******************************************************************/
//
/*******************************************************************/

unsigned int CargadorBMP::GetWidth() {
	return width;
}
unsigned int CargadorBMP::GetHeight() {
	return height;
}
unsigned int CargadorBMP::GetImageSize() {
	return imageSize;
}
unsigned char * CargadorBMP::GetData() {
	return data;
}

/*******************************************************************/
//
/*******************************************************************/

GLuint CargadorBMP::LoadBMP(const char * imagepath) {
	// Apertura del fichero
	FILE * file = fopen(imagepath, "rb");
	if (!file) {
		std::cout << "No se pudo abrir la imagen\n";
		return 0;
	}

	// Lectura de la cabecera
	// Si no ha leido 54 bytes, imprimir error y salir
	if (fread(header, 1, 54, file) != 54) {
		std::cout << "No es un fichero BMP o es invalido\n";
		return false;
	}

	// El encabezado siempre empieza con BM, por lo que hay que 
	// comprobar si dicha condicion se cumple
	if (header[0] != 'B' || header[1] != 'M') {
		std::cout << "No es un fichero BMP o es invalido\n";
		return 0;
	}

	// Lectura de los datos de la imagen
	dataPos 	= *(int*)&(header[0x0A]);
	imageSize	= *(int*)&(header[0x22]);
	width 		= *(int*)&(header[0x12]);
	height		= *(int*)&(header[0x16]);

	// En caso de que algunos datos de la cabecera fueran incorrectos
	if (imageSize == 0) imageSize = width * height * 3;
	if (dataPos == 0) dataPos = 54;

	// Reserva de memoria para la imagen que se leera
	data = new unsigned char [imageSize];

	// Lectura del archivo
	fread(data, 1, imageSize, file);
	fclose(file);
}
