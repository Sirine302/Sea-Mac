#include "main.h"

// on retourne la hauteur de la height map
int Height(BYTE *pHeightMap, int X, int Y)
{
	int x = X % MAP_SIZE;					
	int y = Y % MAP_SIZE;				

	if(!pHeightMap) return 0;				// données valides

	return pHeightMap[x + (y * MAP_SIZE)];	// on retourne la hauteur
}


// couleur en fonction de la hauteur de la heightmap
void SetVertexColor(BYTE *pHeightMap, int x, int y)
{
	if(!pHeightMap) return;					// données de hauteur valide

	// on définit la couleur d'un sommet en fonction de l'indice de hauteur
	// on commence a -0.15f pour le plus foncé + ratio de ratio de la couleur en divisant la hauteur par 265.0f
	float fColor = -0.15f + (Height(pHeightMap, x, y ) / 256.0f);

	// on attribut la teinte au sommet
	glColor3f(0, fColor, 0 );
}

// rendu de la HEIGHT MAP 
void RenderHeightMap(BYTE pHeightMap[])
{
	int X = 0, Y = 0;						// variables qui vont parcourir le tableau
	int x, y, z;							// lisibilité
	float fColor = 0.0f;					// variable qui contiennent la couleur

	if(!pHeightMap) return;					// données valides

	glBegin( GL_QUADS );					// rendu


	// mtn on va dessiner le terrain a partir de la heightmap
	// on va donc parcourir le tableau des données de hauteur et on en tire certaines hauteur pour tracer nos points
	// STEP_SIZE permet d'avoir un terrain + ou - valloné on choisit 16 pour valeur
	for ( X = 0; X < MAP_SIZE; X += STEP_SIZE )
		for ( Y = 0; Y < MAP_SIZE; Y += STEP_SIZE )
		{
			// valeurs x,y,z du sommet inferieur gauche		
			x = X;							
			y = Height(pHeightMap, X, Y );	
			z = Y;							

			// on definit une couleur au sommet
			SetVertexColor(pHeightMap, x, z);

			glVertex3i(x, y, z);

			// valeurs x,y,z du sommet supperieur gauche	
			x = X;										
			y = Height(pHeightMap, X, Y + STEP_SIZE );  
			z = Y + STEP_SIZE ;							
			
			// on definit une couleur au sommet
			SetVertexColor(pHeightMap, x, z);

			glVertex3i(x, y, z);		

			// valeurs x,y,z du sommet supperieur droit	
			x = X + STEP_SIZE; 
			y = Height(pHeightMap, X + STEP_SIZE, Y + STEP_SIZE ); 
			z = Y + STEP_SIZE ;

			// on definit une couleur au sommet
			SetVertexColor(pHeightMap, x, z);
			
			glVertex3i(x, y, z);

			// valeurs x,y,z du sommet inferieur droit	
			x = X + STEP_SIZE; 
			y = Height(pHeightMap, X + STEP_SIZE, Y ); 
			z = Y;

			// on definit une couleur au sommet
			SetVertexColor(pHeightMap, x, z);

			glVertex3i(x, y, z);			
		}
	glEnd();

	// reinit de la couleur
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}

// loading du rax file dans un tableau, chaque valeur est une valeur de hauteur
void LoadRawFile(LPSTR strName, int nSize, BYTE *pHeightMap)
{
	FILE *pFile = NULL;

	// ouverture du fichier en read/binary mode
	pFile = fopen( strName, "rb" );

	// verifions si on trouve le fichier et si on peut l'ouvrir
	if ( pFile == NULL )	
	{
		// msg d'erreur
		MessageBox(NULL, "Ne trouve pas la height map!", "Error", MB_OK);
		return;
	}

	// on load le fichier .raw dans le tableau de données pHeightMap
	fread( pHeightMap, 1, nSize, pFile );

	// verifications
	int result = ferror( pFile );

	// verification si erreur
	if (result)
	{
		MessageBox(NULL, "Can't get data!", "Error", MB_OK);
	}

	// on ferme le fichier
	fclose(pFile);
}
  

