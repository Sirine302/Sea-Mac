# include <iostream>
# include <SDL2/SDL.h>

# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>

# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# include "../include/heightMap.h"
# include "../include/config.h"
# include "../include/quadTree.h" 
#include "../include/visu.h"
#include "../include/gldrawing.h"
// # include "../include/camera.h"

using namespace std;

// NOTE : il faut un fichier .pgm de type P2 (binaire)
// enregistrement photoshop 8bit + export Gimp pgm ASCII  
Heightmap* map = new Heightmap();





#define VITESSE_DEPLACEMENT 1.0
#define VITESSE_ROTATION 0.1

double angle=0.0, pos_x=0.0, pos_y = 3.0, pos_z=0.0, x_vise=1.0, z_vise=0.0; 

bool isFilled = true;

/* ====================================================== */

/* variables globales pour la gestion de la caméra */
float profondeur = 3;
float latitude = 0.0;
float longitude = M_PI/2.;

float obj_rot = 0.0;
unsigned int size_pt = 5;


/* **************** DESSIN A L'ECRAN ******************* */

static void drawFunc(void) { 
	// réinitialisation des buffers couleur et ZBuffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// modification de la matrice de la scène
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Début du dessin de la scène 
	glPushMatrix();
	
	/* placement de la caméra de biri */

	// ici, latitude = phi, longitude = theta 
	// gluLookAt(profondeur*sin(longitude)*sin(latitude), profondeur*cos(latitude) + 3,profondeur*cos(longitude)*sin(latitude),
    //          10.0,0.0,10.0,
    //          0.0,1.0,0.0);

	// placement de la caméra du mec d'internet
	gluLookAt(
        pos_x, 1., pos_z,
        x_vise, 1., z_vise,
        0.0, 1.0, 0.0);

	glColor3f(1.0,0.0,0.0);
	glDrawRepere(5.0);

	glPushMatrix();
	glRotatef(obj_rot,0.0,1.0,0.0);
	glColor3f(1.0,1.0,1.0);
	displayMap(*map, isFilled); 
	
	//glDisable(GL_LIGHTING);

	glPopMatrix();			// Fin du dessin
	glFinish(); 			// Fin de la définition de la scène 
	glutSwapBuffers();		// Changement buffer d'affichage

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
	// ESC, Q ou q : sortie programme
	// F : changement de la vue
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
	dir_x=x_vise - pos_x;
	dir_z=z_vise - pos_z;

	switch(c) {
		// version Biri
		// case GLUT_KEY_UP :
		// 	if (latitude>STEP_ANGLE) latitude -= STEP_ANGLE;
		// 	break;
		// case GLUT_KEY_DOWN :
		// 	if(latitude<M_PI-STEP_ANGLE) latitude += STEP_ANGLE;
		// 	break;
		// case GLUT_KEY_LEFT :
		// 	longitude -= STEP_ANGLE;
		// 	break;
		// case GLUT_KEY_RIGHT :
		// 	longitude += STEP_ANGLE;
		// 	break;

		// Version du mec 
		case GLUT_KEY_UP:
		 	if (latitude>STEP_ANGLE) latitude -= STEP_ANGLE;
			pos_x += dir_x*VITESSE_DEPLACEMENT;
			pos_z += dir_z*VITESSE_DEPLACEMENT;
			x_vise += dir_x*VITESSE_DEPLACEMENT;
			z_vise += dir_z*VITESSE_DEPLACEMENT;
			break;
		case GLUT_KEY_DOWN:
			if(latitude<M_PI-STEP_ANGLE) latitude += STEP_ANGLE;
			pos_x -= dir_x*VITESSE_DEPLACEMENT;
			pos_z -= dir_z*VITESSE_DEPLACEMENT;
			x_vise -= dir_x*VITESSE_DEPLACEMENT;
			z_vise -= dir_z*VITESSE_DEPLACEMENT;
			break;
		case GLUT_KEY_LEFT:
			longitude -= STEP_ANGLE;
			angle -= VITESSE_ROTATION;
			x_vise = pos_x+cos(angle);
			z_vise = pos_z+sin(angle);
			break;
		case GLUT_KEY_RIGHT:
			longitude += STEP_ANGLE;
			angle += VITESSE_ROTATION;
			x_vise = pos_x+cos(angle);
			z_vise = pos_z+sin(angle);
			break;

		case GLUT_KEY_PAGE_UP :
			profondeur += STEP_PROF;
			break;
		case GLUT_KEY_PAGE_DOWN :
			if (profondeur>0.1+STEP_PROF) profondeur -= STEP_PROF;
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
	profondeur = 3;
	latitude = M_PI/2.0;
	longitude = 0.0;

	obj_rot = 0.0;
	size_pt = 5;

	glClearColor(0.0, 0.0, 0.0 ,0.0);	// Background 
	glEnable( GL_DEPTH_TEST);			// Z-Buffer
	glShadeModel(GL_SMOOTH);			// Lissage couleurs
}


// Rotation lente autour de l'axe vertical 
void idle(void) {
	obj_rot+=STEP_ANGLE;
	glutPostRedisplay();
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
	char* fichier = config->config;
    int xSize = config->xsize;
    int ySize = config->ysize;
    int zMin = config->zmin;
    int zMax = config->zmax;
    int zNear = config->znear;
    int zFar = config->zfar;
    int fov = config->fov;

	/* ====================== LOAD MAP ====================== */

	map = createHeightmap(*config);

	/* ================ CREATION DU QUAD TREE =============== */

    Node* quadTree = new Node;
    
	int xMin = 0; 
    int xMax = xSize - xMin;
    int yMin = 0;
    int yMax = ySize - yMin;

	// création du quad tree 
	addNode(quadTree, xMin, xMax, yMin, yMax);


    /* ======================= OPENGL ======================= */

	glutInit(&argc, argv);
	
	// initialisation du mode d'affichage
	glutInitDisplayMode(GLUT_RGBA|GLUT_DEPTH|GLUT_DOUBLE);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(500, 500);

	if (glutCreateWindow("VIZU PRG") == GL_FALSE) {
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
	//glutIdleFunc(idle);				// Rotation lente

	glutMainLoop();					// Appel des callbacks

	return 0;
}