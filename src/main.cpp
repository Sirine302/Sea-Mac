// main.cpp

#include <GL/glut.h>
#include <iostream>

#include "../include/TGALoader.h"
#include "../include/HeightMap.h"
#include "../include/config.h"

using namespace std;

void Display();
void Reshape(int w, int h);
void Special(int key, int x, int y);

int nWnd;
HeightMap heightmap;
double angle=0.0, pos_x=0.0, pos_z=0.0, x_vise=1.0, z_vise=0.0;

int main(int argc, char* argv[])
{
	/* === CONFIGURATION TIMAC === */
	
    Config *config = (Config *)malloc(sizeof(Config));
    config = createConfig(argv[1]);
	if (config) {
		cout << "Fichier de configuration chargé." << endl;
	}

	/* === FENETRE === */

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

	glutInitWindowSize(640, 480);
	glutInitWindowPosition(200, 150);
	nWnd = glutCreateWindow("HeightMap");

	// Initialisations
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_CCW);
	if(!heightmap.LoadFile("heightmap.hmap", 5, 1, TGA_BILINEAR))
	{
		cerr << "Erreur : impossible de charger heightmap.hmap" << endl;
		exit(-1);
	}

	// Callbacks
	glutDisplayFunc(Display);
	glutReshapeFunc(Reshape);
	glutSpecialFunc(Special);
	
	glEnable(GL_DEPTH_TEST);

	glutMainLoop();
	return 0;
}