#include <GL/glut.h>
#include <iostream>

#include "../include/quadTree.h"

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

/* 

FRUSTUM CULLING 

Déterminer quels sont les carrés dans le champs de la caméra 

3 CAS :
    - le triangle représentant le champ de la cam est dans le carré de la node 
    - le carré de la node est entièrement dans le champ de la cam
    - une partie seulement du carré est traversé par la cam

    - tester ces trois cas dans une fonction 
        - renvoie true si le cas est dans le champ 
        - sinon renvoie false

*/ 