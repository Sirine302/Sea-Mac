#include "gldrawing.h"
#include "visu.h"
#include "../include/heightMap.h"

#include <stdio.h>

void glDrawRepere(float length) {
	// dessin du repère : ATTENTION coordonnées x z y
	glBegin(GL_LINES);
		glColor3f(1.,0.,0.);
		glVertex3f(0.,0.,0.);
		glVertex3f(length,0.,0.);
		
		glColor3f(0.,1.,0.);
		glVertex3i(0.,0.,0.);
		glVertex3i(0.,length,0.);
		
		glColor3f(0.,0.,1.);
		glVertex3i(0.,0.,0.);
		glVertex3i(0.,0.,length);
	glEnd();
}

void drawTest() {
	glBegin(GL_LINES);
		glColor3f(1.,0.,0.);
		glVertex3f(0.,0.,0.);
		glVertex3f(5.,5.,0.);
	glEnd();
}