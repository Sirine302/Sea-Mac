#ifndef DRAW_H
#define DRAW_H

//linux
#include <GL/gl.h>
#include <GL/glu.h>

//Dessine un ARBRE :) 
void drawBillboard(float phi, GLuint texture, Point3D scale);

//Dessine la Skybox
void drawCenteredBox(float length , GLuint* textureSky);

GLuint generateTextureJpg(char* name);

#endif