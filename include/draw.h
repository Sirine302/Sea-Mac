#ifndef DRAW_H
#define DRAW_H

//linux
#include <GL/gl.h>
#include <GL/glu.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
# include <iostream>

// Bateau 
void drawBoat(float angle, GLuint texture, Point position);
// Skybox
void drawCenteredBox(float length , GLuint* textureSky);

GLuint generateTextureJpg(char* name);

#endif