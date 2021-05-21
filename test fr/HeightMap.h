// HeightMap.h - représente une heightmap.
// 2004 par Funto. Si vous utilisez cette classe dans un de vos projets, un mail
// de remerciement à funto@nomade.fr serait le bienvenu ;).

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
using namespace std;

class HeightMap
{
public:
	HeightMap();
	~HeightMap();
	// Fonction à appeler une seule fois : elle lit un fichier HMAP et le charge.
	bool LoadFile(char* str_fichier,	// Chemin du fichier à charger
		unsigned int hauteur_max,		// Hauteur maximum atteignable par un point
									// de la heightmap (correspond à un point noir).
		unsigned int largeur_quad,	// Largeur de chaque quad qui compose la
									// heightmap.
		TGAFiltering filtering=TGA_NO_FILTER);	// Filtering de la texture.
	void Afficher();	// Fait ce qu'elle dit...
	void Free();		// Libère la mémoire allouée s'il y en a(appelée par le
						// destructeur automaiquement).
	inline unsigned int GetWidth() {return m_width;}	// Retourne la largeur de
								// la heightmap chargée (correspond au nombre de
								// pixels en largeur de l'image chargée).
	inline unsigned int GetDepth() {return m_depth;}	// Pareil mais avec la
								// hauteur de l'image (qui devient profondeur de la
								// heightmap).
	inline float HeightOfPointAt(int x, int y)	// Renvoie la hauteur d'un point
								// en (x, y). Elle dépend de m_hauteur_max et
								// de la "noirceur" du point sur le fichier image.
	{
		return (float)m_hauteur_max - ((float)m_data[x+y*m_width]/255.0)*(float)m_hauteur_max;
	}
	inline bool IsLoaded() {return m_loaded;}	// Renvoie true si la map est bien
												// chargée.
private:
	GLuint m_id_texture;	// ID de la texture appliquée sur la heightmap
	GLuint m_id_display_list;	// ID de la display list
	unsigned int m_width, m_depth,	// Dimensions
		m_hauteur_max;				// Hauteur maximale d'un point de la heightmap
	unsigned char* m_data;		// Les données chargées, décompressées.
	bool m_loaded;			// Indique si la map a bien été chargée.
};

#endif // HEIGHT_MAP_H
