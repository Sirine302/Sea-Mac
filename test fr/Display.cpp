// Display.cpp

#include "HeightMap.h"
#include <GL/glut.h>
#include <math.h>

extern HeightMap heightmap;
extern double angle, pos_x, pos_z, x_vise, z_vise;

void Display()
{
	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(
		pos_x, 0.0, pos_z,
		x_vise, 0.0, z_vise,
		0.0, 1.0, 0.0);

	glTranslated(0.0, -10.0, -30.0);
	heightmap.Afficher();

	glutSwapBuffers();
	glutPostRedisplay();
}
