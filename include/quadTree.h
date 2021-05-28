#ifndef QUADTREE_H
#define QUADTREE_H

#include <GL/glut.h>
#include <iostream>

#include "geometry.h"
#include "heightMap.h"

typedef struct Node {    
    Square surface;     // coordonnées surface

    // Nodes enfants 
    Node* nordOuest;
    Node* nordEst; 
    Node* sudEst;
    Node* sudOuest;

    uint profondeur;
} QuadTree, Node;

Node * initNode(Node * newNode, Square rect);
bool isLeaf(Node * node);
uint heightQuadTree(Node * node);

#endif