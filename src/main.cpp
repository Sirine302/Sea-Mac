# include <iostream>
# include <SDL2/SDL.h>

# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <chrono>

# include "quadTree.h" 
# include "heightMap.h"
# include "config.h"
# include "gldrawing.h"
# include "geometry.h"
# include "textures.h"

using namespace std;


/* ====================== VARIABLES ===================== */

// paramètres caméra 
#define STEP_ANGLE 	M_PI/90.
#define STEP_PROF  	0.05
#define VITESSE_DEPLACEMENT 1.0
#define VITESSE_ROTATION 1.

float latitude = 0.;
float longitude = M_PI/2.;
float angle = M_PI/2.;

float pos_x = 1.0, pos_y = 1.0, pos_z = 5.0;
Vector pVise, vise, vectL, vectUp;

bool isFilled = true;			// vue quadrillage 
bool vagues = false;		 	// activation des vagues
float timerr = 1;


Image* pgm = new Image();
Node* quadTree = new Node();
Triangle * champCam = new Triangle();

GLuint tabTextureId[6];			// skybox

// bateaux 
const int maxBoat = 30;
GLuint tabBoat[maxBoat]; 
Point * posBoat = (Point *)malloc(sizeof(Point)*maxBoat);


/* ================== DESSIN A L'ECRAN ================== */

static void drawFunc(void) { 
	
	pVise = createPoint(pos_x + cos(latitude) * sin(longitude), 
						pos_y + sin(latitude) * sin(longitude), 
						pos_z + cos(longitude));

	vise = createPoint(	cos(latitude) * sin(longitude),
						sin(latitude) * sin(longitude),
						cos(longitude));
	
	vectL = createPoint(cos(latitude + angle),
						sin(latitude + angle),
						0.);

	vectUp = produitVect(vise,vectL);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glPushMatrix();

		glEnable(GL_DEPTH_TEST);
		
		glDepthMask(GL_FALSE);
		drawCenteredBox(5., tabTextureId);
		glDepthMask(GL_TRUE);
		
		gluLookAt(	pos_x, pos_z, pos_y, 
					pVise.x, pVise.z, pVise.y, 
					vectUp.x, vectUp.z, vectUp.y);

		glTranslatef(- pgm->xMax/2, 0, - pgm->yMax/2);
		
		if (vagues) {
			timerr = SDL_GetPerformanceCounter();
			SDL_Delay(3);
		}

		drawTerrain(quadTree, *pgm, isFilled, true, timerr, {pos_x, pos_y}); 
		
		for (int i = 0; i < maxBoat; i++) {
			drawBoat(latitude, tabBoat[i], posBoat[i]);
		}

	glPopMatrix();
	
	glFinish();
	glutSwapBuffers();
}


/* ================ REDIMENSION FENETRE ================ */


static void reshapeFunc(int width, int height) {

	GLfloat h = (GLfloat) width / (GLfloat) height ;
	glViewport(0, 0, (GLint)width, (GLint)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	
	gluPerspective( 60.0, h, 0.01, 100.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}


/* ================ EVENEMENTS CLAVIER ================= */

static void kbdFunc(unsigned char c, int x, int y) {

	double dir_x, dir_y;
	dir_x = pVise.x - pos_x;
	dir_y = pVise.y - pos_y;

	switch(c) {
		// sortie du programme 
		case 27 :
			exit(0);
			break;

		// vue Heightmap 
		case 'F' : case 'f' : 
			if (isFilled) {
				isFilled = false;
			} 
			else {
				isFilled = true;
			}
			break;

		// activation du temps pour les vagues 
		case 'A' : case 'a' : 
			if (vagues) {
				vagues = false;
			} 
			else {
				vagues = true;
			}
			break;

		// déplacements 
		case 'z' : case 'Z' :
			pos_x += dir_x * VITESSE_DEPLACEMENT;
			pos_y += dir_y * VITESSE_DEPLACEMENT;
			vise.x += dir_x * VITESSE_DEPLACEMENT;
			vise.y += dir_y * VITESSE_DEPLACEMENT;
			break;

		case 'S' : case 's' :
			pos_x -= dir_x * VITESSE_DEPLACEMENT;
			pos_z -= dir_y * VITESSE_DEPLACEMENT;
			vise.x -= dir_x * VITESSE_DEPLACEMENT;
			vise.y -= dir_y * VITESSE_DEPLACEMENT;
			break;

		case 'Q' : case 'q' :
			latitude -= STEP_ANGLE * VITESSE_ROTATION;
			vise.x = sin(longitude) + pos_x;
			vise.y = cos(longitude) + pos_y;
			break;

		case 'D' : case 'd' :
			latitude += STEP_ANGLE * VITESSE_ROTATION;
			vise.x = sin(longitude) + pos_x;
			vise.y = cos(longitude) + pos_y;
			break;

		default:
			printf("Appui sur la touche %c\n",c);
	}
	glutPostRedisplay();
}

/* ====== EVENEMENTS CLAVIER (TOUCHES SPECIALES) ======= */


static void kbdSpFunc(int c, int x, int y) {

	switch(c) {
		case GLUT_KEY_UP :
			pos_z += STEP_PROF * VITESSE_DEPLACEMENT;
			break;

		case GLUT_KEY_DOWN :
			pos_z -= STEP_PROF * VITESSE_DEPLACEMENT;
			break;

		default:
			printf("Appui sur une touche spéciale\n");
	}
	glutPostRedisplay();
}

/* ================== INITIALISATION =================== */

static void init() {

	/* ===== Skybox ===== */ 

    char* name[6]={"assets/back.jpg",
		   "assets/front.jpg",
		   "assets/left.jpg", 
		   "assets/right.jpg", 
		   "assets/bottom.jpg", 
		   "assets/top.jpg"};
    for(int i = 0; i<6; i++){
        tabTextureId[i] = creaTexture(name[i]);
    }	

	/* ===== Bateaux ===== */
	
	char* boat = "assets/boat.png"; 

	for (int i = 0; i < maxBoat; i++) {
		int xPos = rand() % pgm->xMax ; 
		int yPos = rand() % pgm->yMax; 
		int zPos = findZ(pgm->allZ, xPos, yPos, timerr);
		posBoat[i] = createPoint(xPos, yPos, zPos);
		tabBoat[i] = creaTexture(boat);
	}
	
	glClearColor(0.4, 0.7, 1. ,0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
}

void idle(void) {
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
    int xSize = config->xsize;			// largeur du terrain 
    int ySize = config->ysize;			// profondeur du terrain
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

	*champCam = createTriangle({pos_x, pos_y}, zFar, fov);
	cout << "Triangle initialisé. " << endl;


    /* ======================= OPENGL ======================= */

	glutInit(&argc, argv);
	
	// initialisation du mode d'affichage
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);

	glutInitWindowPosition(0, 0);
	glutInitWindowSize(1000, 800);

	if (glutCreateWindow("Sea'MAC | Sirine & Audrey") == GL_FALSE) {
		return 1;
	}

	init();

	glutReshapeFunc(reshapeFunc);	// Redimensionnement
	glutDisplayFunc(drawFunc);		// Affichage 
	glutKeyboardFunc(kbdFunc);		// Event clavier 
	glutSpecialFunc(kbdSpFunc);		// Event clavier (touches spé.)
	glutIdleFunc(idle);				// Animation 

	glutMainLoop();					// Appel des callbacks
	
	return 0;
}
