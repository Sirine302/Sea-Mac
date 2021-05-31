#ifndef GLDRAWING_H
#define GLDRAWING_H

# include <GL/gl.h>
# include "heightMap.h"
# include "quadTree.h"
# include "visu.h"
# include "geometry.h"

// Fonction de dessin d'un repere. L'axe x est rouge, l'axe y vert et l'axe z bleu.
void glDrawRepere(float length);
void drawCam(Triangle tri);
void drawTerrain(Node * node, Image image, bool isFilled, bool frustum, float timerr, Point2D posCam);
void drawTriangles(Point NO, Point NE, Point SO, Point SE, bool isFilled) ;

#endif
