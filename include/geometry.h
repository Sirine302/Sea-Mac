#ifndef GEOMETRY_H
#define GEOMETRY_H

typedef struct Point {
	float x;
	float y;
	float z;
}Point, Vector;

typedef struct Vect2D {
	float x;
	float y;
}Point2D, Vect2D;

typedef struct Square {
    // largeur : l2-l1 
    int l1;
    int l2;
    // hauteur : h2-h1
    int h1;
    int h2;
}Square;

typedef struct Triangle {
    Vect2D p1;
    Vect2D p2;
    Vect2D p3;
}Triangle, Camera;


// Création d'un point à partir de ses coordonnées 
Point createPoint(float x, float y, float z);




#endif