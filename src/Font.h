#ifndef __Font__
#define __Font__

#include "AwesomeGL.h"

class Font {
public:
   GLuint tex;		// texture object

   int w;			// width of texture in pixels
   int h;			// height of texture in pixels

   struct {
      float ax;	// advance.x
      float ay;	// advance.y

      float bw;	// bitmap.width;
      float bh;	// bitmap.height;

      float bl;	// bitmap_left;
      float bt;	// bitmap_top;

      float tx;	// x offset of glyph in texture coordinates
      float ty;	// y offset of glyph in texture coordinates
   } c[128];		// character information

   Font(FT_Face face, int height);
   ~Font();

};

#endif
