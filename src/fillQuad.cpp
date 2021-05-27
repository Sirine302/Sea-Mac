#include "fillQuad.h"

void fillQuadTree(Node * aNode, Image pgm, Config config) {
	for (int i = 0; i < pgm.xMax; i++) {
		for (int j = 0; j < pgm.yMax; j++) {

			// cout << " val to fill : " << (float)(i-pgm.xMax/2)/pgm.xMax * config.xsize << " " <<  (float)(j-pgm.yMax/2)/pgm.yMax * config.ysize << " " <<  (float)pgm.allZ[i][j]/pgm.zMax << endl;

			// Point newPoint = createPoint(
			// 	(float)(i-pgm.xMax/2)/pgm.xMax * config.xsize, 
			// 	(float)(j-pgm.yMax/2)/pgm.yMax * config.ysize, 
			// 	(float)pgm.allZ[i][j]/pgm.zMax * 3 );
			Point newPoint = createPoint (
				i-pgm.xMax/2,
				j-pgm.yMax/2,
				(float)pgm.allZ[i][j]/pgm.zMax * 3
			);
			insert(aNode, newPoint);
		}
	}

}
