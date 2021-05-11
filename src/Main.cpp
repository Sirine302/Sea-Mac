#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#pragma comment(lib, "winmm.lib")

#include "main.h"									
#include "camera.h"										

bool  g_bFullScreen = true;								// mode plein ecran par defaut
HWND  g_hWnd;											// données en rapport avec la fenetre
RECT  g_rRect;											// données en rapport avec la fenetre
HDC   g_hDC;											
HGLRC g_hRC;											
HINSTANCE g_hInstance;									
float g_DT;												


// tableau qui va contenir les donnéess de la height map (fichier .raw qui va stocké des valeurs entre 0 et 255.
// 0 est le plus petit point et 255 le plus haut
BYTE g_HeightMap[MAP_SIZE*MAP_SIZE];					

// des lignes ou du remplissage pour la map
bool  g_bRenderMode = true;									

// camera globale
CCamera g_Camera;


// initialisation de l'app
void Init(HWND hWnd)
{
	g_hWnd = hWnd;										// données en rapport avec la fenetre
	GetClientRect(g_hWnd, &g_rRect);					// données en rapport avec la fenetre
	InitializeOpenGL(g_rRect.right, g_rRect.bottom);	// données en rapport avec la fenetre

	
	// on lit le fichier height map (fichier .raw) et on met les données dans le tab g_HeightMap
	LoadRawFile("Terrain.raw", MAP_SIZE * MAP_SIZE, g_HeightMap);	

	// on donne un pont de vision de départ pour la camera
	g_Camera.PositionCamera(1200, 300, 1150,  1199, 300, 1150,  0, 1, 0);

}


// frequence d'img
bool AnimateNextFrame(int desiredFrameRate)
{
	static float lastTime = GetTickCount() * 0.001f;
	static float elapsedTime = 0.0f;

	float currentTime = GetTickCount() * 0.001f; // temps en miliseconde 
	float deltaTime = currentTime - lastTime; 
	float desiredFPS = 1.0f / desiredFrameRate; 

	elapsedTime += deltaTime; 
	lastTime = currentTime; // maj de lastTime

	// verification qu'on a les fps souhaités
	if( elapsedTime > desiredFPS )
	{
		g_DT = desiredFPS; 
		elapsedTime -= desiredFPS; 

		return true;
	}

	return false;
}

// boucle principale
WPARAM MainLoop()
{
	MSG msg;

	while(1)											// boucle infinie
	{													
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{ 
			if(msg.message == WM_QUIT)					
				break;
			TranslateMessage(&msg);						
			DispatchMessage(&msg);						
		}
		else											
		{ 		
			if(AnimateNextFrame(60))					// on fait en sorte d'animé 60 fps
			{
				g_Camera.Update();							// maj des données de la camera
				RenderScene();							
			}
			else
			{
				Sleep(1);								
			}
		} 
	}

	DeInit();											//on nettoie la memoire allouée

	return(msg.wParam);									
}

// rendu de la scène entiere
void RenderScene() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// on nettoie l'ecran
	glLoadIdentity();									

	// on donne la pos de la camera
	g_Camera.Look();

	RenderHeightMap(g_HeightMap);						// Rendu de la height map


	SwapBuffers(g_hDC);				
}


// messages de la fenetre
LRESULT CALLBACK WinProc(HWND hWnd,UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    PAINTSTRUCT    ps;

    switch (uMsg)
	{ 
    case WM_SIZE:										// redimension de la fenetre
		if(!g_bFullScreen)								
		{
			SizeOpenGLScreen(LOWORD(lParam),HIWORD(lParam));
			GetClientRect(hWnd, &g_rRect);				
		}
        break; 
 
	case WM_PAINT:									
		BeginPaint(hWnd, &ps);									
		EndPaint(hWnd, &ps);							
		break;


	case WM_LBUTTONDOWN:								// quand click gauche de la souris
		
		g_bRenderMode = !g_bRenderMode;

		if(g_bRenderMode) 				
		{
			// triangle en mode non rempli		
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	
		}
		else 
		{
			// triangles en mode rempli 
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	
		}
		break;


	case WM_KEYDOWN:
		switch(wParam) 
		{
			case VK_ESCAPE:								// quand on appuie sur la barre d'espace
				PostQuitMessage(0);						// on quitte la fenetre
				break;
		}
		break;
 
    case WM_CLOSE:										
        PostQuitMessage(0);								
        break; 
    } 
 
    return DefWindowProc (hWnd, uMsg, wParam, lParam); 	
}
    
