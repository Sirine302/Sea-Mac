# include <iostream>
# include <SDL2/SDL.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>

# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# include "quadTree.h" 
# include "heightMap.h"
# include "config.h"
# include "visu.h"
# include "gldrawing.h"
# include "geometry.h"

// SKYBOX :
#include "draw.h"

// # include "../include/camera.h"

using namespace std;

/* ====================== VARIABLES ===================== */

#define VITESSE_DEPLACEMENT 1.0
#define VITESSE_ROTATION 0.1

// dclaration de l'image et du quadTree
Image* pgm = new Image();
Node* quadTree = new Node();
Triangle * champCam = new Triangle();

// vue des triangles
bool isFilled = true;

// Gestion de la caméra
double angle = 0.0;
double pos_x = 10.0, pos_y = 10.0, pos_z = 3.0;
double x_vise = 1.0, z_vise = 0.0; 

//skybox
GLuint tabTextureId[6];

void glDrawOrigin(float axisLength) 
{
    glBegin(GL_LINES);
        glColor3f(1., 0., 0.);
        glVertex3f(0., 0., 0.);
        glVertex3f(axisLength, 0., 0.);

 		glColor3f(1., 0., 0.);
        glVertex3f(0., 0., 0.);
        glVertex3f(-axisLength, 0., 0.);

        glColor3f(0., 1., 0.);
        glVertex3f(0., 0., 0.);
        glVertex3f(0., axisLength, 0.);


        glColor3f(0., 1., 0.);
        glVertex3f(0., 0., 0.);
        glVertex3f(0., -axisLength, 0.);

        glColor3f(0., 0., 1.);
        glVertex3f(0., 0., 0.);
        glVertex3f(0., 0., axisLength);

		glColor3f(0., 0., 1.);
        glVertex3f(0., 0., 0.);
        glVertex3f(0., 0., -axisLength);
    glEnd();
}


/* ================== DESSIN A L'ECRAN ================== */

static void drawFunc(void) { 
	// réinitialisation des buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// modification de la matrice de la scène
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();
		gluLookAt(pos_x, 3., pos_z,
				  x_vise, 3., z_vise,
				  0.0, 1.0, 0.0);
		drawTerrain(quadTree, *pgm, isFilled, intersection(*champCam, quadTree->surface)); 

	glPopMatrix();			// Fin du dessin
	glFinish(); 			// Fin de la définition de la scène 
	glutSwapBuffers();		// Changement buffer d'affichage
	
	//drawTest();
	glDisable(GL_LIGHTING);
	// SKYBOX :
	glLoadIdentity();

	glPushMatrix();
    	glDepthMask(GL_FALSE);
    	//glTranslatef(camera.posCam.x, camera.posCam.y, camera.posCam.z);
    	drawCenteredBox(10., tabTextureId);
    	glDepthMask(GL_TRUE);
    	glPopMatrix();

	glLoadIdentity();
//////////////////////////////////////////////////////////////////////// fin skybox
	
}


/* ================ REDIMENSION FENETRE ================ */

static void reshapeFunc(int width, int height) {

	GLfloat h = (GLfloat) width / (GLfloat) height ;
	
	glViewport(0, 0, (GLint)width, (GLint)height);	// dimension écran GL
	glMatrixMode(GL_PROJECTION);					// matrice de projection
	glLoadIdentity();
	gluPerspective( 60.0, h, 0.01, 10.0 ); 			// Définition caméra 

	glMatrixMode(GL_MODELVIEW);						// Retour pile de matrice
	glLoadIdentity();
}


/* ================ EVENEMENTS CLAVIER ================= */

static void kbdFunc(unsigned char c, int x, int y) {
	// x, y = coordonnées curseur (inutilisé)
	switch(c) {
		case 27 : case 'Q' : case 'q' :
			exit(0);
			break;
		case 'F' : case 'f' : 
			if (isFilled) {
				isFilled = false;
			} 
			else {
				isFilled = true;
			}
			break;
		default:
			printf("Appui sur la touche %c\n",c);
	}
	glutPostRedisplay();
}

/* ====== EVENEMENTS CLAVIER (TOUCHES SPECIALES) ======= */

static void kbdSpFunc(int c, int x, int y) {

	double dir_x, dir_z;
	dir_x = x_vise - pos_x;
	dir_z = z_vise - pos_z;

	switch(c) {
		case GLUT_KEY_UP:
			pos_x += dir_x*VITESSE_DEPLACEMENT;
			pos_z += dir_z*VITESSE_DEPLACEMENT;
			x_vise += dir_x*VITESSE_DEPLACEMENT;
			z_vise += dir_z*VITESSE_DEPLACEMENT;
			break;
		case GLUT_KEY_DOWN:
			pos_x -= dir_x*VITESSE_DEPLACEMENT;
			pos_z -= dir_z*VITESSE_DEPLACEMENT;
			x_vise -= dir_x*VITESSE_DEPLACEMENT;
			z_vise -= dir_z*VITESSE_DEPLACEMENT;
			break;
		case GLUT_KEY_LEFT:
			angle -= VITESSE_ROTATION;
			x_vise = pos_x+cos(angle);
			z_vise = pos_z+sin(angle);
			break;
		case GLUT_KEY_RIGHT:
			angle += VITESSE_ROTATION;
			x_vise = pos_x + cos(angle);
			z_vise = pos_z + sin(angle);
			break;
		default:
			printf("Appui sur une touche spéciale\n");
	}
	glutPostRedisplay();
}


/* ============== EVENEMENTS CLIC SOURIS =============== */

static void mouseFunc(int button, int state, int x, int y) { 
}

/* ================ DEPLACEMENT SOURIS ================= */

static void motionFunc(int x, int y) { 
}


/* ================== INITIALISATION =================== */

static void init() {
	//////////////////////////////////// SKYBOX
    char* name[6]={"sky_img/back.jpg",
		   "sky_img/front.jpg",
		   "sky_img/left.jpg", 
		   "sky_img/right.jpg", 
		   "sky_img/bottom.jpg", 
		   "sky_img/top.jpg"};
    for(int i = 0; i<6; i++){
        tabTextureId[i] = generateTextureJpg(name[i]);
    }
	
	// load support for the JPG and PNG image formats
    int flags=IMG_INIT_JPG|IMG_INIT_PNG;
    int initted=IMG_Init(flags);
    if((initted&flags) != flags) {
    printf("IMG_Init: Failed to init required jpg and png support!\n");
    printf("IMG_Init: %s\n", IMG_GetError());
    // handle error
}

	//////////////////////////////////////////////// FIN SKYBOX
	
	
	glClearColor(0.4, 0.7, 1. ,0.0);	// Background 
	glEnable(GL_DEPTH_TEST);			// Z-Buffer
	glShadeModel(GL_SMOOTH);			// Lissage couleurs
}

int main(int argc, char** argv) {

	/* ================ CONFIGURATION TIMAC ================= */
	
	Config* config = new Config();
	
    config = createConfig(argv[1]);
	if (config) {
		cout << "Fichier de configuration " << config->config << " chargé." << endl;
	}
	else {
		cout << "Echec du fichier de configuration." << config->config << endl;
		return -1;
	}

	// récupération des valeurs du fichier de configuration 
	//char* fichier = config->config;	// nom de l'image 
    int xSize = config->xsize;			// largeur du terrain 
    int ySize = config->ysize;			// profondeur du terrain
    int zMin = config->zmin;			// hauteur min
    int zMax = config->zmax;			// hauteur max
    int zNear = config->znear;			// vue la plus proche 
    int zFar = config->zfar;			// vue la plus loin 
    int fov = config->fov;				// champ de vision  

	/* ====================== LOAD MAP ====================== */

	pgm = loadImage(*config);

	/* ================ CREATION DU QUAD TREE =============== */
    
	int x1 = 0; 
    int x2 = xSize - x1 -1;
    int y1 = 0;
    int y2 = ySize - y1 -1;

	Square rect = createSquare(x1, x2, y1, y2);
	cout << "Square initialisé. " << endl;

	// création du quad tree 
	quadTree = initNode(quadTree, rect);
	cout << "QuadTree initialisé." << endl;


	/* ======================= CAMERA ======================= */

	// *champCam = createTriangle({pos_x, pos_y}, zFar, fov);
	cout << "Triangle initialisé. " << endl;


    /* ======================= OPENGL ======================= */

	glutInit(&argc, argv);
	
	// initialisation du mode d'affichage
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);

	if (glutCreateWindow("VisuTerrIMAC | Sirine & Audrey") == GL_FALSE) {
		return 1;
	}

	init();

	// Callbacks
	glutReshapeFunc(reshapeFunc);	// Redimensionnement
	glutDisplayFunc(drawFunc);		// Affichage 
	glutKeyboardFunc(kbdFunc);		// Event clavier 
	glutSpecialFunc(kbdSpFunc);		// Event clavier (touches spé.)
	glutMouseFunc(mouseFunc);		// Event souris 
	glutMotionFunc(motionFunc);		// Event drag souris 

	glutMainLoop();					// Appel des callbacks
	return 0;
}
