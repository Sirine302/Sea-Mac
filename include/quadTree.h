#ifndef QUADTREE_H
#define QUADTREE_H

#include "geometry.h"
#include "heightMap.h"

typedef struct Node
{    // Les points sont les angles de la surface sur laquelle la node est définie 
    Point NO; 
    Point NE; 
    Point SO; 
    Point SE;

    // Les nodes sont les enfants du noeud dans lequel on se trouve 
    Node* nordOuest;
    Node* nordEst; 
    Node* sudEst;
    Node* sudOuest;
} QuadTree, Node;

void addNode(Node* newNode, Point NO, Point NE, Point SO, Point SE, int ** allZ);

void drawMap(Node * node, int zMax);
void drawSquare(Node node, int zMax);
#endif