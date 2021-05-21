// HeightMap.cpp

#include "../include/HeightMap.h"

HeightMap::HeightMap()
: m_id_texture(0), m_id_display_list(0), m_width(0), m_depth(0), m_hauteur_max(0),
m_data(NULL), m_loaded(false)
{
}

HeightMap::~HeightMap()
{
	Free();
}

bool HeightMap::LoadFile(char* str_fichier, unsigned int hauteur_max,
		unsigned int largeur_quad, TGAFiltering filtering)
{
	unsigned char header[5];	// Ent�te du fichier HMAP
	char str_nom_texture[50];	// Le nom de la texture TGA associ�e.
	TGALoader tga_loader;		// Un TGALoader.
	unsigned char packet_header,	// Le header de chaque paquet (RAW ou RLE).
		uc;
	unsigned int nb_pixels;	// Nombre de pixels repr�sent�s par un paquet
							// (RAW ou RLE).
	int i=0, j=0, x=0, y=0;	// Compteurs

	m_hauteur_max = hauteur_max;

	// On ouvre le fichier
	ifstream fichier(str_fichier, ios::in | ios::binary);

	if(!fichier)
		return false;

	// On lit le header compos� :
	// - sur 1 octet du num�ro de l'octet auquel commencent les donn�es
	// - sur 2 octets de la largeur de la heightmap stock�e en little endian
	// - sur 2 octets de la hauteur de la heightmap stock�e en little endian
	fichier.read((char*)header, 5);

	// On r�cup�re la hauteur et la largeur de la map.
	m_width = ((unsigned int)header[2] << 8) + (unsigned int)header[1];
	m_depth = ((unsigned int)header[4] << 8) + (unsigned int)header[3];

	// On lit le nom de la texture TGA associ�e � la heightmap dans str_nom_texture.
	fichier.read(str_nom_texture, (int)header[0]-5);
	str_nom_texture[header[0]-5] = '\0';

	// On charge la texture TGA dans m_id_texture.
	TGAErrorCode ret = tga_loader.LoadOpenGLTexture((char*)str_nom_texture,
		&m_id_texture, filtering);
	if (ret != TGA_OK)
	{
		cerr << "Erreur TGA : " << ret << endl;
		return false;
	}

	Free();	// Si des donn�es sont allou�es dans m_data on les lib�re.

	// On charge les donn�es dans data.
	m_data = new unsigned char[m_width*m_depth];

	// On parcourt le fichier HMAP paquet apr�s paquet.
	for(i=0 ; i<m_width*m_depth ; i += nb_pixels)
	{
		// On r�cup�re le 1er octet du paquet en cours, qui est son header.
		packet_header = fichier.get();

		// On r�cup�re le nombre de pixels dans le paquet (c'est � dire le nombre
		// form� par les 7 bits de poids faible de packet_header +1).
		nb_pixels = (unsigned int)(packet_header & 0x7F) + 1;
			
		// Si le bit de poids le plus fort de packet_header est � 1, on a affaire
		// � un paquet RLE
		if ((packet_header & 0x80) == 0x80)
		{
			// On r�cup�re dans uc la valeur du pixel r�p�t� nb_pixels fois.
			uc = fichier.get();

			// On r�p�te nb_pixels fois cette valeur dans m_data.
			for(j=0 ; j<nb_pixels ; j++)
				m_data[i+j] = uc;
		}
		// Sinon on a affaire � un paquet plein (RAW), on copie les nb_pixels pixels
		// suivants du fichier HMAP.
		else
			for(j=0 ; j<nb_pixels ; j++)
				m_data[i+j] = fichier.get();
	}

	// On cr�e la display list.
	m_id_display_list =  glGenLists(1);
	glNewList(m_id_display_list, GL_COMPILE);
		glBindTexture(GL_TEXTURE_2D, m_id_texture);
		glBegin(GL_QUADS);
		// On parcourt m_data en largeur et en hauteur en utilisant x et y comme
		// compteurs, mais on s'arr�te avant m_depth pour y et m_width pour
		// x � cause du fait que l'on utilise (x+1) et (y+1) pour dessiner les autres
		// points des quads.
		// Les coordonn�es x et z de chaque quad correspondent aux valeurs
		// des compteurs x et y respectivement multipli�es par la largeur de chaque
		// quad.
		// Les coordonn�es z de chaque vertex de quad d�pendent de la hauteur
		// maximale d'un point de la map et du degr� de "noirceur" du point
		// correspondant en (x,y).
		// Je me doute que je ne suis pas tr�s clair mais je ne vois pas trop comment
		// expliquer, le mieux c'est de regarder le code et d'essayer de
		// comprendre...
		for(y=0 ; y<m_depth-1 ; y++)
			for(x=0 ; x<m_width-1 ; x++)
			{
				glTexCoord2i(0, 0);
				glVertex3f((float)(x*largeur_quad),
					(float)hauteur_max - ((float)m_data[x+y*m_width]/255.0)*(float)hauteur_max,
					(float)(y*largeur_quad));

				glTexCoord2i(0, 1);
				glVertex3f((float)(x*largeur_quad),
					(float)hauteur_max - ((float)m_data[x+(y+1)*m_width]/255.0)*(float)hauteur_max,
					(float)((y+1)*largeur_quad));

				glTexCoord2i(1, 1);
				glVertex3f((float)((x+1)*largeur_quad),
					(float)hauteur_max - ((float)m_data[(x+1)+(y+1)*m_width]/255.0)*(float)hauteur_max,
					(y+1)*largeur_quad);

				glTexCoord2i(1, 0);
				glVertex3f((float)((x+1)*largeur_quad),
					(float)hauteur_max - ((float)m_data[(x+1)+y*m_width]/255.0)*(float)hauteur_max,
					(float)(y*largeur_quad));
			}
		glEnd();
	glEndList();

	fichier.close();

	m_loaded = true;	// On indique que le chargement s'est bien pass�.
	return true;
}

void HeightMap::Afficher()
{
	// On utilise la display list cr�e en Init() si le fichier est bien charg�.
	if(m_loaded)
		glCallList(m_id_display_list);
}

void HeightMap::Free()
{
	// Si des donn�es sont allou�es dans m_data on les lib�re.
	if(m_loaded)
	{
		delete [] m_data;
		m_data = NULL;
		m_loaded = false;
	}
}
