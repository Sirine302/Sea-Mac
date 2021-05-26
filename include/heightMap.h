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

#include "geometry.h"
#include "config.h"

using namespace std;

typedef struct Heightmap {
	// Dimensions & Hauteur maximale d'un point de la heightmap
	int xMax;				// nb row .pgm 
	int yMax;				// nb col .pgm
	int zMax;	 			// valeur max .pgm	

	int zMaxConfig;
	bool m_loaded;			// Indique si la map a bien été chargée.
}Heightmap;

// Chargement des données du .pgm
Heightmap* createHeightmap(Config config); 

int ** recupAllZ(char* fichier, int xMax, int yMax, int zMax);
float findZ(int ** array, int x, int y);

float heightColor(float a, float b, float c, int zMax);
void displayMap(Heightmap map, bool isFilled); // à ranger dans "display.cpp"

void Free(Heightmap * map);		// Libère la mémoire allouée s'il y en a(appelée par le destructeur automatiquement).

#endif // HEIGHT_MAP_H