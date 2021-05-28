#include "quadTree.h"

using namespace std;

Node * initNode(Node * newNode, Square rect) {
    newNode->surface = rect;

    newNode->nordOuest = nullptr;
    newNode->nordEst = nullptr;
    newNode->sudOuest = nullptr;
    newNode->sudEst = nullptr;

    if (rect.y2 - rect.y1 > 1) {
        float x1 = newNode->surface.x1; 
        float y1 = newNode->surface.y1; 
        float x2 = newNode->surface.x2;
        float y2 = newNode->surface.y2;

        int x = (rect.x1 + rect.x2)/2;
        int y = (rect.y1 + rect.y2)/2;

        newNode->nordOuest = new Node();
        newNode->nordEst = new Node();
        newNode->sudOuest = new Node();
        newNode->sudEst = new Node();

        Square rectNO = createSquare(x1, x, y1, y);
        Square rectNE = createSquare(x, x2, y1, y);
        Square rectSO = createSquare(x1, x, y, y2);
        Square rectSE = createSquare(x, x2, y, y2);

        initNode(newNode->nordOuest, rectNO);
        initNode(newNode->nordEst, rectNE);
        initNode(newNode->sudOuest, rectSO);
        initNode(newNode->sudEst, rectSE);
    }
    return newNode;
}

bool isLeaf(Node * node) {
    if (!node->nordOuest && !node->nordEst && !node->sudOuest && !node->sudEst) {
        return true;
    }
    else {
        return false;
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