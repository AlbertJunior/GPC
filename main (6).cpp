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

	GrilaCarteziana(int n, int m) {
		this->n = n+1;
		this->m = m+1;
		this->cx = 0;
		this->cy = 0;
		this->epsilon = 0.1;
		this->CalculeazaDistantaIntreLinii();
		this->DrawBoard();
	}
	GrilaCarteziana() {
		this->n = 16;
		this->m = 16;
		this->cx = 0;
		this->cy = 0;
		this->epsilon = 0.1;
		this->CalculeazaDistantaIntreLinii();
		this->DrawBoard();
	}

	void WritePixel(int linie, int coloana, int raza) {
		if (linie < 1 || linie > this->n || coloana < 1 || coloana > this->m) {
			return;
		}
		vector<pair<int, int>> listaPuncteCerc = getListaPuncteCerc(linie, coloana, raza);
		int i;

		double x_ecran = -1 + epsilon + (linie - 1) * distantaLinii;
		double y_ecran = -1 + epsilon + (coloana - 1) * distantaColoane;
		glBegin(GL_POLYGON);
		for (i = 0; i < listaPuncteCerc.size(); i++) {
			double punctCerc_x = x_ecran + ((double)listaPuncteCerc[i].first) / raza * 0.035;
			double punctCerc_y = y_ecran + ((double)listaPuncteCerc[i].second) / raza * 0.035;
			glVertex2d(punctCerc_y, punctCerc_x);
		}
		glEnd();
	}


	void CalculeazaDistantaIntreLinii() {
		int windowSizeX = glutGet(GLUT_WINDOW_X);
		int windowSizeY = glutGet(GLUT_WINDOW_Y);
		this->distantaLinii = (2 - 2 * epsilon) / (n - 1);
		this->distantaColoane = (2 - 2 * epsilon) / (m - 1);
	}

	void DrawBoard() {
		int i;
		int j;
		
		for (i = 0; i <= n; i++) {
			glBegin(GL_LINES);
			glVertex2d(-1 + epsilon + distantaLinii*(i-1), 1 - epsilon);
			glVertex2d(-1 + epsilon + distantaLinii*(i-1), -1 + epsilon);
			glEnd();
		}

		for (i = 0; i <= m; i++) {
			glBegin(GL_LINES);
			glVertex2d(-1 + epsilon, -1 + epsilon + distantaColoane * (i-1));
			glVertex2d(1 - epsilon, -1 + epsilon + distantaColoane * (i-1));
			glEnd();
		}
	}

	vector<pair<int, int>> getListaPuncteCerc(int linie, int coloana, int raza) {
		vector<pair<int, int>> listaPuncte;
		int x = 0;
		int y = raza;
		int d = 1 - raza;
		int de = 3;
		int dse = -2 * raza + 5;
		
		listaPuncte.push_back(make_pair(x,y));
		listaPuncte.push_back(make_pair(-x, y));
		listaPuncte.push_back(make_pair(x, -y));
		listaPuncte.push_back(make_pair(-x, -y));
		if (x != y) {
			listaPuncte.push_back(make_pair(y,x));
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

	void WriteLine(GrilaCarteziana grilaCarteziana, int l1, int c1, int l2, int c2) {
		double x_ecran1 = -1 + grilaCarteziana.epsilon + (l1 - 1) * grilaCarteziana.distantaLinii;
		double y_ecran1 = -1 + grilaCarteziana.epsilon + (c1 - 1) * grilaCarteziana.distantaColoane;
		double x_ecran2 = -1 + grilaCarteziana.epsilon + (l2 - 1) * grilaCarteziana.distantaLinii;
		double y_ecran2 = -1 + grilaCarteziana.epsilon + (c2 - 1) * grilaCarteziana.distantaColoane;
		glColor3f(1, 0, 0);
		glBegin(GL_LINES);
		glVertex2d(y_ecran1, x_ecran1);
		glVertex2d(y_ecran2, x_ecran2);
		glEnd();
		glColor3f(1, 1, 1);
	}

	void WriteLinePixels(GrilaCarteziana grilaCarteziana, int l1, int c1, int l2, int c2, bool widen_flag) {
		vector<pair<int, int>> puncteLinie;
		if (l2 >= l1 && c2 >= c1 && (c2 - c1) >= (l2 - l1)) {
			int dx = c2 - c1;
			int dy = l2 - l1;
			int d = 2 * dy - dx;
			int dE = 2 * dy;
			int dNE = 2 * (dy - dx);
			int x = c1;
			int y = l1;
			puncteLinie.push_back(make_pair(y, x));
			while (x < c2) {
				if (d <= 0) {
					d += dE;
					x++;
				}
				else {
					d += dNE;
					x++; y++;
				}
				puncteLinie.push_back(make_pair(y, x));
			}

			int i;
			for (i = 0; i < puncteLinie.size(); i++) {
				if (widen_flag == true) {
					grilaCarteziana.WritePixel(puncteLinie[i].first-1, puncteLinie[i].second, 30);
					grilaCarteziana.WritePixel(puncteLinie[i].first+1, puncteLinie[i].second, 30);
				}
				grilaCarteziana.WritePixel(puncteLinie[i].first, puncteLinie[i].second, 30);
			}
		}

		else if (l1 >= l2 && c2 >= c1 && (c2 - c1) >= (l1 - l2)) {
			int dx = c2 - c1;
			int dy = l1 - l2;
			int d = 2 * dy - dx;
			int dE = 2 * dy;
			int dNE = 2 * (dy - dx);
			int x = c1;
			int y = l1;
			puncteLinie.push_back(make_pair(y, x));
			while (x < c2) {
				if (d <= 0) {
					d += dE;
					x++;
				}
				else {
					d += dNE;
					x++; y--;
				}
				puncteLinie.push_back(make_pair(y, x));
			}

			int i;
			for (i = 0; i < puncteLinie.size(); i++) {
				if (widen_flag == true) {
					grilaCarteziana.WritePixel(puncteLinie[i].first - 1, puncteLinie[i].second, 30);
					grilaCarteziana.WritePixel(puncteLinie[i].first + 1, puncteLinie[i].second, 30);
				}
				grilaCarteziana.WritePixel(puncteLinie[i].first, puncteLinie[i].second, 30);
			}
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
	
	GrilaCarteziana grilaCarteziana(15, 15);
	Desenare2D desenare2D;

	desenare2D.WriteLine(grilaCarteziana, 1, 1, 8, 16);
	desenare2D.WriteLinePixels(grilaCarteziana, 1, 1, 8, 16, false);
	desenare2D.WriteLine(grilaCarteziana, 16, 1, 11, 16);
	desenare2D.WriteLinePixels(grilaCarteziana, 16, 1, 11, 16, true);
	/*desenare2D.WriteLine(grilaCarteziana, 1, 16, 16, 11);
	desenare2D.WriteLinePixels(grilaCarteziana, 1, 16, 16, 11);*/
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

