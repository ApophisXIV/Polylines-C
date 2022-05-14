#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* ----------------------------------- TDA ---------------------------------- */
typedef struct {
	float (*puntos)[2];
	size_t n;
} polilinea_t;

/* ---------------------------- Getters & Setters --------------------------- */
size_t polilinea_cantidad_puntos(const polilinea_t *polilinea) {
	if (polilinea == NULL) return 0;
	return polilinea->n;
}

bool polilinea_obtener_punto(const polilinea_t *polilinea, size_t pos, float *x, float *y) {
	if (polilinea == NULL || pos >= polilinea_cantidad_puntos(polilinea) || x == NULL || y == NULL) return false;
	*x = polilinea->puntos[pos][0];
	*y = polilinea->puntos[pos][1];
	return true;
}
bool polilinea_setear_punto(polilinea_t *polilinea, size_t pos, float x, float y) {
	if (polilinea == NULL || pos >= polilinea_cantidad_puntos(polilinea)) return false;
	polilinea->puntos[pos][0] = x;
	polilinea->puntos[pos][1] = y;
	return true;
}

/* ----------------------- Constructor & Destructor ----------------------- */
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

/* ---------------------------------- Utils --------------------------------- */
polilinea_t *polilinea_clonar(const polilinea_t *polilinea) {
	if (polilinea == NULL) return NULL;
	return polilinea_crear((const float (*)[2])polilinea->puntos, polilinea_cantidad_puntos(polilinea));
}

int main(void) {
	const float puntos[3][2] = {{0, 0}, {1, 0}, {0, 1}};

	polilinea_t *p1 = polilinea_crear(puntos, 3);
	if (p1 == NULL) {
		fprintf(stderr, "Error en creacion de polilinea\n");
		return 1;
	}

	float x, y;

	assert(polilinea_cantidad_puntos(p1) == 3);
	assert(!polilinea_obtener_punto(p1, 3, &x, &y));
	assert(polilinea_obtener_punto(p1, 1, &x, &y));
	assert(x == 1 && y == 0);

	polilinea_t *p2 = polilinea_crear_vacia(2);
	if (p2 == NULL) {
		fprintf(stderr, "Error en creacion de polilinea\n");
		return 1;
	}

	assert(polilinea_cantidad_puntos(p2) == 2);
	assert(!polilinea_setear_punto(p2, 2, 0, 0));
	assert(polilinea_setear_punto(p2, 1, 3, 1));
	assert(polilinea_obtener_punto(p2, 1, &x, &y));
	assert(x == 3 && y == 1);

	polilinea_destruir(p2);

	p2 = polilinea_clonar(p1);
	polilinea_destruir(p1);
	if (p2 == NULL) {
		fprintf(stderr, "Error en creacion de polilinea\n");
		return 1;
	}

	assert(polilinea_cantidad_puntos(p2) == 3);
	assert(polilinea_obtener_punto(p2, 2, &x, &y));
	assert(x == 0 && y == 1);

	polilinea_destruir(p2);

	assert(polilinea_crear(puntos, 1UL << 50) == NULL);

	return 0;
}
