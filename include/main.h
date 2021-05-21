#ifndef _MAIN_H
#define _MAIN_H
#define _CRT_SECURE_NO_DEPRECATE

// #include <windows.h>
// #include <gl\gl.h>				
// #include <gl\glu.h>										

#include <SDL2/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "Terrain.h"						
							
// class des points 3D
struct CVector3
{
public:
	
	// constructeur par defaut
	CVector3() {}

	// initialisation des donn�es quand on cr�e une instance
	CVector3(float X, float Y, float Z) 
	{ 
		x = X; y = Y; z = Z;
	}

	// ajout de vecteurs ensemble
	CVector3 operator+(CVector3 vVector)
	{
		
		return CVector3(vVector.x + x, vVector.y + y, vVector.z + z);
	}

	// soustraction de vecteurs 
	CVector3 operator-(CVector3 vVector)
	{
		return CVector3(x - vVector.x, y - vVector.y, z - vVector.z);
	}
	
	// scalaire
	CVector3 operator*(float num)
	{
		return CVector3(x * num, y * num, z * num);
	}

	// division vecteur
	CVector3 operator/(float num)
	{
		return CVector3(x / num, y / num, z / num);
	}

	float x, y, z;						
};


#define SCREEN_WIDTH 800								// largeur de l'ecran a 800px
#define SCREEN_HEIGHT 600								// hauteur de l'ecran a 600 px
#define SCREEN_DEPTH 16									// 16 bits par pixel

extern bool  g_bFullScreen;								// plein ecran par defaut
extern HWND  g_hWnd;									// donn�es relatives a la fenetre
extern RECT  g_rRect;									// donn�es relatives a la fenetre
extern HDC   g_hDC;										
extern HGLRC g_hRC;										
extern HINSTANCE g_hInstance;							// donn�es relatives a la fenetre
extern float g_DT;										// stock le tps ecoul� entre la frame actuelle et l'ancienne


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hprev, PSTR cmdline, int ishow);

// gestion de msg de la fenetre
LRESULT CALLBACK WinProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

// boucle principale
WPARAM MainLoop();

// mode plein ecran
void ChangeToFullScreen();

// donn�es relatives a la fenetre
HWND CreateMyWindow(LPSTR strWindowName, int width, int height, DWORD dwStyle, bool bFullScreen, HINSTANCE hInstance);

// donn�es relatives a la fenetre
bool bSetupPixelFormat(HDC hdc);

// donn�es relatives a la fenetre
void SizeOpenGLScreen(int width, int height);

// openGl
void InitializeOpenGL(int width, int height);

// init de l'app
void Init(HWND hWnd);

// dessine tout � l'ecran
void RenderScene();

// libere la memoire pour l'app
void DeInit();

#endif
