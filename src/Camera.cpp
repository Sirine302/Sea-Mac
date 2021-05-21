#include "main.h"
#include "Camera.h"


// vitesse caméra
#define kSpeed	100.0f							

// fonction de calcule de la fréquence d'images et les intervalles de temps entre les images
void CalculateFrameRate()
{
	static int framesPerSecond = 0;	// on stock les fps
	static float fpsTime = 0.0f; // Temps écoulé jusqu'à mise a jour des FPS
	char strFrameRate[50] = {0}; // affichage des fps

	// augmentation du tps ecoulé
	fpsTime += g_DT;

	// soustraction du temps actuelle par l'ancien temps stoké
	if( fpsTime > 1.0f )
	{
		// réinitialisation des fps
		fpsTime = 0.0f;

		// On copie les fps dans une chaîne à afficher dans la fenêtre
		sprintf(strFrameRate, "Current Frames Per Second: %d", framesPerSecond);

		// Set the window title bar to our string
		//On définit  notre chaine sur la la barre de titre de la fenêtre
		SetWindowText(g_hWnd, strFrameRate);

		// réinitialisation des fps
		framesPerSecond = 0;
	}
	else
	{
		// On augmente les fps
		++framesPerSecond;
	}
}




// On renvoie un vecteur perpendiculaire à partir de 2 vecteurs donnés en prenant le produit en croix											
CVector3 Cross(CVector3 vVector1, CVector3 vVector2)
{
	CVector3 vNormal;	

	// Produit en croix
	vNormal.x = ((vVector1.y * vVector2.z) - (vVector1.z * vVector2.y));
	vNormal.y = ((vVector1.z * vVector2.x) - (vVector1.x * vVector2.z));
	vNormal.z = ((vVector1.x * vVector2.y) - (vVector1.y * vVector2.x));

	return vNormal;										 
}


// Magnitude d'un vecteur

float Magnitude(CVector3 vNormal)
{
	// equation:  magnitude = sqrt(V.x^2 + V.y^2 + V.z^2)
	return (float)sqrt( (vNormal.x * vNormal.x) + 
						(vNormal.y * vNormal.y) + 
						(vNormal.z * vNormal.z) );
}


// Normalize vector
CVector3 Normalize(CVector3 vVector)
{
	float magnitude = Magnitude(vVector);				

	// on divise par la magnitiude pour obtenir normalize vector
	vVector = vVector / magnitude;		
	
	return vVector;										
}


// camera constructeur
CCamera::CCamera()
{
	CVector3 vZero = CVector3(0.0, 0.0, 0.0);		// Initialisation du vecteur à 0 0 0 pour notre position
	CVector3 vView = CVector3(0.0, 1.0, 0.5);		// vision de départ
	CVector3 vUp   = CVector3(0.0, 0.0, 1.0);		// Init a standard up vector

	m_vPosition	= vZero;					// Init de la pos à 0
	m_vView		= vView;					// Init de la vision de départ
	m_vUpVector	= vUp;						// Init du UpVector
}



// Cette fonction règle la position et la vision de la caméra
void CCamera::PositionCamera(float positionX, float positionY, float positionZ,
				  		     float viewX,     float viewY,     float viewZ,
							 float upVectorX, float upVectorY, float upVectorZ)
{
	CVector3 vPosition	= CVector3(positionX, positionY, positionZ);
	CVector3 vView		= CVector3(viewX, viewY, viewZ);
	CVector3 vUpVector	= CVector3(upVectorX, upVectorY, upVectorZ);


	m_vPosition = vPosition;					// Attribue la position
	m_vView     = vView;						// Attribue la vision
	m_vUpVector = vUpVector;					// Attribue le up vector
}


// Vision en fonction de la souris
void CCamera::SetViewByMouse()
{
	POINT mousePos;									
	int middleX = SCREEN_WIDTH  >> 1;				
	int middleY = SCREEN_HEIGHT >> 1;				
	float angleY = 0.0f;							
	float angleZ = 0.0f;							
	
	// recuperer la position actuelle de la souris
	GetCursorPos(&mousePos);						
	
	// Si le cursor ne bouge pas, on ne change rien au niveau de l'ecran
	if( (mousePos.x == middleX) && (mousePos.y == middleY) ) return;

	// On positionne la souris au milieu de la fenetre
	SetCursorPos(middleX, middleY);							

	// On récupère la direction vers laquelle la souris s'est déplacée
	angleY = (float)( (middleX - mousePos.x) ) / 1000.0f;		
	angleZ = (float)( (middleY - mousePos.y) ) / 1000.0f;		

	static float lastRotX = 0.0f; 
 	lastRotX = currentRotX; 
	
	
	// On empeche la camere de faire un tour complet
	currentRotX += angleZ;
 
	// Si la rotation actuelle (en radians) est supérieure à 1.0 on la plafonne
	if(currentRotX > 1.0f)     
	{
		currentRotX = 1.0f;
		
		
		if(lastRotX != 1.0f) 
		{
			
			// normalization
			CVector3 vAxis = Cross(m_vView - m_vPosition, m_vUpVector);
			vAxis = Normalize(vAxis);
		
			// rotation de la camere par l'angle restant  (1.0f - lastRotX)
			RotateView( 1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
		}
	}
	
	// on verifie que la rotation est inferieur a -1.0, on fait en sorte que ca ne continue pas
	else if(currentRotX < -1.0f)
	{
		currentRotX = -1.0f;
		
		// Rotation par l'angle restant
		if(lastRotX != -1.0f)
		{
			// normalize
			CVector3 vAxis = Cross(m_vView - m_vPosition, m_vUpVector);
			vAxis = Normalize(vAxis);
			
			// rotation de la camera par ( -1.0f - lastRotX)
			RotateView( -1.0f - lastRotX, vAxis.x, vAxis.y, vAxis.z);
		}
	}
	// Sinon, on peut faire pivoter la vue autour de notre position
	else 
	{	
		CVector3 vAxis = Cross(m_vView - m_vPosition, m_vUpVector);
		vAxis = Normalize(vAxis);
	
		// rotation autour de l'axe perpendiculaire
		RotateView(angleZ, vAxis.x, vAxis.y, vAxis.z);
	}

	// rotation camera autour de l'axe y
	RotateView(angleY, 0, 1, 0);
}


// On fait pivoter la vue autour de la position 
void CCamera::RotateView(float angle, float x, float y, float z)
{
	CVector3 vNewView;

	// Direction vers laquelle on regarde
	CVector3 vView = m_vView - m_vPosition;		

	float cosTheta = (float)cos(angle);
	float sinTheta = (float)sin(angle);

	// position de x
	vNewView.x  = (cosTheta + (1 - cosTheta) * x * x)		* vView.x;
	vNewView.x += ((1 - cosTheta) * x * y - z * sinTheta)	* vView.y;
	vNewView.x += ((1 - cosTheta) * x * z + y * sinTheta)	* vView.z;

	// position de y
	vNewView.y  = ((1 - cosTheta) * x * y + z * sinTheta)	* vView.x;
	vNewView.y += (cosTheta + (1 - cosTheta) * y * y)		* vView.y;
	vNewView.y += ((1 - cosTheta) * y * z - x * sinTheta)	* vView.z;

	// position de z
	vNewView.z  = ((1 - cosTheta) * x * z - y * sinTheta)	* vView.x;
	vNewView.z += ((1 - cosTheta) * y * z + x * sinTheta)	* vView.y;
	vNewView.z += (cosTheta + (1 - cosTheta) * z * z)		* vView.z;

	// nouvelle vue de la camera
	m_vView = m_vPosition + vNewView;
}


// position gauche/droite de la camera en fonction de la vitesse
void CCamera::StrafeCamera(float speed)
{	
	// position
	m_vPosition.x += m_vStrafe.x * speed;
	m_vPosition.z += m_vStrafe.z * speed;

	// vision
	m_vView.x += m_vStrafe.x * speed;
	m_vView.z += m_vStrafe.z * speed;
}

// position avant/arriere en fct de la vitesse
void CCamera::MoveCamera(float speed)
{
	// vecteur de la vision actuelle
	CVector3 vVector = m_vView - m_vPosition;
	vVector = Normalize(vVector);

	m_vPosition.x += vVector.x * speed;		// acceleration par rapport à la position X
	m_vPosition.y += vVector.y * speed;		// acceleration par rapport à la position X Y
	m_vPosition.z += vVector.z * speed;		// acceleration par rapport à la position X Z
	m_vView.x += vVector.x * speed;			// acceleration par rapport à la vision X
	m_vView.y += vVector.y * speed;			// cceleration par rapport à la vision Y
	m_vView.z += vVector.z * speed;			// cceleration par rapport à la vision Z
}


// gestion input
void CCamera::CheckForMovement()
{	
	// vitesse actuelle
	float speed = kSpeed * g_DT;

	// on verifie si on appuie sur la fleche du haut ou sur w
	if(GetKeyState(VK_UP) & 0x80 || GetKeyState('W') & 0x80) {				

		// on fait avancer la camera
		MoveCamera(speed);				
	}

	// on verifie si on appuie sur la fleche du bas ou sur s
	if(GetKeyState(VK_DOWN) & 0x80 || GetKeyState('S') & 0x80) {			

		// on fait reculer la camera
		MoveCamera(-speed);				
	}

	// on verifie si on appuie sur la fleche gauche ou sur a
	if(GetKeyState(VK_LEFT) & 0x80 || GetKeyState('A') & 0x80) {			

		// on bouge la camera a gauche
		StrafeCamera(-speed);
	}

	// on verifie si on appuie sur la fleche droite ou sur la touche d
	if(GetKeyState(VK_RIGHT) & 0x80 || GetKeyState('D') & 0x80) {			

		// on bouge la camera a droite
		StrafeCamera(speed);
	}	
}


// mise a jour de la vision de la camera
void CCamera::Update() 
{
	// initi d'une var pour le produit en croix
	CVector3 vCross = Cross(m_vView - m_vPosition, m_vUpVector);

	// Normalization
	m_vStrafe = Normalize(vCross);

	// mouvement de la camera avec la souris
	SetViewByMouse();

	// verification si appuie sur clavier
	CheckForMovement();
	
	// Calcule des frames
	CalculateFrameRate();
}


// mise a jour de la camera en fct de la vue
void CCamera::Look()
{
	// on donne la position de notre camera puis la vision de la camera 
	gluLookAt(m_vPosition.x, m_vPosition.y, m_vPosition.z,	
			  m_vView.x,	 m_vView.y,     m_vView.z,	
			  m_vUpVector.x, m_vUpVector.y, m_vUpVector.z);
}
