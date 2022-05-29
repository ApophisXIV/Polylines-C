#ifndef POLY_H
#define POLY_H

#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

#include "color.h"

struct polilinea;
typedef struct polilinea polilinea_t;

polilinea_t *polilinea_crear_vacia(size_t n);

void polilinea_destruir(polilinea_t *polilinea);

polilinea_t *leer_polilinea(FILE *f);

bool polilinea_setear_punto(polilinea_t *polilinea, size_t pos, float x, float y);

bool polilinea_setear_color(polilinea_t *polilinea, color_t color);

#endif	  // POLY_H