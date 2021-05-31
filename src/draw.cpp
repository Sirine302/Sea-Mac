# include "geometry.h"
#include "draw.h"



//Dessine un ARBRE
void drawBoat(float angle, GLuint texture, Point position) {
    
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBegin(GL_QUADS);
        glColor3f(1., 1., 1.);
        glTexCoord2f(1.,1.); glVertex3f(position.x + 2, 3* position.z/ 255, position.y -2);
        glTexCoord2f(1.,0.); glVertex3f(position.x + 2, 3* position.z/255 + 4, position.y -2);
        glTexCoord2f(0.,0.); glVertex3f(position.x - 2, 3* position.z/255 + 4, position.y -2);
        glTexCoord2f(0.,1.); glVertex3f(position.x- 2, 3* position.z/255, position.y -2);

    glEnd();
    glBindTexture(GL_TEXTURE_2D, 0);
    glDisable(GL_TEXTURE_2D);
}


//Dessine la Skybox
void drawCenteredBox(float length, GLuint* textureSky) {

    float currentColor[4];
    glGetFloatv(GL_CURRENT_COLOR,currentColor);
    glEnable(GL_TEXTURE_2D);
    
    float l = length/2;
    //glColor3f(1., 1., 1.);
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