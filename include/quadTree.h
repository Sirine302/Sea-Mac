#ifndef QUADTREE_H
#define QUADTREE_H

#include <GL/glut.h>
#include <iostream>

#include "geometry.h"
#include "heightMap.h"

typedef struct Node {    
    Square surface;

    Node* nordOuest;
    Node* nordEst; 
    Node* sudEst;
    Node* sudOuest;

    // autres informations 
    uint profondeur;
    Point2D centerNode;
} QuadTree, Node;

Node * initNode(Node * newNode, Square rect);
bool isLeaf(Node * node);
uint heightQuadTree(Node * node);

#endif