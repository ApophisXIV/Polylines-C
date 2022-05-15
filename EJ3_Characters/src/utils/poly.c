/**
 * @file poly.c
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief Polyline implementation
 * @version 0.1
 * @date 2022-05-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#include "../../inc/poly.h"
#include "../../inc/characters.h"
#include <stdlib.h>

/* --------------------------------- Macros --------------------------------- */
#define N_FILAS(c) (sizeof(c) / sizeof(c[0]))

/* ----------------------------------- TDA ---------------------------------- */
struct polilinea {
	float (*puntos)[2];
	size_t n;
};

/* ------------------------ Constructor & Destructor ------------------------ */
polilinea_t *polilinea_crear_vacia(size_t n) {
	if (n == 0) return NULL;

	polilinea_t *poly = malloc(sizeof(polilinea_t));
	if (poly == NULL) return NULL;

	poly->puntos = malloc(n * sizeof(float[2]));
	if (poly->puntos == NULL) {
		free(poly);
		return NULL;
	}

	poly->n = n;
	return poly;
}

polilinea_t *polilinea_crear(const float puntos[][2], size_t n) {
	if (n == 0) return NULL;

	polilinea_t *poly = polilinea_crear_vacia(n);
	if (poly == NULL) return NULL;

	for (size_t i = 0; i < n; i++)
		polilinea_setear_punto(poly, i, puntos[i][0], puntos[i][1]);

	return poly;
}

void polilinea_destruir(polilinea_t *polilinea) {
	if (polilinea == NULL) return;

	free(polilinea->puntos);
	free(polilinea);
}

/* --------------------------------- Getters -------------------------------- */
bool polilinea_obtener_punto(const polilinea_t *polilinea, size_t pos, float *x, float *y) {
	if (polilinea == NULL || pos >= polilinea_cantidad_puntos(polilinea) || x == NULL || y == NULL) return false;
	*x = polilinea->puntos[pos][0];
	*y = polilinea->puntos[pos][1];
	return true;
}

size_t polilinea_cantidad_puntos(const polilinea_t *polilinea) {
	if (polilinea == NULL) return 0;
	return polilinea->n;
}

/* --------------------------------- Setters -------------------------------- */
bool polilinea_setear_punto(polilinea_t *polilinea, size_t pos, float x, float y) {
	if (polilinea == NULL || pos >= polilinea_cantidad_puntos(polilinea)) return false;
	polilinea->puntos[pos][0] = x;
	polilinea->puntos[pos][1] = y;
	return true;
}

/* ---------------------------------- Utils --------------------------------- */
polilinea_t *polilinea_clonar(const polilinea_t *polilinea) {
	if (polilinea == NULL) return NULL;
	return polilinea_crear((const float(*)[2])polilinea->puntos, polilinea_cantidad_puntos(polilinea));
}


// Dictionary to translate the character to the corresponding character points
typedef struct {
	const char caracter;
	const float (*puntos)[2];
	const size_t cantidad_puntos;
} caracteres_t;

polilinea_t *letra_a_polilinea(const char letra) {
	const char lower_input_c = letra >= 'A' && letra <= 'Z' ? letra + 32 : letra;
	static const caracteres_t caracteres[] = {
		{'a', caracter_a, N_FILAS(caracter_a)},
		{'b', caracter_b, N_FILAS(caracter_b)},
		{'c', caracter_c, N_FILAS(caracter_c)},
		{'d', caracter_d, N_FILAS(caracter_d)},
		{'e', caracter_e, N_FILAS(caracter_e)},
		{'f', caracter_f, N_FILAS(caracter_f)},
		{'g', caracter_g, N_FILAS(caracter_g)},
		{'h', caracter_h, N_FILAS(caracter_h)},
		{'i', caracter_i, N_FILAS(caracter_i)},
		{'j', caracter_j, N_FILAS(caracter_j)},
		{'k', caracter_k, N_FILAS(caracter_k)},
		{'l', caracter_l, N_FILAS(caracter_l)},
		{'m', caracter_m, N_FILAS(caracter_m)},
		{'n', caracter_n, N_FILAS(caracter_n)},
		{'o', caracter_o, N_FILAS(caracter_o)},
		{'p', caracter_p, N_FILAS(caracter_p)},
		{'q', caracter_q, N_FILAS(caracter_q)},
		{'r', caracter_r, N_FILAS(caracter_r)},
		{'s', caracter_s, N_FILAS(caracter_s)},
		{'t', caracter_t, N_FILAS(caracter_t)},
		{'u', caracter_u, N_FILAS(caracter_u)},
		{'v', caracter_v, N_FILAS(caracter_v)},
		{'w', caracter_w, N_FILAS(caracter_w)},
		{'x', caracter_x, N_FILAS(caracter_x)},
		{'y', caracter_y, N_FILAS(caracter_y)},
		{'z', caracter_z, N_FILAS(caracter_z)},
		{'0', caracter_0, N_FILAS(caracter_0)},
		{'1', caracter_1, N_FILAS(caracter_1)},
		{'2', caracter_2, N_FILAS(caracter_2)},
		{'3', caracter_3, N_FILAS(caracter_3)},
		{'4', caracter_4, N_FILAS(caracter_4)},
		{'5', caracter_5, N_FILAS(caracter_5)},
		{'6', caracter_6, N_FILAS(caracter_6)},
		{'7', caracter_7, N_FILAS(caracter_7)},
		{'8', caracter_8, N_FILAS(caracter_8)},
		{'9', caracter_9, N_FILAS(caracter_9)},
		{' ', caracter_espacio, N_FILAS(caracter_espacio)},
		{'.', caracter_derecha, N_FILAS(caracter_derecha)},
		{',', caracter_izquierda, N_FILAS(caracter_izquierda)},
		{'/', caracter_arriba, N_FILAS(caracter_arriba)},
		{'\\', caracter_abajo, N_FILAS(caracter_abajo)},
	};
	static const size_t n_caracteres = N_FILAS(caracteres);
	for (size_t i = 0; i < n_caracteres; i++)
		if (caracteres[i].caracter == lower_input_c)
			return polilinea_crear(caracteres[i].puntos, caracteres[i].cantidad_puntos);
	return NULL;
}