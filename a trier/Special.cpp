// Special.cpp

// déplacement et rotation de la caméra 

#include <math.h>
#include <GL/glut.h>

#define VITESSE_DEPLACEMENT 1.0
#define VITESSE_ROTATION 0.1

extern double angle, pos_x, pos_z, x_vise, z_vise;

void Special(int key, int x, int y)
{
	double dir_x, dir_z;
	dir_x=x_vise-pos_x;
	dir_z=z_vise-pos_z;
	switch(key)
	{
	case GLUT_KEY_UP:
		pos_x+=dir_x*VITESSE_DEPLACEMENT;
		pos_z+=dir_z*VITESSE_DEPLACEMENT;
		x_vise += dir_x*VITESSE_DEPLACEMENT;
		z_vise += dir_z*VITESSE_DEPLACEMENT;
		break;
	case GLUT_KEY_DOWN:
		pos_x-=dir_x*VITESSE_DEPLACEMENT;
		pos_z-=dir_z*VITESSE_DEPLACEMENT;
		x_vise -= dir_x*VITESSE_DEPLACEMENT;
		z_vise -= dir_z*VITESSE_DEPLACEMENT;
		break;
	case GLUT_KEY_LEFT:
		angle-=VITESSE_ROTATION;
		x_vise = pos_x+cos(angle);
		z_vise = pos_z+sin(angle);
		break;
	case GLUT_KEY_RIGHT:
		angle+=VITESSE_ROTATION;
		x_vise = pos_x+cos(angle);
		z_vise = pos_z+sin(angle);
		break;
	}
}
