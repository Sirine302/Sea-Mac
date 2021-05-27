#include "geometry.h"


/* 

FRUSTUM CULLING 

Déterminer quels sont les carrés dans le champs de la caméra 

3 CAS :
    - le triangle représentant le champ de la cam est dans le carré de la node 
    - le carré de la node est entièrement dans le champ de la cam
    - une partie seulement du carré est traversé par la cam

    - tester ces trois cas dans une fonction 
        - renvoie true si le cas est dans le champ 
        - sinon renvoie false

*/ 

Point createPoint(float x, float y, float z) {
	Point  point;
	point.x = x;
	point.y = y;
	point.z = z;
	return point;
}

Vect2D create2D(float x, float y) {
	Vect2D vect;
	vect.x = x;
	vect.y = y;
	return vect;
}


Vect2D createVectorFromPoints(Point2D p1, Point2D p2){   
    Vect2D vect;
    vect.x = p2.x - p1.x;
    vect.y = p2.y - p1.y;
    return vect;
}

Vect2D VectPlusVect(Vect2D p, Vect2D v){
    Vect2D newPoint;
    newPoint.x = p.x + v.x;
    newPoint.y = p.y + v.y;
    return newPoint;
}

// Norme d'un vecteur V
float norm(Vect2D v){
    float norme;
    norme = sqrt(v.x * v.x + v.y * v.y);
    return norme;
}


Square createSquare(int x, int y, int largeur, int hauteur) {
    Square aSquare;
    aSquare.x = x;
    aSquare.y = y;
    aSquare.largeur = largeur;
    aSquare.hauteur = hauteur;
    return aSquare;
}

// créer un triangle (calculs à vérifier, j'ai probablement écrit n'importe quoi)
Triangle createTriangle(Point2D position, int zFar, int fov) {
    Triangle tri;

    Point2D* positionFar = new Point2D; 
    *positionFar = create2D(0, zFar);
    Vect2D * distZfar = new Vect2D;
    *distZfar = createVectorFromPoints(position, *positionFar);

    float normOp = tan(fov/2) * norm(*distZfar);
    float thetaOp = M_PI/2; 

    tri.p1 = position;
    tri.p2 = create2D(normOp*cos(thetaOp), normOp*sin(thetaOp));
    tri.p3 = create2D(- normOp*cos(thetaOp), normOp*sin(thetaOp));

    return tri;
}

// vérifie si le point est dans le square de la node 
bool pointInSquare(Point point, Square rect){
    return (point.x >= rect.x - rect.largeur &&
            point.x <= rect.x + rect.largeur &&
            point.y >= rect.y - rect.hauteur && 
            point.y <= rect.y + rect.hauteur);
}

// vérifie si le point est dans le triangle de la vue caméra
// si le point est à droite de tous les côtés, alors il est dans le triangle 

float dot(Vect2D v1, Vect2D v2)
{
    return v1.x * v2.x + v1.y * v2.y;
}

bool isRightSide(Vect2D point, Vect2D p1, Vect2D p2) {
    Vect2D normale = {p2.y-p1.y, p1.x-p2.x};
    Vect2D direction = {point.x - p1.x, point.y - p1.y};
    return dot(normale,direction) > 0;
}

// si le point est dans le champ de la caméra 
bool pointInTriangle(Vect2D point, Triangle triangle) {
    if (isRightSide(point, triangle.p1, triangle.p2) &&
        isRightSide(point, triangle.p2, triangle.p3) &&
        isRightSide(point, triangle.p3, triangle.p1)) {
        return true;
    }
    else {
        return false;
    }
}

// vérifie si intersection entre le triangle et le rectangle 
// bool intersection(Triangle tri, Square rect) {
//     if (pointInSquare(tri.p1, rect) ||
//         pointInSquare(tri.p2, rect) ||
//         pointInSquare(tri.p3, rect) || 

//         pointInTriangle(create2D(rect.l1, rect.h1), tri) ||
//         pointInTriangle(create2D(rect.l1, rect.h2), tri) ||
//         pointInTriangle(create2D(rect.l2, rect.h1), tri) ||
//         pointInTriangle(create2D(rect.l2, rect.h2), tri)) {
//         return true;
//     }

//     else {
//         return false;
//     }
// }