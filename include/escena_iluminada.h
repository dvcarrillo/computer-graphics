/*******************************************************************/
// David Vargas Carrillo
// Informatica Grafica - Practica 4
// Diciembre 2017
//
// Fichero: escena_iluminada.h
// Definiciones de la estructura y metodos de la 
// clase EscenaIluminada
/*******************************************************************/

#ifndef _ESCENA_ILUMINADA_H
#define _ESCENA_ILUMINADA_H

#include "luz.h"
#include "cubo.h"
#include "tetraedro.h"
#include "esfera.h"
#include "objetoPLY.h"
#include "material.h"

/**
 * EscenaIluminada presenta una disposicion de objetos en el mundo
 * junto a un conjunto de luces
 *
 * Al tratarse de una clase de prueba para ver el comportamiento de
 * la luz en un escenario determinado, todos los objetos y propiedades
 * de la luz son estaticamente asignados en el constructor
 */

class EscenaIluminada
{
private:
	// Objetos presentes en la escena
	ObjetoPLY beethoven;

	// Luces en la escena
	int estado;		// 0 apagadas, 1 encendidas
	Luz luz1;
	Luz luz2;

	// Limites de movimiento de las luces
	float pos_x_actual;
	float dir_x_actual, dir_z_actual;
	// luz1 se mueve en el eje X desde las siguientes posiciones
	const float LIM_MIN_POSICION_LUZ = 20.0, LIM_MAX_POSICION_LUZ = -20.0;
	bool pos_adelante;
	// luz2 gira respecto al eje Y con estos valores para la componente Z
	const float LIM_MIN_DIRECCION_LUZ = 0.0, LIM_MAX_DIRECCION_LUZ = 1.0;
	bool dir_adelante;

	// Material del objeto
	int mat_seleccionado;
	Material *material1;
	Material *material2;
	Material *material3;
public:
	// Constructor por defecto
	EscenaIluminada();
	// Destructor
	~EscenaIluminada();

	// Cambia el modo de dibujado de sus objetos
	void SetModoDibujado(char modo);
	// Dibuja e ilumina la escena
	void DibujarEscena();

	// Mueve la luz 1
	void MoverLuz1();
	// Gira la luz 2
	void MoverLuz2();

	// Especifica el material a dibujar
	void SetMaterial(int num);
	// Apaga y enciende las luces en la escena
	void InterruptorLuces();
	// Modifica el modo de sombreado de las luces
	void InterruptorSombreado();
};

#endif
