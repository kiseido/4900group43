// 4900group43.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#define M_PI 3.14159265358979323846
#define M_COS60 0.5
#define M_SIN60 0.86602540378443860
int windowWidth = 800;
int windowHeight = 600;

void myInit();
void myDraw();
void drawTestPiece(double cX, double cY, double cZ, int div, int c);
void drawStrip(double cX, double* cY, double cZ, double* prevR, double r2, double h, int div, int c);

main(int argc, char *argv[])
{

	/* Initialize window system */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(windowWidth, windowHeight);
	glutCreateWindow("Hello World");

	/* Initialize graphics */
	myInit();

	/* Display callback and enter event loop */
	glutDisplayFunc(&myDraw);
	glutMainLoop();
}

void myInit()
{
	/* Background color */
	glClearColor(0.0, 0.0, 0.0, 1.0);

	/* Projection */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    //glOrtho(-15.0, 15.0, -2.0, 10.0, -15.0, 15.0);
    //glFrustum(-15.0, 15.0, -2.0, 10.0, -15.0, 15.0);
    gluPerspective(60, windowWidth / windowHeight, 1, 50);
    gluLookAt(1.0, 15.0, -15, 0.0, 0.0, -2.0, 0.0, 1.0, 0.0);
}

void myDraw()
{
	/* Clear the screen */
	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	/* Example code to draw 3 white points /
	/* Draw your points here **/

    //glBegin(GL_POLYGON);
    //glVertex3f(0.75, 0.75, 0.0);
    //glVertex3f(0.25, 0.25, 0.0);
    //glVertex3f(0.75, 0.25, 0.0);
    //glEnd();
    int curPieceIndex = 0;
    double xs[6];
    double ys[6];
    double zs[6];
    int cs[6];
    cs[0] = 2;
    cs[1] = 3;
    cs[2] = 5;
    cs[3] = 6;
    cs[4] = 10;
    cs[5] = 15;

    int count = 0;
    int boardRadius = 5;
    double boardX = 0;
    double boardY = 0;
    double tileRadius = 1;
    double tileRadMod = 0.95;
    double vX = tileRadius * M_COS60;
    double vY = tileRadius * M_SIN60;
    double hX = tileRadius * 1;
    for (int i = 0; i <= boardRadius; i++) {
        int id2 = i / 2;
        int ir2 = i % 2;
        int hTiles = boardRadius - id2 - ir2;
        double tileX = (1 + M_COS60) * tileRadius * i;
        for (int j = 0; j <= hTiles; j++) {
            double tileY = (j * 2 + ir2)* vY;
            double d = i+max(0,j-id2);
            double c = 0.25 + d * (0.75 / boardRadius);
            glColor3f(c, c, c);
            for (int modX = -1; modX <= 1; modX += 2) {
                for (int modY = -1; modY <= 1; modY += 2) {
                    glBegin(GL_POLYGON);
                    glVertex3f(boardX + modX * tileX - vX * tileRadMod, 0.0, boardY + modY * tileY + vY * tileRadMod);
                    glVertex3f(boardX + modX * tileX + vX * tileRadMod, 0.0, boardY + modY * tileY + vY * tileRadMod);
                    glVertex3f(boardX + modX * tileX + hX * tileRadMod, 0.0, boardY + modY * tileY + 0.0 * tileRadMod);
                    glVertex3f(boardX + modX * tileX + vX * tileRadMod, 0.0, boardY + modY * tileY - vY * tileRadMod);
                    glVertex3f(boardX + modX * tileX - vX * tileRadMod, 0.0, boardY + modY * tileY - vY * tileRadMod);
                    glVertex3f(boardX + modX * tileX - hX * tileRadMod, 0.0, boardY + modY * tileY + 0.0 * tileRadMod);
                    glEnd();
                    count++;
                    if (j == 0 && ir2 == 0) {
                        break;
                    }
                    if (j == hTiles && (i == 0 || i == boardRadius)) {
                        xs[curPieceIndex] = boardX + modX * tileX;
                        ys[curPieceIndex] = 0;
                        zs[curPieceIndex] = boardY + modY * tileY;
                        curPieceIndex++;
                    }
                }
                if (i == 0) {
                    break;
                }
            }
        }
    }

    for (int i = 0; i < 6; i++) {
        drawTestPiece(xs[i], ys[i], zs[i], 12, cs[i]);
    }
	/* Execute draw commands */
	glFlush();
}

void drawTestPiece(double cX, double cY, double cZ, int div, int c) {
    double prevR = 0.75;
    drawStrip(cX, &cY, cZ, &prevR, 0.50, 0.25, div, c);
    drawStrip(cX, &cY, cZ, &prevR, 0.25, 0.15, div, c);
    drawStrip(cX, &cY, cZ, &prevR, 0.25, 0.25, div, c);
    drawStrip(cX, &cY, cZ, &prevR, 0.40, 0.0, div, c);
    drawStrip(cX, &cY, cZ, &prevR, 0.40, 0.05, div, c);
    drawStrip(cX, &cY, cZ, &prevR, 0.30, 0.0, div, c);
    drawStrip(cX, &cY, cZ, &prevR, 0.20, 0.05, div, c);
    drawStrip(cX, &cY, cZ, &prevR, 0.25, 0.05, div, c);
    drawStrip(cX, &cY, cZ, &prevR, 0.30, 0.075, div, c);
    drawStrip(cX, &cY, cZ, &prevR, 0.35, 0.1, div, c);
    drawStrip(cX, &cY, cZ, &prevR, 0.40, 0.15, div, c);
    drawStrip(cX, &cY, cZ, &prevR, 0.45, 0.2, div, c);
    drawStrip(cX, &cY, cZ, &prevR, 0.50, 0.25, div, c);
    drawStrip(cX, &cY, cZ, &prevR, 0.30, 0.0, div, c);
    drawStrip(cX, &cY, cZ, &prevR, 0.30, 0.10, div, c);
    drawStrip(cX, &cY, cZ, &prevR, 0.00, 0.0, div, c);
}

void drawStrip(double cX, double* cY, double cZ, double* prevR, double r2, double h, int div, int c) {

    double r1 = *prevR;
    double i = 0.25 + (1 + (r1-r2)/sqrt((r2-r1)*(r2-r1) + h*h))/3;
    glColor3f(c%2==0?i:0, c%3==0?i:0, c%5==0?i:0);
    glBegin(GL_TRIANGLE_STRIP);
    for (int d = 0; d <= div; d++) {
        glVertex3f(cX + r1 * cos(2 * M_PI * d / div), *cY, cZ + r1 * sin(2 * M_PI * d / div));
        glVertex3f(cX + r2 * cos(2 * M_PI * d / div), *cY + h, cZ + r2 * sin(2 * M_PI * d / div));
    }
    //glVertex3f();
    glEnd();
    *cY += h;
    *prevR = r2;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
