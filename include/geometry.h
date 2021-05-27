#ifndef GEOMETRY_H
#define GEOMETRY_H

# include <math.h>

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
    float x;
    float y;
    float largeur;
    float hauteur;
}Square;

typedef struct Triangle {
    Vect2D p1;
    Vect2D p2;
    Vect2D p3;
}Triangle, Camera;


// Création d'un point à partir de ses coordonnées 
Point createPoint(float x, float y, float z);

Vect2D create2D(float x, float y);

Vect2D createVectorFromPoints(Point2D p1, Point2D p2);

Vect2D VectPlusVect(Vect2D p, Vect2D v);

// Norme d'un vecteur V
float norm(Vect2D v);

Square createSquare(int x, int y, int largeur, int hauteur);

// créer un triangle (calculs à vérifier, j'ai probablement écrit n'importe quoi)
Triangle createTriangle(Point2D position, int zFar, int fov);

// vérifie si le point est dans le square de la node 
bool pointInSquare(Point point, Square rect);

// vérifie si le point est dans le triangle de la vue caméra
// si le point est à droite de tous les côtés, alors il est dans le triangle
float dot(Vect2D v1, Vect2D v2);
bool isRightSide(Vect2D point, Vect2D p1, Vect2D p2);

// si le point est dans le champ de la caméra 
bool pointInTriangle(Vect2D point, Triangle triangle);

// vérifie si intersection entre le triangle et le rectangle 
bool intersection(Triangle tri, Square rect);


#endif