# include "gldrawing.h"


// Dessine les triangles d'une node 
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

// Dessine le terrain 
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


// Dessine un bateau
void drawBoat(float angle, GLuint texture, Point position) {

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texture);

    glPushMatrix();
		// glRotatef(angle/M_PI*180, 1., 0., 0.);      // tentative de rotation 
		
		glBegin(GL_QUADS);
			glColor3f(1., 1., 1.);

			glTexCoord2f(1.,1.); 
			glVertex3f(position.x + 2, 3* position.z/ 255, position.y -2);
			
			glTexCoord2f(1.,0.); 
			glVertex3f(position.x + 2, 3* position.z/255 + 4, position.y -2);
			
			glTexCoord2f(0.,0.); 
			glVertex3f(position.x - 2, 3* position.z/255 + 4, position.y -2);
			
			glTexCoord2f(0.,1.); 
			glVertex3f(position.x- 2, 3* position.z/255, position.y -2);

		glEnd();
    glPopMatrix();
	
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}


// Dessine la Skybox
void drawCenteredBox(float length, GLuint* textureSky) {

    float currentColor[4];
    glGetFloatv(GL_CURRENT_COLOR,currentColor);
    glEnable(GL_TEXTURE_2D);
    
    float l = length/2;
    glColor3f(120, 120, 120);


   /* ================ 5 | TOP ================ */
    glBindTexture(GL_TEXTURE_2D, textureSky[5]);
    glBegin(GL_QUADS);
        glTexCoord2f(1.,1.); glVertex3f(-l , l, -l);
        glTexCoord2f(1.,0.); glVertex3f(-l , l, l);
        glTexCoord2f(0.,0.); glVertex3f(l , l, l);
        glTexCoord2f(0.,1.); glVertex3f(l , l, -l);
    glEnd();

   /* ================ 4 | FLOOR ================ */ 
    glBindTexture(GL_TEXTURE_2D, textureSky[4]);
    glBegin(GL_QUADS);
        
        glTexCoord2f(1.,0.); glVertex3f(-l , -l, -l);
        glTexCoord2f(0.,0.); glVertex3f(l , -l, -l);
        glTexCoord2f(0.,1.); glVertex3f(l , -l, l);
        glTexCoord2f(1.,1.);glVertex3f(-l , -l, l);
    glEnd();

    /* ================ 0 | Back ================ */    
    glBindTexture(GL_TEXTURE_2D, textureSky[0]);
    glBegin(GL_QUADS);
        glTexCoord2f(1.,1.); glVertex3f(l , -l, l);
        glTexCoord2f(1.,0.); glVertex3f(l , l, l);
        glTexCoord2f(0.,0.); glVertex3f(-l , l, l);
        glTexCoord2f(0.,1.); glVertex3f(-l , -l, l);
    glEnd();
    

    /* ================ 1 | Front ================ */    
    glBindTexture(GL_TEXTURE_2D, textureSky[1]);
    glBegin(GL_QUADS);
        
        glTexCoord2f(1.,1.); glVertex3f(-l , -l, -l);
        glTexCoord2f(1.,0.); glVertex3f(-l , l, -l);
        glTexCoord2f(0.,0.); glVertex3f(l , l, -l);
        glTexCoord2f(0.,1.); glVertex3f(l , -l, -l);
    glEnd();

    
   /* ================ 2 | Left ================ */
    glBindTexture(GL_TEXTURE_2D, textureSky[2]);
    glBegin(GL_QUADS);
        glTexCoord2f(1.,1.); glVertex3f(l , -l, -l);
        glTexCoord2f(1.,0.); glVertex3f(l , l, -l);
        glTexCoord2f(0.,0.); glVertex3f(l , l, l);
        glTexCoord2f(0.,1.); glVertex3f(l , -l, l);
    glEnd();



   /* ================ 3 | Right ================ */ 
    glBindTexture(GL_TEXTURE_2D, textureSky[3]);
    glBegin(GL_QUADS);
        glTexCoord2f(1.,1.);  glVertex3f(-l,-l,l);
        glTexCoord2f(1.,0.); glVertex3f(-l,l,l);
        glTexCoord2f(0.,0.);glVertex3f(-l,l,-l);
        glTexCoord2f(0.,1.); glVertex3f(-l,-l,-l);
    glEnd();

    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);   
}