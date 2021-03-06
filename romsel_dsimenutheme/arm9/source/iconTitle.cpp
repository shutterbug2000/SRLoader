/*-----------------------------------------------------------------
 Copyright (C) 2005 - 2013
		Michael "Chishm" Chisholm
		Dave "WinterMute" Murphy
		Claudio "sverx"
		Michael "mtheall" Theall

 This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

------------------------------------------------------------------*/

#include <nds.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/stat.h>
#include <gl2d.h>
#include "graphics/fontHandler.h"

#define ICON_POS_X	112
#define ICON_POS_Y	96

#define BOX_PY 13

// Graphic files
#include "icon_unk.h"
#include "icon_gbc.h"

static int iconTexID[40];
static int gbcTexID;
static tNDSBanner banner;

static glImage icon1[1];
static glImage icon2[1];
static glImage icon3[1];
static glImage icon4[1];
static glImage icon5[1];
static glImage icon6[1];
static glImage icon7[1];
static glImage icon8[1];
static glImage icon9[1];
static glImage icon10[1];
static glImage icon11[1];
static glImage icon12[1];
static glImage icon13[1];
static glImage icon14[1];
static glImage icon15[1];
static glImage icon16[1];
static glImage icon17[1];
static glImage icon18[1];
static glImage icon19[1];
static glImage icon20[1];
static glImage icon21[1];
static glImage icon22[1];
static glImage icon23[1];
static glImage icon24[1];
static glImage icon25[1];
static glImage icon26[1];
static glImage icon27[1];
static glImage icon28[1];
static glImage icon29[1];
static glImage icon30[1];
static glImage icon31[1];
static glImage icon32[1];
static glImage icon33[1];
static glImage icon34[1];
static glImage icon35[1];
static glImage icon36[1];
static glImage icon37[1];
static glImage icon38[1];
static glImage icon39[1];

static glImage gbcIcon[1];

u8 *clearTiles;
u16 *blackPalette;
u8 *tilesModified;

void iconTitleInit()
{
	clearTiles = new u8[(32 * 32) / 2]();
	blackPalette = new u16[16]();
	tilesModified = new u8[(32 * 32) / 2];
}

static inline void writeBannerText(int textlines, const char* text1, const char* text2, const char* text3)
{
	switch(textlines) {
		case 0:
		default:
			printLargeCentered(false, BOX_PY+19, text1);
			break;
		case 1:
			printLargeCentered(false, BOX_PY+9, text1);
			printLargeCentered(false, BOX_PY+28, text2);
			break;
		case 2:
			printLargeCentered(false, BOX_PY, text1);
			printLargeCentered(false, BOX_PY+19, text2);
			printLargeCentered(false, BOX_PY+19*2, text3);
			break;
	}
}

static void convertIconTilesToRaw(u8 *tilesSrc, u8 *tilesNew)
{
	const int PY = 32;
	const int PX = 16;
	const int TILE_SIZE_Y = 8;
	const int TILE_SIZE_X = 4;
	int index = 0;
	for (int tileY = 0; tileY < PY / TILE_SIZE_Y; ++tileY)
	{
		for (int tileX = 0; tileX < PX / TILE_SIZE_X; ++tileX)
			for (int pY = 0; pY < TILE_SIZE_Y; ++pY)
				for (int pX = 0; pX < TILE_SIZE_X; ++pX)//TILE_SIZE/2 since one u8 equals two pixels (4 bit depth)
					tilesNew[pX + tileX * TILE_SIZE_X + PX * (pY + tileY * TILE_SIZE_Y)] = tilesSrc[index++];
	}
}

void loadIcon(u8 *tilesSrc, u16 *palSrc, int num)//(u8(*tilesSrc)[(32 * 32) / 2], u16(*palSrc)[16])
{
	convertIconTilesToRaw(tilesSrc, tilesModified);

	glDeleteTextures(1, &iconTexID[num]);
	switch (num) {
		case 0:
		default:
			iconTexID[num] =
			glLoadTileSet(icon1, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 1:
			iconTexID[num] =
			glLoadTileSet(icon2, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 2:
			iconTexID[num] =
			glLoadTileSet(icon3, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 3:
			iconTexID[num] =
			glLoadTileSet(icon4, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 4:
			iconTexID[num] =
			glLoadTileSet(icon5, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 5:
			iconTexID[num] =
			glLoadTileSet(icon6, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 6:
			iconTexID[num] =
			glLoadTileSet(icon7, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 7:
			iconTexID[num] =
			glLoadTileSet(icon8, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 8:
			iconTexID[num] =
			glLoadTileSet(icon9, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 9:
			iconTexID[num] =
			glLoadTileSet(icon10, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 10:
			iconTexID[num] =
			glLoadTileSet(icon11, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 11:
			iconTexID[num] =
			glLoadTileSet(icon12, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 12:
			iconTexID[num] =
			glLoadTileSet(icon13, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 13:
			iconTexID[num] =
			glLoadTileSet(icon14, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 14:
			iconTexID[num] =
			glLoadTileSet(icon15, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 15:
			iconTexID[num] =
			glLoadTileSet(icon16, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 16:
			iconTexID[num] =
			glLoadTileSet(icon17, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 17:
			iconTexID[num] =
			glLoadTileSet(icon18, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 18:
			iconTexID[num] =
			glLoadTileSet(icon19, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 19:
			iconTexID[num] =
			glLoadTileSet(icon20, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 20:
			iconTexID[num] =
			glLoadTileSet(icon21, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 21:
			iconTexID[num] =
			glLoadTileSet(icon22, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 22:
			iconTexID[num] =
			glLoadTileSet(icon23, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 23:
			iconTexID[num] =
			glLoadTileSet(icon24, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 24:
			iconTexID[num] =
			glLoadTileSet(icon25, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 25:
			iconTexID[num] =
			glLoadTileSet(icon26, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 26:
			iconTexID[num] =
			glLoadTileSet(icon27, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 27:
			iconTexID[num] =
			glLoadTileSet(icon28, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 28:
			iconTexID[num] =
			glLoadTileSet(icon29, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 29:
			iconTexID[num] =
			glLoadTileSet(icon30, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 30:
			iconTexID[num] =
			glLoadTileSet(icon31, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 31:
			iconTexID[num] =
			glLoadTileSet(icon32, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 32:
			iconTexID[num] =
			glLoadTileSet(icon33, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 33:
			iconTexID[num] =
			glLoadTileSet(icon34, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 34:
			iconTexID[num] =
			glLoadTileSet(icon35, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 35:
			iconTexID[num] =
			glLoadTileSet(icon36, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 36:
			iconTexID[num] =
			glLoadTileSet(icon37, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 37:
			iconTexID[num] =
			glLoadTileSet(icon38, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
		case 38:
			iconTexID[num] =
			glLoadTileSet(icon39, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) palSrc, // Image palette
						(u8*) tilesModified // Raw image data
						);
			break;
	}
}

void loadUnkIcon(int num)
{
	glDeleteTextures(1, &iconTexID[num]);
	switch (num) {
		case 0:
		default:
			iconTexID[num] =
			glLoadTileSet(icon1, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 1:
			iconTexID[num] =
			glLoadTileSet(icon2, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 2:
			iconTexID[num] =
			glLoadTileSet(icon3, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 3:
			iconTexID[num] =
			glLoadTileSet(icon4, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 4:
			iconTexID[num] =
			glLoadTileSet(icon5, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 5:
			iconTexID[num] =
			glLoadTileSet(icon6, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 6:
			iconTexID[num] =
			glLoadTileSet(icon7, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 7:
			iconTexID[num] =
			glLoadTileSet(icon8, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 8:
			iconTexID[num] =
			glLoadTileSet(icon9, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 9:
			iconTexID[num] =
			glLoadTileSet(icon10, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 10:
			iconTexID[num] =
			glLoadTileSet(icon11, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 11:
			iconTexID[num] =
			glLoadTileSet(icon12, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 12:
			iconTexID[num] =
			glLoadTileSet(icon13, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 13:
			iconTexID[num] =
			glLoadTileSet(icon14, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 14:
			iconTexID[num] =
			glLoadTileSet(icon15, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 15:
			iconTexID[num] =
			glLoadTileSet(icon16, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 16:
			iconTexID[num] =
			glLoadTileSet(icon17, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 17:
			iconTexID[num] =
			glLoadTileSet(icon18, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 18:
			iconTexID[num] =
			glLoadTileSet(icon19, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 19:
			iconTexID[num] =
			glLoadTileSet(icon20, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 20:
			iconTexID[num] =
			glLoadTileSet(icon21, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 21:
			iconTexID[num] =
			glLoadTileSet(icon22, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 22:
			iconTexID[num] =
			glLoadTileSet(icon23, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 23:
			iconTexID[num] =
			glLoadTileSet(icon24, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 24:
			iconTexID[num] =
			glLoadTileSet(icon25, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 25:
			iconTexID[num] =
			glLoadTileSet(icon26, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 26:
			iconTexID[num] =
			glLoadTileSet(icon27, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 27:
			iconTexID[num] =
			glLoadTileSet(icon28, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 28:
			iconTexID[num] =
			glLoadTileSet(icon29, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 29:
			iconTexID[num] =
			glLoadTileSet(icon30, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 30:
			iconTexID[num] =
			glLoadTileSet(icon31, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 31:
			iconTexID[num] =
			glLoadTileSet(icon32, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 32:
			iconTexID[num] =
			glLoadTileSet(icon33, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 33:
			iconTexID[num] =
			glLoadTileSet(icon34, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 34:
			iconTexID[num] =
			glLoadTileSet(icon35, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 35:
			iconTexID[num] =
			glLoadTileSet(icon36, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 36:
			iconTexID[num] =
			glLoadTileSet(icon37, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 37:
			iconTexID[num] =
			glLoadTileSet(icon38, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
		case 38:
			iconTexID[num] =
			glLoadTileSet(icon39, // pointer to glImage array
						32, // sprite width
						32, // sprite height
						32, // bitmap image width
						32, // bitmap image height
						GL_RGB16, // texture type for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
						TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
						GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
						16, // Length of the palette to use (16 colors)
						(u16*) icon_unkPal, // Image palette
						(u8*) icon_unkBitmap // Raw image data
						);
			break;
	}
}

void loadGBCIcon()
{
	glDeleteTextures(1, &gbcTexID);
	
	gbcTexID =
	glLoadTileSet(gbcIcon, // pointer to glImage array
				32, // sprite width
				32, // sprite height
				32, // bitmap image width
				32, // bitmap image height
				GL_RGB16, // texture type for glTexImage2D() in videoGL.h
				TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
				TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
				GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT,
				16, // Length of the palette to use (16 colors)
				(u16*) icon_gbcPal, // Image palette
				(u8*) icon_gbcBitmap // Raw image data
				);
}

static void clearIcon(int num)
{
	loadIcon(clearTiles, blackPalette, num);
}

void drawIcon(int Xpos, int Ypos, int num)
{
	switch (num) {
		case 0:
		default:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon1);
			break;
		case 1:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon2);
			break;
		case 2:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon3);
			break;
		case 3:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon4);
			break;
		case 4:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon5);
			break;
		case 5:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon6);
			break;
		case 6:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon7);
			break;
		case 7:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon8);
			break;
		case 8:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon9);
			break;
		case 9:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon10);
			break;
		case 10:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon11);
			break;
		case 11:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon12);
			break;
		case 12:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon13);
			break;
		case 13:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon14);
			break;
		case 14:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon15);
			break;
		case 15:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon16);
			break;
		case 16:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon17);
			break;
		case 17:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon18);
			break;
		case 18:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon19);
			break;
		case 19:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon20);
			break;
		case 20:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon21);
			break;
		case 21:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon22);
			break;
		case 22:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon23);
			break;
		case 23:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon24);
			break;
		case 24:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon25);
			break;
		case 25:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon26);
			break;
		case 26:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon27);
			break;
		case 27:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon28);
			break;
		case 28:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon29);
			break;
		case 29:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon30);
			break;
		case 30:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon31);
			break;
		case 31:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon32);
			break;
		case 32:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon33);
			break;
		case 33:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon34);
			break;
		case 34:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon35);
			break;
		case 35:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon36);
			break;
		case 36:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon37);
			break;
		case 37:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon38);
			break;
		case 38:
			glSprite(Xpos, Ypos, GL_FLIP_NONE, icon39);
			break;
	}
}

void drawIconGBC(int Xpos, int Ypos)
{
	glSprite(Xpos, Ypos, GL_FLIP_NONE, gbcIcon);
}

void iconUpdate(bool isDir, const char* name, int num)
{
	clearText(false);

	if (isDir)
	{
		// icon
		clearIcon(num);
	}
	else if (strlen(name) >= 5 && strcasecmp(name + strlen(name) - 5, ".argv") == 0)
	{
		// look through the argv file for the corresponding nds file
		FILE *fp;
		char *line = NULL, *p = NULL;
		// size_t size = 0;
		ssize_t rc;

		// open the argv file
		fp = fopen(name, "rb");
		if (fp == NULL)
		{
			clearIcon(num);
			fclose(fp);
			return;
		}

		// done with the file at this point
		fclose(fp);

		if (p && *p)
		{
			// we found an argument
			struct stat st;

			// truncate everything after first argument
			strtok(p, "\n\r\t ");

			if (strlen(p) < 4 || strcasecmp(p + strlen(p) - 4, ".nds") != 0)
			{
				// this is not an nds file!
				clearIcon(num);
			}
			else
			{
				// let's see if this is a file or directory
				rc = stat(p, &st);
				if (rc != 0)
				{
					// stat failed
					clearIcon(num);
				}
				else if (S_ISDIR(st.st_mode))
				{
					// this is a directory!
					clearIcon(num);
				}
				else
				{
					iconUpdate(false, p, num);
				}
			}
		}
		else
		{
			clearIcon(num);
		}
		// clean up the allocated line
		free(line);
	}
	else
	{
		// this is an nds file!
		FILE *fp;
		unsigned int iconTitleOffset;
		int ret;

		// open file for reading info
		fp = fopen(name, "rb");
		if (fp == NULL)
		{
			// icon
			clearIcon(num);
			fclose(fp);
			return;
		}

		ret = fseek(fp, offsetof(tNDSHeader, bannerOffset), SEEK_SET);
		if (ret == 0)
			ret = fread(&iconTitleOffset, sizeof (int), 1, fp); // read if seek succeed
		else
			ret = 0; // if seek fails set to !=1

		if (ret != 1)
		{
			// icon
			loadUnkIcon(num);
			fclose(fp);
			return;
		}

		if (iconTitleOffset == 0)
		{
			// icon
			loadUnkIcon(num);
			fclose(fp);
			return;
		}
		ret = fseek(fp, iconTitleOffset, SEEK_SET);
		if (ret == 0)
			ret = fread(&banner, sizeof (banner), 1, fp); // read if seek succeed
		else
			ret = 0; // if seek fails set to !=1

		if (ret != 1)
		{
			// icon
			loadUnkIcon(num);
			fclose(fp);
			return;
		}

		// close file!
		fclose(fp);

		// icon
		DC_FlushAll();
		loadIcon(banner.icon, banner.palette, num);
	}
}

void titleUpdate(bool isDir, const char* name)
{
	clearText(false);

	if (isDir)
	{
		// text
		writeBannerText(1, name, "[directory]", "");
	}
	else if (strcasecmp(name + strlen(name) - 3, ".gb") == 0 ||
				strcasecmp (name + strlen(name) - 4, ".sgb") == 0 ||
				strcasecmp (name + strlen(name) - 4, ".gbc") == 0 )
	{
		writeBannerText(0, name, "", "");
	}
	else if (strlen(name) >= 5 && strcasecmp(name + strlen(name) - 5, ".argv") == 0)
	{
		// look through the argv file for the corresponding nds file
		FILE *fp;
		char *line = NULL, *p = NULL;
		size_t size = 0;
		ssize_t rc;

		// open the argv file
		fp = fopen(name, "rb");
		if (fp == NULL)
		{
			writeBannerText(0, "(can't open file!)", "", "");
			fclose(fp);
			return;
		}

		// read each line
		while ((rc = __getline(&line, &size, fp)) > 0)
		{
			// remove comments
			if ((p = strchr(line, '#')) != NULL)
				*p = 0;

			// skip leading whitespace
			for (p = line; *p && isspace((int) *p); ++p)
				;

			if (*p)
				break;
		}

		// done with the file at this point
		fclose(fp);

		if (p && *p)
		{
			// we found an argument
			struct stat st;

			// truncate everything after first argument
			strtok(p, "\n\r\t ");

			if (strlen(p) < 4 || strcasecmp(p + strlen(p) - 4, ".nds") != 0)
			{
				// this is not an nds file!
				writeBannerText(0, "(invalid argv file!)", "", "");
			}
			else
			{
				// let's see if this is a file or directory
				rc = stat(p, &st);
				if (rc != 0)
				{
					// stat failed
					writeBannerText(0, "(can't find argument!)", "", "");
				}
				else if (S_ISDIR(st.st_mode))
				{
					// this is a directory!
					writeBannerText(0, "(invalid argv file!)", "", "");
				}
				else
				{
					titleUpdate(false, p);
				}
			}
		}
		else
		{
			writeBannerText(0, "(no argument!)", "", "");
		}
		// clean up the allocated line
		free(line);
	}
	else
	{
		// this is an nds file!
		FILE *fp;
		unsigned int iconTitleOffset;
		int ret;

		// open file for reading info
		fp = fopen(name, "rb");
		if (fp == NULL)
		{
			// text
			writeBannerText(0, "(can't open file!)", "", "");
			fclose(fp);
			return;
		}

		ret = fseek(fp, offsetof(tNDSHeader, bannerOffset), SEEK_SET);
		if (ret == 0)
			ret = fread(&iconTitleOffset, sizeof (int), 1, fp); // read if seek succeed
		else
			ret = 0; // if seek fails set to !=1

		if (ret != 1)
		{
			// text
			writeBannerText(0, "(can't read file!)", "", "");
			fclose(fp);
			return;
		}

		if (iconTitleOffset == 0)
		{
			// text
			writeBannerText(1, name, "(no title/icon)", "");
			fclose(fp);
			return;
		}
		ret = fseek(fp, iconTitleOffset, SEEK_SET);
		if (ret == 0)
			ret = fread(&banner, sizeof (banner), 1, fp); // read if seek succeed
		else
			ret = 0; // if seek fails set to !=1

		if (ret != 1)
		{
			// text
			writeBannerText(0, "(can't read icon/title!)", "", "");
			fclose(fp);
			return;
		}

		// close file!
		fclose(fp);

		// turn unicode into ascii (kind of)
		// and convert 0x0A into 0x00
		char *p = (char*) banner.titles[PersonalData->language];
		int bannerlines = 0;
		for (unsigned int i = 0; i < sizeof (banner.titles[PersonalData->language]); i += 2)
		{
			if ((p[i] == 0x0A) || (p[i] == 0xFF)) {
				p[i / 2] = 0;
				bannerlines += 1;
			} else
				p[i / 2] = p[i];
		}

		// text
		switch(bannerlines) {
			case 0:
			default:
				printLargeCentered(false, BOX_PY+19, p);
				break;
			case 1:
				printLargeCentered(false, BOX_PY+9, p);
				p += strlen(p) + 1;
				printLargeCentered(false, BOX_PY+28, p);
				break;
			case 2:
				printLargeCentered(false, BOX_PY, p);
				p += strlen(p) + 1;
				printLargeCentered(false, BOX_PY+19, p);
				p += strlen(p) + 1;
				printLargeCentered(false, BOX_PY+19*2, p);
				break;
		}
		
	}
}
