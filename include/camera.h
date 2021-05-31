#ifndef CAMERA_H
#define CAMERA_H

# include <iostream>
# include <SDL2/SDL.h>

# include <GL/gl.h>
# include <GL/glu.h>
# include <GL/glut.h>

# include <stdlib.h>
# include <stdio.h>
# include <math.h>

# include "geometry.h"

#define STEP_ANGLE	M_PI/90.
#define STEP_PROF	M_PI/90.

/* variables globales pour la gestion de la caméra */
extern float profondeur;
extern float latitude;
extern float longitude;

typedef struct Camera {
    Point position;
    Vector dirRegard;
    Vector up;
}Camera;

#endif