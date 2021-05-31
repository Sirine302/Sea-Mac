#include "gldrawing.h"

#include <stdio.h>

void glDrawRepere(float length) {
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
void drawCam(Triangle tri) {
	glBegin(GL_TRIANGLE_STRIP);
		glColor3f(1., 0., 0.);
		glVertex3f(tri.p1.x, 3., tri.p1.y);
		glVertex3f(tri.p2.x, 3., tri.p2.y);
		glVertex3f(tri.p3.x, 3., tri.p3.y);
	glEnd();
}

void drawTriangles(Point NO, Point NE, Point SO, Point SE, bool isFilled) {
	glEnable(GL_DEPTH_TEST);	
	if (isFilled) {
		glBegin(GL_TRIANGLE_STRIP);
	}
	else {
		glBegin(GL_LINE_STRIP);
	}
		float m1 = heightColor(SO.z, NO.z, NE.z, 255);
		float m2 = heightColor(SO.z, SE.z, NE.z, 255);

		glColor3f(0., 0., m1);
		glVertex3f(SO.x, SO.z / 255 * 3, SO.y);
		glVertex3f(NO.x, NO.z / 255 * 3, NO.y);
		glVertex3f(NE.x, NE.z / 255 * 3, NE.y);

		glColor3f(0., 0., m2);
		glVertex3f(SO.x, SO.z / 255 * 3, SO.y);
		glVertex3f(SE.x, SE.z / 255 * 3, SE.y);
		glVertex3f(NE.x, NE.z / 255 * 3, NE.y);

	glEnd();
}

void drawTerrain(Node * node, Image image, bool isFilled, bool frustum, float time, Point2D posCam) {

	if ((isLeaf(node) && frustum)) {	
		Point NO = createPoint(	node->surface.x1, 
								node->surface.y1, 
								findZ(image.allZ, 
									  node->surface.x1, 
									  node->surface.y1, time));

		Point NE = createPoint(	node->surface.x2, 
								node->surface.y1, 
								findZ(image.allZ, 
									  node->surface.x2, 
									  node->surface.y1, time));

		Point SO = createPoint(	node->surface.x1, 
								node->surface.y2, 
								findZ(image.allZ, 
									  node->surface.x1, 
									  node->surface.y2, time));

		Point SE = createPoint(	node->surface.x2, 
								node->surface.y2, 
								findZ(image.allZ, 
									  node->surface.x2, 
									  node->surface.y2, time));

		drawTriangles(NO, NE, SO, SE, isFilled);
	}
	else {
		drawTerrain(node->nordOuest, image, isFilled, frustum, time, posCam);
		drawTerrain(node->nordEst, image, isFilled, frustum, time, posCam);
		drawTerrain(node->sudOuest, image, isFilled, frustum, time, posCam);
		drawTerrain(node->sudEst, image, isFilled, frustum, time, posCam);
	}
}
