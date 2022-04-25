
#include <math.h>
#include <stdbool.h>	// for bool
#include <stddef.h>		// for size_t
#include <stdio.h>

#define EPSILON 1E-7
#define PI 3.1415926535897932
#define DEG_TO_RAD(x) ((x)*PI / 180.0)

void trasladar(float polilinea[][2], size_t n, float dx, float dy) {
	for (size_t i = 0; i < n; polilinea[i][0] += dx, polilinea[i][1] += dy, i++);
}

void rotar(float polilinea[][2], size_t n, double rad) {
	for (size_t i = 0; i < n; i++) {
		const float x = polilinea[i][0];
		const float y = polilinea[i][1];
		polilinea[i][0] = x * cos(rad) - y * sin(rad);
		polilinea[i][1] = x * sin(rad) + y * cos(rad);
	}
}

// Helper
void print_polilinea(const float polilinea[][2], size_t n) {
	for (size_t i = 0; i < n; i++)
		printf("(%f, %f)\n", polilinea[i][0], polilinea[i][1]);
}

/* --------------- Vector operations for n-dimensional vectors -------------- */
// Vector addition
void vec_add(const float v1[], const float v2[], float res[], const size_t n) {
	for (size_t i = 0; i < n; (res[i] = v1[i] + v2[i]), i++);
}
// Vector subtraction
void vec_sub(const float v1[], const float v2[], float res[], const size_t n) {
	for (size_t i = 0; i < n; (res[i] = v1[i] - v2[i]), i++);
}
// Vector dot product
float vec_dot(const float v1[], const float v2[], const size_t n) {
	float res = 0;
	for (size_t i = 0; i < n; (res += v1[i] * v2[i]), i++);
	return res;
}
// Vetor escalar product
void vec_scalar(const float v1[], const float k, float res[], const size_t n) {
	for (size_t i = 0; i < n; (res[i] = v1[i] * k), i++);
}
// Vector norm
float vec_norm(const float v[], const size_t n) {
	return sqrt(vec_dot(v, v, n));
}
/* -------------------------------------------------------------------------- */

double distancia_punto_a_polilinea(const float polilinea[][2], size_t n, float px, float py) {
	// Point-to-polygon distance equation
	// alpha = [ (vec_p - vec_a ) · (vec_b - vec_a) ] / [ norm ( (vec_b - vec_a) ) ^ 2 ]

	// If alpha is negative or zero, the closest point is A.
	// If alpha is greater or equal to one, the closest point is B.
	// If alpha is between zero and one, the closest point is A + alpha * (B - A)

	const float vec_p[2] = {px, py};
	double min_distance;	// Loop invariant

	for (size_t i = 0; i < n - 1; i++) {

		const float vec_a[2] = {polilinea[i][0], polilinea[i][1]};
		const float vec_b[2] = {polilinea[i + 1][0], polilinea[i + 1][1]};

		float vec_ab[2];
		vec_sub(vec_b, vec_a, vec_ab, 2);

		float vec_ap[2];
		vec_sub(vec_p, vec_a, vec_ap, 2);

		const double alpha = vec_dot(vec_ap, vec_ab, 2) / (vec_norm(vec_ab, 2) * vec_norm(vec_ab, 2));

		double actual_distance;

		if (alpha <= 0)
			actual_distance = vec_norm(vec_ap, 2);

		else if (alpha >= 1) {
			float vec_bp[2];
			vec_sub(vec_p, vec_b, vec_bp, 2);
			actual_distance = vec_norm(vec_bp, 2);
		}

		else {
			// Closest point is A + alpha * (B - A)
			float vec_aux[2];
			vec_scalar(vec_ab, alpha, vec_aux, 2);
			vec_add(vec_aux, vec_a, vec_aux, 2);
			vec_sub(vec_p, vec_aux, vec_aux, 2);
			actual_distance = vec_norm(vec_aux, 2);
		}

		if (i == 0)
			min_distance = actual_distance;

		// A smaller distance was found
		if (actual_distance < min_distance)
			min_distance = actual_distance;
	}

	return min_distance;
}

bool test_distance(const float polilinea[][2], size_t n) {

	const double ptos_prueba[][2] = {
		{0, 0},
		{0, 2},
		{6, 1},
		{2, 2},
		{1, 1},
		{1, 4},
		{5, 4},
		{-1, -3},
		{3, 3},
		{5, 3},
		{0, 7},
	};
	const double ref_dist[] = {
		1.0000000000,
		0.4472136322,
		1.0000000000,
		1.3416407687,
		0.8944271977,
		0.0000000000,
		0.7071067812,
		4.1231056256,
		1.0000000000,
		0.0000000000,
		2.2360679775,
	};

	for (size_t i = 0; i < n; i++) {
		const double dist = distancia_punto_a_polilinea(polilinea, n, ptos_prueba[i][0], ptos_prueba[i][1]);
		if ((float)dist != (float)ref_dist[i]) {
			printf("Expected: %f, Actual: %f - ", ref_dist[i], dist);
			return false;
		}
	}
	return true;
}

bool test_translate(float polilinea[][2], size_t n) {
	const float ref_polilinea[][2] = {
		{1, 2},
		{2, 4},
		{2, 6},
		{3, 6},
		{4, 5},
		{5, 5},
		{6, 4},
		{5, 3},
		{6, 2},
		{3, 1},
	};
	// return !memcmp(polilinea, ref_polilinea, sizeof(ref_polilinea)); // This could be used instead of the next lines

	for (size_t i = 0; i < n; i++)
		if (polilinea[i][0] != ref_polilinea[i][0] || polilinea[i][1] != ref_polilinea[i][1]) {
			printf("Expected: (%.2f, %.2f), Actual: (%.2f, %.2f) - ", ref_polilinea[i][0], ref_polilinea[i][1], polilinea[i][0], polilinea[i][1]);
			return false;
		}
	return true;
}

bool test_rotate(float polilinea[][2], size_t n) {
	// Rotate 90 degrees
	const float ref_polilinea[][2] = {
		{-1, 0},
		{-3, 1},
		{-5, 1},
		{-5, 2},
		{-4, 3},
		{-4, 4},
		{-3, 5},
		{-2, 4},
		{-1, 5},
		{0, 2},
	};

	for (size_t i = 0; i < n; i++) {
		if (fabs(polilinea[i][0] - ref_polilinea[i][0]) > EPSILON || fabs(polilinea[i][1] - ref_polilinea[i][1]) > EPSILON) {
			printf("Expected: (%.2f, %.2f), Actual: (%.2f, %.2f) - ", ref_polilinea[i][0], ref_polilinea[i][1], polilinea[i][0], polilinea[i][1]);
			return false;
		}
	}
	return true;
}

int main(void) {

	float polilinea[][2] = {
		{0, 1},
		{1, 3},
		{1, 5},
		{2, 5},
		{3, 4},
		{4, 4},
		{5, 3},
		{4, 2},
		{5, 1},
		{2, 0},
	};

	const size_t n = sizeof(polilinea) / sizeof(polilinea[0]);

	printf("Prueba distancia: ");
	if (!test_distance((const float(*)[2])polilinea, n)) {	  // -Werror compile warning supressed castign to (const float(*)[2])
		printf("FAIL\n");
		return 1;
	}
	printf("PASS\n");

	trasladar(polilinea, n, 1, 1);
	printf("Prueba traslacion: ");
	if (!test_translate(polilinea, n)) {
		printf("FAIL\n");
		return 1;
	}
	trasladar(polilinea, n, -1, -1);	// Restore original polilinea
	printf("PASS\n");

	rotar(polilinea, n, DEG_TO_RAD(90));	// 90 degrees for simplicity
	printf("Prueba rotacion: ");
	if (!test_rotate(polilinea, n)) {
		printf("FAIL\n");
		return 1;
	}
	printf("PASS\n");

	printf("%s: OK\n", __FILE__);
}
