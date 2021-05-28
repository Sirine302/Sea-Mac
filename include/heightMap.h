// HeightMap.h - représente une heightmap.
#ifndef HEIGHT_MAP_H
#define HEIGHT_MAP_H

#ifdef WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
#include <fstream>
#include <sstream> 
# include <stdlib.h>
# include <stdio.h>
# include <math.h>

#include "geometry.h"
#include "config.h"
#include "quadTree.h"

using namespace std;

typedef struct Image {
	int xMax;				// nb row .pgm 
	int yMax;				// nb col .pgm
	int zMax;	 			// valeur max .pgm	

	int ** allZ;			// tableau de tous les Z
}Image;

Image* loadImage(Config config); 
float findZ(int ** array, int x, int y);
float heightColor(float a, float b, float c, int zMax);

#endif // HEIGHT_MAP_H