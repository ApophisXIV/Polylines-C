#include "color.h"

#define R_SHIFT 2
#define G_SHIFT 1

color_t color_crear(bool r, bool g, bool b) {
	return (color_t)(r << R_SHIFT | g << G_SHIFT | b);
}

void color_a_rgb(color_t c, uint8_t *r, uint8_t *g, uint8_t *b) {
	*r = ((c >> R_SHIFT) & 1) * 255;
	*g = ((c >> G_SHIFT) & 1) * 255;
	*b = (c & 1) * 255;
}
