// Lab3Exempluu.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"

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
// numarul maxim de iteratii pentru testarea apartenentei la mult.Julia-Fatou
#define NRITER_JF 5000
#define NRITER_MDB 5000
// modulul maxim pentru testarea apartenentei la mult.Julia-Fatou
#define MODMAX_JF 10000000
#define MODMAX_MDB 2
// ratii ptr. CJuliaFatou
#define RX_JF 0.01
#define RY_JF 0.01
#define RX_MDB 0.01
#define RY_MDB 0.01

unsigned char prevKey;

class Color {
public:
	Color(double r, double g, double b) {
		this->r = r;
		this->g = g;
		this->b = b;
	}
	double getR() {
		return r;
	}
	double getG() {
		return g;
	}
	double getB() {
		return b;
	}
private:
	double r;
	double g;
	double b;
};
vector<Color*> colors;

void createColors(int numberOfColors) {

	double stepsPerColor = numberOfColors / 3.0;
	int stepsPerColorInt = stepsPerColor + 0.5;
	int step = 1;
	double r = 0.0;
	double g = 0.0;
	double b = 0.0;

	while (step < stepsPerColorInt)
	{
		colors.push_back(new Color(r, g, b));
		r += 1.0 / stepsPerColorInt;
		step++;
	}
	r = 0.5;
	step = 0;
	while (step < stepsPerColorInt)
	{
		colors.push_back(new Color(r, g, b));
		g += 1.0 / stepsPerColorInt;
		step++;
	}
	r = 0.1;
	g = 0.1;
	step = 0;
	while (step < stepsPerColorInt)
	{
		colors.push_back(new Color(r, g, b));
		b += 1.0 / stepsPerColorInt;
		step++;
	}
}



class CComplex {
public:
	CComplex() : re(0.0), im(0.0) {}
	CComplex(double re1, double im1) : re(re1 * 1.0), im(im1 * 1.0) {}
	CComplex(const CComplex &c) : re(c.re), im(c.im) {}
	~CComplex() {}

	CComplex &operator=(CComplex &c)
	{
		re = c.re;
		im = c.im;
		return *this;
	}

	double getRe() { return re; }
	void setRe(double re1) { re = re1; }

	double getIm() { return im; }
	void setIm(double im1) { im = im1; }

	double getModul() { return sqrt(re * re + im * im); }

	int operator==(CComplex &c1)
	{
		return ((re == c1.re) && (im == c1.im));
	}

	CComplex pow2()
	{
		CComplex rez;
		rez.re = powl(re * 1.0, 2) - powl(im * 1.0, 2);
		rez.im = 2.0 * re * im;
		return rez;
	}

	friend CComplex& operator+(CComplex &c1, CComplex &c2);
	friend CComplex& operator*(CComplex &c1, CComplex &c2);

	void print(FILE *f)
	{
		fprintf(f, "%.20f%+.20f i", re, im);
	}

private:
	double re, im;
};

CComplex& operator +(CComplex &c1, CComplex &c2)
{
	CComplex *rez = new CComplex(c1.re + c2.re, c1.im + c2.im);
	return *rez;
}

CComplex& operator*(CComplex &c1, CComplex &c2)
{
	CComplex *rez = new CComplex(c1.re * c2.re - c1.im * c2.im,
		c1.re * c2.im + c1.im * c2.re);
	return *rez;
}

class CJuliaFatou {
public:
	CJuliaFatou()
	{
		// m.c se initializeaza implicit cu 0+0i

		m.nriter = NRITER_JF;
		m.modmax = MODMAX_JF;
	}

	CJuliaFatou(CComplex &c)
	{
		m.c = c;
		m.nriter = NRITER_JF;
		m.modmax = MODMAX_JF;
	}

	~CJuliaFatou() {}

	void setmodmax(double v) { assert(v <= MODMAX_JF); m.modmax = v; }
	double getmodmax() { return m.modmax; }

	void setnriter(int v) { assert(v <= NRITER_JF); m.nriter = v; }
	int getnriter() { return m.nriter; }

	// testeaza daca x apartine multimii Julia-Fatou Jc
	// returneaza 0 daca apartine, -1 daca converge finit, +1 daca converge infinit
	int isIn(CComplex &x)
	{
		int rez = 0;
		// tablou in care vor fi memorate valorile procesului iterativ z_n+1 = z_n * z_n + c
		CComplex z0, z1;

		z0 = x;
		for (int i = 1; i < m.nriter; i++)
		{
			z1 = z0 * z0 + m.c;
			if (z1 == z0)
			{
				// x nu apartine m.J-F deoarece procesul iterativ converge finit
				rez = -1;
				break;
			}
			else if (z1.getModul() > m.modmax)
			{
				// x nu apartine m.J-F deoarece procesul iterativ converge la infinit
				rez = 1;
				break;
			}
			z0 = z1;
		}

		return rez;
	}

	// afisarea multimii J-F care intersecteaza multimea argument
	void display(double xmin, double ymin, double xmax, double ymax)
	{
		glPushMatrix();
		glLoadIdentity();

		//    glTranslated((xmin + xmax) * 1.0 / (xmin - xmax), (ymin + ymax)  * 1.0 / (ymin - ymax), 0);
		//    glScaled(1.0 / (xmax - xmin), 1.0 / (ymax - ymin), 1);
			// afisarea propriu-zisa
		glBegin(GL_POINTS);
		for (double x = xmin; x <= xmax; x += RX_JF)
			for (double y = ymin; y <= ymax; y += RY_JF)
			{
				CComplex z(x, y);
				int r = isIn(z);
				//        z.print(stdout);
				if (r == 0)
				{
					//          fprintf(stdout, "   \n");
					glVertex3d(x, y, 0);
				}
				else if (r == -1)
				{
					//          fprintf(stdout, "   converge finit\n");
				}
				else if (r == 1)
				{
					//          fprintf(stdout, "   converge infinit\n");
				}
			}
		fprintf(stdout, "STOP\n");
		glEnd();

		glPopMatrix();
	}

private:
	struct SDate {
		CComplex c;
		// nr. de iteratii
		int nriter;
		// modulul maxim
		double modmax;
	} m;
};

// multimea Julia-Fatou pentru z0 = 0 si c = -0.12375+0.056805i
void Display1() {
	CComplex c(-0.12375, 0.056805);
	CJuliaFatou cjf(c);

	glColor3f(1.0, 0.1, 0.1);
	cjf.setnriter(30);
	cjf.display(-0.8, -0.4, 0.8, 0.4);
}

// multimea Julia-Fatou pentru z0 = 0 si c = -0.012+0.74i
void Display2() {
	CComplex c(-0.012, 0.74);
	CJuliaFatou cjf(c);

	glColor3f(1.0, 0.1, 0.1);
	cjf.setnriter(30);
	cjf.display(-1, -1, 1, 1);
}


class Mandelbrot {
public:
	Mandelbrot()
	{
		m.nriter = NRITER_MDB;
		m.modmax = MODMAX_MDB;
	}


	~Mandelbrot() {}

	void setmodmax(double v) { assert(v <= MODMAX_MDB); m.modmax = v; }
	double getmodmax() { return m.modmax; }

	void setnriter(int v) { assert(v <= NRITER_MDB); m.nriter = v; }
	int getnriter() { return m.nriter; }

	// testeaza daca x apartine multimii Julia-Fatou Jc
	// returneaza 0 daca apartine, -1 daca converge finit, +1 daca converge infinit
	int isIn(CComplex &x)
	{
		int rez = 0;
		int steps =0;
		// tablou in care vor fi memorate valorile procesului iterativ z_n+1 = z_n * z_n + c
		CComplex z1, z2;

		z1 = x;
		for (int i = 2; i < m.nriter; i++)
		{
			steps++;
			z2 = z1 * z1 + x;
			if (z1.getModul() > m.modmax)
			{
				// x nu apartine m.J-F deoarece procesul iterativ converge la infinit
				rez = steps;
				break;
			}
			z1 = z2;
		}

		return rez;
	}

	void display(double xmin, double ymin, double xmax, double ymax)
	{
		int numberOfColors = 10;
		glPushMatrix();
		glLoadIdentity();

		glTranslated((xmin + xmax) * 2.0 / (xmin - xmax), 
					(ymin + ymax)  * 2.0 / (ymin - ymax), 0);
		glScaled(2.0 / (xmax - xmin), 2.0 / (ymax - ymin), 1);
			// afisarea propriu-zisa
		glBegin(GL_POINTS);
		createColors(m.nriter);
		createColors(m.nriter);
		createColors(m.nriter);
		fprintf(stdout, "%d\n", colors.size());

		int rmax = 0;
		for (double x = xmin; x <= xmax; x += RX_MDB)
			for (double y = ymin; y <= ymax; y += RY_MDB)
			{
				CComplex z(x, y);
				int r = isIn(z);

				glColor3f(1.0, 0.1, 0.1);
				if (r == 0)
				{
					glColor3f(colors[0]->getR(), colors[0]->getG(), colors[0]->getB());
					glVertex3d(x, y, 0);
				}
				else
				{
					//fprintf(stdout, "    %d\n", r);
					double value = double(r * colors.size())/ double(m.nriter);
					int intValue = value;
					//fprintf(stdout, "    %d\n", intValue);
					//fprintf(stdout, "    %lf\n", value);
					glColor3f(colors[intValue]->getR(), colors[intValue]->getG(), colors[intValue]->getB());
					//glColor3f(1.0, (1-value)*(1-value), 1.0);
					glVertex3d(x, y, 1);
				}
			}
		fprintf(stdout, "STOP\n");
		fprintf(stdout, "%d\n", rmax);
		glEnd();

		glPopMatrix();
	}

private:
	struct SDate {
		// nr. de iteratii
		int nriter;
		// modulul maxim
		double modmax;
	} m;
};




void Display3() {
	Mandelbrot* mdb =  new Mandelbrot();
	//glColor3f(1.0, 0.1, 0.1);
	mdb->setnriter(50);
	mdb->display(-2, -2, 2, 2);
}

void Init(void) {

	glClearColor(1.0, 1.0, 1.0, 1.0);

	glLineWidth(1);

	//   glPointSize(3);

	glPolygonMode(GL_FRONT, GL_LINE);
}

void Display(void) {
	switch (prevKey) {
	case '1':
		glClear(GL_COLOR_BUFFER_BIT);
		Display1();
		break;
	case '2':
		glClear(GL_COLOR_BUFFER_BIT);
		Display2();
		break;
	case '3':
		glClear(GL_COLOR_BUFFER_BIT);
		Display3();
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
