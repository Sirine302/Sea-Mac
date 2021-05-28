#include "geometry.h"


/* ============= POINTS & VECTEURS ============== */ 

// crée point 3D 
Point createPoint(float x, float y, float z) {
	Point  point;
	point.x = x;
	point.y = y;
	point.z = z;
	return point;
}

// crée vecteur 3D 
Vector create3D(float x, float y, float z) {
	Vector vect;
	vect.x = x;
	vect.y = y;
	vect.z = z;
	return vect;
}

// crée vecteur / point 2D 
Vect2D create2D(float x, float y) {
	Vect2D vect;
	vect.x = x;
	vect.y = y;
	return vect;
}

// crée vecteur avec deux points 
Vect2D createVectorFromPoints(Point2D p1, Point2D p2){   
    Vect2D vect;
    vect.x = p2.x - p1.x;
    vect.y = p2.y - p1.y;
    return vect;
}


/* ====== OPERATIONS SUR POINTS & VECTEURS ====== */ 

// addition de vecteurs 
Vect2D VectPlusVect(Vect2D p, Vect2D v){
    Vect2D newPoint;
    newPoint.x = p.x + v.x;
    newPoint.y = p.y + v.y;
    return newPoint;
}

// produit vectoriel 
Vector produitVect(Vector a, Vector b) {
    Vector produit;
    produit.x = a.y * b.z - a.z * b.y;
    produit.y = -a.x * b.z + a.z * b.x;
    produit.z = a.x * b.y -a.y * b.x;
    return produit;
}

// norme du vecteur 
float norm(Vect2D v){
    return sqrt(v.x * v.x + v.y * v.y);
}

// produit scalaire 
float dot(Vect2D v1, Vect2D v2) {
    return v1.x * v2.x + v1.y * v2.y;
}

// normalise le vecteur 
Vect2D normalize(Vect2D v) {
    float n = norm(v);
    if (n == 0.)
        return v;
    v.x /= n;
    v.y /= n;
    return v;
}

// multiplie le vecteur 
Vect2D multVector(Vect2D v, float a) {
    if (a == 0.) {
        v.x = 0.;
        v.y = 0.;
        return v; 
    }
    v.x *= a;
    v.y *= a;
    return v;
}

/* ============= SQUARE & TRIANGLE ============== */ 


Square createSquare(int x1, int x2, int y1, int y2) {
    Square aSquare;
    aSquare.x1 = x1;
    aSquare.y1 = y1;
    aSquare.x2 = x2;
    aSquare.y2 = y2;
    return aSquare;
}

// créer un triangle (calculs à vérifier, j'ai probablement écrit n'importe quoi)
Triangle createTriangle(Point2D positionCam, int zFar, int fov) {
    Triangle tri;
    
    positionCam.x = 0;
    positionCam.y = 0;
    zFar = 3;
    fov = 100;

    Vect2D lToZfar = create2D(positionCam.x, zFar + positionCam.y);
    Vect2D normDistZfar = normalize(lToZfar);

    float x = normDistZfar.x * cos(fov/2) + normDistZfar.y  * sin(fov/2) + positionCam.x;
    float y = - normDistZfar.x * sin(fov/2) + normDistZfar.y * cos(fov/2) + positionCam.y;

    float x2 = normDistZfar.x * cos(- fov/2) + normDistZfar.y  * sin(- fov/2) + positionCam.x;
    float y2 = - normDistZfar.x * sin(- fov/2) + normDistZfar.y * cos(- fov/2) + positionCam.y;

    Point2D proj = create2D(x,y);
    Point2D proj2 = create2D(x2,y2);
    
    float longueurH = norm(lToZfar) / cos(fov/2);
    cout << longueurH << endl;
    
    tri.p1 = positionCam;
    tri.p2 = multVector(proj, longueurH);
    tri.p3 = multVector(proj2, longueurH);
    cout << "duh" << endl;
    return tri;
}

/* =============== INTERSECTIONS ================ */ 


// vérifie si le point est dans le square de la node 
bool pointInSquare(Point2D point, Square rect){
    return (point.x >= rect.x2 - rect.x1 &&
            point.x <= rect.x2 &&
            point.y >= rect.y2 - rect.y1 && 
            point.y <= rect.y2);
}

// si le point est à droite de tous les côtés, alors il est dans le triangle 
bool isRightSide(Vect2D point, Vect2D p1, Vect2D p2) {
    Vect2D normale = {p2.y-p1.y, p1.x-p2.x};
    Vect2D direction = {point.x - p1.x, point.y - p1.y};
    return dot(normale,direction) > 0;
}

// vérifie que le point est dans le champ de la caméra 
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
bool intersection(Triangle tri, Square rect) {
    if (// triangle dans le carré de la node
        pointInSquare(tri.p1, rect) ||    
        pointInSquare(tri.p2, rect) ||
        pointInSquare(tri.p3, rect) || 
        
        // le quad est en partie dans le triangle 
        pointInTriangle(create2D(rect.x1, rect.y1), tri) ||
        pointInTriangle(create2D(rect.x1, rect.y2), tri) ||
        pointInTriangle(create2D(rect.x2, rect.y1), tri) ||
        pointInTriangle(create2D(rect.x2, rect.y2), tri)) {
        return true;
    }

    else {
        return false;
    }
}


/* 
FRUSTUM CULLING 

Déterminer quels sont les carrés dans le champ de la caméra 

3 CAS :
    - le triangle représentant le champ de la cam est dans le carré de la node O 
    - le carré de la node est entièrement dans le champ de la cam
    - une partie seulement du carré est traversé par la cam

    - tester ces trois cas dans une fonction 
        - renvoie true si le cas est dans le champ 
        - sinon renvoie false
*/ 
