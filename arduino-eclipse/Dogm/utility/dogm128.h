/*

  dogm128.h

  (c) 2010 Oliver Kraus (olikraus@gmail.com)
  
  This file is part of the dogm128 library.

  The dogm128 library is free software: you can redistribute it and/or modify
  it under the terms of the Lesser GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  The dogm128 library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  Lesser GNU General Public License for more details.

  You should have received a copy of the Lesser GNU General Public License
  along with dogm128.  If not, see <http://www.gnu.org/licenses/>.

  Display Selection
  one of the following constants could be defined:
    DOGM128_HW
    DOGS102_HW
    DOGM132_HW
    
  Normal or Revers Display Mode
    DOG_REVERSE
    
    
*/

#ifndef _DOGM128_H
#define _DOGM128_H

//#define DOG_REVERSE

//#define DOGM128_HW	/* uncomment for the DOGM128 display */
//#define DOGS102_HW		/* uncomment for the DOGS102 display */
//#define DOGM132_HW	/* uncomment for the DOGM132 display */

/* default is DOGM128_HW */
//#if !defined DOGM128_HW && !defined DOGM132_HW && !defined DOGS102_HW
//#define DOGM128_HW
//#endif

// prevent duplicate definition
//#if defined DOGM128_HW
//#if defined DOGM132_HW
//#undef DOGM132_HW
//#endif
//#if defined DOGS102_HW
//#undef DOGS102_HW
//#endif
//#endif
//#if defined DOGM132_HW && defined DOGS102_HW
//#undef DOGS102_HW
//#endif

#include "dogmpgm.h"
#include "dogmfont.h"

/* Arduino Pin assignments have been moved to dogmspi.c */

/* hight of a page for all supported DOG devices */ 
#define DOG_PAGE_HEIGHT 8

/* setings for the various DOG displays */
//#ifdef DOGM128_HW
//#define DOG_WIDTH 128
//#define DOG_HEIGHT 64
//#endif

//#ifdef DOGS102_HW
//#define DOG_WIDTH 102
//#define DOG_HEIGHT 64
//#endif

//#ifdef DOGM132_HW
//#define DOG_WIDTH 132
//#define DOG_HEIGHT 32
//#endif

/* derived constants */
//#define DOG_PAGE_CNT (DOG_HEIGHT/DOG_PAGE_HEIGHT)
//#define DOG_PAGE_WIDTH DOG_WIDTH

#define DOG_PAGE_WIDTH 132


#ifdef __cplusplus
extern "C" {
#endif

#define DOGS102_HW 1
#define DOGM128_HW 2
#define DOGM132_HW 3

extern uint8_t dog_model;
extern uint8_t dog_width;
extern uint8_t dog_height;
extern uint8_t dog_page_cnt;
extern uint8_t dog_reverse;

extern unsigned char dog_page_buffer[DOG_PAGE_WIDTH];

extern uint8_t dog_min_y;
extern uint8_t dog_max_y;

unsigned char dog_spi_out(unsigned char data);
void dog_spi_enable_client(void);
void dog_spi_disable_client(void);
void dog_cmd_mode(void);
void dog_data_mode(void);

  
void dog_Delay(uint16_t val);				/* delay in milliseconds */
void dog_Init(unsigned short pin_a0);
void dog_SetContrast(uint8_t val);			/* values between 0 and 63 allowed, previosly named dog_set_contranst() */
void dog_SetInvertPixelMode(uint8_t val);	/* previosly named dog_set_inverse() */

  
  
/* --- page functions --- */

void dog_StartPage(void);
uint8_t dog_NextPage(void);

/* --- dogmspi.c --- */
extern uint8_t dog_spi_pin_a0;

void dog_spi_init(void);
unsigned char dog_spi_out(unsigned char data);
void dog_spi_enable_client(void);
void dog_spi_disable_client(void);
void dog_cmd_mode(void);
void dog_data_mode(void);


/* --- set/clr functions --- */

//extern unsigned char dog_bit_to_mask[8];	/* dogmsd.c */
unsigned char* dog_get_bit_to_mask();

void dog_SetPixel(uint8_t x, uint8_t y);	/* dogmsp.c */
void dog_ClrPixel(uint8_t x, uint8_t y);	/* dogmcp.c */
void dog_XorPixel(uint8_t x, uint8_t y);	/* v1.01, dogmxp.c */

/* x1 must be lower or equal to x2 */
void dog_SetHLine(uint8_t x1, uint8_t x2, uint8_t y); 	/* v1.01, dogmsh.c */
void dog_ClrHLine(uint8_t x1, uint8_t x2, uint8_t y); 	/* v1.03, dogmch.c */
void dog_XorHLine(uint8_t x1, uint8_t x2, uint8_t y); 	/* v1.03, dogmxh.c */

uint8_t dog_get_vline_mask(uint8_t y1, uint8_t y2);	/* internal function, dogmov.c */
/* y1 must be lower or equal to y2 */
void dog_SetVLine(uint8_t x, uint8_t y1, uint8_t y2);			/* dogmsv.c */
void dog_ClrVLine(uint8_t x, uint8_t y1, uint8_t y2);			/* dogmcv.c */
void dog_XorVLine(uint8_t x, uint8_t y1, uint8_t y2);			/* dogmxv.c */

/* x1 must be lower or equal to x2 */
/* y1 must be lower or equal to y2 */
void dog_SetBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);	/* dogmsb.c */
void dog_ClrBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);	/* dogmcb.c */
void dog_XorBox(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2);	/* dogmxb.c */

/* --- bitmap functions --- */

/* at position (x,y) set a pixel for each logical one bit in the bitmap pattern */
/* the bitmap must contain (w+7)/8 bytes, each byte is interpreted as bitmap pattern */
/* most significant bit of the byte in the pattern is on the left */
void dog_SetHBitmap(uint8_t x, uint8_t y, const unsigned char *bitmap, uint8_t w); /* v1.01, dogmsm.c */
void dog_SetHBitmapP(uint8_t x, uint8_t y, DOG_PGM_P bitmap, uint8_t w); /* v1.01, dogmsmp.c */
void dog_SetBitmap(uint8_t x, uint8_t y, const unsigned char *bitmap, uint8_t w, uint8_t h); /* v1.01, dogmsm.c */
void dog_SetBitmapP(uint8_t x, uint8_t y, DOG_PGM_P bitmap, uint8_t w, uint8_t h); /* v1.01, dogmsmp.c */

/* --- draw functions --- */
/*
  size = 0:
  +++
  +#+
  +++
  size = 1:
  +#+
  ###
  +#+
*/

void dog_DrawPoint(uint8_t x, uint8_t y, uint8_t size); 	/* dogmdp.c */
void dog_DrawLine(uint8_t x1, uint8_t y1, uint8_t x2, uint8_t y2, uint8_t size); 	/* dogmdl.c */
void dog_DrawArc(uint8_t mx, uint8_t my, uint8_t r, uint8_t w0, uint8_t w1, uint8_t size);  	/* dogmda.c */


/* --- font information --- */

/* start: internal definitions. Do not call or use these definitions directly */
uint16_t dog_font_pgm_read_word(DOG_PGM_P buf) DOG_ATTR_FN_INLINE;
uint8_t dog_char(uint8_t x, uint8_t y, DOG_PGM_P font, uint8_t mode, uint8_t rot, unsigned char code);
#define fnt_get_bbox_capital_a(buf) (dog_font_pgm_read_word((buf)+0))
#define fnt_get_bbox_small_a(buf) (dog_font_pgm_read_word((buf)+2))
#define fnt_get_bbox_width(buf) (dog_pgm_read((buf)+4))
#define fnt_get_bbox_height(buf) (dog_pgm_read((buf)+5))
#define fnt_get_bbox_descent(buf) (dog_pgm_read((buf)+6))
#define FNT_DATA 7
/* end: internal definitions */


uint8_t dog_GetCharWidth(DOG_PGM_P font, unsigned char code);	/* dogmfont.c */

uint8_t dog_GetFontBBXHeight(DOG_PGM_P buf);
uint8_t dog_GetFontBBXWidth(DOG_PGM_P buf);
uint8_t dog_GetFontBBXDescent(DOG_PGM_P buf);
  
uint8_t dog_DrawChar(uint8_t x, uint8_t y, DOG_PGM_P font, unsigned char code); /* dogmfont.c */
uint8_t dog_DrawRChar(uint8_t x, uint8_t y, uint8_t rot, DOG_PGM_P font, unsigned char code);

uint8_t dog_GetStrWidth(DOG_PGM_P font, const char *s); /* dogmds.c */
uint8_t dog_DrawStr(uint8_t x, uint8_t y, DOG_PGM_P font, const char *s);	/* dogmds.c */
uint8_t dog_DrawRStr(uint8_t x, uint8_t y, uint8_t rot, DOG_PGM_P font, const char *s);

uint8_t dog_GetStrWidthP(DOG_PGM_P font, DOG_PSTR_P s); /* dogmdsp.c */
uint8_t dog_DrawStrP(uint8_t x, uint8_t y, DOG_PGM_P font, DOG_PSTR_P s); /* dogmdsp.c */
uint8_t dog_DrawRStrP(uint8_t x, uint8_t y, uint8_t rot, DOG_PGM_P font, DOG_PSTR_P s);


/* --- math --- */

  /* w: 0..255     64 = PI/2, 128 = PI, 192 = 3*PI/2 */
  /* returns: -64 .. 64 */
signed char dog_sin(uint8_t w);	/* dogmma.c */
signed char dog_cos(uint8_t w);	/* dogmma.c */

/* --- other --- */
char *dog_itoa(unsigned long v);


/* --- breakout --- */

void bo_Setup(uint8_t level);
void bo_Draw(void);
void bo_Step(void);
void bo_SetX(uint8_t pos);

/* --- walk --- */

void walk_Draw(void);
void walk_Step(void);

/* --- spacetrash --- */

void st_Draw(void);
void st_Step(uint8_t player_pos, uint8_t is_auto_fire, uint8_t is_fire);



#ifdef __cplusplus
}
#endif


#endif 

