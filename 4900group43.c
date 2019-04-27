// 4900group43.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#define M_PI 3.14159265358979323846
#define M_COS60 0.5
#define M_SIN60 0.86602540378443860

void myInit();
void myDraw();

main(int argc, char *argv[])
{

	/* Initialize window system */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(800, 600);
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
    gluPerspective(90, 0.8 / 0.6, 1, 30);
    gluLookAt(0.0, 15.0, -7.5, 0.0, 0.0, -2.0, 0.0, 1.0, 0.0);
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
    glBegin(GL_POLYGON);

    glEnd();
    int count = 0;
    int boardRadius = 2;
    double boardX = 0;
    double boardY = 0;
    double tileRadius = 0.75;
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
                }
                if (i == 0) {
                    break;
                }
            }
        }
    }

	/* Execute draw commands */
	glFlush();
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
