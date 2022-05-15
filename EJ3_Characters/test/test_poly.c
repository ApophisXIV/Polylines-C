#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

#include "../inc/characters.h"
#include "../inc/poly.h"

bool test_poly() {

	const float puntos[3][2] = {{0, 0}, {1, 0}, {0, 1}};

	polilinea_t *p1 = polilinea_crear(puntos, 3);
	if (p1 == NULL) {
		fprintf(stdout, "Error en creacion de polilinea\n");
		return false;
	}

	float x, y;

	assert(polilinea_cantidad_puntos(p1) == 3);
	assert(!polilinea_obtener_punto(p1, 3, &x, &y));
	assert(polilinea_obtener_punto(p1, 1, &x, &y));
	assert(x == 1 && y == 0);

	polilinea_t *p2 = polilinea_crear_vacia(2);
	if (p2 == NULL) {
		fprintf(stdout, "Error en creacion de polilinea\n");
		return false;
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
		fprintf(stdout, "Error en creacion de polilinea\n");
		return false;
	}

	assert(polilinea_cantidad_puntos(p2) == 3);
	assert(polilinea_obtener_punto(p2, 2, &x, &y));
	assert(x == 0 && y == 1);

	polilinea_destruir(p2);

	assert(polilinea_crear(puntos, 1UL << 50) == NULL);

	return true;
}

int main(void) {
	if (!test_poly()) return 1;
	return 0;
}
