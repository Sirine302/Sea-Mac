#include <iostream>
#include <stdlib.h>
#include <stdio.h>

#include "../include/config.h"

using namespace std;

Config* createConfig(char *config){
    Config* maConfig = new Config();
    FILE* map = NULL; 
    char line[256]="";

    map = fopen(config, "r+");
    if (map == NULL){
        return NULL;
    }
    else {
        fgets(line, 256, map);
        sscanf(line,"%s", &maConfig->config);
        fgets(line, 256, map); 
        sscanf(line,"%i %i %i %i", &maConfig->xsize, &maConfig->ysize, &maConfig->zmin, &maConfig->zmax);
        fgets(line, 256, map); 
        sscanf(line,"%i %i %i", &maConfig->znear, &maConfig->zfar, &maConfig->fov);
    }
    fclose(map); 

    return maConfig;
}