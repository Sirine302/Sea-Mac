// HeightMap.cpp
#include <ctime>
#include <math.h>
#include <SDL2/SDL.h>
#include "heightMap.h"
#include <chrono>

// créer createHeightmap 
Image* loadImage(Config config) {
	Image* image = new Image;
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

	image->xMax = xMax;
	image->yMax = yMax;
	image->zMax = zMax;

	int ** tab = (int **)malloc(xMax*sizeof(int*));

	for (int i = 0; i < xMax; i++) {
		tab[i] = (int *)malloc(yMax*sizeof(int));
		
		for (int j = 0; j<yMax; j++) {
			ss >> tab[i][j];
		}		
	}

	image->allZ = tab;

	cout << "Données du .pgm récupérées." << endl;
	infile.close();

	return image;
}

float findZ(int ** array, int x, int y, float timerr) {
	return array[x][y] + cos(timerr * x)*10;
}

float heightColor(float a, float b, float c, int zMax) {
	return (a+b+c)/(3*zMax);
}
