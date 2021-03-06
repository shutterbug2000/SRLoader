/*-----------------------------------------------------------------
 Copyright (C) 2015
	Matthew Scholefield

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
#include <maxmod9.h>
#include <gl2d.h>
#include "FontGraphic.h"

// Graphic files
#include "top.h"
#include "bottom.h"
#include "shoulder.h"
#include "nintendo_dsi_menu.h"
#include "bubble.h"
#include "bubble_arrow.h"
#include "bips.h"
#include "scroll_window.h"
#include "scroll_windowfront.h"
#include "button_arrow.h"
#include "start_text.h"
#include "start_border.h"
#include "brace.h"
#include "box_full.h"
#include "box_empty.h"

// Built-in icons
#include "icon_gbc.h"

#include "../iconTitle.h"
#include "graphics.h"
#include "fontHandler.h"

extern bool renderScreens;
extern bool whiteScreen;

extern int colorRvalue;
extern int colorGvalue;
extern int colorBvalue;

extern bool showbubble;
extern bool showSTARTborder;

extern bool titleboxXmoveleft;
extern bool titleboxXmoveright;

extern bool applaunchprep;

extern int romtype;

int movetimer = 0;

int titleboxYmovepos = 0;

extern int spawnedtitleboxes;
extern int cursorPosition;
int titleboxXpos;
int titlewindowXpos;

bool renderingTop = true;
int subBgTexID, mainBgTexID, shoulderTexID, ndsimenutextTexID, bubbleTexID, bubblearrowTexID;
int bipsTexID, scrollwindowTexID, scrollwindowfrontTexID, buttonarrowTexID, startTexID, startbrdTexID, braceTexID, boxfullTexID, boxemptyTexID;

glImage subBgImage[(256 / 16) * (256 / 16)];
glImage mainBgImage[(256 / 16) * (256 / 16)];
glImage shoulderImage[(128 / 16) * (64 / 32)];
glImage ndsimenutextImage[(256 / 16) * (32 / 16)];
glImage bubbleImage[(256 / 16) * (128 / 16)];
glImage bubblearrowImage[(16 / 16) * (16 / 16)];
glImage bipsImage[(8 / 8) * (32 / 8)];
glImage scrollwindowImage[(32 / 16) * (32 / 16)];
glImage scrollwindowfrontImage[(32 / 16) * (32 / 16)];
glImage buttonarrowImage[(32 / 16) * (32 / 16)];
glImage startImage[(64 / 16) * (8 / 16)];
glImage startbrdImage[(32 / 16) * (128 / 16)];
glImage braceImage[(16 / 16) * (128 / 16)];
glImage boxfullImage[(64 / 16) * (64 / 16)];
glImage boxemptyImage[(64 / 16) * (64 / 16)];

extern mm_sound_effect snd_stop;

//-------------------------------------------------------
// set up a 2D layer construced of bitmap sprites
// this holds the image when rendering to the top screen
//-------------------------------------------------------

void initSubSprites(void)
{

	oamInit(&oamSub, SpriteMapping_Bmp_2D_256, false);
	int id = 0;

	//set up a 4x3 grid of 64x64 sprites to cover the screen
	for (int y = 0; y < 3; y++)
		for (int x = 0; x < 4; x++)
		{
			oamSub.oamMemory[id].attribute[0] = ATTR0_BMP | ATTR0_SQUARE | (64 * y);
			oamSub.oamMemory[id].attribute[1] = ATTR1_SIZE_64 | (64 * x);
			oamSub.oamMemory[id].attribute[2] = ATTR2_ALPHA(1) | (8 * 32 * y) | (8 * x);
			++id;
		}

	swiWaitForVBlank();

	oamUpdate(&oamSub);
}

void drawBG(glImage *images)
{
	for (int y = 0; y < 256 / 16; y++)
	{
		for (int x = 0; x < 256 / 16; x++)
		{
			int i = y * 16 + x;
			glSprite(x * 16, y * 16, GL_FLIP_NONE, &images[i & 255]);
		}
	}
}
void drawBubble(glImage *images)
{
	for (int y = 0; y < 128 / 16; y++)
	{
		for (int x = 0; x < 256 / 16; x++)
		{
			int i = y * 16 + x;
			glSprite(x * 16, y * 16, GL_FLIP_NONE, &images[i & 255]);
		}
	}
}

void startRendering(bool top)
{
	if (top)
	{
		lcdMainOnBottom();
		vramSetBankC(VRAM_C_LCD);
		vramSetBankD(VRAM_D_SUB_SPRITE);
		REG_DISPCAPCNT = DCAP_BANK(2) | DCAP_ENABLE | DCAP_SIZE(3);
	}
	else
	{
		lcdMainOnTop();
		vramSetBankD(VRAM_D_LCD);
		vramSetBankC(VRAM_C_SUB_BG);
		REG_DISPCAPCNT = DCAP_BANK(3) | DCAP_ENABLE | DCAP_SIZE(3);
	}
}

bool isRenderingTop()
{
	return renderingTop;
}

void vBlankHandler()
{
	if (renderScreens) {
		startRendering(renderingTop);
		glBegin2D();
		{
			if (renderingTop)
			{
				glBoxFilledGradient(0, -64, 256, 112,
							  RGB15(colorRvalue,colorGvalue,colorBvalue), RGB15(0,0,0), RGB15(0,0,0), RGB15(colorRvalue,colorGvalue,colorBvalue)
							);
				glBoxFilledGradient(0, 112, 256, 192,
							  RGB15(0,0,0), RGB15(colorRvalue,colorGvalue,colorBvalue), RGB15(colorRvalue,colorGvalue,colorBvalue), RGB15(0,0,0)
							);
				drawBG(mainBgImage);
				glSprite(-2, 172, GL_FLIP_NONE, &shoulderImage[0 & 31]);
				glSprite(178, 172, GL_FLIP_NONE, &shoulderImage[1 & 31]);
				if (whiteScreen) glBoxFilled(0, 0, 256, 192, RGB15(31, 31, 31));
				updateText(renderingTop);
				glColor(RGB15(31, 31, 31));
			}
			else
			{
				drawBG(subBgImage);
				if (showbubble) drawBubble(bubbleImage);
				else glSprite(0, 32, GL_FLIP_NONE, ndsimenutextImage);
				glColor(RGB15(colorRvalue, colorGvalue, colorBvalue));
				glSprite(0, 171, GL_FLIP_NONE, buttonarrowImage);
				glSprite(224, 171, GL_FLIP_H, buttonarrowImage);
				
				if (titleboxXmoveleft) {
					if (movetimer == 4) {
						if (showbubble) mmEffectEx(&snd_stop);
						titlewindowXpos -= 1;
						movetimer++;
					} else if (movetimer < 4) {
						titleboxXpos -= 16;
						titlewindowXpos -= 1;
						movetimer++;
					} else {
						titleboxXmoveleft = false;
						movetimer = 0;
					}
				} else if (titleboxXmoveright) {
					if (movetimer == 4) {
						if (showbubble) mmEffectEx(&snd_stop);
						titlewindowXpos += 1;
						movetimer++;
					} else if (movetimer < 4) {
						titleboxXpos += 16;
						titlewindowXpos += 1;
						movetimer++;
					} else {
						titleboxXmoveright = false;
						movetimer = 0;
					}
				}
				
				glColor(RGB15(31, 31, 31));
				glSprite(19+titlewindowXpos, 171, GL_FLIP_NONE, scrollwindowImage);
				int bipXpos = 30;
				for(int i = 0; i < 39; i++) {
					if (i < spawnedtitleboxes) glSprite(bipXpos, 178, GL_FLIP_NONE, bipsImage);
					else glSprite(bipXpos, 178, GL_FLIP_NONE, &bipsImage[1 & 31]);
					bipXpos += 5;
				}
				glColor(RGB15(colorRvalue, colorGvalue, colorBvalue));
				glSprite(19+titlewindowXpos, 171, GL_FLIP_NONE, scrollwindowfrontImage);
				glColor(RGB15(31, 31, 31));
				glSprite(72-titleboxXpos, 80, GL_FLIP_NONE, braceImage);
				int spawnedboxXpos = 96;
				int iconXpos = 112;
				for(int i = 0; i < 39; i++) {
					if (i < spawnedtitleboxes) {
						glSprite(spawnedboxXpos-titleboxXpos, 84, GL_FLIP_NONE, boxfullImage);
						if (romtype == 1) drawIconGBC(iconXpos-titleboxXpos, 96);
						else drawIcon(iconXpos-titleboxXpos, 96, i);
					} else
						glSprite(spawnedboxXpos-titleboxXpos, 84, GL_FLIP_NONE, boxemptyImage);
					spawnedboxXpos += 64;
					iconXpos += 64;
				}
				if (applaunchprep) {
					// Cover selected app
					for (int y = 0; y < 4; y++)
					{
						for (int x = 0; x < 4; x++)
						{
							glSprite(96+x*16, 84+y*16, GL_FLIP_NONE, &subBgImage[2 & 255]);
						}
					}
					glSprite(96, 84-titleboxYmovepos, GL_FLIP_NONE, boxfullImage);
					if (romtype == 1) drawIconGBC(112, 96-titleboxYmovepos);
					else drawIcon(112, 96-titleboxYmovepos, cursorPosition);
					titleboxYmovepos += 6;
					if (titleboxYmovepos > 192) whiteScreen = true;
				}
				glSprite(spawnedboxXpos+10-titleboxXpos, 80, GL_FLIP_H, braceImage);
				if (showSTARTborder) {
					glColor(RGB15(colorRvalue, colorGvalue, colorBvalue));
					glSprite(96, 80, GL_FLIP_NONE, startbrdImage);
					glSprite(96+32, 80, GL_FLIP_H, startbrdImage);
					glColor(RGB15(31, 31, 31));
				}
				if (showbubble) glSprite(120, 72, GL_FLIP_NONE, bubblearrowImage);	// Make the bubble look like it's over the START border
				if (showSTARTborder) glSprite(95, 144, GL_FLIP_NONE, startImage);
				if (whiteScreen) glBoxFilled(0, 0, 256, 192, RGB15(31, 31, 31));
				updateText(renderingTop);
				glColor(RGB15(31, 31, 31));
			}
		}
		glEnd2D();
		GFX_FLUSH = 0;
		renderingTop = !renderingTop;
	}
}

void graphicsInit()
{
	titleboxXpos = cursorPosition*64;
	titlewindowXpos = cursorPosition*5;

	irqSet(IRQ_VBLANK, vBlankHandler);
	irqEnable(IRQ_VBLANK);
	////////////////////////////////////////////////////////////
	videoSetMode(MODE_5_3D);
	videoSetModeSub(MODE_5_2D);

	// Initialize OAM to capture 3D scene
	initSubSprites();

	// The sub background holds the top image when 3D directed to bottom
	bgInitSub(3, BgType_Bmp16, BgSize_B16_256x256, 0, 0);

	// Initialize GL in 3D mode
	glScreen2D();

	// Set up enough texture memory for our textures
	// Bank A is just 128kb and we are using 194 kb of
	// sprites
	// vramSetBankA(VRAM_A_TEXTURE);
	vramSetBankB(VRAM_B_TEXTURE);
	vramSetBankF(VRAM_F_TEX_PALETTE); // Allocate VRAM bank for all the palettes
	vramSetBankE(VRAM_E_MAIN_BG);
	
	subBgTexID = glLoadTileSet(subBgImage, // pointer to glImage array
							16, // sprite width
							16, // sprite height
							256, // bitmap width
							256, // bitmap height
							GL_RGB16, // texture type for glTexImage2D() in videoGL.h
							TEXTURE_SIZE_256, // sizeX for glTexImage2D() in videoGL.h
							TEXTURE_SIZE_256, // sizeY for glTexImage2D() in videoGL.h
							GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT, // param for glTexImage2D() in videoGL.h
							16, // Length of the palette to use (16 colors)
							(u16*) bottomPal, // Load our 16 color tiles palette
							(u8*) bottomBitmap // image data generated by GRIT
							);

	ndsimenutextTexID = glLoadTileSet(ndsimenutextImage, // pointer to glImage array
							256, // sprite width
							32, // sprite height
							256, // bitmap width
							32, // bitmap height
							GL_RGB16, // texture type for glTexImage2D() in videoGL.h
							TEXTURE_SIZE_256, // sizeX for glTexImage2D() in videoGL.h
							TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
							GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT, // param for glTexImage2D() in videoGL.h
							16, // Length of the palette to use (16 colors)
							(u16*) nintendo_dsi_menuPal, // Load our 16 color tiles palette
							(u8*) nintendo_dsi_menuBitmap // image data generated by GRIT
							);

	bubbleTexID = glLoadTileSet(bubbleImage, // pointer to glImage array
							16, // sprite width
							16, // sprite height
							256, // bitmap width
							128, // bitmap height
							GL_RGB16, // texture type for glTexImage2D() in videoGL.h
							TEXTURE_SIZE_256, // sizeX for glTexImage2D() in videoGL.h
							TEXTURE_SIZE_128, // sizeY for glTexImage2D() in videoGL.h
							GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT, // param for glTexImage2D() in videoGL.h
							16, // Length of the palette to use (16 colors)
							(u16*) bubblePal, // Load our 16 color tiles palette
							(u8*) bubbleBitmap // image data generated by GRIT
							);

	bubblearrowTexID = glLoadTileSet(bubblearrowImage, // pointer to glImage array
							16, // sprite width
							16, // sprite height
							16, // bitmap width
							16, // bitmap height
							GL_RGB16, // texture type for glTexImage2D() in videoGL.h
							TEXTURE_SIZE_16, // sizeX for glTexImage2D() in videoGL.h
							TEXTURE_SIZE_16, // sizeY for glTexImage2D() in videoGL.h
							GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT, // param for glTexImage2D() in videoGL.h
							16, // Length of the palette to use (16 colors)
							(u16*) bubble_arrowPal, // Load our 16 color tiles palette
							(u8*) bubble_arrowBitmap // image data generated by GRIT
							);

	bipsTexID = glLoadTileSet(bipsImage, // pointer to glImage array
							8, // sprite width
							8, // sprite height
							8, // bitmap width
							32, // bitmap height
							GL_RGB16, // texture type for glTexImage2D() in videoGL.h
							TEXTURE_SIZE_8, // sizeX for glTexImage2D() in videoGL.h
							TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
							GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT, // param for glTexImage2D() in videoGL.h
							16, // Length of the palette to use (16 colors)
							(u16*) bipsPal, // Load our 16 color tiles palette
							(u8*) bipsBitmap // image data generated by GRIT
							);

	scrollwindowTexID = glLoadTileSet(scrollwindowImage, // pointer to glImage array
							32, // sprite width
							32, // sprite height
							32, // bitmap width
							32, // bitmap height
							GL_RGB16, // texture type for glTexImage2D() in videoGL.h
							TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
							TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
							GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT, // param for glTexImage2D() in videoGL.h
							16, // Length of the palette to use (16 colors)
							(u16*) scroll_windowPal, // Load our 16 color tiles palette
							(u8*) scroll_windowBitmap // image data generated by GRIT
							);

	scrollwindowfrontTexID = glLoadTileSet(scrollwindowfrontImage, // pointer to glImage array
							32, // sprite width
							32, // sprite height
							32, // bitmap width
							32, // bitmap height
							GL_RGB16, // texture type for glTexImage2D() in videoGL.h
							TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
							TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
							GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT, // param for glTexImage2D() in videoGL.h
							16, // Length of the palette to use (16 colors)
							(u16*) scroll_windowfrontPal, // Load our 16 color tiles palette
							(u8*) scroll_windowfrontBitmap // image data generated by GRIT
							);

	buttonarrowTexID = glLoadTileSet(buttonarrowImage, // pointer to glImage array
							32, // sprite width
							32, // sprite height
							32, // bitmap width
							32, // bitmap height
							GL_RGB16, // texture type for glTexImage2D() in videoGL.h
							TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
							TEXTURE_SIZE_32, // sizeY for glTexImage2D() in videoGL.h
							GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT, // param for glTexImage2D() in videoGL.h
							16, // Length of the palette to use (16 colors)
							(u16*) button_arrowPal, // Load our 16 color tiles palette
							(u8*) button_arrowBitmap // image data generated by GRIT
							);

	startTexID = glLoadTileSet(startImage, // pointer to glImage array
							64, // sprite width
							8, // sprite height
							64, // bitmap width
							8, // bitmap height
							GL_RGB16, // texture type for glTexImage2D() in videoGL.h
							TEXTURE_SIZE_64, // sizeX for glTexImage2D() in videoGL.h
							TEXTURE_SIZE_8, // sizeY for glTexImage2D() in videoGL.h
							GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT, // param for glTexImage2D() in videoGL.h
							16, // Length of the palette to use (16 colors)
							(u16*) start_textPal, // Load our 16 color tiles palette
							(u8*) start_textBitmap // image data generated by GRIT
							);

	startbrdTexID = glLoadTileSet(startbrdImage, // pointer to glImage array
							32, // sprite width
							128, // sprite height
							32, // bitmap width
							128, // bitmap height
							GL_RGB16, // texture type for glTexImage2D() in videoGL.h
							TEXTURE_SIZE_32, // sizeX for glTexImage2D() in videoGL.h
							TEXTURE_SIZE_128, // sizeY for glTexImage2D() in videoGL.h
							GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT, // param for glTexImage2D() in videoGL.h
							16, // Length of the palette to use (16 colors)
							(u16*) start_borderPal, // Load our 16 color tiles palette
							(u8*) start_borderBitmap // image data generated by GRIT
							);

	braceTexID = glLoadTileSet(braceImage, // pointer to glImage array
							16, // sprite width
							128, // sprite height
							16, // bitmap width
							128, // bitmap height
							GL_RGB16, // texture type for glTexImage2D() in videoGL.h
							TEXTURE_SIZE_16, // sizeX for glTexImage2D() in videoGL.h
							TEXTURE_SIZE_128, // sizeY for glTexImage2D() in videoGL.h
							GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT, // param for glTexImage2D() in videoGL.h
							16, // Length of the palette to use (16 colors)
							(u16*) bracePal, // Load our 16 color tiles palette
							(u8*) braceBitmap // image data generated by GRIT
							);

	boxfullTexID = glLoadTileSet(boxfullImage, // pointer to glImage array
							64, // sprite width
							64, // sprite height
							64, // bitmap width
							64, // bitmap height
							GL_RGB16, // texture type for glTexImage2D() in videoGL.h
							TEXTURE_SIZE_64, // sizeX for glTexImage2D() in videoGL.h
							TEXTURE_SIZE_64, // sizeY for glTexImage2D() in videoGL.h
							GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT, // param for glTexImage2D() in videoGL.h
							16, // Length of the palette to use (16 colors)
							(u16*) box_fullPal, // Load our 16 color tiles palette
							(u8*) box_fullBitmap // image data generated by GRIT
							);

	boxemptyTexID = glLoadTileSet(boxemptyImage, // pointer to glImage array
							64, // sprite width
							64, // sprite height
							64, // bitmap width
							64, // bitmap height
							GL_RGB16, // texture type for glTexImage2D() in videoGL.h
							TEXTURE_SIZE_64, // sizeX for glTexImage2D() in videoGL.h
							TEXTURE_SIZE_64, // sizeY for glTexImage2D() in videoGL.h
							GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT, // param for glTexImage2D() in videoGL.h
							16, // Length of the palette to use (16 colors)
							(u16*) box_emptyPal, // Load our 16 color tiles palette
							(u8*) box_emptyBitmap // image data generated by GRIT
							);
							
	loadGBCIcon();

	mainBgTexID = glLoadTileSet(mainBgImage, // pointer to glImage array
								16, // sprite width
								16, // sprite height
								256, // bitmap width
								256, // bitmap height
								GL_RGB16, // texture type for glTexImage2D() in videoGL.h
								TEXTURE_SIZE_256, // sizeX for glTexImage2D() in videoGL.h
								TEXTURE_SIZE_256, // sizeY for glTexImage2D() in videoGL.h
								GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT, // param for glTexImage2D() in videoGL.h
								16, // Length of the palette to use (16 colors)
								(u16*) topPal, // Load our 16 color tiles palette
								(u8*) topBitmap // image data generated by GRIT
								);

	shoulderTexID = glLoadTileSet(shoulderImage, // pointer to glImage array
								128, // sprite width
								32, // sprite height
								128, // bitmap width
								64, // bitmap height
								GL_RGB16, // texture type for glTexImage2D() in videoGL.h
								TEXTURE_SIZE_128, // sizeX for glTexImage2D() in videoGL.h
								TEXTURE_SIZE_64, // sizeY for glTexImage2D() in videoGL.h
								GL_TEXTURE_WRAP_S | GL_TEXTURE_WRAP_T | TEXGEN_OFF | GL_TEXTURE_COLOR0_TRANSPARENT, // param for glTexImage2D() in videoGL.h
								16, // Length of the palette to use (16 colors)
								(u16*) shoulderPal, // Load our 16 color tiles palette
								(u8*) shoulderBitmap // image data generated by GRIT
								);

}