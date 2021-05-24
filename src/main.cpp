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


/*********************************************************/
/* fonction de dessin de la scène à l'écran              */
static void drawFunc(void) { 
	/* reinitialisation des buffers : couleur et ZBuffer */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/* modification de la matrice de la scène */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	/* Debut du dessin de la scène */
	glPushMatrix();
	
	/* placement de la caméra de biri */
	// ici, latitude = phi, longitude = theta 
	// gluLookAt(profondeur*sin(longitude)*sin(latitude), profondeur*cos(latitude) + 3,profondeur*cos(longitude)*sin(latitude),
    //          10.0,0.0,10.0,
    //          0.0,1.0,0.0);

	// placement de la caméra du mec 
	gluLookAt(
        pos_x, 0.0, pos_z,
        x_vise, 0.0, z_vise,
        0.0, 1.0, 0.0);

	glColor3f(1.0,0.0,0.0);
	glDrawRepere(5.0);

	// // noircit une partie de la map (loin de l'origine)
	// float position[4] = {10.0,10.0,10.0,1.0};
	// float black[3] = {0.0,0.0,0.0};
	// float intensite[3] = {1000.0,1000.0,1000.0};
	// glEnable(GL_LIGHTING);
	// glEnable(GL_LIGHT0);
	// glLightfv(GL_LIGHT0,GL_POSITION,position);
	// glLightfv(GL_LIGHT0,GL_DIFFUSE,intensite);
	// glLightfv(GL_LIGHT0,GL_SPECULAR,black);


	glPushMatrix();
	glRotatef(obj_rot,0.0,1.0,0.0);
	glColor3f(1.0,1.0,1.0);
	displayMap(*map, isFilled); 
	
	glDisable(GL_LIGHTING);

	/* Fin du dessin */
	glPopMatrix();

	/* fin de la définition de la scène */
	glFinish();

	/* changement de buffer d'affichage */
	glutSwapBuffers();
}

/*********************************************************/
/* fonction de changement de dimension de la fenetre     */
/* paramètres :                                          */
/* - width : largeur (x) de la zone de visualisation     */
/* - height : hauteur (y) de la zone de visualisation    */

static void reshapeFunc(int width,int height) {

	GLfloat h = (GLfloat) width / (GLfloat) height ;
	
	/* dimension de l'écran GL */
	glViewport(0, 0, (GLint)width, (GLint)height);
	/* construction de la matrice de projection */
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	/* définition de la camera */
	gluPerspective( 60.0, h, 0.01, 10.0 );

	/* Retour a la pile de matrice Modelview et effacement de celle-ci */
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

/*********************************************************/
/* fonction associée aux interruptions clavier           */
/* paramètres :                                          */
/* - c : caractère saisi                                 */
/* - x,y : coordonnée du curseur dans la fenêtre         */

static void kbdFunc(unsigned char c, int x, int y) {
	// ESC, Q ou q : sortie programme
	// F : changement de la vue

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

/*********************************************************/
/* fonction associée aux interruptions clavier pour les  */
/*          touches spéciales                            */
/* paramètres :                                          */
/* - c : code de la touche saisie                        */
/* - x,y : coordonnée du curseur dans la fenêtre         */

static void kbdSpFunc(int c, int x, int y) {

	/* sortie du programme si utilisation des touches ESC */
	double dir_x, dir_z;
	dir_x=x_vise - pos_x;
	dir_z=z_vise - pos_z;

	switch(c) {
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


/*********************************************************/
/* fonction associée au clic de la souris                */
/* paramètres :                                          */
/* - button : nom du bouton pressé GLUT_LEFT_BUTTON,     */
/*   GLUT_MIDDLE_BUTTON ou GLUT_RIGHT_BUTTON             */
/* - state : état du bouton button GLUT_DOWN ou GLUT_UP  */
/* - x,y : coordonnées du curseur dans la fenêtre        */

static void mouseFunc(int button, int state, int x, int y) { 
}


/*********************************************************/
/* fonction associée au déplacement de la souris bouton  */
/* enfoncé.                                              */
/* paramètres :                                          */
/* - x,y : coordonnées du curseur dans la fenêtre        */

static void motionFunc(int x, int y) { 
}


/* ***************** INITIALISATION ******************** */
/* initialisation des paramètres de rendu et des objets  */
/* de la scène.                           			     */

static void init() {
	profondeur = 3;
	latitude = M_PI/2.0;
	longitude = 0.0;

	obj_rot = 0.0;
	size_pt = 5;

	/* INITIALISATION DES PARAMETRES GL */
	/* Background color */
	glClearColor(0.0, 0.0, 0.0 ,0.0);
	/* activation du ZBuffer */
	glEnable( GL_DEPTH_TEST);

	/* lissage des couleurs sur les facettes */
	glShadeModel(GL_SMOOTH);
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
	map = createHeightmap(fichier);

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
	
	// initialisation du mode d'affichage :
	// RVB + ZBuffer + Double buffer
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