/*******************************************************************/
// David Vargas Carrillo
// Informatica Grafica - Practica 4
// Octubre 2017
//
// Fichero: objeto3D.cc
// Declaraciones de los metodos de la clase objeto3D
/*******************************************************************/

#include "objeto3D.h"

/*******************************************************************/
//
/*******************************************************************/

Objeto3D::Objeto3D() {
	vertices = {};
	lados = {};
	lados1 = {};
	lados2 = {};
	color1 = {};
	color2 = {};
	n_vertices = {};
	n_lados = {};
	puntos = false;
	alambre = false;
	solido = true;
	ajedrez = false;
	child = {};
	tras_x = 0.0f; tras_y = 0.0f; tras_z = 0.0f;
	rota_x = 0.0f; rota_y = 0.0f; rota_z = 0.0f;
	esca_x = 1.0f; esca_y = 1.0f; esca_z = 1.0f;
	LIM_MIN_MOVIMIENTO = 1.0f;
	LIM_MAX_MOVIMIENTO = 1.0f;
	MAGNITUD_PASO = 0.0f;
	posicion_movimiento = 0.0f;
	adelante = true;
	rot_cuerpo = false;
	noot = false;
	mov_pingu = false;
}

/*******************************************************************/
//
/*******************************************************************/

void Objeto3D::AddObjeto(Objeto3D *obj3D) {
	child.push_back(obj3D);
}

/*******************************************************************/
//
/*******************************************************************/

void Objeto3D::CalcularNormales() {
	// Vectores de vertices y lados usando vertex3f
	// Necesarios para calcular de forma correcta las normales
	std::vector<_vertex3f> vertex_vertices, vertex_lados;
	std::vector<_vertex3f> nlados_vertex;		// Normales de lados (vertex3f)
	std::vector<_vertex3f> nvertices_vertex;	// Normales de vertices (vertex3f)

	// Representa un lado del objeto
	_vertex3f lado;
	// Rellenar el vector de lados de vertex3f
	for (int i = 0; i < lados.size(); i += 3) {
		lado.x = lados[i];
		lado.y = lados[i + 1];
		lado.z = lados[i + 2];
		vertex_lados.push_back(lado);
	}

	// Representa un vertice del objeto
	_vertex3f vert;
	// Rellenar el vector de vertices de vertex3f
	for (int i = 0; i < vertices.size(); i += 3) {
		vert.x = vertices[i];
		vert.y = vertices[i + 1];
		vert.z = vertices[i + 2];
		vertex_vertices.push_back(vert);
	}

	// CALCULO DE LAS NORMALES DE CARAS
	_vertex3f p0, p1, p2;
	for (int i = 0; i < vertex_lados.size(); ++i) {
		// Obtencion de los tres puntos que representan un lado
		p0 = vertex_vertices[vertex_lados[i].x];
		p1 = vertex_vertices[vertex_lados[i].y];
		p2 = vertex_vertices[vertex_lados[i].z];
		// Diferencia con respecto a p0 de ambos puntos
		_vertex3f diff_1 = p1 - p0;
		_vertex3f diff_2 = p2 - p0;
		// Producto vectorial de los vectores diferencia para obtener
		// la normal de la cara
		_vertex3f normal_cara = diff_1.cross_product(diff_2);
		// Se normaliza la normal obtenida
		normal_cara.normalize();
		// Se introduce la normal en el vector de normales de caras
		nlados_vertex.push_back(normal_cara);
	}

	// CALCULO DE LAS NORMALES DE VERTICES
	nvertices_vertex.resize(vertices.size() / 3);
	for (int i = 0; i < vertex_lados.size(); i++) {
		// Calculo de las normales de los vertices
		nvertices_vertex[vertex_lados[i].x] += nlados_vertex[i];
		nvertices_vertex[vertex_lados[i].y] += nlados_vertex[i];
		nvertices_vertex[vertex_lados[i].z] += nlados_vertex[i];
	}

	// Se transforman los vectores de normales con vertex3f a los
	// vectores de normales propios de nuestra clase
	for (int i = 0; i < nlados_vertex.size(); ++i) {
		n_lados.push_back(nlados_vertex[i].x);
		n_lados.push_back(nlados_vertex[i].y);
		n_lados.push_back(nlados_vertex[i].z);
	}
	for (int i = 0; i < nvertices_vertex.size(); ++i) {
		n_vertices.push_back(nvertices_vertex[i].x);
		n_vertices.push_back(nvertices_vertex[i].y);
		n_vertices.push_back(nvertices_vertex[i].z);
	}
}

/*******************************************************************/
//
/*******************************************************************/

void Objeto3D::SetTransformaciones(float t_x, float t_y, float t_z, 
	float r_x, float r_y, float r_z, float e_x, float e_y, float e_z) {
	tras_x = t_x; tras_y = t_y; tras_z = t_z;
	rota_x = r_x; rota_y = r_y; rota_z = r_z;
	esca_x = e_x; esca_y = e_y; esca_z = e_z;
}

/*******************************************************************/
//
/*******************************************************************/

void Objeto3D::SetModoDibujado(char modo) {
	switch(modo) {
		case('p'):	// puntos
			puntos = true;
			alambre = false;
			solido = false;
			ajedrez = false;
			break;
		case('f'):	// solido
			puntos = false;
			alambre = false;
			solido = true;
			ajedrez = false;
			break;
		case ('c'):	// ajedrez
			puntos = false;
			alambre = false;
			solido = false;
			ajedrez = true;
			break;
		default:	// alambre
			puntos = false;
			alambre = true;
			solido = false;
			ajedrez = false;
	}

	for (int i = 0; i < child.size(); i++) {
			child[i]->SetModoDibujado(modo);
		}
}

/*******************************************************************/
//
/*******************************************************************/

void Objeto3D::SetColor(float r, float g, float b) {
	color_r = r;
	color_g = g;
	color_b = b;
}

/*******************************************************************/
//
/*******************************************************************/

void Objeto3D::SetMaterial(Material *mat) {
	material = mat;
}

/*******************************************************************/
//
/*******************************************************************/

void Objeto3D::EnableMaterial() {
	material->Enable();
}

/*******************************************************************/
//
/*******************************************************************/

void Objeto3D::Dibujar() {
	// Dibujar los vertices
	glVertexPointer(3, GL_FLOAT, 0, &vertices[0]);
	// Indicar el vector de normales de vertices
	glNormalPointer(GL_FLOAT, 0, &n_vertices[0]);

	// Iniciar parametros GL
	/* glLineWidth(2); */
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);

	// Dibujado en modo ajedrez
	if (ajedrez && !solido && !puntos && !alambre) {
		// Se dibuja por separado cada cara asignandole un color
		glEnableClientState(GL_COLOR_ARRAY);
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glColorPointer(3, GL_FLOAT, 0, &color1[0]);
		glDrawElements(GL_TRIANGLES, lados1.size(), GL_UNSIGNED_INT, &lados1[0]);

		glColorPointer(3, GL_FLOAT, 0, &color2[0]);
		glDrawElements(GL_TRIANGLES, lados2.size(), GL_UNSIGNED_INT, &lados2[0]);

		glDisableClientState(GL_COLOR_ARRAY);
	}
	else{ 
		// Dibujado en modo solido
		if (!ajedrez && solido && !puntos && !alambre) {
		 	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		 	
		}
		// Dibujado en modo puntos
		else if (!ajedrez && !solido && puntos && !alambre) {
			glPointSize(4);
			glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
		}
		// Dibujado en modo alambre
		else {
		 	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}
		glDrawElements(GL_TRIANGLES, lados.size(),
		 	GL_UNSIGNED_INT, &lados[0]);
	}

	// Desactivar parametros GL
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

/*******************************************************************/
//
/*******************************************************************/

void Objeto3D::DibujarSolido(float r, float g, float b) {
	glColor3b(r, g, b);
	Dibujar();
}

/*******************************************************************/
//
/*******************************************************************/

void Objeto3D::DibujadoJerarquico() {
	glPushMatrix();
		if (mov_pingu) {
			if (adelante) {
				posicion_movimiento += MAGNITUD_PASO;
				if (posicion_movimiento >= LIM_MAX_MOVIMIENTO)
					adelante = false;
			} else {
				posicion_movimiento -= MAGNITUD_PASO;
				if (posicion_movimiento <= LIM_MIN_MOVIMIENTO)
					adelante = true;
			}
			glTranslatef(0.0f, 0.0f, posicion_movimiento);
		} else if (noot) {
			if (adelante) {
				posicion_movimiento += MAGNITUD_PASO;
				if (posicion_movimiento >= LIM_MAX_MOVIMIENTO)
					adelante = false;
			} else {
				posicion_movimiento -= MAGNITUD_PASO;
				if (posicion_movimiento <= LIM_MIN_MOVIMIENTO)
					adelante = true;
			}
		} else if (rot_cuerpo) {
			if (adelante) {
				posicion_movimiento += MAGNITUD_PASO;
				if (posicion_movimiento >= LIM_MAX_MOVIMIENTO)
					adelante = false;
			} else {
				posicion_movimiento -= MAGNITUD_PASO;
				if (posicion_movimiento <= LIM_MIN_MOVIMIENTO)
					adelante = true;
			}
			glRotatef(posicion_movimiento, 0.0f, 1.0f, 0.0f);
		}
		glPushMatrix();
			// Transformaciones de la figura dibujada
			glScalef(esca_x, esca_y, esca_z);		// Escalado (vector esca)
			glTranslatef(tras_x, tras_y, tras_z);	// Traslacion (vector tras)
			if (noot) glScalef(1.0f, 1.0f, posicion_movimiento);
			glRotatef(rota_x, 1.0f, 0.0f, 0.0f);	// Rotacion en X
			glRotatef(rota_y, 0.0f, 1.0f, 0.0f);	// Rotacion en Y
			glRotatef(rota_z, 0.0f, 0.0f, 1.0f);	// Rotacion en Z
			// Dibujado de la figura actual
			DibujarSolido(color_r, color_g, color_b);
		glPopMatrix();
		
		// Dibujado de los hijos de la figura
		for (int i = 0; i < child.size(); i++) {
			child[i]->DibujadoJerarquico();
		}
	glPopMatrix();
}

/*******************************************************************/
//
/*******************************************************************/

void Objeto3D::EnableRotacion(float v) {
	LIM_MIN_MOVIMIENTO = -45.0f;
	LIM_MAX_MOVIMIENTO = 45.0f;
	MAGNITUD_PASO = v;
	(rot_cuerpo == false) ? rot_cuerpo = true : rot_cuerpo = false;
	std::cout << "Figura animada: Rotacion activada" << endl;
}
void Objeto3D::EnableDesplazamiento(float v) {
	LIM_MIN_MOVIMIENTO = -50.0f;
	LIM_MAX_MOVIMIENTO = 25.0f;
	MAGNITUD_PASO = v;
	(mov_pingu == false) ? mov_pingu = true : mov_pingu = false;
	std::cout << "Figura animada: Desplazamiento activado" << endl;
}
void Objeto3D::EnableNoot(float v) {
	LIM_MIN_MOVIMIENTO = 1.0f;
	LIM_MAX_MOVIMIENTO = 4.0f;
	MAGNITUD_PASO = v;
	(noot == false) ? noot = true : noot = false;
	std::cout << "Figura animada: n00t activado" << endl;
}
