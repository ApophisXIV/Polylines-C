#include "../../inc/figure.h"

const char *figura_tipo_a_cadena(figura_tipo_t figura) {
	static const char *lut_fig_str[] = {
		[ICONO] = "Icono",
		[NIVEL] = "Nivel",
		[SPRITE] = "Sprite",
		[UNKNOWN] = "Unknown",
	};
	return lut_fig_str[figura];
}