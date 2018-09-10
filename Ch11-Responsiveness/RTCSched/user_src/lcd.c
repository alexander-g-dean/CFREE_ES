//#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include "glyph_api.h"
#include "ST7579_LCD.h"
#include "lcd.h"
#include "ior5f100le.h"
#include "r_cg_userdefine.h"

/*-------------------------------------------------------------------------*
 * Globals
 *-------------------------------------------------------------------------*/
static  T_glyphHandle  G_lcd;
uint8_t G_CharWidth = 5u;
uint8_t G_CharHeight = 7u;
int32_t G_ind_x   = LCD_W/2;
int32_t G_ind_y   = (LCD_H/2)-4;
int32_t G_ind_x_next = LCD_W/2;;
int32_t G_ind_y_next = (LCD_H/2)-4;

uint8_t LCDCenter(uint8_t aStrLen)
{
	return (LCD_W-G_CharWidth*aStrLen)/2;
}
uint8_t LCDRight(uint8_t aStrLen)
{
	return LCD_W - G_CharWidth * aStrLen;
}

void LCDInit (void)
{
    T_glyphError  err;
    
    err = GlyphOpen(&G_lcd, 0);

    if (err == GLYPH_ERROR_NONE) {
        GlyphNormalScreen(G_lcd);
        GlyphClearScreen(G_lcd);
    }
}


void LCDClear (void)
{   
    GlyphClearScreen(G_lcd);   
}


void LCDFont (LCDFONT font)
{
    
    switch (font) {
    case FONT_LOGOS:
       GlyphSetFont(G_lcd, GLYPH_FONT_LOGOS);
			 G_CharWidth = 16u;
			 G_CharHeight = 16u;
       break;

    case FONT_LARGE:
       GlyphSetFont(G_lcd, GLYPH_FONT_8_BY_8);
			 G_CharWidth = 8u;
			 G_CharHeight = 8u;
       break;

    case FONT_SMALL:
       GlyphSetFont(G_lcd, GLYPH_FONT_5_BY_7);
			 G_CharWidth = 5u;
			 G_CharHeight = 7u;
       break;
    }
}


void LCDClearLine (uint8_t aLine)
{
    uint8_t y = aLine * G_CharHeight;

    GlyphEraseBlock(G_lcd, 0u, y, 95u, y + 7u);
}

void LCDString (const char *aStr, uint8_t aX, uint8_t aY)
{
    GlyphSetXY (G_lcd, aX, aY);
    GlyphString(G_lcd, (uint8_t *)aStr, strlen(aStr));
}

void LCDStringLine (const char *aStr, uint8_t aX, uint8_t aLine)
{
		uint8_t y = aLine * G_CharHeight;
    LCDString(aStr, aX, y);
}

void LCDStringPos (const char *aStr, uint8_t aPos, uint8_t aY)
{
    uint8_t  x = aPos  * G_CharWidth;
    LCDString(aStr, x, aY);
}

void LCDStringLinePos (const char *aStr, uint8_t aPos, uint8_t aLine)
{
    uint8_t  x = aPos  * G_CharWidth;
    LCDStringLine(aStr, x, aLine);
}

/*void LCDStringAlign(const char *aStr, T_LCD_ALIGN aAlign, uint8_t aY)
{
	uint8_t x;
	switch(aAlign)
	{
		case LEFT:
			x = 0;
		break;
		case RIGHT:
			x = LCD_W - strlen(aStr)*G_CharWidth;
		break;
		case CENTER:
			x = LCD_W/2 - strlen(aStr)*G_CharWidth/2;
		break;
		default:
		break;
	}
	
	LCDString(aStr, x, aY);
}*/

void LCDChar(char aChar, uint8_t aX, uint8_t aLine)
{
    uint8_t  y = aLine * G_CharHeight;
	
		GlyphSetXY (G_lcd, aX, y);
    GlyphChar(G_lcd, (uint32_t)aChar);  
}

void LCDCharPos(char aChar, uint8_t aPos, uint8_t aLine)
{
    uint8_t  x;
    uint8_t  y;

    x = aPos  * G_CharWidth;
    y = aLine * G_CharHeight;
	
		GlyphSetXY (G_lcd, x, y);
    GlyphChar(G_lcd, (uint32_t)aChar);  
}

void  LCDPrintf(uint8_t aLine, uint8_t aPos, char *aFormat, ...)
{
    uint8_t  y;
    char buffer[100];
    va_list marker;
    
		y = aLine * G_CharHeight;
	
    // Convert to a string for output
    va_start(marker, aFormat);
    vsprintf(buffer, aFormat, marker);
    va_end(marker);
    
    LCDStringPos(buffer, aPos, y);
}

void  LCDInvert()
{
	GlyphInvertScreen(G_lcd);
}

