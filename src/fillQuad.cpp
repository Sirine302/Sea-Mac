#include "fillQuad.h"

void fillQuadTree(Node * aNode, Image pgm, Config config) {
	for (int i = 0; i < pgm.xMax; i++) {
		for (int j = 0; j < pgm.yMax; j++) {
			
			Point newPoint = createPoint((float)i/pgm.xMax * config.xsize, (float)j/pgm.yMax * config.ysize, (float)pgm.allZ[i][j]/pgm.zMax);
			insert(aNode, newPoint);
		}
	}

}
