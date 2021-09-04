#include <cstdlib>
#include <cstdio>
#include "glut.h"
#include <gl/GL.h>
#include <iostream>
#include <cmath>
#define N 45
#define LG 5


using namespace std;

// dimensiunea ferestrei in pixeli
#define dim 300

unsigned char prevKey;

struct punct {
    float x, y, z;
}P1, P2, P3;




int lastKey = 1;
int cer = 2;
/*
void InitialPs() {
    P1.x = 6;
    P1.y = 3;
    P1.z = 4;
    P2.x = 15;
    P2.y = 9;
    P2.z = 7;
    P3.x = 16;
    P3.y = 8;
    P3.z = 14;
}*/

void InitialPs() {
    P1.x = -6;
    P1.y = 3;
    P1.z = -4;
    P2.x = -15;
    P2.y = 9;
    P2.z = -7;
    P3.x = -16;
    P3.y = 8;
    P3.z = -14;
}

void DisplayAxe() {
    int X, Y, Z;
    X = Y = 200;
    Z = 200;

    glLineWidth(2);

    // axa Ox - verde
    glColor3f(0, 1, 0);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0, 0, 0);
    glVertex3f(X, 0, 0);
    glEnd();

    // axa Oy - albastru
    glColor3f(0, 0, 1);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0, 0, 0);
    glVertex3f(0, Y, 0);
    glEnd();

    // axa Oz - rosu
    glColor3f(1, 0, 0);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, Z);
    glEnd();

    glLineWidth(1);
}

void DisplayTriunghi() {
    double pi = 2 * acos(0.0);
    glPushMatrix();
    if (lastKey >= 5) {
        double D1 = sqrt((P2.x - P1.x) * (P2.x - P1.x) + (P2.z - P1.z) * (P2.z - P1.z));
        double D2 = sqrt((P2.x - P1.x) * (P2.x - P1.x) + (P2.z - P1.z) * (P2.z - P1.z) + (P2.y - P1.y) * (P2.y - P1.y));
        double p3x = ((P2.z - P1.z) * (P3.x - P1.x) - (P3.z - P1.z) * (P2.x - P1.x)) / D1;
        double p3y = ((P3.y - P1.y) * D1) / D2 - (((P2.y - P1.y) * ((P2.x - P1.x) * (P3.x - P1.x) + (P2.z - P1.z) * (P3.z - P1.z))) / (D1 * D2));
        double D3 = sqrt(p3x * p3x + p3y * p3y);
        cout << "p3x " << p3x << '\n';
        cout << "p3y " << p3y << '\n';
        cout << "D3 " << D3 << '\n';
        double alpha = acos(abs(p3x) / D3) * (180.0 / pi);
        cout << alpha << '\n';
        if (p3x >= 0 && p3y >= 0) {
            double unghi = 90 - alpha;
            glRotated(unghi, 0, 0, 1);
        }
        else if (p3x >= 0 && p3y < 0) {
            double unghi = 90 + alpha;
            glRotated(unghi, 0, 0, 1);
        }
        else if (p3x < 0 && p3y >= 0) {
            double unghi = 90 - alpha;
            glRotated(-unghi, 0, 0 ,1);
        }
        else {
            double unghi = 90 + alpha;
            glRotated(-unghi, 0, 0, 1);
        }
    }
    if (lastKey >= 4) {
        double D1 = sqrt((P2.x - P1.x) * (P2.x - P1.x) + (P2.z - P1.z) * (P2.z - P1.z));
        double D2 = sqrt((P2.x - P1.x) * (P2.x - P1.x) + (P2.z - P1.z) * (P2.z - P1.z) + (P2.y - P1.y) * (P2.y - P1.y));
        double phi = acos(D1 / D2) * (180.0 / pi);
        if (P2.y >= 0) {
            glRotated(phi, 1, 0, 0);
        }
        else {
            glRotated(-phi, 1, 0, 0);
        }
    }
    if (lastKey >= 3) {
        double D1 = sqrt((P2.x - P1.x) * (P2.x - P1.x) + (P2.z - P1.z) * (P2.z - P1.z));
        double theta = acos(abs(P2.x - P1.x) / D1) * (180.0 / pi);
        if (P2.x >= 0 && P2.z >= 0) {
            double unghi = 90 - theta;
            glRotated(-unghi, 0, 1, 0);
        }
        else if (P2.x >= 0 && P2.z < 0) {
            double unghi = 90 + theta;
            glRotated(-unghi, 0, 1, 0);
        }
        else if (P2.x < 0 && P2.z >= 0) {
            double unghi = 90 - theta;
            glRotated(unghi, 0, 1, 0);
        }
        else {
            double unghi = 90 + theta;
            //cout << unghi << '\n';
            glRotated(unghi, 0, 1, 0);
        }
    }
    if (lastKey >= 2) {
        glTranslated(-P1.x, -P1.y, -P1.z);
    }
    glColor3f(0.2, 0.7, 0.1); // Blue
    glBegin(GL_TRIANGLES); 
        glVertex3f(P1.x, P1.y, P1.z);
        glVertex3f(P2.x, P2.y, P2.z);
        glVertex3f(P3.x, P3.y, P3.z);
    glEnd();
    glPointSize(5.0f);
    glBegin(GL_POINTS);
        glColor3f(1, 1, 0); //GALBEN
        glVertex3f(P1.x, P1.y, P1.z);
        glColor3f(0, 1, 1); //ALBASTRU
        glVertex3f(P2.x, P2.y, P2.z);
        glColor3f(1, 0, 1); //ROZ
        glVertex3f(P3.x, P3.y, P3.z);
    glEnd();
    glPopMatrix();

}
void DrawCube() {
    //fete fata-spate
    glColor3f(1, 1, 0);
    glBegin(GL_QUADS);
        glVertex3f(0, 0, 0);
        glVertex3f(LG, 0, 0);
        glVertex3f(LG, LG, 0);
        glVertex3f(0, LG, 0);
    glEnd();

    //fete top bottom
    glColor3f(0, 1, 1);
    glBegin(GL_QUADS);
        glVertex3f(0, 0, 0);
        glVertex3f(LG, 0, 0);
        glVertex3f(LG, 0, LG);
        glVertex3f(0, 0, LG);
    glEnd();

    // fete stanga dreapta
    glColor3f(1, 0, 1);
    glBegin(GL_QUADS);
        glVertex3f(0, 0, 0);
        glVertex3f(0, LG, 0);
        glVertex3f(0, LG, LG);
        glVertex3f(0, 0, LG);
    glEnd();

    glColor3f(1, 0, 1);
    glBegin(GL_QUADS);
        glVertex3f(LG, 0, 0);
        glVertex3f(LG, LG, 0);
        glVertex3f(LG, LG, LG);
        glVertex3f(LG, 0, LG);
    glEnd();

    glColor3f(0, 1, 1);
    glBegin(GL_QUADS);
        glVertex3f(0, LG, 0);
        glVertex3f(LG, LG, 0);
        glVertex3f(LG, LG, LG);
        glVertex3f(0, LG, LG);
    glEnd();

    glColor3f(1, 1, 0);
    glBegin(GL_QUADS);
        glVertex3f(0, 0, LG);
        glVertex3f(LG, 0, LG);
        glVertex3f(LG, LG, LG);
        glVertex3f(0, LG, LG);
    glEnd();

    //MARTOR
    glColor3f(0, 0, 0);
    glBegin(GL_LINE_STRIP);
    glVertex3f(0, 0, 0);
    glVertex3f(LG, LG, LG);
    glEnd();
}

void DisplayCubeCheck(double n) {
    glPushMatrix();
        glRotated(n, 1, 1, 1);
        DrawCube();
    glPopMatrix();
}

void DisplayCube(double n) {
    double pi = 2 * acos(0.0);

    glPushMatrix();
    if (lastKey >= 6) {
        glRotated(45, 0, 1, 0);
    }
    if (lastKey >= 5) {
        double D1 = sqrt(3);
        double theta = acos(1 / D1) * (180.0 / pi);
        double unghi = 90 - theta;
        glRotated(-unghi, 1, 0, 0);
    }
    if (lastKey >= 4) {
        glRotated(n, 0, 0, 1);
    }
    if (lastKey >= 3) {
        double D1 = sqrt(3);
        double theta = acos(1 / D1) * (180.0 / pi);
        double unghi = 90 - theta;
        glRotated(unghi, 1, 0, 0);
    }
    if (lastKey >= 2) {
        glRotated(-45, 0, 1, 0);
    }

    DrawCube();
    glPopMatrix();
}

void Cerinta2() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(20, 1, 0, 0);
    glRotated(-20, 0, 1, 0);
    DisplayAxe();
    DisplayTriunghi();
}


void Cerinta3Check(double n) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(20, 1, 0, 0);
    glRotated(-20, 0, 1, 0);
    DisplayAxe();
    DisplayCubeCheck(n);
}

void Cerinta3(double n) {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(20, 1, 0, 0);
    glRotated(-20, 0, 1, 0);
    DisplayAxe();
    DisplayCube(n);
}

// rotatia cu un unghi de 10 grade in raport cu axa x
void DisplayX() {
    glMatrixMode(GL_MODELVIEW);
    glRotated(10, 1, 0, 0);
}

// rotatia cu un unghi de 10 grade in raport cu axa y
void DisplayY() {
    glMatrixMode(GL_MODELVIEW);
    glRotated(10, 0, 1, 0);
}

// rotatia cu un unghi de 10 grade in raport cu axa z
void DisplayZ() {
    glMatrixMode(GL_MODELVIEW);
    glRotated(10, 0, 0, 1);
}

// Translatia cu 0.2, 0.2, 0.2
void DisplayT() {
    glMatrixMode(GL_MODELVIEW);
    glTranslatef(0.2, 0.2, 0.2);
}

// Scalarea cu 1.2, 1.2, 1.2
void DisplayS() {
    glMatrixMode(GL_MODELVIEW);
    glScalef(1.2, 1.2, 1.2);
}

void Init(void) {
    glClearColor(1, 1, 1, 1);
    glLineWidth(2);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-10, 10, -10, 10, 30, -30);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glRotated(20, 1, 0, 0);
    glRotated(-20, 0, 1, 0);
}

void Display(void) {
    switch (prevKey)
    {
    case 'a':
        DisplayAxe();
        break;
    case '0':
        glClear(GL_COLOR_BUFFER_BIT);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        glRotated(20, 1, 0, 0);
        glRotated(-20, 0, 1, 0);
        lastKey = 0;
        break;
    case '1':
        lastKey = 1;
        cer = 1;
        glClear(GL_COLOR_BUFFER_BIT);
        Cerinta2();
        break;
    case '2':
        lastKey = 2;
        cer = 1;
        glClear(GL_COLOR_BUFFER_BIT);
        Cerinta2();
        break;
    case '3':
        lastKey = 3;
        cer = 1;
        glClear(GL_COLOR_BUFFER_BIT);
        Cerinta2();
        break;
    case '4':
        lastKey = 4;
        cer = 1;
        glClear(GL_COLOR_BUFFER_BIT);
        Cerinta2();
        break;
    case '5':
        lastKey = 5;
        cer = 1;
        glClear(GL_COLOR_BUFFER_BIT);
        Cerinta2();
        break;
    case 'q':
        lastKey = 1;
        cer = 2;
        glClear(GL_COLOR_BUFFER_BIT);
        Cerinta3(N);
        break;
    case 'w':
        lastKey = 2;
        cer = 2;
        glClear(GL_COLOR_BUFFER_BIT);
        Cerinta3(N);
        break;
    case 'e':
        lastKey = 3;
        cer = 2;
        glClear(GL_COLOR_BUFFER_BIT);
        Cerinta3(N);
        break;
    case 'r':
        lastKey = 4;
        cer = 2;
        glClear(GL_COLOR_BUFFER_BIT);
        Cerinta3(N);
        break;
    case 'u':
        lastKey = 5;
        cer = 2;
        glClear(GL_COLOR_BUFFER_BIT);
        Cerinta3(N);
        break;
    case 'i':
        lastKey = 6;
        cer = 2;
        glClear(GL_COLOR_BUFFER_BIT);
        Cerinta3(N);
        break;
    case 'o':
        lastKey = 6;
        cer = 2;
        glClear(GL_COLOR_BUFFER_BIT);
        Cerinta3Check(N);
        break;

    
    case 'x':
        glClear(GL_COLOR_BUFFER_BIT);
        DisplayX();
        DisplayAxe();
        if (cer == 1)
            DisplayTriunghi();
        else
            DisplayCube(N);
        break;
    case 'y':
        glClear(GL_COLOR_BUFFER_BIT);
        DisplayY();
        DisplayAxe();
        if (cer == 1)
            DisplayTriunghi();
        else
            DisplayCube(N);
        break;
    case 'z':
        glClear(GL_COLOR_BUFFER_BIT);
        DisplayZ();
        DisplayAxe();
        if (cer == 1)
            DisplayTriunghi();
        else
            DisplayCube(N);
        break;
    case 't':
        glClear(GL_COLOR_BUFFER_BIT);
        DisplayT();
        DisplayAxe();
        if (cer == 1)
            DisplayTriunghi();
        else
            DisplayCube(N);
        break;
    case 's':
        glClear(GL_COLOR_BUFFER_BIT);
        DisplayS();
        DisplayAxe();
        if (cer == 1)
            DisplayTriunghi();
        else
            DisplayCube(N);
        break;
    default:
        break;
    }
    glutSwapBuffers();
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
    InitialPs();

    glutInit(&argc, argv);

    glutInitWindowSize(dim, dim);

    glutInitWindowPosition(100, 100);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

    glutCreateWindow(argv[0]);

    Init();

    glutReshapeFunc(Reshape);

    glutKeyboardFunc(KeyboardFunc);

    glutMouseFunc(MouseFunc);

    glutDisplayFunc(Display);

    glutMainLoop();

    return 0;
}