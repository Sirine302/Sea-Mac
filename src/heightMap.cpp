// HeightMap.cpp

#include "../include/heightMap.h"


// créer createHeightmap 
Heightmap* createHeightmap(Config config) {
	Heightmap* myMap = new Heightmap;
	int xMax, yMax, zMax;

	ifstream infile(config.config);
	stringstream ss;
	string inputLine = "";

	// First line : version
	getline(infile,inputLine);
	cout << "Version : " << inputLine << endl;

	// Line 2 : comment 
	getline(infile,inputLine);
	cout << inputLine << endl;

	// Continue with a stringstream
	ss << infile.rdbuf();

	// Line 3 : size
	ss >> yMax >> xMax;
	cout << yMax << " columns and " << xMax << " rows" << endl;
	
	ss >> zMax; 
	cout << "Valeur couleur max : " << zMax << endl;

	myMap->xMax = xMax;
	myMap->yMax = yMax;
	myMap->zMax = zMax;
	myMap->zMaxConfig = config.zmax;

	infile.close();
	return myMap;
}

// tableau permettant de récupérer les Z 
int ** recupAllZ(char* fichier, int xMax, int yMax, int zMax) {

	ifstream infile(fichier);
	stringstream ss;
	string inputLine = "";
	
	getline(infile,inputLine);
	getline(infile,inputLine);
	ss << infile.rdbuf();
	ss >> yMax >> xMax;
	ss >> zMax; 

	int ** tab = (int **)malloc(xMax*sizeof(int*));

	for (int i = 0; i < xMax; i++) {
		tab[i] = (int *)malloc(yMax*sizeof(int));
		
		for (int j = 0; j<yMax; j++) {
			ss >> tab[i][j];
		}		
	}

	cout << "Données du .pgm récupérées." << endl;
	infile.close();

	return tab;
}

float findZ(int ** array, int x, int y) {
    return array[x][y];
}

// float findZ(int x, int y, Heightmap map) {
// 	return map.tabPoints[x + y * map.xMax].z ;
// }

float heightColor(float a, float b, float c, int zMax) {
	return (a+b+c)/(3*zMax);
}

// void displayMap(Heightmap map, bool isFilled) {

// 	for(int y = 0; y < map.yMax - 1; y++) {
// 		for(int x = 0; x < map.xMax - 1; x ++) {
// 		if (isFilled) {
// 			glBegin(GL_TRIANGLE_STRIP);
// 		}
// 		else {
// 			glBegin(GL_LINE_STRIP);
// 		}

// 			// Triangle 1
// 			float m1 = heightColor(	map.tabPoints[x + y * map.xMax].z/map.zMaxConfig, 
// 									map.tabPoints[x + y+1 * map.xMax].z/map.zMaxConfig,
// 									map.tabPoints[x+1 + y+1 * map.xMax].z/map.zMaxConfig);

// 			glColor3f(0.0, m1, 0.0);						// couleur selon hauteur moyenne
// 			glVertex3f(x, findZ(x, y, map), y);				// 1
// 			glVertex3f(x, findZ(x, y+1, map), y+1);			// 2
// 			glVertex3f(x+1, findZ(x+1, y+1, map), y+1);		// 3

// 			// // Triangle 2
// 			float m2 = heightColor(	map.tabPoints[x + y * map.xMax].z/map.zMaxConfig, 
// 									map.tabPoints[x+1 + y * map.xMax].z/map.zMaxConfig,
// 									map.tabPoints[x+1 + y+1 * map.xMax].z/map.zMaxConfig);
// 			glColor3f(0.0, m2, 0.0);						// Couleur selon hauteur moyenne
// 			glVertex3f(x, findZ(x, y, map), y);				// 1
// 			glVertex3f(x+1, findZ(x+1, y, map), y);			// 4
// 			glVertex3f(x+1, findZ(x+1, y+1, map), y+1);		// 3
			
// 		glEnd();
// 		}
// 	}

// 	map.m_loaded = true;									// Le chargement s'est bien passé.
// }

// void Free(Heightmap * map) {
// 	// Si des données sont allouées dans tabPoints on les libère.
// 	if(map->m_loaded)
// 	{
// 		delete [] map->tabPoints;
// 		map->tabPoints = NULL;
// 		map->m_loaded = false;
// 	}
// }
