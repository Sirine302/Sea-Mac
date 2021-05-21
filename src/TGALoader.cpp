// TGALoader.cpp - chargeur de fichiers TGA.
// 2004 par Funto. Si vous utilisez cette classe dans un de vos projets, un mail
// de remerciement � funto@nomade.fr serait le bienvenu ;).

#include "../include/TGALoader.h"

TGALoader::TGALoader()
: m_data(NULL), m_loaded(false), m_height(0), m_width(0), m_bpp(0)
{
}

TGALoader::TGALoader(char* path, TGAErrorCode* error/*=NULL*/)
: m_data(NULL), m_loaded(false), m_height(0), m_width(0), m_bpp(0)
{
	if (error == NULL) LoadFile(path);
	else *error = LoadFile(path);
}

TGALoader::~TGALoader()
{
	Free();
}

TGAErrorCode TGALoader::LoadFile(char* path)
{
	unsigned char header[18];
	ifstream file((const char*)path, ios::in | ios::binary);
	unsigned int i=0, j=0;
	bool origin_non_bottom_left=false;	// Indique si l'image a pour origine le point
										// en bas � gauche (par d�faut) ou en bas
										// � droite.

	if (!file)
		return TGA_FILE_NOT_FOUND;

	file.read((char*)header, 18);

	this->Free();

	m_width = ((unsigned int)header[13] << 8) + (unsigned int)header[12];
	m_height = ((unsigned int)header[15] << 8) + (unsigned int)header[14];
	m_bpp = ((unsigned int)header[16])>>3;	// (x>>3 �quivaut � x/8)

	if (!((m_width == 1 || m_width == 2 || m_width == 4 || m_width == 8 ||
		m_width == 16 || m_width == 32 || m_width == 64 || m_width == 128 ||
		m_width == 256 || m_width == 512) &&
		(m_height == 1 || m_height == 2 || m_height == 4 || m_height == 8 ||
		m_height == 16 || m_height == 32 || m_height == 64 || m_height == 128 ||
		m_height == 256 || m_height == 512)))
	{
		m_loaded = false;
		return TGA_NOT_POWER_OF_TWO;
	}

	// Bit 5 de l'octet 17
	origin_non_bottom_left = ((header[17] & 0x20) == 0x20 ? true : false);

	if ((m_data = (unsigned char*)malloc(m_height*m_width*m_bpp)) == NULL)
	{
		m_loaded = false;
		return TGA_NOT_ENOUGH_MEMORY;
	}

	// On place le pointeur du fichier apr�s le header (18 1ers bytes)
	// et apr�s l' "identification field", dont la taille est indiqu�e dans
	// header[0].
	file.seekg(18+(long)header[0], ios::beg);

	// header[2] d�termine le type d'image :
	// 1 -> non compress�, utilise une palette.
	// 2 -> non compress�, vraies couleurs.
	// 9 -> compress� en RLE, utilise une palette.
	// 10 -> compress� en RLE, n'utilise pas de palette.
	// Les autres types d'iages ne sont pas support�s.
	
	// TYPE 2 - non compress�, vraies couleurs, 24 ou 32 bits
	if (header[2] == 2 && (m_bpp == 3 || m_bpp == 4))
	{
		for(i=0 ; i<m_width*m_height*m_bpp ; i+=m_bpp)
		{
			m_data[i+2] = file.get();					// R
			m_data[i+1] = file.get();					// G
			m_data[i] = file.get();						// B
			if(m_bpp == 4) m_data[i+3] = file.get();	// A
		}
	}

	// TYPE 10 - RLE, vraies couleurs, 24 ou 32 bits
	else if (header[2] == 10 && (m_bpp == 3 || m_bpp == 4))
	{
		unsigned char packet_header, red, green, blue, alpha;
		unsigned int nb_pixels;	// Nombre de pixels repr�sent�s par un paquet.
		for(i=0 ; i<m_width*m_height*m_bpp ; i += nb_pixels*m_bpp)
		{
			packet_header = file.get();
			nb_pixels = (unsigned int)(packet_header & 0x7F) + 1;
			
			// Paquet RLE
			if ((packet_header & 0x80) == 0x80)
			{
				blue = file.get();
				green = file.get();
				red = file.get();
				if(m_bpp == 4) alpha = file.get();

				for(j=0 ; j<nb_pixels*m_bpp ; j += m_bpp)
				{
					m_data[i+j] = red;
					m_data[i+j+1] = green;
					m_data[i+j+2] = blue;
					if(m_bpp == 4) m_data[i+j+3] = alpha;
				}
			}
			// Paquet plein (RAW)
			else
			{
				for(j=0 ; j<nb_pixels*m_bpp ; j+=m_bpp)
				{
					m_data[i+j+2] = file.get();					// B
					m_data[i+j+1] = file.get();					// G
					m_data[i+j] = file.get();					// R
					if(m_bpp == 4) m_data[i+j+3] = file.get();	// A
				}
			}
		}
	}

	// Pour les images d'un type non support�, on renvoie une erreur et rien n'est
	// charg�.
	else
	{
		free(m_data);
		m_data = NULL;
		m_loaded = false;
		return TGA_UNSUPPORTED_TYPE;
	}

	// Pour les images dont l'origine est en haut � gauche, on fait un flip
	// vertical.
	if (origin_non_bottom_left)
	{
		unsigned char temp;
		for(i=0 ; i<m_height/2 ; i++)
		{
			for(j=0 ; j<m_width*m_bpp ; j++)
			{
				temp = m_data[i*m_width*m_bpp + j];
				m_data[i*m_width*m_bpp + j] = m_data[(m_height-i-1)*m_width*m_bpp + j];
				m_data[(m_height-i-1)*m_width*m_bpp + j] = temp;
			}
		}
	}

	m_loaded = true;
	file.close();
	return TGA_OK;
}

#ifdef TGA_OPENGL_SUPPORT

GLuint TGALoader::SendToOpenGL(TGAFiltering filtering //=TGA_NO_FILTER
							   )
{
	GLuint result = 0;
	if(m_loaded)
	{
		glGenTextures(1, &result);
		SendToOpenGLWithID(result, filtering);
	}
	return result;
}

void TGALoader::SendToOpenGLWithID(GLuint ID,
								   TGAFiltering filtering //=TGA_NO_FILTER
								  )
{
	if (m_loaded)
	{
		glBindTexture(GL_TEXTURE_2D, ID);
		if(filtering == TGA_BILINEAR || filtering == TGA_TRILINEAR
#ifdef GL_TEXTURE_MAX_ANISOTROPY_EXT
			|| filtering == TGA_ANISOTROPIC
#endif
			)
		{
			gluBuild2DMipmaps(
				GL_TEXTURE_2D,
				m_bpp,
				m_width,
				m_height,
				(m_bpp == 3 ? GL_RGB : GL_RGBA),
				GL_UNSIGNED_BYTE,
				m_data);
		}
		else
		{
			glTexImage2D(
				GL_TEXTURE_2D,
				0,			// mipmap == 0
				m_bpp,
				m_width,
				m_height,
				0,			// largeur du bord == 0
				(m_bpp == 3 ? GL_RGB : GL_RGBA),
				GL_UNSIGNED_BYTE,
				m_data);
		}

		if (filtering == TGA_NO_FILTER)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		}
		else if (filtering == TGA_LINEAR)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		}
		else if (filtering == TGA_BILINEAR)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_LINEAR_MIPMAP_NEAREST);
		}
		else if (filtering == TGA_TRILINEAR)
		{
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_LINEAR_MIPMAP_LINEAR);
		}
#ifdef GL_TEXTURE_MAX_ANISOTROPY_EXT
		else if (filtering == TGA_ANISOTROPIC)
		{
			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, 2.0f) ; 
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,
				GL_LINEAR_MIPMAP_LINEAR);
		}
#endif

		
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	}
}

TGAErrorCode TGALoader::LoadOpenGLTexture(
		char* path,
		GLuint* pID, //=NULL
		TGAFiltering filtering //=TGA_NO_FILTER
										)
{
	TGAErrorCode ret = LoadFile(path);
	if(ret == TGA_OK)
	{
		if(pID != NULL)
			(*pID) = SendToOpenGL(filtering);
		else
			SendToOpenGL(filtering);
		Free();
	}
	return ret;
}

TGAErrorCode TGALoader::LoadOpenGLTextureWithID(
		char* path,
		GLuint ID,
		TGAFiltering filtering //=TGA_NO_FILTER
											   )
{
	TGAErrorCode ret = LoadFile(path);
	if(ret == TGA_OK)
	{
		SendToOpenGLWithID(ID, filtering);
		Free();
	}
	return ret;
}

#endif	// defined TGA_OPENGL_SUPPORT

void TGALoader::Free()
{
	if (m_loaded)
	{
		free(m_data);
		m_data = NULL;
		m_loaded = false;
		m_height = 0;
		m_width = 0;
		m_bpp = 0;
	}
}
