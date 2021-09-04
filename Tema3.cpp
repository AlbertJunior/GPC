// Lab3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <cassert>
#include <cfloat>
#include <cstring>
#include "glut.h"
#include <iostream>
#include <vector>

using namespace std;

// dimensiunea ferestrei in pixeli
#define dim 300

unsigned char prevKey;

class GrilaCarteziana {
public:
	int n;
	int m;
	double cx;
	double cy;
	double epsilon;
	double distantaLinii;
	double distantaColoane;

	GrilaCarteziana(int n, int m, int cx, int cy) {
		this->n = n;
		this->m = m;
		this->cx = cx;
		this->cy = cy;
		this->epsilon = 0.1;
		this->CalculeazaDistantaIntreLinii();
		this->DrawBoard();
		glColor3f(1, 0, 0);
		WritePixel(0, 0, 30);
		glColor3f(1, 1, 1);

	}
	GrilaCarteziana() {
		this->n = 16;
		this->m = 16;
		this->cx = 0;
		this->cy = 0;
		this->epsilon = 0.1;
		this->CalculeazaDistantaIntreLinii();
		this->DrawBoard();
		glColor3f(1, 0, 0);
		WritePixel(cx, cy, 30);
		glColor3f(1, 1, 1);
	}

	void WritePixel(int coloana, int linie, int raza) {
		linie = linie + this->cy;
		coloana = coloana + this->cx;

		if (linie < 0 || linie >= this->m || coloana < 0 || coloana >= this->n) {
			return;
		}
		vector<pair<int, int>> listaPuncteCerc = getListaPuncteCerc(coloana, linie, raza);
		int i;
		int maxDimensionSize;
		if (n >= m) {
			maxDimensionSize = n;
		}
		else {
			maxDimensionSize = m;
		}

		double x_ecran = -1 + epsilon + (coloana)*distantaColoane;
		double y_ecran = -1 + epsilon + (linie)*distantaLinii;
		glBegin(GL_POLYGON);
		for (i = 0; i < listaPuncteCerc.size(); i++) {
			double punctCerc_x = x_ecran + ((double)listaPuncteCerc[i].first) / raza / ((float)maxDimensionSize * 1.5);
			double punctCerc_y = y_ecran + ((double)listaPuncteCerc[i].second) / raza / ((float)maxDimensionSize * 1.5);
			glVertex2d(punctCerc_x, punctCerc_y);
		}
		glEnd();
	}


	void CalculeazaDistantaIntreLinii() {
		int windowSizeX = glutGet(GLUT_WINDOW_X);
		int windowSizeY = glutGet(GLUT_WINDOW_Y);
		this->distantaLinii = (double)((2.0 - 2 * epsilon) / double(this->n - 1));
		this->distantaColoane = (double)((2.0 - 2 * epsilon) / double(this->m - 1));
	}

	void DrawBoard() {
		int i;
		int j;

		for (i = 1; i <= m; i++) {
			glBegin(GL_LINES);
			glVertex2d(-1 + epsilon + this->distantaColoane * (i - 1), 1 - epsilon);
			glVertex2d(-1 + epsilon + this->distantaColoane * (i - 1), -1 + epsilon);
			glEnd();
		}

		for (i = 1; i <= n; i++) {
			glBegin(GL_LINES);
			glVertex2d(-1 + epsilon, -1 + epsilon + this->distantaLinii * (i - 1));
			glVertex2d(1 - epsilon, -1 + epsilon + this->distantaLinii * (i - 1));
			glEnd();
		}
	}

	vector<pair<int, int>> getListaPuncteCerc(int coloana, int linie, int raza) {
		linie = linie + this->cx;
		coloana = coloana + this->cy;

		vector<pair<int, int>> listaPuncte;
		int x = 0;
		int y = raza;
		int d = 1 - raza;
		int de = 3;
		int dse = -2 * raza + 5;

		listaPuncte.push_back(make_pair(x, y));
		listaPuncte.push_back(make_pair(-x, y));
		listaPuncte.push_back(make_pair(x, -y));
		listaPuncte.push_back(make_pair(-x, -y));
		if (x != y) {
			listaPuncte.push_back(make_pair(y, x));
			listaPuncte.push_back(make_pair(-y, x));
			listaPuncte.push_back(make_pair(y, -x));
			listaPuncte.push_back(make_pair(-y, -x));
		}

		while (y > x) {
			if (d < 0) {
				d += 2 * x + 3;
				x++;
			}
			else {
				d += 2 * (x - y) + 5;
				x++;
				y--;
			}
			listaPuncte.push_back(make_pair(x, y));
			listaPuncte.push_back(make_pair(-x, y));
			listaPuncte.push_back(make_pair(x, -y));
			listaPuncte.push_back(make_pair(-x, -y));
			if (x != y) {
				listaPuncte.push_back(make_pair(y, x));
				listaPuncte.push_back(make_pair(-y, x));
				listaPuncte.push_back(make_pair(y, -x));
				listaPuncte.push_back(make_pair(-y, -x));
			}
		}
		return listaPuncte;
	}

};

class Desenare2D {

public:

	void WriteLine(GrilaCarteziana grilaCarteziana, int x0, int y0, int xn, int yn) {

		cout << x0 << " " << y0 << " " << xn << " " << yn << '\n';
		cout << grilaCarteziana.epsilon << '\n';
		double x0_ecran = -1 + grilaCarteziana.epsilon + (x0 + grilaCarteziana.cx) * grilaCarteziana.distantaColoane;
		double y0_ecran = -1 + grilaCarteziana.epsilon + (y0 + grilaCarteziana.cy) * grilaCarteziana.distantaLinii;
		double xn_ecran = -1 + grilaCarteziana.epsilon + (xn + grilaCarteziana.cx) * grilaCarteziana.distantaColoane;
		double yn_ecran = -1 + grilaCarteziana.epsilon + (yn + grilaCarteziana.cy) * grilaCarteziana.distantaLinii;

		glColor3f(1, 0, 0);
		glBegin(GL_LINES);
		glVertex2d(x0_ecran, y0_ecran);
		glVertex2d(xn_ecran, yn_ecran);
		glEnd();
		glColor3f(1, 1, 1);
	}

	void WriteLinePixels(GrilaCarteziana grilaCarteziana, int x0, int y0, int xn, int yn, int pattern_flag) {
		vector<pair<int, int>> puncteLinie;
		cout << x0 << " " << y0 << " " << xn << " " << yn << '\n';

		if (x0 > xn) {
			swap(x0, xn);
			swap(y0, yn);
		}
		cout << x0 << " " << y0 << " " << xn << " " << yn << '\n';
		// dy/dx <= 1 si yn>=y0
		cout << abs(xn - x0) << " " << abs(yn - y0) << '\n';
		if (yn >= y0 && abs(xn - x0) >= abs(yn - y0)) {
			cout << "Intru aici\n";
			int dx = xn - x0;
			int dy = abs(yn - y0);
			int d = 2 * dy - dx; //2a+b       a=dy, b=-dx
			int dE = 2 * dy; //2a
			int dNE = 2 * (dy - dx);//2(a+b)
			int x = x0;
			int y = y0;
			puncteLinie.push_back(make_pair(x, y));
			while (x < xn) {
				if (d <= 0) {
					d += dE;
					x++;
				}
				else {
					d += dNE;
					x++; y++;
				}
				puncteLinie.push_back(make_pair(x, y));
			}

			this->drawPoints(grilaCarteziana, puncteLinie, pattern_flag);
		}
		// dy/dx > 1 si yn>=y0
		else if (yn >= y0 && abs(xn - x0) < abs(yn - y0)) {
			cout << "Am intrat";
			int dx = xn - x0;
			int dy = yn - y0;
			//int d = 2 * dx - dy;
			int d = dy - 2 * dx;
			int dN = -2 * dx;
			int dNE = 2 * (dy - dx);
			int x = x0;
			int y = y0;
			puncteLinie.push_back(make_pair(x, y));
			while (y < yn) {
				if (d > 0) {
					d += dN;
					y++;
				}
				else {
					d += dNE;
					x++; y++;
				}
				puncteLinie.push_back(make_pair(x, y));
			}

			this->drawPoints(grilaCarteziana, puncteLinie, pattern_flag);
		}
		// dy/dx <= 1 si yn<=y0
		else if (yn <= y0 && abs(xn - x0) >= abs(yn - y0)) {
			int dx = xn - x0;
			int dy = yn - y0;
			int d = 2 * dy + dx;
			int dE = 2 * dy;
			int dSE = 2 * (dy + dx);
			int x = x0;
			int y = y0;
			puncteLinie.push_back(make_pair(x, y));
			while (x < xn) {
				if (d > 0) {
					d += dE;
					x++;
				}
				else {
					d += dSE;
					x++; y--;
				}
				puncteLinie.push_back(make_pair(x, y));
			}

			this->drawPoints(grilaCarteziana, puncteLinie, pattern_flag);
		}
		// dy/dx > 1 si yn < y0 
		else if (y0 > yn && abs(xn - x0) < abs(yn - y0)) {
			int dx = xn - x0;
			int dy = yn - y0;
			cout << "DY " << dy << '\n';
			int d = (dy + 2 * dx);
			cout << "D " << d << '\n';
			int dS = 2 * dx;
			int dSE = 2 * (dx + dy);
			cout << "DSE " << dSE << '\n';
			cout << "dS " << dS << '\n';
			int x = x0;
			int y = y0;
			puncteLinie.push_back(make_pair(x, y));
			while (y > yn) {
				if (d < 0) {
					d += dS;
					y--;
				}
				else {
					d += dSE;
					x++; y--;
				}
				puncteLinie.push_back(make_pair(x, y));
			}

			this->drawPoints(grilaCarteziana, puncteLinie, pattern_flag);

		}
	}

	void drawPoints(GrilaCarteziana grilaCarteziana, vector<pair<int, int>> points, int pattern_flag) {
		int i;
		for (i = 0; i < points.size(); i++) {
			/*
			...
			X-X
			...
			*/
			if (pattern_flag == 1) {
				grilaCarteziana.WritePixel(points[i].first - 1, points[i].second, 30);
				grilaCarteziana.WritePixel(points[i].first + 1, points[i].second, 30);
			}
			/*
			.X.
			.-.
			.X.
			*/
			else if (pattern_flag == 2) {
				grilaCarteziana.WritePixel(points[i].first, points[i].second - 1, 30);
				grilaCarteziana.WritePixel(points[i].first, points[i].second + 1, 30);
			}
			/*
			.X.
			X-X
			.X.
			*/
			else if (pattern_flag == 3) {
				grilaCarteziana.WritePixel(points[i].first, points[i].second - 1, 30);
				grilaCarteziana.WritePixel(points[i].first, points[i].second + 1, 30);
				grilaCarteziana.WritePixel(points[i].first - 1, points[i].second, 30);
				grilaCarteziana.WritePixel(points[i].first + 1, points[i].second, 30);
			}
			/*
			XXX
			X-X
			XXX
			*/
			else if (pattern_flag == 4) {
				grilaCarteziana.WritePixel(points[i].first - 1, points[i].second - 1, 30);
				grilaCarteziana.WritePixel(points[i].first, points[i].second - 1, 30);
				grilaCarteziana.WritePixel(points[i].first + 1, points[i].second - 1, 30);
				grilaCarteziana.WritePixel(points[i].first - 1, points[i].second, 30);
				grilaCarteziana.WritePixel(points[i].first + 1, points[i].second, 30);
				grilaCarteziana.WritePixel(points[i].first, points[i].second + 1, 30);
				grilaCarteziana.WritePixel(points[i].first - 1, points[i].second + 1, 30);
				grilaCarteziana.WritePixel(points[i].first + 1, points[i].second + 1, 30);
			}
			cout << points[i].first << " " << points[i].second << '\n';
			grilaCarteziana.WritePixel(points[i].first, points[i].second, 30);
		}
	}

};

void Init(void) {

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glLineWidth(1);

	glPointSize(3);

	glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void)
{


	//Exemplu tema
	
	GrilaCarteziana grilaCarteziana(16, 16, 0, 0);
	//GrilaCarteziana grilaCarteziana(25, 30, 3, 2);
	Desenare2D desenare2D;

	desenare2D.WriteLine(grilaCarteziana, 0, 0, 15, 7);
	desenare2D.WriteLinePixels(grilaCarteziana, 0, 0, 15, 7, 0);

	desenare2D.WriteLine(grilaCarteziana, 0, 15, 15, 10);
	desenare2D.WriteLinePixels(grilaCarteziana, 0, 15, 15, 10, 2);
	

	/*
	GrilaCarteziana grilaCarteziana(25, 25, 3, 6);
	Desenare2D desenare2D;
	desenare2D.WriteLine(grilaCarteziana, 0, 3, 5, 16);
	desenare2D.WriteLinePixels(grilaCarteziana, 0, 3, 5, 16, 0);

	desenare2D.WriteLine(grilaCarteziana, 10, 18, 15, 7);
	desenare2D.WriteLinePixels(grilaCarteziana, 10, 18, 15, 7, 1);

	desenare2D.WriteLine(grilaCarteziana, -3, -3, -1, -1);
	desenare2D.WriteLinePixels(grilaCarteziana, -3, -3, -1, -1, 0);
	*/

	glFlush();
}

void Reshape(int w, int h)
{
	glFlush();
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

}

void KeyboardFunc(unsigned char key, int x, int y)
{
	prevKey = key;
	if (key == 27) // escape
		exit(0);
	glutPostRedisplay();
}

void MouseFunc(int button, int state, int x, int y)
{
}

int main(int argc, char** argv)
{
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

