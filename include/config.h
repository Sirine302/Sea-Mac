#ifndef CONFIG_H
#define CONFIG_H

#include <stdlib.h>
#include <stdio.h>

/* récupération du fichier de configuration .timac" */ 

typedef struct Config {
    char config[20];
    int xsize;
    int ysize;
    int zmin;
    int zmax;
    int znear;
    int zfar;    
    int fov;
}config;

Config* createConfig(char *config);

#endif