#include <stddef.h>
#include <stdint.h>

typedef uint8_t color_t;
typedef struct {
	float (*points)[2];	   // Los puntos que dumpeaste
	size_t n;			   // La cantidad de puntos de la poly individual
	color_t color;		   // El color de la poly
} poly_t;

// Completa con las cosas que falten
// Los tipos de entidades que te podes encontrar
typedef enum {
	ICONO,
	NIVEL,
	SPRITE,
	FUEL,
	TURRETS,
	TANK,
	FLOOR,
	REACTOR,
	UNKNOWN,
} entity_nature_t;

typedef struct {
	poly_t *draw;			 // La/s poly/s que te podes encontrar por cada entidad
	size_t n_poly;			 // La cantidad de polys que tiene la entidad
	entity_nature_t type;	 // El tipo de entidad (Icono, Nivel, etc)
} entity_t;

typedef struct {
	entity_t *entities;	   // Las entidades presentes en el nivel
	size_t n_levels;	   // La cantidad de entidades presentes en el nivel
} level_t;
/* -------------------------------------------------------------------------- */




/* -------------------------------------------------------------------------- */
/*                              EJEMPLO ESTATICO                              */
/* -------------------------------------------------------------------------- */
// Te doy un ejemplo si todo fuera estatico, vos encargate de convertirlo a los tipos que corresponden
#define MAX_POLY_POINTS 10
typedef struct {
	float points[MAX_POLY_POINTS][2];	 // Los puntos que dumpeaste
	size_t n;							 // La cantidad de puntos de la poly individual
	color_t color;						 // El color de la poly
} poly_static_t;

#define MAX_POLYS_PER_ENTITY 10
typedef struct {
	poly_static_t draw[MAX_POLYS_PER_ENTITY];
	size_t n_poly;
	entity_nature_t type;
} entity_static_t;

#define MAX_ENTITIES_PER_LEVEL 10
typedef struct {
	entity_static_t entities[MAX_ENTITIES_PER_LEVEL];
	size_t n_entities;
} levels_static_t;

typedef enum {
	NIVEL1NE,
	NIVEL1SE,
	NIVEL1R,
	NIVEL1NW,
	NIVEL1SW,
	UNKNOWN
} level_name_t;

int main(int argc, char const *argv[]) {

	levels_static_t levels[2] = {
		[NIVEL1NE] = {
			.n_entities = 2,
			.entities = {
				{.type = ICONO, .n_poly = 2, .draw = {
                    {.points = {{0, 0}, {0, 0}, {0, 0}, {0, 0}}, .n = 4, .color = 0x1F},
                    {.points = {{0, 0}, {0, 0}, {0, 0}, {0, 0}}, .n = 4, .color = 0x0F},
                }},
                {.type = NIVEL, .n_poly = 1, .draw = {
                    {.points = {{0, 0}, {0, 0}, {0, 0}, {0, 0}}, .n = 4, .color = 0x1F},
                }},
			},
		},
		[NIVEL1SE] = {
			.n_entities = 1,
			.entities = {
				{.type = ICONO, .n_poly = 4, .draw = {
                    {.points = {{0, 0}, {0, 0}, {0, 0}, {0, 0}}, .n = 4, .color = 0x1F},
                    {.points = {{0, 0}, {0, 0}, {0, 0}, {0, 0}}, .n = 4, .color = 0x0F},
                    {.points = {{0, 0}, {0, 0}, {0, 0}, {0, 0}}, .n = 4, .color = 0x1F},
                    {.points = {{0, 0}, {0, 0}, {0, 0}, {0, 0}}, .n = 4, .color = 0x0F},
                }},
			},
		},
    };

    return 0;
}
