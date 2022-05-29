#include "../../inc/poly.h"
#include <stdint.h>
#include <stdio.h>

struct polilinea {
	char foo;	 // "Struct has no members" error -> I use a char to avoid it
};

polilinea_t *polilinea_crear_vacia(size_t n) {
	printf("POLILINEA N=%zd\n", n);
	static polilinea_t x;
	return &x;
}

void polilinea_destruir(polilinea_t *polilinea) {}

bool polilinea_setear_punto(polilinea_t *polilinea, size_t pos, float x, float y) {
	printf("POLILINEA[%zd] = (%.2f, %.2f)\n", pos, x, y);
	return true;
}

bool polilinea_setear_color(polilinea_t *polilinea, color_t color) {
	uint8_t r, g, b;
	color_a_rgb(color, &r, &g, &b);
	printf("POLILINEA COLOR: (%d, %d, %d)\n", r, g, b);
	return true;
}

#define POLY_R_COLOR_SHIFT 15
#define POLY_G_COLOR_SHIFT 14
#define POLY_B_COLOR_SHIFT 13

#define POLY_N_POINTS_MASK 0x03FF
#define GET_POLY_N_POINTS(poly_header) (poly_header & POLY_N_POINTS_MASK)

polilinea_t *leer_polilinea(FILE *f) {
	if (f == NULL) return NULL;

	uint16_t poly_header;
	if (fread(&poly_header, sizeof(uint16_t), 1, f) != 1) return NULL;

	color_t c = color_crear(
		(poly_header >> POLY_R_COLOR_SHIFT) & 0x1,
		(poly_header >> POLY_G_COLOR_SHIFT) & 0x1,
		(poly_header >> POLY_B_COLOR_SHIFT) & 0x1);

	const uint16_t n_points = GET_POLY_N_POINTS(poly_header);

	float points[n_points][2];

	if (fread(points, sizeof(float) * 2, n_points, f) != n_points) return NULL;

	polilinea_t *poly = polilinea_crear_vacia(n_points);
	if (poly == NULL) return NULL;

	if (!polilinea_setear_color(poly, c)) {
		polilinea_destruir(poly);
		return NULL;
	}

	for (size_t i = 0; i < n_points; i++)
		if (!polilinea_setear_punto(poly, i, points[i][0], points[i][1])) {
			polilinea_destruir(poly);
			return NULL;
		}

	return poly;
}