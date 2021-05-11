#ifndef _TERRAIN_H
#define _TERRAIN_H


#define MAP_SIZE		1024				// taille du fichier .raw de la height map
#define STEP_SIZE		16					// largeur et hauteur de chaque sommet
#define HEIGHT_RATIO	1.5f				// ratio de y en fct de x et z

//on renvoit la hauteur (0 à 255) à partir de la heightmap 
int Height(BYTE *pHeightMap, int X, int Y);

// loading du fichier .raw
void LoadRawFile(LPSTR strName, int nSize, BYTE *pHeightMap);

// transormation des données de la heightmap et les dessine à l'ecran
void RenderHeightMap(BYTE *pHeightMap);

#endif

