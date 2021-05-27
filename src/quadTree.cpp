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

    if (rect.largeur > 1) {

        newNode->nordOuest = new Node();
        newNode->nordEst = new Node();
        newNode->sudOuest = new Node();
        newNode->sudEst = new Node();

        // Le point de référence est au centre de la surface 
        float x = newNode->surface.x; 
        float y = newNode->surface.y; 
        float w = newNode->surface.largeur;
        float h = newNode->surface.hauteur;

        cout << endl << "je subdivise autour du point : " << x << " " << y << " " << w << " " << h << endl;

        Square rectNO = createSquare(x - w/2, y + h/2, w/2, h/2);
        Square rectNE = createSquare(x + w/2, y + h/2, w/2, h/2);
        Square rectSO = createSquare(x - w/2, y - h/2, w/2, h/2);
        Square rectSE = createSquare(x + w/2, y - h/2, w/2, h/2);

        initNode(newNode->nordOuest, rectNO);
        initNode(newNode->nordEst, rectNE);
        initNode(newNode->sudOuest, rectSO);
        initNode(newNode->sudEst, rectSE);
    }
    return newNode;
}

void insert(Node* node, Point point) {

    if (!isLeaf(node)) {
        if (pointInSquare(point, node->nordOuest->surface)) {
            insert (node->nordOuest, point); 
        }
        if(pointInSquare(point, node->nordEst->surface)) {
            insert(node->nordEst, point);
        }
        if(pointInSquare(point, node->sudOuest->surface)) {
            insert(node->sudOuest, point);
        }
        if(pointInSquare(point, node->sudEst->surface)) {
            insert(node->sudEst, point);
        }
    }

    else if (isLeaf(node)) {
        // cout << "je veux insérer " << point.x << " " << point.y << " " << point.z << endl;

        if (node->nbPoints < 4) {
            node->tabPoints[node->nbPoints] = point;
            node->nbPoints++;
        } 
        else {
            cout << "ERROR" << endl;
        }
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


uint heightQuadTree(Node * node) {
    uint heightNO = 0;
    uint heightNE = 0;
    uint heightSO = 0;
    uint heightSE = 0;

    if (isLeaf(node)) {
        return 1;
    }

    if (node->nordOuest) {
        heightNO = heightQuadTree(node->nordOuest);
    }
    if (node->nordEst) {
        heightNE = heightQuadTree(node->nordEst);
    }
    if (node->sudOuest) {
        heightSO = heightQuadTree(node->sudOuest);
    }
    if (node->sudEst) {
        heightSE = heightQuadTree(node->sudEst);
    }

    if (heightNO >= heightNE && 
        heightNO >= heightSO && 
        heightNO >= heightSE) {
        return heightNO + 1;
    }
    else if (heightNE >= heightNO && 
             heightNE >= heightSO && 
             heightNE >= heightSE) {
        return heightNE + 1;
    }
    else if (heightSO >= heightNO && 
             heightSO >= heightNE && 
             heightSO >= heightSE) {
        return heightSO + 1;
    }
    else if (heightSE >= heightNO && 
             heightSE >= heightSO && 
             heightSE >= heightNE) {
        return heightSE + 1;
    }

    return -1;

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