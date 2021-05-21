#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "config.h"

/* fonction de dessin : mettre ce qu'on veut afficher à l'intérieur */
void display(void)
{
    //Clear all pixels
    glClear(GL_COLOR_BUFFER_BIT);
    // Don't wait start processing buffered OpenGL routines
    glFlush();
}

void init(void)
{
    //select clearing (background) color
    glClearColor(0.0, 0.0, 0.0, 0.0);

    //initialize viewing values 
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, 1.0, 0.0, 1.0, -1.0, 1.0);

}

// compiler : make main
// exécuter : bin/main config.timac
int main(int argc, char*argv[]){

    /* ========== CREATE CONFIG ========== */ 

    Config *config = (Config *)malloc(sizeof(Config));
    config = createConfig(argv[1]);

    //test
    printf(
        "Map : %s \nx : %i | y : %i | zmin : %i | zmax : %i \nznear : %i | zfar : %i | fov : %i \n", 
        config->config, config->xsize, config->ysize, config->zmin, config->zmax, config->znear, config->zfar, config->fov
    );


    /* ========== AFFICHAGE FENETRE ========== */ 

    // Initialise GLUT
    glutInit(&argc, argv);
    
    // Settings
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800,800);
    glutInitWindowPosition(100,100);
    
    // Create the window
    glutCreateWindow("Sirine & Audrey | VisuTerrIMAC");
    init();
    glutDisplayFunc(display);
    
    //Enter the GLUT event loop
    glutMainLoop();

    return 0;
}