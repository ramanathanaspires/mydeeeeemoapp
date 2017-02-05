
#ifndef _CFBUTILS_H
#define _CFBUTILS_H

#include <asm/types.h>

/* This constant, being ORed with the color index tells the library
 * to draw in exclusive-or mode (that is, drawing the same second time
 * in the same place will remove the element leaving the background intact).
 */
#define XORMODE	0x80000000

union multiptr {
        unsigned char *p8;
        unsigned short *p16;
        unsigned long *p32;
};

extern __u32 xres, yres;
extern unsigned long pixval[309][225];

int open_framebuffer(void);
void close_framebuffer(void);
void setcolor(unsigned colidx, unsigned value);
void put_cross(int x, int y, unsigned colidx);
void pixel (int x, int y, unsigned colidx);
void line (int x1, int y1, int x2, int y2, unsigned colidx);
void rect (int x1, int y1, int x2, int y2, unsigned colidx);
void fillrect (int x1, int y1, int x2, int y2, unsigned colidx);
void cleansig();
void getpixelvalues(int,int,int,int);


#endif /* _CFBUTILS_H */
