#include <stdlib.h>
#include <stdio.h>
#include "config.h"


// compiler : make main
// exécuter : bin/main config.timac
int main(int argc, char*argv[]){
    /* CREATE CONFIG */ 
    Config *config = (Config *)malloc(sizeof(Config));
    config = createConfig(argv[1]);

    //test (ça compile bizarrement, mais ça marche)
    printf("Map : %s \nx : %i | y : %i | zmin : %i | zmax : %i \nznear : %i | zfar : %i | fov : %i \n", config->config, config->xsize, config->ysize, config->zmin, config->zmax, config->znear, config->zfar, config->fov);

    return 0;
}