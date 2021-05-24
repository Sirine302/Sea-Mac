// HeightMap.h - représente une heightmap.
#ifndef HEIGHT_MAP_H
#define HEIGHT_MAP_H

#ifdef WIN32
#include <windows.h>
#endif
#include <GL/gl.h>
#include <GL/glu.h>
#include "TGALoader.h"
#include <iostream>
#include <fstream>
#include <sstream> 

using namespace std;

typedef struct Point {
	float x;
	float y;
	float z;
}Point;

typedef struct Heightmap {

	GLuint m_id_texture;		// Texture appliquée sur la heightmap
	GLuint m_id_display_list;	// ID de la display list
	
	// Dimensions & Hauteur maximale d'un point de la heightmap
	int xMax;				// nb row .pgm 
	int yMax;				// nb col .pgm
	int zMax;	 			// valeur max .pgm	

	Point* tabPoints;		// Récupère les coordonnées de chaque point
	bool m_loaded;			// Indique si la map a bien été chargée.
}Heightmap;

// Création d'un point à partir de ses coordonnées 
Point createPoint(float x, float y, float z);

// Chargement des données du .pgm
Heightmap* createHeightmap(char* fichier); 
void displayMap(Heightmap map, bool isFilled);

void Afficher(Heightmap map, GLuint list);	// Fait ce qu'elle dit...
void Free(Heightmap * map);		// Libère la mémoire allouée s'il y en a(appelée par le destructeur automatiquement).



/*
bool IsLoaded(Heightmap * map); // vérifie le chargement de la map 

// Retourne la largeur de la heightmap chargée (correspond au nombre de pixels en largeur de l'image chargée).
inline unsigned int GetWidth(Heightmap * map);

// Pareil mais avec la hauteur de l'image (qui devient profondeur de la heightmap).
inline unsigned int GetDepth(Heightmap * map);

// Renvoie la hauteur d'un point en (x, y) : dépend de m_hauteur_max et de la "noirceur" du point.
inline float HeightOfPointAt(int x, int y);
	// return (float)m_hauteur_max - ((float)m_data[x+y*m_width]/255.0)*(float)m_hauteur_max;
*/

#endif // HEIGHT_MAP_H