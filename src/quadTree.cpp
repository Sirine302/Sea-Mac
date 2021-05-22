#include <GL/glut.h>
#include <iostream>

#include "quadTree.h"

using namespace std;

// Ici : définition de toutes les fonctions liées au quadTree 

void addNode(Node* newNode, int l1, int l2, int h1, int h2) {
    // Dimensions du carré couvert par la node 
    newNode->nodeSquare = {l1, l2, h1, h2};

    int l = (l1 + l2)/2; // centre de la largeur du carré 
    int h = (h1 + h2)/2; // centre de la hauteur du carré 

    //vérif : si la longueur est toujours entière 
    if (l2-l1 > 1 && h2-h1 > 1) {
        newNode->nordOuest = new Node;
        newNode->nordEst = new Node;
        newNode->sudOuest =  new Node;
        newNode->sudEst = new Node;
        
        // ajoute une node avec les dimensions / coordonnées du quad 
        addNode(newNode->nordOuest, l1, l, h1, h);
        addNode(newNode->nordEst, l, l2, h1, h);
        addNode(newNode->sudOuest, l, l2, h1, h);
        addNode(newNode->nordOuest, l, l2, h, h2);
    }
}
