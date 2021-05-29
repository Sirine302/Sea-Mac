// #include <SDL/SDL.h>
// #include <SDL/SDL_image.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
# include <iostream>
#include "draw.h"



//Dessine un ARBRE :) 
// void drawBillboard(float phi, GLuint texture, Point3D scale) {
//             glRotatef(phi*(360/(2*M_PI)),0.,0.,1.);
//             glScalef(scale.x,scale.y,scale.z);
//             glEnable(GL_TEXTURE_2D);
//             glBindTexture(GL_TEXTURE_2D, texture);
//             glBegin(GL_QUADS);

//                 //ColorRGB eclairage = illuminationLambert(createPoint(0.5,0.,0.), createPoint(0.,0.,0.), createPoint(0.,0.5,0.), soleil);
//                 //glColor3f(eclairage.r,eclairage.g,eclairage.b);

//                 glTexCoord2f(0.,0.);
//                 glVertex3f(0.,-0.5,1.);

//                 glTexCoord2f(1.,0.);
//                 glVertex3f(0.,0.5,1.);

//                 glTexCoord2f(1.,1.);
//                 glVertex3f(0.,0.5,0.);

//                 glTexCoord2f(0.,1.);
//                 glVertex3f(0.,-0.5,0.);

//             glEnd();
//             glBindTexture(GL_TEXTURE_2D, 0);
//             glDisable(GL_TEXTURE_2D);
// }




//Dessine la Skybox
void drawCenteredBox(float length, GLuint* textureSky) {

    float currentColor[4];
    glGetFloatv(GL_CURRENT_COLOR,currentColor);
    glEnable(GL_TEXTURE_2D);
    
    float l = length/2;
    //glColor3f(1., 1., 1.);
    glColor3f(120, 120, 120);


   /***** 2 = TOP ******/
    glBindTexture(GL_TEXTURE_2D, textureSky[5]);
    glBegin(GL_QUADS);
        glTexCoord2f(1.,1.); glVertex3f(-l , l, -l);
        glTexCoord2f(1.,0.); glVertex3f(-l , l, l);
        glTexCoord2f(0.,0.); glVertex3f(l , l, l);
        glTexCoord2f(0.,1.); glVertex3f(l , l, -l);
    glEnd();

   /***** 4 = FLOOR | OK ******/ 
    glBindTexture(GL_TEXTURE_2D, textureSky[4]);
    glBegin(GL_QUADS);
        
        glTexCoord2f(1.,0.); glVertex3f(-l , -l, -l);
        glTexCoord2f(0.,0.); glVertex3f(l , -l, -l);
        glTexCoord2f(0.,1.); glVertex3f(l , -l, l);
        glTexCoord2f(1.,1.);glVertex3f(-l , -l, l);
    glEnd();



   /***** 1 = face 1 ******/
    glBindTexture(GL_TEXTURE_2D, textureSky[3]);
    glBegin(GL_QUADS);
        glTexCoord2f(1.,1.);  glVertex3f(-l,-l,l);
        glTexCoord2f(1.,0.); glVertex3f(-l,l,l);
        glTexCoord2f(0.,0.);glVertex3f(-l,l,-l);
        glTexCoord2f(0.,1.); glVertex3f(-l,-l,-l);
    glEnd();

    
   /***** 3 = face 2 OK + COHERENTE AU PLAFOND ******/
    glBindTexture(GL_TEXTURE_2D, textureSky[2]);
    glBegin(GL_QUADS);
        glTexCoord2f(1.,1.); glVertex3f(l , -l, -l);
        glTexCoord2f(1.,0.); glVertex3f(l , l, -l);
        glTexCoord2f(0.,0.); glVertex3f(l , l, l);
        glTexCoord2f(0.,1.); glVertex3f(l , -l, l);
    glEnd();



   /***** 5 = face 3 ******/
    glBindTexture(GL_TEXTURE_2D, textureSky[1]);
    glBegin(GL_QUADS);
        
        glTexCoord2f(1.,1.); glVertex3f(-l , -l, -l);
        glTexCoord2f(1.,0.); glVertex3f(-l , l, -l);
        glTexCoord2f(0.,0.); glVertex3f(l , l, -l);
        glTexCoord2f(0.,1.); glVertex3f(l , -l, -l);
    glEnd();


   /***** 6 = face 4 ******/
    glBindTexture(GL_TEXTURE_2D, textureSky[0]);
    glBegin(GL_QUADS);
        glTexCoord2f(1.,1.); glVertex3f(l , -l, l);
        glTexCoord2f(1.,0.); glVertex3f(l , l, l);
        glTexCoord2f(0.,0.); glVertex3f(-l , l, l);
        glTexCoord2f(0.,1.); glVertex3f(-l , -l, l);
    glEnd();
    

    // glBindTexture(GL_TEXTURE_2D, 0);
    // glDisable(GL_TEXTURE_2D);   
}


GLuint generateTextureJpg(char* name){
    GLuint textureId;
    
    SDL_Surface* image = IMG_Load(name);
    if(!image){
        printf("%s\n", IMG_GetError());
    }
    else{
    glGenTextures(1, &textureId);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->w, image->h, 0, GL_RGB, GL_UNSIGNED_BYTE, image->pixels);
    glBindTexture(GL_TEXTURE_2D, 0);
     }
    return textureId;

}