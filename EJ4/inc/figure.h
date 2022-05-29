#ifndef FIGURE_H
#define FIGURE_H

typedef enum {
	ICONO,
	NIVEL,
	SPRITE,
	UNKNOWN,
} figura_tipo_t;

const char *figura_tipo_a_cadena(figura_tipo_t figura);

#endif	  // FIGURE_H