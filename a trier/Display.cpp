// Display.cpp

#include "../include/heightMap.h"
#include <GL/glut.h>
#include <math.h>

extern double angle, pos_x, pos_z, x_vise, z_vise;
/*
Heightmap map;
void Display()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
		0, 0.0, 0,
		0, 0.0, 0,
		0.0, 1.0, 0.0);

	glTranslated(0.0, -10.0, -30.0);

	displayMap(map);

	glutSwapBuffers();
	glutPostRedisplay();
}
*/