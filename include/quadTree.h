#ifndef QUADTREE_H
#define QUADTREE_H

#include "geometry.h"
#include "heightMap.h"

typedef struct Node {    
    Square surface;     // coordonnées surface

    // Nodes enfants 
    Node* nordOuest;
    Node* nordEst; 
    Node* sudEst;
    Node* sudOuest;

    // Points
    int nbPoints;       // nb points contenus
    Point tabPoints[4]; // points de la node

} QuadTree, Node;

Node * initNode(Node * newNode, Square rect);
void insert(Node* node, Point point);

bool isLeaf(Node * node);
void repartition(Point point, Node* node);
void subdivide(Node * node);

#endif