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
	
    Config* config = new Config();
	
    config = createConfig(argv[1]);
	if (config) {
		cout << "Fichier de configuration chargé." << endl;
		cout << config->config << endl;
	}
	else {
		cout << "Echec du fichier de configuration." << endl;
		return -1;
	}

	// récupération des valeurs du fichier de configuration : dimensions heightmap 
	char* fichier = config->config;
    int xSize = config->xsize;
    int ySize = config->ysize;
    int zMin = config->zmin;
    int zMax = config->zmax;
    int zNear = config->znear;
    int zFar = config->zfar;
    int fov = config->fov;

	/* ================ CREATION DU QUAD TREE =============== */

    Node* quadTree = new Node;
    
	int xMin = 0; 
    int xMax = xSize-xMin;
    int yMin = 0;
    int yMax = ySize - yMin;

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

	/*	NOTE : La fonction glCullFace() a trois options possibles :
		- GL_BACK : élimine les faces arrière (valeur initiale); 
		- GL_FRONT : élimine les faces avant ;
		- GL_FRONT_AND_BACK : éliminent les faces avant et arrière.
		
	GL_CCW : considère que les faces avant sont celles définies 
	dans le sens contraire des aiguilles d'une montre. */

	glCullFace(GL_CCW); 


	/* ====================== LOAD MAP ====================== */

	// NOTE : il faut un fichier .pgm de type P2 (binaire) pour que ça marche
	// fichier obtenu avec : enregistrement photoshop 8bit + export Gimp pgm ASCII  

	int test = 0, row = 0, col = 0, numrows = 0, numcols = 0;
	ifstream infile(fichier);
	stringstream ss;
	string inputLine = "";

	// First line : version
	getline(infile,inputLine);
	cout << "Version : " << inputLine << endl;

	getline(infile,inputLine);
	cout << inputLine << endl;

	// Continue with a stringstream
	ss << infile.rdbuf();
	// Second line : size
	ss >> numcols >> numrows;
	cout << numcols << " columns and " << numrows << " rows" << endl;

	ss >> test; 
	cout << "Valeur max : " << test << endl;
	int array[numrows][numcols];

	// Following lines : data
	for(row = 0; row < numrows; ++row) {
		for (col = 0; col < numcols; ++col){ 
			ss >> array[row][col];
			
			// [A FAIRE] 
			// dans ce tableau, on récupère toutes les coordonnées des points de l'image :
			// 		- x = row, 
			// 		- y = col, 
			// 		- z = array[row][col]  

		}
	}

	infile.close();

	/* ===================== CALLBACKS ====================== */

	glutDisplayFunc(Display); // affichage
	glutReshapeFunc(Reshape); // resize écran
	glutSpecialFunc(Special); // mouvement caméra 
	
	glEnable(GL_DEPTH_TEST); // autorisation test de profondeur
	glutMainLoop(); // lancement de la loop qui traite les evenements 

	return 0;
}