// TGALoader.h - chargeur de fichiers TGA.
// 2004 par Funto. Si vous utilisez cette classe dans un de vos projets, un mail
// de remerciement à funto@nomade.fr serait le bienvenu ;).

#ifndef TGALOADER_H
#define TGALOADER_H

#define TGA_OPENGL_SUPPORT

#include <cstdlib>
#include <iostream>
#include <fstream>

#ifdef TGA_OPENGL_SUPPORT
	#ifdef WIN32
	#include <windows.h>
	#endif
#include <GL/gl.h>
#include <GL/glu.h>
#endif // defined TGA_OPENGL_SUPPORT

using namespace std;

enum TGAErrorCode
{
	TGA_OK,
	TGA_FILE_NOT_FOUND,
	TGA_UNSUPPORTED_TYPE,
	TGA_NOT_ENOUGH_MEMORY,
	TGA_NOT_POWER_OF_TWO
};

#ifdef TGA_OPENGL_SUPPORT
enum TGAFiltering
{
	TGA_NO_FILTER,
	TGA_LINEAR,
	TGA_BILINEAR,
	TGA_TRILINEAR
#ifdef GL_TEXTURE_MAX_ANISOTROPY_EXT
	,TGA_ANISOTROPIC
#endif
};
#endif

class TGALoader
{
private:
	unsigned char* m_data;
	bool m_loaded;
	unsigned int m_height, m_width;
	unsigned int m_bpp;	// Bytes Per Pixel : 0, 3 ou 4
public:
	TGALoader();
	TGALoader(char* path, TGAErrorCode* error=NULL);
	~TGALoader();
	TGAErrorCode LoadFile(char* path);

#ifdef TGA_OPENGL_SUPPORT
	GLuint SendToOpenGL(TGAFiltering filtering=TGA_NO_FILTER);

	void SendToOpenGLWithID(GLuint ID, TGAFiltering filtering=TGA_NO_FILTER);

	TGAErrorCode LoadOpenGLTexture(char* path, GLuint* pID=NULL,
		TGAFiltering filtering=TGA_NO_FILTER);

	TGAErrorCode LoadOpenGLTextureWithID(char* path, GLuint ID,
		TGAFiltering filtering=TGA_NO_FILTER);
#endif

	void Free();

	inline unsigned char* GetData() {return m_data;}
	inline bool IsLoaded() {return m_loaded;}
	inline unsigned int GetHeight() {return m_height;}
	inline unsigned int GetWidth() {return m_width;}
	inline unsigned int GetBpp() {return m_bpp;}
};

#endif // !defined TGALOADER_H
