#ifndef _CAMERA_H
#define _CAMERA_H


// Class de la camera
class CCamera {

public:

	// camera constructeur
	CCamera();	

	// données de la camera comme la position ou la vision
	CVector3 Position() {	return m_vPosition;		}
	CVector3 View()		{	return m_vView;			}
	CVector3 UpVector() {	return m_vUpVector;		}
	CVector3 Strafe()	{	return m_vStrafe;		}
	
	// ceci change la position, vue et vecteur haut de la camera
	void PositionCamera(float positionX, float positionY, float positionZ,
			 		    float viewX,     float viewY,     float viewZ,
						float upVectorX, float upVectorY, float upVectorZ);

	// rotation de la camera autour de la position
	void RotateView(float angle, float X, float Y, float Z);

	// mouvement de la camera en fct des mouvements de la souris
	void SetViewByMouse(); 

	// rotation de la camera autour d'un point
	void RotateAroundPoint(CVector3 vCenter, float X, float Y, float Z);

	// mouvement camera gauche ou droite
	void StrafeCamera(float speed);

	// mv avant arriere
	void MoveCamera(float speed);

	// on verifie s'il y a l'utilisation du clavier
	void CheckForMovement();

	// maj des données
	void Update();

	// gluLookAt()
	void Look();

private:

	// position de la camera
	CVector3 m_vPosition;					

	// vision de la camera
	CVector3 m_vView;						

	// vecteurup de la camera
	CVector3 m_vUpVector;		
	
	
	CVector3 m_vStrafe;						
};

#endif
