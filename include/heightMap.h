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
}Image, ntm;

typedef struct Heightmap {
	Config config;
	Image image;
}Heightmap;


// Chargement des données du .pgm
Image* loadImage(Config config); 

void initMap(Heightmap * map, Config config, Image image);

float findZ(int ** array, int x, int y);
Point ** recupAllPoints(char* fichier, int xMax, int yMax, int zMax);
float heightColor(float a, float b, float c, int zMax);
void Free(Image * map);		// Libère la mémoire allouée s'il y en a(appelée par le destructeur automatiquement).

#endif // HEIGHT_MAP_H