# include <GL/glut.h>
# include <iostream>

# include "../include/TGALoader.h"
# include "../include/HeightMap.h"

# include "../include/config.h"
# include "../include/quadTree.h" 
# include "../include/pgmb_io.h"

using namespace std;

	/* ====================================================== */

void Display();
void Reshape(int w, int h);
void Special(int key, int x, int y);

int nWnd;
HeightMap heightmap;
double angle=0.0, pos_x=0.0, pos_z=0.0, x_vise=1.0, z_vise=0.0;

int main(int argc, char* argv[])
{
	/* ================ CONFIGURATION TIMAC ================= */
	
    Config *config = (Config *)malloc(sizeof(Config));
    config = createConfig(argv[1]);
	if (config) {
		cout << "Fichier de configuration chargé." << endl;
	}


	/* ================ CREATION DU QUAD TREE =============== */

    Node* quadTree = new Node;
    
	// récupération des valeurs du fichier de configuration : dimensions heightmap 
	int xMin = 0; 
    int xMax = config->xsize;
    int yMin = 0;
    int yMax = config->ysize;

	// création du quad tree 
	addNode(quadTree, xMin, xMax, yMin, yMax);


	/* ======================= FENETRE ====================== */

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 150);
	nWnd = glutCreateWindow("Sirine & Audrey | HeightMap");


	/* ================= TEXTURE & AFFICHAGE ================ */

	// Initialisations
	// autorise les textures 
	glEnable(GL_TEXTURE_2D);

	// active l'élimination des faces 
	glEnable(GL_CULL_FACE);

	/*	La fonction glCullFace() a trois options possibles :
		- GL_BACK : élimine les faces arrière (valeur initiale); 
		- GL_FRONT : élimine les faces avant ;
		- GL_FRONT_AND_BACK : éliminent les faces avant et arrière.
		
	GL_CCW : considère que les faces avant sont celles définies 
	dans le sens contraire des aiguilles d'une montre. */

	glCullFace(GL_CCW); 


	/* ====================== LOAD FILE ===================== */
	// visiblement ne fonctionne pas, va savoir pourquoi (à retravailler)
	// char const *file = "./src/heightmap.hmap";

	// if(!heightmap.LoadFile(file, 5, 1, TGA_BILINEAR))
	// {
	// 	cerr << "Erreur : impossible de charger heightmap.hmap" << endl;
	// 	exit(-1);
	// }

	// Callbacks
	//glutDisplayFunc(Display); // affichage
	glutReshapeFunc(Reshape); // resize écran
	glutSpecialFunc(Special); // mouvement caméra 
	
	glEnable(GL_DEPTH_TEST); // autorisation test de profondeur
	glutMainLoop(); // lancement de la loop qui traite les evenements 

	return 0;
}