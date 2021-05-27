#include "gldrawing.h"

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



void drawTriangles(Node * node, bool isFilled) {
	// cout << "J'ETRE FEUILLE TO DRAW" << endl;

	Point NO = node->tabPoints[0];
	Point NE = node->tabPoints[1];
	Point SO = node->tabPoints[2];
	Point SE = node->tabPoints[3];
	
	// cout << NO.x << " " << NO.y << " " << NO.z << endl;
	// cout << NE.x << " " << NE.y << " " << NE.z << endl;
	// cout << SO.x << " " << SO.y << " " << SO.z << endl;
	// cout << SE.x << " " << SE.y << " " << SE.z << endl;


	glVertex3f(SO.x, SO.z, SO.y);
	glVertex3f(NO.x, NO.z, NO.y);
	glVertex3f(NE.x, NE.z, NE.y);

	glVertex3f(SO.x, SO.z, SO.y);
	glVertex3f(SE.x, SE.z, SE.y);
	glVertex3f(NE.x, NE.z, NE.y);

	glEnd();
}


void drawTerrain(Node * node, bool isFilled) {


	if (isLeaf(node)) {	
		if (isFilled) {
			glBegin(GL_TRIANGLE_STRIP);
		}
		else {
			glBegin(GL_LINE_STRIP);
		}
		
			drawTriangles(node, isFilled);

		glEnd();

	}
	else {
		drawTerrain(node->nordOuest, isFilled);
		drawTerrain(node->nordEst, isFilled);
		drawTerrain(node->sudOuest, isFilled);
		drawTerrain(node->sudEst, isFilled);
	}
}
