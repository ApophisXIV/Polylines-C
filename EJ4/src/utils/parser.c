#include <stdint.h>

#include "../../inc/color.h"
#include "../../inc/parser.h"

#define NAME_STR_LEN 20

#define INFINITE_FLAG_SHIFT 6
#define IS_INFINITE(cfg_byte) ((cfg_byte >> INFINITE_FLAG_SHIFT) & 1)

#define FIGURE_TYPE_MASK 0x07	 // 0000 0111
#define FIGURE_TYPE_SHIFT 1
#define GET_FIGURE_TYPE(cfg_byte) ((cfg_byte >> FIGURE_TYPE_SHIFT) & FIGURE_TYPE_MASK)

bool leer_encabezado_figura(FILE *f, char nombre[], figura_tipo_t *tipo, bool *infinito, size_t *cantidad_polilineas) {
	if (f == NULL) return false;

	// Figure name reading
	if (fread(nombre, NAME_STR_LEN, 1, f) != 1) return false;

	// Figure properties reading
	uint8_t cfg_byte;
	if (fread(&cfg_byte, sizeof(cfg_byte), 1, f) != 1) return false;

	*infinito = IS_INFINITE(cfg_byte);
	*tipo = GET_FIGURE_TYPE(cfg_byte);

	// Figure n polylines
	if (fread(cantidad_polilineas, sizeof(uint16_t), 1, f) != 1) return false;

	return true;
}