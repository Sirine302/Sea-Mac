#include <GL/glut.h>
#include <iostream>

#include "../include/quadTree.h"

using namespace std;

// Ici : définition de toutes les fonctions liées au quadTree 

void addNode(Node* newNode, Point NO, Point NE, Point SO, Point SE, int ** allZ) {
    // Sommets de la zone couverte par la node  
    newNode->NO = NO;
    newNode->NE = NE; 
    newNode->SO = SO;
    newNode->SE = SE;

    int l = (NO.x + NE.x)/2; // centre de la largeur du carré 
    int h = (NO.x + SO.x)/2; // centre de la hauteur du carré 

    //vérif si la longueur est toujours entière
    if (NE.x - NO.x > 1 && NO.y - SO.y > 1) {
        newNode->nordOuest = new Node;
        newNode->nordEst = new Node;
        newNode->sudOuest =  new Node;
        newNode->sudEst = new Node;
        
        // ajoute les nodes avec les coordonnées des sommets de sa zone  
        addNode(newNode->nordOuest, 
            NO, 
            createPoint(l, NO.y, findZ(allZ, l, NO.y)), 
            createPoint(NO.x, h, findZ(allZ, NO.x, h)),
            createPoint(l, h, findZ(allZ, l, h)),
            allZ);

        addNode(newNode->nordEst, 
            createPoint(l, NE.y, findZ(allZ, l, NE.y)), 
            NE, 
            createPoint(l, h, findZ(allZ, l, h)),
            createPoint(NE.x, h, findZ(allZ, NE.x, h)),
            allZ);

        addNode(newNode->sudOuest, 
            createPoint(SO.x, h, findZ(allZ, SO.x, h)),
            createPoint(l, h, findZ(allZ, l, h)),
            SO, 
            createPoint(l, SO.y, findZ(allZ, l, SO.y)),
            allZ);

        addNode(newNode->sudEst, 
            createPoint(l, h, findZ(allZ, l, h)),
            createPoint(SE.x, h, findZ(allZ, SE.x, h)),             
            createPoint(l, SE.y, findZ(allZ, l, SE.y)), 
            SE,
            allZ);    
    }
    else {
        newNode->nordOuest = nullptr;
        newNode->nordEst = nullptr;
        newNode->sudOuest =  nullptr;
        newNode->sudEst = nullptr;

    }
}

// Si une branche n'a aucun enfant, c'est une feuille 
bool isLeaf(Node * node) {
    if (!node->nordOuest && !node->nordEst && !node->sudOuest && !node->sudEst) {
        return true;   // true = c'est une feuille  
    }
    else {
        return false;    // false = pas une feuille
    }
}

// Dessine les triangles d'un square d'une node 
void drawSquare(Node node, int zMax) {

    // Triangle 1
    float m1 = heightColor(	node.SO.z, node.NO.z, node.NE.z, zMax);
    glColor3f(0.0, m1, 0.0);     // Couleur selon z moyen

    glVertex3f(node.SO.x, node.SO.z, node.SO.y);    // SO
    glVertex3f(node.NO.x, node.NO.z, node.NO.y);	// NO
    glVertex3f(node.NE.x, node.NE.z, node.NE.y);	// NE

    // // Triangle 2
    float m2 = heightColor(	node.SO.z, node.SE.z, node.NE.z, zMax);    
    glColor3f(0.0, m2, 0.0);     // Couleur selon z moyen

    glVertex3f(node.SO.x, node.SO.z, node.SO.y);    // SO
    glVertex3f(node.SE.x, node.SE.z, node.SE.y);	// SE
    glVertex3f(node.NE.x, node.NE.z, node.NE.y);	// NE
}

void drawMap(Node * node, int zMax) {
    if (isLeaf(node)) {
        drawSquare(*node, zMax);
    }
    else {
        cout << node->NE.x << " " << node->NE.y << "je suis pas une feuille" << endl;
        drawMap(node->nordOuest, zMax);
        drawMap(node->nordEst, zMax);
        drawMap(node->sudOuest, zMax);
        drawMap(node->sudEst, zMax);
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