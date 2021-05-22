# include <cstdlib>
# include <iostream>
# include <iomanip>
# include <fstream>
# include <cmath>

# include "../include/pgmb_io.h"

using namespace std;

//****************************************************************************80
//    CH_CAP capitalizes a single character.
char ch_cap ( char ch ){
  if ( 97 <= ch && ch <= 122){
    ch = ch - 32;
  }   
  return ch;
}

//****************************************************************************80
//    PGMB_CHECK_DATA checks the data for a binary portable gray map file.
bool pgmb_check_data (int xsize, int ysize, unsigned char maxg, unsigned char *g){
  int i;
  unsigned char *index;
  int j;

  if ( xsize <= 0 ){
    cout << "\n";
    cout << "PGMB_CHECK_DATA: Error!\n";
    cout << "  xsize <= 0.\n";
    cout << "  xsize = " << xsize << "\n";
    return true;
  }

  if ( ysize <= 0 ){
    cout << "\n";
    cout << "PGMB_CHECK_DATA: Error!\n";
    cout << "  ysize <= 0.\n";
    cout << "  ysize = " << ysize << "\n";
    return true;
  }

  if ( g == NULL ){
    cout << "\n";
    cout << "PGMB_CHECK_DATA: Error!\n";
    cout << "  Null pointer to g.\n";
    return true;
  }

  index = g;

  for ( j = 0; j < ysize; j++ ){
    for ( i = 0; i < xsize; i++ ){
      if ( maxg < *index ){
        cout << "\n";
        cout << "PGMB_CHECK_DATA - Fatal error!\n";
        cout << "  Data exceeds MAXG = " << ( int ) maxg << "\n";
        cout << "  G(" << i << "," << j << ")=" << ( int ) (*index) << "\n";
        return true;
      }
      index = index + 1;
    }
  } 
  return false;
}

//****************************************************************************80
//    PGMB_EXAMPLE sets up some data for a binary portable gray map file.
bool pgmb_example ( int xsize, int ysize, unsigned char *g ){
  int i;
  unsigned char *indexg;
  int j;
  int periods = 3;
  float PI = 3.14159265;
  float x;
  float y;

  indexg = g;

  for ( i = 0; i < ysize; i++ ){
    y = ( ( float ) ( 2 * i ) ) / ( ( float ) ( ysize - 1 ) ) - 1.0;

    for ( j = 0; j < xsize; j++ ){
      x = ( 2.0 * PI * ( float ) ( periods * j ) ) / ( ( float ) ( xsize - 1 ) );
      *indexg = ( unsigned char ) ( 20.0 * ( sin ( x ) - y + 2 ) );
      indexg = indexg + 1;
    }
  }
  return false;
}

//****************************************************************************80
//    PGMB_READ reads the header and data from a binary portable gray map file.
bool pgmb_read ( string input_name, int &xsize, int &ysize, unsigned char &maxg, unsigned char **g ){
  bool error;
  ifstream input;

  input.open ( input_name.c_str ( ), ios::binary );

  if ( !input ){
    cout << "\n";
    cout << "PGMB_READ: Fatal error!\n";
    cout << "  Cannot open the input file " << input_name << "\n";
    return true;
  }

    //  Read the header.
    error = pgmb_read_header ( input, xsize, ysize, maxg );

    if ( error ){
        cout << "\n";
        cout << "PGMB_READ: Fatal error!\n";
        cout << "  PGMB_READ_HEADER failed.\n";
        return true;
    }

//  Allocate storage for the data.
  *g = new unsigned char [ xsize * ysize ];

//  Read the data.
  error = pgmb_read_data ( input, xsize, ysize, *g );

  if ( error ){
    cout << "\n";
    cout << "PGMB_READ: Fatal error!\n";
    cout << "  PGMB_READ_DATA failed.\n";
    return true;
  }

//  Close the file.
  input.close();

  return false;
}

//****************************************************************************80
//    PGMB_READ_DATA reads the data in a binary portable gray map file.
bool pgmb_read_data ( ifstream &input, int xsize, int ysize, unsigned char *g ){
  char c;
  bool error;
  int i;
  unsigned char *indexg;
  int j;

  indexg = g;

  for ( j = 0; j < ysize; j++ )
  {
    for ( i = 0; i < xsize; i++ )
    {
      input.read ( &c, 1 );
      *indexg = ( unsigned char ) c;
      indexg = indexg + 1;
      error = input.eof();
      if ( error )
      {
        cout << "\n";
        cout << "PGMB_READ_DATA - Fatal error!\n";
        cout << "  End of file reading pixel (" 
          << i << ", " << j <<") \n";
        return true;
      }
    }
  }
  return false;
}

//****************************************************************************80
//    PGMB_READ_HEADER reads the header of a binary portable gray map file.
bool pgmb_read_header ( ifstream &input, int &xsize, int &ysize, unsigned char &maxg ){
  int fred;
  string line;
  string rest;
  int step;
  string word;

  step = 0;

  while ( 1 )
  {
    getline ( input, line );

    if ( input.eof ( ) )
    {
      cout << "\n";
      cout << "PGMB_READ_HEADER - Fatal error!\n";
      cout << "  End of file.\n";
      return true;
    }

    if ( line[0] == '#' )
    {
      continue;
    }

    if ( step == 0 )
    {
      s_word_extract_first ( line, word, rest );

      if ( s_len_trim ( word ) <= 0 )
      {
        continue;
      }

      if ( !s_eqi ( word, "P5" ) )
      {
        cout << "\n";
        cout << "PGMB_READ_HEADER - Fatal error.\n";
        cout << "  Bad magic number = \"" << word << "\".\n";
        return true;
      }
      line = rest;
      step = 1;
    }

    if ( step == 1 )
    {
      s_word_extract_first ( line, word, rest );
 
      if ( s_len_trim ( word ) <= 0){
        continue;
      }
      xsize = atoi (word.c_str());
      line = rest;
      step = 2;
    }

    if ( step == 2 )
    {
      s_word_extract_first ( line, word, rest );

      if ( s_len_trim ( word ) <= 0 )
      {
        continue;
      }
      ysize = atoi ( word.c_str ( ) );
      line = rest;
      step = 3;
    }

    if ( step == 3 )
    {
      s_word_extract_first ( line, word, rest );

      if ( s_len_trim ( word ) <= 0 )
      {
        continue;
      }
      fred = atoi ( word.c_str ( ) );
      maxg = ( unsigned char ) fred;
      line = rest;
      break;
    }
  }

  return false;
}

//****************************************************************************80

//    PGMB_READ_TEST tests the binary portable gray map read routines.
bool pgmb_read_test ( string input_name )
{
  bool error;
  unsigned char *g;
  unsigned char maxg;
  int xsize;
  int ysize;

//  Read the data.

  error = pgmb_read ( input_name, xsize, ysize, maxg, &g );

  if (error){
    cout << "\n";
    cout << "PGMB_READ_TEST: Fatal error!\n";
    cout << "  PGMB_READ failed.\n";
    delete [] g;
    return true;
  }

//  Check the data.

  error = pgmb_check_data ( xsize, ysize, maxg, g );

  delete [] g;

  if ( error ){
    cout << "\n";
    cout << "  PGMB_CHECK_DATA reports bad data from the file.\n";
    return true;
  }

  cout << "\n";
  cout << "  PGMB_CHECK_DATA passes the data from the file.\n";

  return false;
}


//    S_EQI reports whether two strings are equal, ignoring case.
bool s_eqi ( string s1, string s2 )
{
  int i;
  int nchar;
  int s1_length;
  int s2_length;

  s1_length = s1.length ( );
  s2_length = s2.length ( );

  if (s1_length < s2_length){
    nchar = s1_length;
  }
  else {
    nchar = s2_length;
  }

//  The strings are not equal if they differ over their common length.
  for ( i = 0; i < nchar; i++ ){
    if ( ch_cap ( s1[i] ) != ch_cap (s2[i])){
      return false;
    }
  }

//  The strings are not equal if the longer one includes nonblanks
//  in the tail.
  if ( nchar < s1_length){
    for ( i = nchar; i < s1_length; i++){
      if ( s1[i] != ' '){
        return false;
      }
    } 
  }
  else if ( nchar < s2_length){
    for ( i = nchar; i < s2_length; i++){
      if ( s2[i] != ' ' ){
        return false;
      }
    } 
  }

  return true;
}
//****************************************************************************80
//    S_LEN_TRIM returns the length of a string to the last nonblank.
int s_len_trim ( string s )
{
  int n;

  n = s.length ( );

  while ( 0 < n ) 
  {
    if ( s[n-1] != ' ' )
    {
      return n;
    }
    n = n - 1;
  }

  return n;
}
//****************************************************************************80
//    S_WORD_EXTRACT_FIRST extracts the first word from a string.
void s_word_extract_first ( string s, string &s1, string &s2 ){
  int i;
  int mode;
  int s_len;

  s_len = s.length();
  s1 = "";
  s2 = "";
  mode = 1;

  for (i = 0; i < s_len; i++){
    if (mode == 1) {
      if (s[i] !=' ') {
         mode = 2;
      }
    }
    else if ( mode == 2){
      if ( s[i] == ' ' ){
        mode = 3;
      }
    }
    else if ( mode == 3){
      if ( s[i] != ' '){
        mode = 4;
      }
    }
    if (mode == 2){
      s1 = s1 + s[i];
    }
    else if (mode == 4)
    {
      s2 = s2 + s[i];
    }
  }
  return;
}
//****************************************************************************80
