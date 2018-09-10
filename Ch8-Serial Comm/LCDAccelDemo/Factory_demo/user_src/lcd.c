#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <glyph_api.h>
#include <lcd.h>
#include <ior5f100le.h>

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
    LCDFont(FONT_LARGE);
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

void  LCDTest()
{
	GlyphClearScreen(G_lcd);
	GlyphDrawTestPattern(G_lcd);
}

void  LCDInvert()
{
	GlyphInvertScreen(G_lcd);
}

/* pxmap bit map */
#define TOP_L   0x1
#define TOP_R   0x2
#define BOT_L   0x4
#define BOT_R   0x8

/*
 * Draw the 4px indicator on the graph of volume and frequency. Be sure not to
 * wipe out the axes while drawing.
 */
void LCDDrawIndicator(void)
{
    /*
     * The indicator is a 4px box. Each pixel is represented by a bit in pxmap
     * as described below: 
     *
     * pxmap bits:  0x1 | 0x2      TOP_L | TOP_R
     *              ----|----  ==  ------|------
     *              0x4 | 0x8      BOT_L | BOT_R
    
     * If a bit is high, it means that pixel is overlapped with an axis and
     * should not be erased.
     */
#if 0
    uint8_t pxmap = 0;
	
    /* Left side of the indicator overlaps the y-axis */
    if (G_ind_x == ((LCD_W/2)-4))
        pxmap = TOP_L | BOT_L;
    /* Right side of the indicator overlaps the y-axis */
    else if ((G_ind_x+1) == ((LCD_W/2)-4))
        pxmap = TOP_R | BOT_R;
    
    /* Top of the indicator overlaps the x-axis */
    if (G_ind_y == ((LCD_H/2)-4))
        pxmap |= TOP_L | TOP_R;     /* Use OR to preserve y-axis overlap */
    /* Bottom of the indicator overlaps the x-axis */
    else if ((G_ind_y+1) == ((LCD_H/2)-4))
        pxmap |= BOT_L | BOT_R;     /* Use OR to preserve y-axis overlap */

    /* Erase the part of the indicator that doesn't overlap the axes */
    switch (pxmap) {
    case 0:         /* No overlap, erase the whole indicator */
        GlyphEraseBlock(G_lcd, G_ind_x, G_ind_y, G_ind_x+1, G_ind_y+1);
        break;
    case (1|2):     /* Overlap on top only. Erase bottom only. */
        GlyphEraseBlock(G_lcd, G_ind_x, G_ind_y+1, G_ind_x+1, G_ind_y+1);
        break;
    case (1|4):     /* Overlap on left side only. Erase right side only. */
        GlyphEraseBlock(G_lcd, G_ind_x+1, G_ind_y, G_ind_x+1, G_ind_y+1);
        break;
    case (2|8):     /* Overlap on right side only. Erase left side only. */
        GlyphEraseBlock(G_lcd, G_ind_x, G_ind_y, G_ind_x, G_ind_y+1);
        break;
    case (4|8):     /* Overlap on bottom only. Erase top only. */
        GlyphEraseBlock(G_lcd, G_ind_x, G_ind_y, G_ind_x+1, G_ind_y);
        break;
    case (1|2|4):   /* Overlap top and left. Erase bottom right. */
        GlyphEraseBlock(G_lcd, G_ind_x+1, G_ind_y+1, G_ind_x+1, G_ind_y+1);
        break;
    case (1|2|8):   /* Overlap top and right. Erase bottom left. */
        GlyphEraseBlock(G_lcd, G_ind_x, G_ind_y+1, G_ind_x, G_ind_y+1);
        break;
    case (1|4|8):   /* Overlap bottom and left. Erase top right. */
        GlyphEraseBlock(G_lcd, G_ind_x+1, G_ind_y, G_ind_x+1, G_ind_y);
        break;
    case (2|4|8):   /* Overlap bottom and right. Erase top left. */
        GlyphEraseBlock(G_lcd, G_ind_x, G_ind_y, G_ind_x, G_ind_y);
        break;
    default:        /* Shouldn't get here */
        break;
    }
#endif
		
    /* Draw the indicator's next position */
    GlyphDrawBlock(G_lcd, G_ind_x_next+LCD_W/2, G_ind_y_next+LCD_H/2, 
									 G_ind_x_next+3+LCD_W/2, G_ind_y_next+3+LCD_H/2);
    
    /* Mark the _next coordinates as now being the current ones */
    G_ind_x = G_ind_x_next;
    G_ind_y = G_ind_y_next;
}

void  LCDTest2(void)
{
	while (1) {
		// Red on, green off
		P5_bit.no2 = 0;
		P5_bit.no5 = 1;
		GlyphDrawBlock(G_lcd, 0, 0, LCD_W-1, LCD_H-1);
		// Green on, red off
		P5_bit.no2 = 1;
		P5_bit.no5 = 0;
		GlyphEraseBlock(G_lcd, 0, 0, LCD_W-1, LCD_H-1);
	}
}
