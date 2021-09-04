// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include "glut.h"
#include <iostream>

// dimensiunea ferestrei in pixeli
#define dim 300
#define INF 999999999
using namespace std;

unsigned char prevKey;

void Longchamps() {
	double xmax, ymax, xmin, ymin;
	double a = 0.2;
	double pi = 4 * atan(1.0);
	double ratia = 0.001, ratie_triunghiuri = 0.015;
	double t;

	// calculul valorilor maxime/minime ptr. x si y
	// aceste valori vor fi folosite ulterior la scalare
	xmax = -INF;
	xmin = INF;
	ymax = -INF;
	ymin = INF;
	double fractie = 0.05;
	for (t = -pi/2 + ratia + fractie; t < -pi/6 - fractie; t += ratia) {
		if (fabs(t - pi / 6) < 0.000001 ||
			fabs(t + pi / 6) < 0.000001) {
			continue;
		}
		double x1, y1;
		x1 = a / ((4 * pow(cos(t), 2.0)) - 3);
		xmax = (xmax < x1) ? x1 : xmax;
		xmin = (xmin > x1) ? x1 : xmin;

		y1 = (a*tan(t)) / ((4 * pow(cos(t), 2.0)) - 3);
		ymax = (ymax < y1) ? y1 : ymax;
		ymin = (ymin > y1) ? y1 : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);
	cout << xmax << " " << ymax << '\n';
	xmax *= 1.1;
	ymax *= 1.05;
	glColor3f(0.1, 0.1, 1); // albastru
	glBegin(GL_LINE_LOOP);
	for (t = -pi / 2 + fractie +ratia; t < -pi / 6 - fractie; t += ratia) {
		if (fabs(t - pi / 6) < 0.000001 ||
			fabs(t + pi / 6) < 0.000001) {
			continue;
		}
		double x1, y1;
		x1 = a / ((4 * pow(cos(t), 2.0)) - 3);
		y1 = (a * tan(t)) / ((4 * pow(cos(t), 2.0)) - 3);
		glVertex2f(x1/xmax, y1/ymax);
	}
	glVertex2f(-1*0.91, 1*0.95);
	glEnd();

	glColor3f(1, 0, 0);
	glBegin(GL_TRIANGLES);
	for (t = -pi / 2 + fractie + ratia + 0.0025; t < -pi / 6 - fractie; t += ratie_triunghiuri) {
		if (fabs(t - pi / 6) < 0.000001 ||
			fabs(t + pi / 6) < 0.000001) {
			continue;
		}
		double x1, y1, x2, y2;
		x1 = a / ((4 * pow(cos(t), 2.0)) - 3);
		y1 = (a * tan(t)) / ((4 * pow(cos(t), 2.0)) - 3);
		double t1;

		t1 = t + 0.005;
		x2 = a / ((4 * pow(cos(t1), 2.0)) - 3);
		y2 = (a * tan(t1)) / ((4 * pow(cos(t1), 2.0)) - 3);

		if (pow((x1 - x2), 2.0) + pow((y1 - y2), 2.0) < 0.00005)
		{
			continue;
		}

		glVertex2f(-1 * 0.91, 1 * 0.95);
		glVertex2f(x1/xmax, y1/ymax);
		glVertex2f(x2/xmax, y2/ymax);
	}
	glEnd();



}
void Hipocicloida() {
	double xmax, ymax, xmin, ymin;
	double R = 0.1, r = 0.3;
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double t;

	// calculul valorilor maxime/minime ptr. x si y
	// aceste valori vor fi folosite ulterior la scalare
	xmax = -INF;
	xmin = INF;
	ymax = -INF;
	ymin = INF;
	for (t = -0 + ratia; t < 2 * pi; t += ratia) {
		double x1, y1;
		x1 = (R - r)*cos(r / R * t) - r * cos(t - r / R * t);
		xmax = (xmax < x1) ? x1 : xmax;
		xmin = (xmin > x1) ? x1 : xmin;

		y1 = (R - r)*sin(r / R * t) - r * sin(t - r / R * t);
		ymax = (ymax < y1) ? y1 : ymax;
		ymin = (ymin > y1) ? y1 : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);
	xmax *= 2;
	ymax *= 2;
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (t = -0 + ratia; t < 2 * pi; t += ratia) {
		double x1, y1;
		x1 = (R - r) * cos(r / R * t) - r * cos(t - r / R * t);
		y1 = (R - r) * sin(r / R * t) - r * sin(t - r / R * t);
		glVertex2f(x1/ xmax, y1/ ymax);
	}
	glEnd();
}

void Epicicloida() {
	double xmax, ymax, xmin, ymin;
	double R = 0.1, r = 0.3;
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double t;

	xmax = -INF;
	xmin = INF;
	ymax = -INF;
	ymin = INF;
	for (t = -0 + ratia; t < 2 * pi; t += ratia) {
		double x1, y1;
		x1 = (R + r) * cos(r / R * t) - r * cos(t + r / R * t);
		xmax = (xmax < x1) ? x1 : xmax;
		xmin = (xmin > x1) ? x1 : xmin;

		y1 = (R + r)*sin(r / R * t) - r * sin(t + r / R * t);
		ymax = (ymax < y1) ? y1 : ymax;
		ymin = (ymin > y1) ? y1 : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

	xmax *= 1.5;
	ymax *= 1.5;

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (t = -0 + ratia; t < 2 * pi; t += ratia) {
		double x1, y1;
		x1 = (R + r) * cos(r / R * t) - r * cos(t + r / R * t);
		y1 = (R + r) * sin(r / R * t) - r * sin(t + r / R * t);
		// am fi putut face o scalare uniforma
		// glVertex2f(x1/ xmax, y1/ xmax);
		glVertex2f(x1/ xmax, y1/ ymax);
	}
	glEnd();
}

void Cicloida() {
	double xmax, ymax, xmin, ymin;
	double a = 0.1, b = 0.2;
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double t;
	double t1 = -3 * pi - 0.20;
	//double t1 = -9.6; // ales prin try and error pentru a arata exact ca in imagine
	double t2 = -t1;
	// calculul valorilor maxime/minime ptr. x si y
	// aceste valori vor fi folosite ulterior la scalare
	xmax = -INF;
	xmin = INF;
	ymax = -INF;
	ymin = INF;
	for (t = t1 + ratia; t < t2; t += ratia) {
		double x1, y1;
		x1 = a * t - b * sin(t);
		xmax = (xmax < x1) ? x1 : xmax;
		xmin = (xmin > x1) ? x1 : xmin;

		y1 = a - b * cos(t);
		ymax = (ymax < y1) ? y1 : ymax;
		ymin = (ymin > y1) ? y1 : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);
	xmax *= 1.2;
	ymax *= 3.3;
	double left_const = 0.08;
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (t = t1 + ratia; t < t2; t += ratia) {
		double x1, y1;
		x1 = a * t - b * sin(t);
		y1 = a - b * cos(t);
		glVertex2f(x1 / xmax - left_const, y1 / ymax);
	}
	glEnd();
}

void MelculLuiPascal() {
	double xmax, ymax, xmin, ymin;
	double a = 0.3, b = 0.2;
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double t;

	xmax = -INF;
	xmin = INF;
	ymax = -INF;
	ymin = INF;
	for (t = -pi + ratia; t < pi; t += ratia) {
		double x1, y1;
		x1 = 2 * (a * cos(t) + b) * cos(t);
		xmax = (xmax < x1) ? x1 : xmax;
		xmin = (xmin > x1) ? x1 : xmin;

		y1 = 2 * (a * cos(t) + b) * sin(t);
		ymax = (ymax < y1) ? y1 : ymax;
		ymin = (ymin > y1) ? y1 : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

	xmax *= 1.15;
	ymax *= 1.7;
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_LOOP);
	for (t = -pi + ratia; t < pi; t += ratia) {
		double x1, y1;
		x1 = 2 * (a * cos(t) + b) * cos(t);
		y1 = 2 * (a * cos(t) + b) * sin(t);
		glVertex2f(x1 / xmax, y1/ ymax);
	}
	glEnd();
}

void FunctiaExemplu() {
	double ymax, ymin, xmax;
	double a = 0.4;
	double pi = 4 * atan(1.0);
	double ratia = 0.001;
	double t, x, y;
	int dom_x = 26; // gasit matematic, numarand cateva varfuri avem nevoie

	ymax = -INF;
	ymin = INF;
	xmax = dom_x * 1.2;

	for (x = 0 ; x <= dom_x; x += ratia) {
		double round, dist;
		if (x == 0) {
			y = 1;
		}
		else {
			round = floor(x + 0.5);
			if (round > x)
				dist = round - x;
			else
				dist = x - round;
			y = dist / x;
			ymax = (ymax < y) ? y : ymax;
			ymin = (ymin > y) ? y : ymin;
		}
	}

	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);
	ymax += 0.01;

	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (x = 0; x <= dom_x; x += ratia) {
		double round, dist;

		if (x == 0) {
			y = 1;
		}
		else {
			round = floor(x + 0.5);
			if (round > x)
				dist = round - x;
			else
				dist = x - round;
			y = dist / x;
		}
		glVertex2f(x / xmax, y / ymax);
	}
	glEnd();
}

void LemniscataBernoulli() {
	double xmax, ymax, xmin, ymin;
	double a = 0.4;
	double pi = 4 * atan(1.0);
	double ratia = 0.00001;
	double t;

	xmax = -INF;
	xmin = INF;
	ymax = -INF;
	ymin = INF;
	for (t = -pi / 4 + ratia; t < pi / 4; t += ratia) {
		double r1, r2, x, y;
		r1 = a* sqrt(2 * cos(2 * t));
		x = r1 * cos(t);
		y = r1 * sin(t);
		xmax = (xmax < x) ? x : xmax;
		xmin = (xmin > x) ? x : xmin;
		ymax = (ymax < y) ? y : ymax;
		ymin = (ymin > y) ? y : ymin;

		r2 = - a*sqrt(2 * cos(2 * t));
		x = r2 * cos(t);
		y = r2 * sin(t);
		xmax = (xmax < x) ? x : xmax;
		xmin = (xmin > x) ? x : xmin;
		ymax = (ymax < y) ? y : ymax;
		ymin = (ymin > y) ? y : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);
	xmax *= 1.9;
	ymax *= 5;

	double dim_spatiu = 0.002;
	glColor3f(1, 0.1, 0.1);
	glBegin(GL_LINE_STRIP);
	for (t = +pi / 4 + ratia - dim_spatiu; t >-pi / 4 ; t -= ratia) {
		double r, x, y;
		r = +a * sqrt(2 * cos(2 * t));
		x = r * cos(t);
		y = r * sin(t);
		x /= xmax;
		y /= ymax;

		glVertex2f(x, y);
	}
	for (t = -pi / 4 + ratia ; t < pi / 4 - dim_spatiu; t += ratia) {
		double r, x, y;
		r = -a * sqrt(2 * cos(2 * t));
		x = r * cos(t);
		y = r * sin(t);
		x /= xmax;
		y /= ymax;

		glVertex2f(x, y);
	}
	glEnd();
}

void SpiralaLogiritmica() {
	double xmax, ymax, xmin, ymin;
	double a = 0.02;
	double pi = 4 * atan(1.0);
	double e = 2.71828;
	double ratia = 0.02;
	double t;
	//double t2 = 3.02;
	double t2 = pi - 0.15;
	xmax = -INF;
	xmin = INF;
	ymax = -INF;
	ymin = INF;
	for (t = 0 + ratia; t < t2; t += ratia) {
		double r1, x, y;
		r1 = a * pow(e, (1 + t));
		x = r1 * cos(t);
		y = r1 * sin(t);
		xmax = (xmax < x) ? x : xmax;
		xmin = (xmin > x) ? x : xmin;
		ymax = (ymax < y) ? y : ymax;
		ymin = (ymin > y) ? y : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);
	xmax *= 1.1;
	ymax *= 2.8;
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (t = 0 + ratia; t < 3.02; t += ratia) {
		double r1, x, y;
		r1 = a * pow(e, (1 + t));
		x = r1 * cos(t);
		y = r1 * sin(t);

		glVertex2f(x/xmax, y/ymax);
	}
	glEnd();
}

void Display1() {
	double xmax, ymax, xmin, ymin;
	double a = 1, b = 2;
	double pi = 4 * atan(1.0);
	double ratia = 0.05;
	double t;

	// calculul valorilor maxime/minime ptr. x si y
	// aceste valori vor fi folosite ulterior la scalare
	xmax = a - b - 1;
	xmin = a + b + 1;
	ymax = ymin = 0;
	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = a + b * cos(t);
		xmax = (xmax < x1) ? x1 : xmax;
		xmin = (xmin > x1) ? x1 : xmin;

		x2 = a - b * cos(t);
		xmax = (xmax < x2) ? x2 : xmax;
		xmin = (xmin > x2) ? x2 : xmin;

		y1 = a * tan(t) + b * sin(t);
		ymax = (ymax < y1) ? y1 : ymax;
		ymin = (ymin > y1) ? y1 : ymin;

		y2 = a * tan(t) - b * sin(t);
		ymax = (ymax < y2) ? y2 : ymax;
		ymin = (ymin > y2) ? y2 : ymin;
	}

	xmax = (fabs(xmax) > fabs(xmin)) ? fabs(xmax) : fabs(xmin);
	ymax = (fabs(ymax) > fabs(ymin)) ? fabs(ymax) : fabs(ymin);

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = (a + b * cos(t)) / xmax;
		x2 = (a - b * cos(t)) / xmax;
		y1 = (a * tan(t) + b * sin(t)) / ymax;
		y2 = (a * tan(t) - b * sin(t)) / ymax;

		glVertex2f(x1, y1);
	}
	glEnd();

	glBegin(GL_LINE_STRIP);
	for (t = -pi / 2 + ratia; t < pi / 2; t += ratia) {
		double x1, y1, x2, y2;
		x1 = (a + b * cos(t)) / xmax;
		x2 = (a - b * cos(t)) / xmax;
		y1 = (a * tan(t) + b * sin(t)) / ymax;
		y2 = (a * tan(t) - b * sin(t)) / ymax;

		glVertex2f(x2, y2);
	}
	glEnd();
}

// graficul functiei
// $f(x) = \bar sin(x) \bar \cdot e^{-sin(x)}, x \in \langle 0, 8 \cdot \pi \rangle$,
void Display2() {
	double pi = 4 * atan(1.0);
	double xmax = 8 * pi;
	double ymax = exp(1.1);
	double ratia = 0.05;

	// afisarea punctelor propriu-zise precedata de scalare
	glColor3f(1, 0.1, 0.1); // rosu
	glBegin(GL_LINE_STRIP);
	for (double x = 0; x < xmax; x += ratia) {
		double x1, y1;
		x1 = x / xmax;
		y1 = (fabs(sin(x)) * exp(-sin(x))) / ymax;

		glVertex2f(x1, y1);
	}
	glEnd();
}


void Init(void) {

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glLineWidth(1);

	//   glPointSize(4);

	glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
	glClear(GL_COLOR_BUFFER_BIT);

	switch (prevKey) {
	case '1':
		Display1();
		break;
	case '2':
		Display2();
		break;
	case '3':
		FunctiaExemplu();
		break;
	case '4':
		MelculLuiPascal();
		break;
	case '5':
		Longchamps();
		break;
	case '6':
		Cicloida();
		break;
	case '7':
		Epicicloida();
		break;
	case '8':
		Hipocicloida();
		break;
	case '9':
		LemniscataBernoulli();
		break;
	case '0':
		SpiralaLogiritmica();
		break;
	default:
		break;
	}

	glFlush();
}

void Reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
}

void KeyboardFunc(unsigned char key, int x, int y) {
	prevKey = key;
	if (key == 27) // escape
		exit(0);
	glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y) {
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);

	glutInitWindowSize(dim, dim);

	glutInitWindowPosition(100, 100);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutCreateWindow(argv[0]);

	Init();

	glutReshapeFunc(Reshape);

	glutKeyboardFunc(KeyboardFunc);

	glutMouseFunc(MouseFunc);

	glutDisplayFunc(Display);

	glutMainLoop();

	return 0;
}
