#include <stdio.h>
#include <string.h>

/* Level Structure
	LEVEL_NAME :
		FUEL    : (x,y,angle)
		TURRETS : (x,y,angle)
*/

// TODO: Decide if the aproach desired is defining limits like MAX_LEVEL_ENTITIES

typedef enum {
	FUEL,
	TURRETS,
	REACTOR,
} entity_nature_t;

const char *entity_nature_str_lut[] = {
	[FUEL] = "FUEL",
	[TURRETS] = "TURRETS",
	[REACTOR] = "REACTOR",
};

typedef struct {
	int x, y;
	float angle;
	entity_nature_t type;
} entity_t;

#define MAX_LEVEL_ENTITIES 12
typedef struct {
	entity_t entities[MAX_LEVEL_ENTITIES];
	size_t n_entities;
} level_t;

typedef enum {
	NIVEL1NE,
	NIVEL1SE,
	NIVEL1R,
	NIVEL1NW,
	NIVEL1SW,
	UNKNOWN
} level_name_t;

const level_name_t str_level_name_lut(const char *str_level) {
	static const char *str_level_lut[] = {
		[NIVEL1NE] = "NIVEL1NE",
		[NIVEL1SE] = "NIVEL1SE",
		[NIVEL1R] = "NIVEL1R",
		[NIVEL1NW] = "NIVEL1NW",
		[NIVEL1SW] = "NIVEL1SW",
		[UNKNOWN] = "UNKNOWN",
	};

	for (size_t i = 0; i < sizeof(str_level_lut) / sizeof(str_level_lut[0]); i++)
		if (strcmp(str_level, str_level_lut[i]) == 0)
			return (level_name_t)i;
	return UNKNOWN;
}

const level_t level_entities_lut(level_name_t level) {

	static const level_t level_entities_lut[] = {
		[NIVEL1NE] = {
			.entities = {
				{.x = 1064, .y = 13, .angle = 0, .type = FUEL},
				{.x = 1685, .y = 113, .angle = 0, .type = FUEL},
				{.x = 916, .y = 75, .angle = -0.66, .type = TURRETS},
				{.x = 1425, .y = 159, .angle = 0.66, .type = TURRETS},
			},
			.n_entities = 4,
		},
		[NIVEL1SE] = {
			.entities = {
				{.x = 482, .y = 94, .angle = 0, .type = FUEL},
				{.x = 1751, .y = 247, .angle = 0, .type = FUEL},
				{.x = 423, .y = 195, .angle = -0.66, .type = TURRETS},
				{.x = 806, .y = 215, .angle = -0.33, .type = TURRETS},
				{.x = 1254, .y = 153, .angle = 0.66, .type = TURRETS},
				{.x = 1587, .y = 223, .angle = 2.23, .type = TURRETS},
			},
			.n_entities = 6,
		},
		[NIVEL1SW] = {
			.entities = {
				{.x = 820, .y = 46, .angle = 0, .type = FUEL},
				{.x = 1196, .y = 68, .angle = 0, .type = FUEL},
				{.x = 1602, .y = 46, .angle = 0, .type = FUEL},
				{.x = 70, .y = 46, .angle = 0, .type = TURRETS},
				{.x = 506, .y = 12, .angle = 0, .type = TURRETS},
				{.x = 952, .y = 12, .angle = 0, .type = TURRETS},
				{.x = 1385, .y = 12, .angle = 0, .type = TURRETS},
				{.x = 757, .y = 210, .angle = 3.14, .type = TURRETS},
				{.x = 1161, .y = 210, .angle = 3.14, .type = TURRETS},
			},
			.n_entities = 8,
		},
		[NIVEL1NW] = {
			.entities = {
				{.x = 188, .y = 429, .angle = 0, .type = FUEL},
				{.x = 667, .y = 600, .angle = 0, .type = FUEL},
				{.x = 1054, .y = 404, .angle = 3.14, .type = FUEL},
				{.x = 574, .y = 344, .angle = 3.14, .type = FUEL},
				{.x = 257, .y = 440, .angle = 0.66, .type = TURRETS},
				{.x = 719, .y = 674, .angle = 2.23, .type = TURRETS},
				{.x = 985, .y = 565, .angle = 0, .type = TURRETS},
				{.x = 1125, .y = 417, .angle = 3.8, .type = TURRETS},
				{.x = 862, .y = 163, .angle = 3.8, .type = TURRETS},
				{.x = 626, .y = 323, .angle = 2.23, .type = TURRETS},
				{.x = 505, .y = 331, .angle = 3.8, .type = TURRETS},
				{.x = 378, .y = 296, .angle = 2.23, .type = TURRETS},
			},
			.n_entities = 12,
		},
		[NIVEL1R] = {
			.entities = {
				{.x = 815, .y = 309, .angle = 0, .type = REACTOR},
			},
			.n_entities = 1,
		},

	};

	return level_entities_lut[level];
}

int main() {

	// Suposed to be the level name
	// const char *str_level = "NIVEL1NE";

	// First, we need to know the asociated enum value in order to know the level structure.
	// const level_name_t level = str_level_name_lut(str_level);

	// Then, we need to know the level structure in order to know the entities.
	// const level_t level_entities = level_entities_lut(level);

	// Finally, we can print the entities.
	// printf("Level %s has %zd entities:\n", str_level, level_entities.n_entities);
	// for (size_t i = 0; i < level_entities.n_entities; i++)
	// 	printf("%s: (%d, %d, %f)\n", entity_nature_str_lut[level_entities.entities[i].type], level_entities.entities[i].x, level_entities.entities[i].y, level_entities.entities[i].angle);

	const char *str_levels[] = {
		"NIVEL1NE",
		"NIVEL1SE",
		"NIVEL1SW",
		"NIVEL1NW",
		"NIVEL1R",
	};

	for (size_t i = 0; i < 5; i++) {
		const level_name_t level = str_level_name_lut(str_levels[i]);
		const level_t level_entities = level_entities_lut(level);
		printf("Level %s has %zd entities:\n", str_levels[i], level_entities.n_entities);
		for (size_t j = 0; j < level_entities.n_entities; j++)
			printf("%s: (%d, %d, %f)\n", entity_nature_str_lut[level_entities.entities[j].type], level_entities.entities[j].x, level_entities.entities[j].y, level_entities.entities[j].angle);
		printf("------------------------------------------------\n");
	}

	return 0;
}
