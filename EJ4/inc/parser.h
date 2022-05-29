#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>
#include <stdio.h>

#include "figure.h"
#include "poly.h"

bool leer_encabezado_figura(FILE *f, char nombre[], figura_tipo_t *tipo, bool *infinito, size_t *cantidad_polilineas);
polilinea_t *leer_polilinea(FILE *f);

#endif	  // PARSER_H