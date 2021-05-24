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

	GLuint m_id_texture;		// Texture appliquée sur la heightmap
	GLuint m_id_display_list;	// ID de la display list
	
	// Dimensions & Hauteur maximale d'un point de la heightmap
	int xMax;				// nb row .pgm 
	int yMax;				// nb col .pgm
	int zMax;	 			// valeur max .pgm	

	int zMaxConfig;
	
	Point* tabPoints;		// Récupère les coordonnées de chaque point
	bool m_loaded;			// Indique si la map a bien été chargée.
}Heightmap;


// Chargement des données du .pgm
Heightmap* createHeightmap(Config config); 

void displayMap(Heightmap map, bool isFilled); // à ranger dans "display.cpp"

void Free(Heightmap * map);		// Libère la mémoire allouée s'il y en a(appelée par le destructeur automatiquement).

#endif // HEIGHT_MAP_H