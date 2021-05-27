#ifndef GLDRAWING_H
#define GLDRAWING_H

#include <GL/gl.h>
# include "heightMap.h"
# include "quadTree.h"
#include "visu.h"

// Fonction de dessin d'un repere. L'axe x est rouge, l'axe y vert et l'axe z bleu.
void glDrawRepere(float length);
void drawTest();
void drawRect(Point ref);

void drawTerrain(Node * node, bool isFilled);
void drawTriangles(Node * node, bool isFilled);

#endif
