// Reshape.cpp

// reshape de la fenêtre 

#include <GL/glut.h>

void Reshape(int w, int h)
{
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0, (GLdouble)w/(GLdouble)h, 1, 200);
}
