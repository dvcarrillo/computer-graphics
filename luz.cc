/*******************************************************************/
// David Vargas Carrillo
// Informatica Grafica - Practica 4
// Diciembre 2017
//
// Fichero: luz.cc
// Declaraciones de los metodos de la clase Luz
/*******************************************************************/

#include "luz.h"

/*******************************************************************/
//
/*******************************************************************/

Luz::Luz() {
	posicion[0] = 0.0; posicion[1] = 0.0;
	posicion[2] = 0.0; posicion[3] = 0.0;

	direccion[0] = 0.0; direccion[1] = 0.0;
	direccion[2] = 0.0; direccion[3] = 0.0;

	color_ambiente[0] = 0.0; color_ambiente[1] = 0.0;
	color_ambiente[2] = 0.0; color_ambiente[3] = 1.0;

	color_difuso[0] = 0.0; color_difuso[1] = 0.0;
	color_difuso[2] = 0.0; color_difuso[3] = 1.0;

	color_especular[0] = 0.0; color_especular[1] = 0.0;
	color_especular[2] = 0.0; color_especular[3] = 1.0;

	numero_luz = -1;
	type = -1;
	modo_sombreado = 1;
}


/*******************************************************************/
//
/*******************************************************************/

Luz::Luz(int num) {
	posicion[0] = 0.0; posicion[1] = 0.0;
	posicion[2] = 0.0; posicion[3] = 0.0;

	direccion[0] = 0.0; direccion[1] = 0.0;
	direccion[2] = 0.0; direccion[3] = 0.0;

	color_ambiente[0] = 0.0; color_ambiente[1] = 0.0;
	color_ambiente[2] = 0.0; color_ambiente[3] = 1.0;

	color_difuso[0] = 0.0; color_difuso[1] = 0.0;
	color_difuso[2] = 0.0; color_difuso[3] = 1.0;

	color_especular[0] = 0.0; color_especular[1] = 0.0;
	color_especular[2] = 0.0; color_especular[3] = 1.0;

	if ((num >= 0) && (num <= 7)) {
		numero_luz = num;
	} else {
		numero_luz = -1;
	}
	type = -1;
	modo_sombreado = 1;
}

/*******************************************************************/
//
/*******************************************************************/

void Luz::SetPosicion(float pos_x, float pos_y, float pos_z) {
	GLfloat nueva_pos[4] = {pos_x, pos_y, pos_z, 1.0};
	std::copy(nueva_pos, nueva_pos + 4, posicion);
	GLfloat nueva_dir[4] = {0.0, 0.0, 0.0, 0.0};
	std::copy(nueva_dir, nueva_dir + 4, direccion);
	type = 1;
}

/*******************************************************************/
//
/*******************************************************************/

void Luz::SetDireccion(float vec_x, float vec_y, float vec_z) {
	GLfloat nueva_dir[4] = {vec_x, vec_y, vec_z, 0.0};
	std::copy(nueva_dir, nueva_dir + 4, direccion);
	GLfloat nueva_pos[4] = {0.0, 0.0, 0.0, 1.0};
	std::copy(nueva_pos, nueva_pos + 4, posicion);
	type = 0;
}

/*******************************************************************/
//
/*******************************************************************/

void Luz::SetColorDifuso(float dif_r, float dif_g, float dif_b) {
	GLfloat nuevo_cdifuso[4] = {dif_r, dif_g, dif_b, 1.0};
	std::copy(nuevo_cdifuso, nuevo_cdifuso + 4, color_difuso);
}

/*******************************************************************/
//
/*******************************************************************/

void Luz::SetColorEspecular(float esp_r, float esp_g, float esp_b) {
	GLfloat nuevo_cespecular[4] = {esp_r, esp_g, esp_b, 1.0};
	std::copy(nuevo_cespecular, nuevo_cespecular + 4, color_especular);
}

/*******************************************************************/
//
/*******************************************************************/

void Luz::SetColorAmbiente(float amb_r, float amb_g, float amb_b) {
	GLfloat nuevo_cambiente[4] = {amb_r, amb_g, amb_b, 1.0};
	std::copy(nuevo_cambiente, nuevo_cambiente + 4, color_ambiente);
}

/*******************************************************************/
//
/*******************************************************************/

void Luz::SetNumeroLuz(int num) {
	if ((num >= 0) && (num <= 7)) {
		if (numero_luz == -1)
			numero_luz = num;
		else {
			std::cout << "ATENCION: se ha cambiado el numero de luz ";
			std::cout << numero_luz << " por " << num << std::endl;
			Disable();
			numero_luz = num;
			Enable();
		}
	} else {
		std::cout << "ERROR: Valor invalido para set numero de luz" << std::endl;
	}
}

/*******************************************************************/
//
/*******************************************************************/

void Luz::CambiarModoSombreado() {
	(modo_sombreado == 0) ? modo_sombreado = 1 : modo_sombreado = 0;
}

/*******************************************************************/
//
/*******************************************************************/

void Luz::Enable() {
	// Activacion de propiedades de OpenGL
	glEnable(GL_SMOOTH);		// Activar el modo sombreado suave
	glEnable(GL_LIGHTING);		// Activar el modelo de iluminacion
	glEnable(GL_DEPTH_TEST);	// Activar el buffer de profundidad
	if (modo_sombreado == 0)	// Aplicar a OpenGL el modo de sombreado
		glShadeModel(GL_FLAT);
	else
		glShadeModel(GL_SMOOTH);

	// Asignacion de propiedades dependientes del numero de luz
	switch (numero_luz) {
		case 0:
			glLightfv(GL_LIGHT0, GL_AMBIENT, color_ambiente);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, color_difuso);
			glLightfv(GL_LIGHT0, GL_SPECULAR, color_especular);
			if (type == 1)
				glLightfv(GL_LIGHT0, GL_POSITION, posicion);
			else
				glLightfv(GL_LIGHT0, GL_POSITION, direccion);
			glEnable(GL_LIGHT0);
			break;
		case 1:
			glLightfv(GL_LIGHT1, GL_AMBIENT, color_ambiente);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, color_difuso);
			glLightfv(GL_LIGHT1, GL_SPECULAR, color_especular);
			if (type == 1)
				glLightfv(GL_LIGHT1, GL_POSITION, posicion);
			else
				glLightfv(GL_LIGHT1, GL_POSITION, direccion);
			glEnable(GL_LIGHT1);
			break;
		case 2:
			glLightfv(GL_LIGHT2, GL_AMBIENT, color_ambiente);
			glLightfv(GL_LIGHT2, GL_DIFFUSE, color_difuso);
			glLightfv(GL_LIGHT2, GL_SPECULAR, color_especular);
			if (type == 1)
				glLightfv(GL_LIGHT2, GL_POSITION, posicion);
			else
				glLightfv(GL_LIGHT2, GL_POSITION, direccion);
			glEnable(GL_LIGHT2);
			break;
		case 3:
			glLightfv(GL_LIGHT3, GL_AMBIENT, color_ambiente);
			glLightfv(GL_LIGHT3, GL_DIFFUSE, color_difuso);
			glLightfv(GL_LIGHT3, GL_SPECULAR, color_especular);
			if (type == 1)
				glLightfv(GL_LIGHT3, GL_POSITION, posicion);
			else
				glLightfv(GL_LIGHT3, GL_POSITION, direccion);
			glEnable(GL_LIGHT3);
			break;
		case 4:
			glLightfv(GL_LIGHT4, GL_AMBIENT, color_ambiente);
			glLightfv(GL_LIGHT4, GL_DIFFUSE, color_difuso);
			glLightfv(GL_LIGHT4, GL_SPECULAR, color_especular);
			if (type == 1)
				glLightfv(GL_LIGHT4, GL_POSITION, posicion);
			else
				glLightfv(GL_LIGHT4, GL_POSITION, direccion);
			glEnable(GL_LIGHT4);
			break;
		case 5:
			glLightfv(GL_LIGHT5, GL_AMBIENT, color_ambiente);
			glLightfv(GL_LIGHT5, GL_DIFFUSE, color_difuso);
			glLightfv(GL_LIGHT5, GL_SPECULAR, color_especular);
			if (type == 1)
				glLightfv(GL_LIGHT5, GL_POSITION, posicion);
			else
				glLightfv(GL_LIGHT5, GL_POSITION, direccion);
			glEnable(GL_LIGHT5);
			break;
		case 6:
			glLightfv(GL_LIGHT6, GL_AMBIENT, color_ambiente);
			glLightfv(GL_LIGHT6, GL_DIFFUSE, color_difuso);
			glLightfv(GL_LIGHT6, GL_SPECULAR, color_especular);
			if (type == 1)
				glLightfv(GL_LIGHT6, GL_POSITION, posicion);
			else
				glLightfv(GL_LIGHT6, GL_POSITION, direccion);
			glEnable(GL_LIGHT6);
			break;
		case 7:
			glLightfv(GL_LIGHT7, GL_AMBIENT, color_ambiente);
			glLightfv(GL_LIGHT7, GL_DIFFUSE, color_difuso);
			glLightfv(GL_LIGHT7, GL_SPECULAR, color_especular);
			if (type == 1)
				glLightfv(GL_LIGHT7, GL_POSITION, posicion);
			else
				glLightfv(GL_LIGHT7, GL_POSITION, direccion);
			glEnable(GL_LIGHT7);
			break;
		default:
			std::cout << "ERROR: se ha intentado activar una luz con un "
			<< "numero no definido o incorrecto" << std::endl;	
	}
}

/*******************************************************************/
//
/*******************************************************************/

void Luz::Disable() {
	// Se desactiva la luz vinculada a OpenGL
	switch (numero_luz) {
		case 0:
			glDisable(GL_LIGHT0);
			break;
		case 1:
			glDisable(GL_LIGHT1);
			break;
		case 2:
			glDisable(GL_LIGHT2);
			break;
		case 3:
			glDisable(GL_LIGHT3);
			break;
		case 4:
			glDisable(GL_LIGHT4);
			break;
		case 5:
			glDisable(GL_LIGHT5);
			break;
		case 6:
			glDisable(GL_LIGHT6);
			break;
		case 7:
			glDisable(GL_LIGHT7);
			break;
		default:
			std::cout << "ERROR: se ha intentado desactivar una luz con un "
			<< "numero no definido o incorrecto" << std::endl;	
	}

	// Se desactivan las propiedades que permiten la ilumacion
	// De este modo, el resto de figuras apareceran como se pretende
	glDisable(GL_SMOOTH);		// Activar el modo sombreado suave
	glDisable(GL_LIGHTING);		// Activar el modelo de iluminacion
}

/*******************************************************************/
//
/*******************************************************************/

void Luz::ImprimeInformacion() {
	std::cout << "\n---------------------------------------\n";
	std::cout << "INFORMACION DE LA LUZ " << numero_luz << " :\n\n";
	std::cout << "Posicion: ";
	for (int i = 0; i < 4; ++i) {
		std::cout << posicion[i] << " ";
	}
	std::cout << "\nDireccion: ";
	for (int i = 0; i < 4; ++i) {
		std::cout << direccion[i] << " ";
	}
	std::cout << "\nModo: " << type << std::endl;
	std::cout << "Colores:\n\tDifuso: ";
	for (int i = 0; i < 4; ++i) {
		std::cout << color_difuso[i] << " ";
	}
	std::cout << "\n\tEspecular: ";
	for (int i = 0; i < 4; ++i) {
		std::cout << color_especular[i] << " ";
	}
	std::cout << "\n\tAmbiente: ";
	for (int i = 0; i < 4; ++i) {
		std::cout << color_ambiente[i] << " ";
	}
	std::cout << "\n---------------------------------------\n";
}

/*******************************************************************/
//
/*******************************************************************/

void Luz::DibujaPosicion() {
	Cubo cubo_emisor;
	cubo_emisor.BuildCubo(3);

	glPushMatrix();
		glTranslatef(posicion[0], posicion[1], posicion[2]);
		cubo_emisor.Dibujar();
	glPopMatrix();
}
