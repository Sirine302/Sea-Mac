#ifndef GLDRAWING_H
#define GLDRAWING_H

# include <GL/gl.h>
# include <GL/glu.h>
# include <SDL2/SDL.h>
# include <SDL2/SDL_image.h>
# include <string>
# include <iostream>
# include <stdio.h>

# include "heightMap.h"
# include "quadTree.h"
# include "geometry.h"

// Map 
void drawTerrain(Node * node, Image image, bool isFilled, bool frustum, float timerr, Point2D posCam);
void drawTriangles(Point NO, Point NE, Point SO, Point SE, bool isFilled) ;

// Bateau 
void drawBoat(float angle, GLuint texture, Point position);

// Skybox
void drawCenteredBox(float length , GLuint* textureSky);

GLuint generateTextureJpg(char* name);


#endif
