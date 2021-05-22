# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <cmath>

using namespace std;

/* ==================== READ PBM ==================== */

// PGMB_READ reads the header and data from a binary portable gray map file.
bool pgmb_read ( string file_in_name, int &xsize, int &ysize, 
                 unsigned char &maxg, unsigned char **g );

// PGMB_READ_DATA reads the data in a binary portable gray map file.
bool pgmb_read_data ( ifstream &file_in, int xsize, int ysize, 
                      unsigned char *g );

// PGMB_READ_HEADER reads the header of a binary portable gray map file.
bool pgmb_read_header ( ifstream &file_in, int &xsize, int &ysize, 
                        unsigned char &maxg );

// PGMB_READ_TEST tests the binary portable gray map read routines.
bool pgmb_read_test ( string file_in_name );


/* ===================== OTHER ===================== */

// CH_CAP capitalizes a single character.
char ch_cap ( char ch );

// PGMB_CHECK_DATA checks the data for a binary portable gray map file.
bool pgmb_check_data ( int xsize, int ysize, unsigned char maxg, unsigned char *g );

// PGMB_EXAMPLE sets up some data for a binary portable gray map file.
bool pgmb_example ( int xsize, int ysize, unsigned char *g );

// S_EQI reports whether two strings are equal, ignoring case.
bool s_eqi ( string s1, string s2 );

// S_LEN_TRIM returns the length of a string to the last nonblank.
int s_len_trim ( string s );

// S_WORD_EXTRACT_FIRST extracts the first word from a string.
void s_word_extract_first ( string s, string &s1, string &s2 );
