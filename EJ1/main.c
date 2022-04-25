#include <math.h>
#include <stdio.h>

#define DT 0.001

#define G 9.81

#define VELOCIDAD_INICIAL 20
#define ANGULO_INICIAL 50

#define PI 3.14159265359
#define DEG_TO_RAD(x) (x * PI / 180)

#define POS_X0 0
#define POS_Y0 0

double computar_velocidad(double vi, double a, double dt) {
	return vi + a * dt;
}
double computar_posicion(double pi, double vi, double dt) {
	return pi + vi * dt;
}

int main(void) {

	// Condiciones iniciales de velocidad y posicion
	// vx0 = v0*cos(a)
	// vy0 = v0*sin(a)

	const double VX0 = VELOCIDAD_INICIAL * cos(DEG_TO_RAD(ANGULO_INICIAL));
	const double VY0 = VELOCIDAD_INICIAL * sin(DEG_TO_RAD(ANGULO_INICIAL));

	// Ecuacion horaria
	// r_x = x0 + vx0*t
	// r_y = y0 + vy0*t - 0.5*g*t^2

	double x = POS_X0;
	double y = POS_Y0;
	double vy = VY0;
	double t = 0;

	printf("x,y,t\n");	  // Columnas de la tabla

	while (y >= 0) {
	    printf("%f, %f, %f\n", x, y, t);
		vy = computar_velocidad(vy, -G, DT);
		y = computar_posicion(y, vy, DT);
        x = computar_posicion(x, VX0, DT);
		t += DT;
	}

	return 0;
}
