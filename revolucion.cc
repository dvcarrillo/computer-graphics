/*******************************************************************/
// David Vargas Carrillo
// Informatica Grafica - Practica 2
// Octubre 2017
//
// Fichero: revolucion.cc
// Declaraciones de los metodos de la clase Revolucion
/*******************************************************************/

#include "revolucion.h"

/*******************************************************************/
//
/*******************************************************************/

Revolucion::Revolucion() {
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
	nvertices_perfil = 0;
	hay_tapas = false;
}

/*******************************************************************/
//
/*******************************************************************/

// Actualmente con los vertices definidos se dibuja un peon
void Revolucion::BuildPeon(float size) {
	// Se elimina el vector de lados por si hubiese alguno registrado
	lados.clear();
	lados1.clear();
	lados2.clear();
	// Se redefine el vector vertices teniendo en cuenta el multiplicador
	// de dimension
	vertices = {fabs((float)1.0*size), (float)-1.4*size, fabs((float)0.0*size),	// v0
				fabs((float)1.0*size),  (float)-1.1*size, fabs((float)0.0*size),	// v1
				fabs((float)0.5*size),  (float)-0.7*size, fabs((float)0.0*size),	// v2
				fabs((float)0.4*size),  (float)-0.4*size, fabs((float)0.0*size),	// v3
				fabs((float)0.4*size),  (float)0.5*size,  fabs((float)0.0*size),	// v4
				fabs((float)0.5*size),  (float)0.6*size,  fabs((float)0.0*size),	// v5
				fabs((float)0.3*size),  (float)0.6*size,  fabs((float)0.0*size),	// v6
				fabs((float)0.5*size),  (float)0.8*size,  fabs((float)0.0*size),	// v7
				fabs((float)0.55*size), (float)1.0*size,  fabs((float)0.0*size),	// v8
				fabs((float)0.5*size),  (float)1.2*size,  fabs((float)0.0*size),	// v9
				fabs((float)0.3*size),  (float)1.4*size,  fabs((float)0.0*size)};	// v10
	// La variable de vertices del perfil se ajusta segun lo introducido
	nvertices_perfil = vertices.size() / 3;
}

/*******************************************************************/
//
/*******************************************************************/

void Revolucion::RotarPerfil_Y(float angle) {
	// Almacenan las coordenadas de cada nuevo punto rotado
	float rotpunto_x, rotpunto_y, rotpunto_z;

	for (int i = 0; i < (nvertices_perfil * 3); i += 3)
	{
		// Rotacion de un punto original dado el angulo
		rotpunto_x = cos(angle) * vertices[i] + sin(angle) * vertices[i+2];
		rotpunto_y = vertices[i+1];
		rotpunto_z = -sin(angle) * vertices[i] + cos(angle) * vertices[i+2];
		// Introduccion del nuevo punto en el vector de vertices
		vertices.push_back(rotpunto_x);
		vertices.push_back(rotpunto_y);
		vertices.push_back(rotpunto_z);
	}
}

/*******************************************************************/
//
/*******************************************************************/

void Revolucion::BuildFigura(int num_vueltas) {
	// Angulo de rotacion en cada vuelta
	float angulo = 2 * M_PI / num_vueltas;
	// Iteracion por cada vuelta de la figura
	for (int vuelta = 1; vuelta <= num_vueltas; ++vuelta) {
		// Crea un nuevo perfil a partir de la rotacion del original
		RotarPerfil_Y(angulo * vuelta);
		// Iteradores para introducir los lados en el vector
		int v_a;
		int v_b;
		int v_c;
		// Se itera por los indices de un perfil, uniendo los vertices
		// del perfil rotado y su anterior
		for (int j = 0; j < nvertices_perfil - 1; j++) {
			// LADOS PARES
			// Asignacion de los indices de vertices a las variables
			v_a = j + nvertices_perfil * vuelta;
			v_b = v_a - nvertices_perfil;
			v_c = v_a + 1;
			// Introduccion de los indices en el vector lados
			lados.push_back(v_a);
			lados.push_back(v_b);
			lados.push_back(v_c);
			//lados.push_back(v_a);
			// Introduccion de los indices en el vector lados1 (ajedrez)
			lados1.push_back(v_a);
			lados1.push_back(v_b);
			lados1.push_back(v_c);
			//lados1.push_back(v_a);

			// LADOS IMPARES
			// Asignacion de los indices de vertices a las variables
			v_a = v_b;
			v_b = v_a + 1;
			v_c = (j + nvertices_perfil * vuelta) + 1;
			// Introduccion de los indices en el vector lados
			lados.push_back(v_a);
			lados.push_back(v_b);
			lados.push_back(v_c);
			//lados.push_back(v_a);
			// Introduccion de los indices en el vector lados2 (ajedrez)
			lados2.push_back(v_a);
			lados2.push_back(v_b);
			lados2.push_back(v_c);
			//lados2.push_back(v_a);
		}
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
}

/*******************************************************************/
//
/*******************************************************************/

void Revolucion::BuildTapas() {
	if (!hay_tapas) {
		// TAPA INFERIOR
		// Adicion del vertice central: se busca la posicion minima de y
		float pos_y = vertices[1];
		for (int i = 1; i < vertices.size(); i += 3)
			if (vertices[i] < pos_y) pos_y = vertices[i];

		vertices.push_back(0);		// X
		vertices.push_back(pos_y);	// Y
		vertices.push_back(0);		// Z

		// Se calcula el indice del vertice agregado
		int indice_central_inf = (vertices.size() / 3) - 1;

		// Iteradores para agregar los nuevos lados
		int v_a = 0;
		int v_b = nvertices_perfil;

	 	for (int i = nvertices_perfil*2; i < (vertices.size() / 3); i += nvertices_perfil) {
	 		// Adicion de los indices al vector de lados
		 	lados.push_back (v_a);
		 	lados.push_back (v_b);
		 	lados.push_back (indice_central_inf);
		 	//lados.push_back (v_a);
		 	// Adicion de los indices al vector de lados ajedrez
		 	if (i % 2 == 0) {
		 		lados1.push_back (v_a);
			 	lados1.push_back (v_b);
			 	lados1.push_back (indice_central_inf);
			 	//lados1.push_back (v_a);
		 	}
		 	else {
		 		lados2.push_back (v_a);
			 	lados2.push_back (v_b);
			 	lados2.push_back (indice_central_inf);
			 	//lados2.push_back (v_a);
		 	}
	 		v_a = v_b;
			v_b += nvertices_perfil;
		}

		// TAPA SUPERIOR
		// Adicion del vertice central superior
		pos_y = vertices[1];
		for (int i = 1; i < vertices.size(); i += 3)
			if (vertices[i] > pos_y) pos_y = vertices[i];

		vertices.push_back(0);		// X
		vertices.push_back(pos_y);	// Y
		vertices.push_back(0);		// Z

		// Se calcula el indice del vertice agregado
		indice_central_inf = (vertices.size() / 3) - 1;

		// Iteradores para agregar los nuevos lados
		v_a = nvertices_perfil - 1;
		v_b = v_a + nvertices_perfil;

	 	for (int i = nvertices_perfil*2; i < (vertices.size() / 3); i += nvertices_perfil) {
	 		// Adicion de los indices al vector de lados
		 	lados.push_back (v_a);
		 	lados.push_back (indice_central_inf);
		 	lados.push_back (v_b);
		 	//lados.push_back (v_a);

		 	// Adicion de los indices al vector de lados ajedrez
		 	if (i % 2 == 0) {
		 		lados1.push_back (v_a);
			 	lados1.push_back (indice_central_inf);
			 	lados1.push_back (v_b);
			 	//lados1.push_back (v_a);
		 	}
		 	else {
		 		lados2.push_back (v_a);
			 	lados2.push_back (indice_central_inf);
			 	lados2.push_back (v_b);
			 	//lados2.push_back (v_a);
		 	}
	 		v_a = v_b;
			v_b += nvertices_perfil;
		}
		hay_tapas = true;
	}
}

/*******************************************************************/
//
/*******************************************************************/

void Revolucion::DeleteTapas() {
	if (hay_tapas) {
		// TAPA INFERIOR
		// Elimina el vertice central inferior
		vertices.pop_back();
		vertices.pop_back();
		vertices.pop_back();

		for (int i = nvertices_perfil; i < (vertices.size() / 3); i += nvertices_perfil) {
	 		// Adicion de los indices al vector de lados
		 	lados.pop_back ();
		 	lados.pop_back ();
		 	lados.pop_back ();
		 	//lados.pop_back ();
		 	// Adicion de los indices al vector de lados ajedrez
		 	if (i % 2 == 0) {
		 		lados1.pop_back ();
			 	lados1.pop_back ();
			 	lados1.pop_back ();
			 	//lados1.pop_back ();
		 	}
		 	else {
		 		lados2.pop_back ();
			 	lados2.pop_back ();
			 	lados2.pop_back ();
			 	//lados2.pop_back ();
		 	}
		}

		// TAPA SUPERIOR
		// Elimina el vertice central superior
		vertices.pop_back();
		vertices.pop_back();
		vertices.pop_back();

		for (int i = nvertices_perfil*2; i < (vertices.size() / 3); i += nvertices_perfil) {
	 		// Adicion de los indices al vector de lados
		 	lados.pop_back ();
		 	lados.pop_back ();
		 	lados.pop_back ();
		 	//lados.pop_back ();
		 	// Adicion de los indices al vector de lados ajedrez
		 	if (i % 2 == 0) {
		 		lados1.pop_back ();
			 	lados1.pop_back ();
			 	lados1.pop_back ();
			 	//lados1.pop_back ();
		 	}
		 	else {
		 		lados2.pop_back ();
			 	lados2.pop_back ();
			 	lados2.pop_back ();
			 	//lados2.pop_back ();
		 	}
		}
		hay_tapas = false;
	}
}
