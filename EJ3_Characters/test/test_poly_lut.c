#include <assert.h>
#include <stdbool.h>
// #include <stdio.h>

#include "../inc/characters.h"	  // For testing
#include "../inc/poly.h"

bool verificar_puntos(polilinea_t *p, const float puntos[][2]) {
	if (p == NULL) return false;
	const size_t n_puntos = polilinea_cantidad_puntos(p);
	float x, y;
	for (size_t i = 0; i < n_puntos; i++) {
		polilinea_obtener_punto(p, i, &x, &y);
		if (x != puntos[i][0] || y != puntos[i][1]) return false;
		// printf("%f %f - %f %f\n", x, y, puntos[i][0], puntos[i][1]);
	}
	return true;
}

int main(void) {

	polilinea_t *p = letra_a_polilinea('E');
	if (p == NULL) return 1;
	if (!verificar_puntos(p, caracter_e)){
        polilinea_destruir(p);
        return 1;
    }

    p = letra_a_polilinea('z');
    if (p == NULL) return 1;
    if (!verificar_puntos(p, caracter_z)){
        polilinea_destruir(p);
        return 1;
    }

    p = letra_a_polilinea('\n');
    if (p != NULL) {
        polilinea_destruir(p);
        return 1;
    }

    polilinea_destruir(p);

	return 0;
}
