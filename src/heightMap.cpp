// HeightMap.cpp

#include "../include/heightMap.h"


// créer createHeightmap 
Heightmap* createHeightmap(Config config) {
	Heightmap* myMap = new Heightmap;

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
	ss >> myMap->yMax >> myMap->xMax;
	cout << myMap->yMax << " columns and " << myMap->xMax << " rows" << endl;
	
	ss >> myMap->zMax; 
	cout << "Valeur couleur max : " << myMap->zMax << endl;

	int array[myMap->xMax][myMap->yMax];
	myMap->tabPoints = new Point[myMap->xMax * myMap->yMax];
	int count = 0;


	for(int x = 0; x < myMap->xMax; x++) {
		for (int y = 0; y < myMap->yMax; y++){ 

			ss >> array[x][y];
			float z = array[x][y];

			float newX = (x/myMap->xMax) * config.xsize;
			float newY = (y/myMap->yMax) * config.ysize;
			float newZ = (z/myMap->zMax) * config.zmax;

			Point newPoint = createPoint(newX, newY, newZ);
			myMap->tabPoints[count] = newPoint;
			count++;
		}
	}
	myMap->zMaxConfig = config.zmax;
	
	cout << "Données du .pgm récupérées." << endl;	
	infile.close();
	return myMap;
}

float findZ(int x, int y, Heightmap map) {
	return map.tabPoints[x + y * map.xMax].z ;
}

float heightColor(float a, float b, float c) {
	return (a+b+c)/3;
}

void displayMap(Heightmap map, bool isFilled) {

	for(int y = 0; y < map.yMax - 1; y++) {
		for(int x = 0; x < map.xMax - 1; x ++) {
		if (isFilled) {
			glBegin(GL_TRIANGLE_STRIP);
		}
		else {
			glBegin(GL_LINE_STRIP);
		}

			// Triangle 1
			float m1 = heightColor(	map.tabPoints[x + y * map.xMax].z/map.zMaxConfig, 
									map.tabPoints[x + y+1 * map.xMax].z/map.zMaxConfig,
									map.tabPoints[x+1 + y+1 * map.xMax].z/map.zMaxConfig);
			glColor3f(0.0, m1, 0.0);						// couleur selon hauteur moyenne
			glVertex3f(x, findZ(x, y, map), y);				// 1
			glVertex3f(x, findZ(x, y+1, map), y+1);			// 2
			glVertex3f(x+1, findZ(x+1, y+1, map), y+1);		// 3

			// // Triangle 2
			float m2 = heightColor(	map.tabPoints[x + y * map.xMax].z/map.zMaxConfig, 
									map.tabPoints[x+1 + y * map.xMax].z/map.zMaxConfig,
									map.tabPoints[x+1 + y+1 * map.xMax].z/map.zMaxConfig);
			glColor3f(0.0, m2, 0.0);						// Couleur selon hauteur moyenne
			glVertex3f(x, findZ(x, y, map), y);				// 1
			glVertex3f(x+1, findZ(x+1, y, map), y);			// 4
			glVertex3f(x+1, findZ(x+1, y+1, map), y+1);		// 3
		glEnd();
		}
	}

	map.m_loaded = true;									// Le chargement s'est bien passé.
}

void Free(Heightmap * map) {
	// Si des données sont allouées dans tabPoints on les libère.
	if(map->m_loaded)
	{
		delete [] map->tabPoints;
		map->tabPoints = NULL;
		map->m_loaded = false;
	}
}
