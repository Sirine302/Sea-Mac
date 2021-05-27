#include <GL/glut.h>
#include <iostream>

#include "quadTree.h"

using namespace std;

// Ici : définition de toutes les fonctions liées au quadTree 

Node * initNode(Node * newNode, Square rect) {
    newNode->surface = rect;

    newNode->nordOuest = nullptr;
    newNode->nordEst = nullptr;
    newNode->sudOuest = nullptr;
    newNode->sudEst = nullptr;

    newNode->nbPoints = 0;

    return newNode;
}

void insert(Node* node, Point point) {
    cout << point.x << " " << point.y << " " << point.z << endl;
    if (pointInSquare(point, node->surface)) {
        if (node->nbPoints < 4) {
            node->tabPoints[node->nbPoints] = point;
            node->nbPoints++;
        } 
        else {
            if (isLeaf(node)) {
                subdivide(node);
            }
            repartition(point, node);
        }
    }
    else {
        cout << "out of square" << endl;
    }
}

void subdivide(Node * node) {

    node->nordOuest = new Node();
    node->nordEst = new Node();
    node->sudOuest = new Node();
    node->sudEst = new Node();

    // Le point de référence est au centre de la surface 
    float x = node->surface.x; 
    float y = node->surface.x; 
    float w = node->surface.largeur;
    float h = node->surface.hauteur;

    cout << "coord point ref : " << x << " " << y << " " << w << " " << h << endl;

    Square rectNO = createSquare(x - w/2, y + h/2, w/2, h/2);
    Square rectNE = createSquare(x + w/2, y + h/2, w/2, h/2);
    Square rectSO = createSquare(x - w/2, y - h/2, w/2, h/2);
    Square rectSE = createSquare(x + w/2, y - h/2, w/2, h/2);

    initNode(node->nordOuest, rectNO);
    initNode(node->nordEst, rectNE);
    initNode(node->sudOuest, rectSO);
    initNode(node->sudEst, rectSE);
}

// à voir si on en a besoin 
void repartition(Point point, Node* node)
{
    if (pointInSquare(point, node->nordOuest->surface)) {
        insert(node->nordOuest, point);
    } 
    else if(pointInSquare(point, node->nordEst->surface)) {
        insert(node->nordEst, point);
    }
    else if(pointInSquare(point, node->sudOuest->surface)) {
        insert(node->sudOuest, point);
    }
    else if(pointInSquare(point, node->sudEst->surface)) {
        insert(node->sudEst, point);
    }
}

bool isLeaf(Node * node) {
    if (!node->nordOuest && !node->nordEst && !node->sudOuest && !node->sudEst) {
        return true;   // true = c'est une feuille  
    }
    else {
        return false;    // false = pas une feuille
    }
}

/*

Parcours de l'arbre : 
    > récupération des z OK 
    > affichage des triangles (faire fonction drawQuad / drawTriangle)
        - condition 0 : si c'est une feuille 
        - condition 1 : le LOD le permet 
        - condition 2 : le Frustum Culling le permet 
            > Si on appuie sur F
                    > Vision fils de fer 
                        - Si c'est une feuille 
                            > Couleur qui change 
*/