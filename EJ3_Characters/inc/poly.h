/**
 * @file poly.h
 * @author Guido Rodriguez (guerodriguez@fi.uba.ar)
 * @brief Polyline class
 * @version 0.1
 * @date 2022-05-14
 *
 * @copyright Copyright (c) 2022
 *
 */

#ifndef _POLY_H_
#define _POLY_H_

#include <stddef.h>
#include <stdbool.h>

/* ----------------------------- Data structures ---------------------------- */
struct polilinea;
typedef struct polilinea polilinea_t;

/* ------------------------------- Prototypes ------------------------------- */
// Constructor & destructor
polilinea_t *polilinea_crear(const float puntos[][2], size_t n);
polilinea_t *polilinea_crear_vacia(size_t n);
void polilinea_destruir(polilinea_t *polilinea);

// Getters
bool polilinea_obtener_punto(const polilinea_t *polilinea, size_t pos, float *x, float *y);
size_t polilinea_cantidad_puntos(const polilinea_t *polilinea);

// Setters
bool polilinea_setear_punto(polilinea_t *polilinea, size_t pos, float x, float y);

// Utils
polilinea_t *polilinea_clonar(const polilinea_t *polilinea);
polilinea_t *letra_a_polilinea(const char letra);

#endif	  // _POLY_H_