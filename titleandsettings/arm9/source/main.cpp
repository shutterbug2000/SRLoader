/*-----------------------------------------------------------------
 Copyright (C) 2005 - 2013
	Michael "Chishm" Chisholm
	Dave "WinterMute" Murphy
	Claudio "sverx"

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
#include <fat.h>
#include <sys/stat.h>
#include <limits.h>

#include <string.h>
#include <unistd.h>
#include <gl2d.h>

#include "graphics/graphics.h"

#include "ndsLoaderArm9.h"

#include "graphics/fontHandler.h"

#include "inifile.h"

bool renderScreens = true;

const char* settingsinipath = "sd:/_nds/srloader/settings.ini";
const char* bootstrapinipath = "sd:/_nds/nds-bootstrap.ini";

bool showlogo = true;
bool gotosettings = false;

std::string arm7DonorPath;

bool autorun = false;
int theme = 0;

bool bstrap_boostcpu = false;
bool bstrap_boostvram = false;
bool bstrap_debug = false;
bool bstrap_lockARM9scfgext = false;

void LoadSettings(void) {
	// GUI
	CIniFile settingsini( settingsinipath );

	autorun = settingsini.GetInt("SRLOADER", "AUTORUNGAME", 0);
	showlogo = settingsini.GetInt("SRLOADER", "SHOWLOGO", 1);
	gotosettings = settingsini.GetInt("SRLOADER", "GOTOSETTINGS", 0);

	// Customizable UI settings.
	theme = settingsini.GetInt("SRLOADER", "THEME", 0);

	// nds-bootstrap
	CIniFile bootstrapini( bootstrapinipath );

	arm7DonorPath = bootstrapini.GetString( "NDS-BOOTSTRAP", "ARM7_DONOR_PATH", "");
	bstrap_boostcpu = bootstrapini.GetInt("NDS-BOOTSTRAP", "BOOST_CPU", 0);
	bstrap_boostvram = bootstrapini.GetInt("NDS-BOOTSTRAP", "BOOST_VRAM", 0);
	bstrap_debug = bootstrapini.GetInt("NDS-BOOTSTRAP", "DEBUG", 0);
	bstrap_lockARM9scfgext = bootstrapini.GetInt("NDS-BOOTSTRAP", "LOCK_ARM9_SCFG_EXT", 0);
}

void SaveSettings(void) {
	// GUI
	CIniFile settingsini( settingsinipath );

	settingsini.SetInt("SRLOADER", "AUTORUNGAME", autorun);
	settingsini.SetInt("SRLOADER", "SHOWLOGO", showlogo);
	settingsini.SetInt("SRLOADER", "GOTOSETTINGS", gotosettings);

	// UI settings.
	settingsini.SetInt("SRLOADER", "THEME", theme);
	settingsini.SaveIniFile(settingsinipath);

	// nds-bootstrap
	CIniFile bootstrapini( bootstrapinipath );

	bootstrapini.SetString( "NDS-BOOTSTRAP", "ARM7_DONOR_PATH", arm7DonorPath);
	bootstrapini.SetInt("NDS-BOOTSTRAP", "BOOST_CPU", bstrap_boostcpu);
	bootstrapini.SetInt("NDS-BOOTSTRAP", "BOOST_VRAM", bstrap_boostvram);
	bootstrapini.SetInt("NDS-BOOTSTRAP", "DEBUG", bstrap_debug);
	bootstrapini.SetInt("NDS-BOOTSTRAP", "LOCK_ARM9_SCFG_EXT", bstrap_lockARM9scfgext);
	bootstrapini.SaveIniFile(bootstrapinipath);
}

int screenmode = 0;
// int subscreenmode = 0;

int settingscursor = 0;

using namespace std;

//---------------------------------------------------------------------------------
void stop (void) {
//---------------------------------------------------------------------------------
	while (1) {
		swiWaitForVBlank();
	}
}

char filePath[PATH_MAX];

//---------------------------------------------------------------------------------
void doPause(int x, int y) {
//---------------------------------------------------------------------------------
	// iprintf("Press start...\n");
	printSmall(false, x, y, "Press start...");
	while(1) {
		scanKeys();
		if(keysDown() & KEY_START)
			break;
	}
	scanKeys();
}

std::string ReplaceAll(std::string str, const std::string& from, const std::string& to) {
    size_t start_pos = 0;
    while((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // Handles case where 'to' is a substring of 'from'
    }
    return str;
}

void loadROMselect() {
	if (theme == 0) runNdsFile ("sd:/_nds/srloader/dsimenu.srldr", 0, 0);
	else runNdsFile ("sd:/_nds/srloader/dsmenu.srldr", 0, 0);
}

//---------------------------------------------------------------------------------
int main(int argc, char **argv) {
//---------------------------------------------------------------------------------

	// overwrite reboot stub identifier
	extern u64 *fake_heap_end;
	*fake_heap_end = 0;

	defaultExceptionHandler();

	// Read user name
	char *username = (char*)PersonalData->name;
		
	// text
	for (int i = 0; i < 10; i++) {
		if (username[i*2] == 0x00)
			username[i*2/2] = 0;
		else
			username[i*2/2] = username[i*2];
	}

#ifndef EMULATE_FILES

	if (!fatInitDefault()) {
		graphicsInit();
		fontInit();
		printSmall(true, 1, 2, username);
		printSmall(false, 4, 4, "fatinitDefault failed!");
		stop();
	}

#endif

	std::string filename;
	std::string bootstrapfilename;

	LoadSettings();
	
	swiWaitForVBlank();
	scanKeys();

	if (!gotosettings && autorun && !(keysHeld() & KEY_B)) {
		CIniFile bootstrapini( bootstrapinipath );
		bootstrapfilename = bootstrapini.GetString("NDS-BOOTSTRAP", "BOOTSTRAP_PATH","");
		bootstrapfilename = ReplaceAll( bootstrapfilename, "fat:/", "sd:/");
		runNdsFile (bootstrapfilename.c_str(), 0, 0);
	}
	
	char vertext[12];
	// snprintf(vertext, sizeof(vertext), "Ver %d.%d.%d   ", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH); // Doesn't work :(
	snprintf(vertext, sizeof(vertext), "Ver %d.%d.%d   ", 1, 1, 2);

	if (showlogo) {
		graphicsInit();
		fontInit();
	}

	if (gotosettings) {
		if (!showlogo) {
			graphicsInit();
			fontInit();
		}
		screenmode = 1;
		gotosettings = false;
		SaveSettings();
	} else if (showlogo) {
		unsigned int * SCFG_ROM=	(unsigned int*)0x4004000;		
		unsigned int * SCFG_CLK=	(unsigned int*)0x4004004;
		unsigned int * SCFG_EXT=	(unsigned int*)0x4004008;
		unsigned int * SCFG_MC=		(unsigned int*)0x4004010;
		unsigned int * SCFG_ROM_ARM7_COPY=	(unsigned int*)0x2370000;
		unsigned int * SCFG_EXT_ARM7_COPY=  (unsigned int*)0x2370001;

		if(*SCFG_EXT>0) {
			char text1[48], text2[48], text3[48], text4[48], text5[48], text6[48]; 
			
			snprintf (text1, sizeof(text1), "DSI SCFG_ROM ARM9 : %x",*SCFG_ROM);			
			snprintf (text2, sizeof(text2), "DSI SCFG_CLK ARM9 : %x",*SCFG_CLK);
			snprintf (text3, sizeof(text3), "DSI SCFG_EXT ARM9 : %x",*SCFG_EXT);			
			snprintf (text4, sizeof(text4), "DSI SCFG_MC ARM9 : %x",*SCFG_MC);
			
			snprintf (text5, sizeof(text5), "DSI SCFG_ROM ARM7 : %x",*SCFG_ROM_ARM7_COPY);
			snprintf (text6, sizeof(text6), "DSI SCFG_EXT ARM7 : %x",*SCFG_EXT_ARM7_COPY);
			
			int yPos = 4;
			
			printSmall(false, 4, yPos, text1);
			yPos += 16;
			printSmall(false, 4, yPos, text2);
			yPos += 16;
			printSmall(false, 4, yPos, text3);
			yPos += 16;
			printSmall(false, 4, yPos, text4);
			yPos += 16;
			printSmall(false, 4, yPos, text5);
			yPos += 16;
			printSmall(false, 4, yPos, text6);
			
			//test RAM
			//unsigned int * TEST32RAM=	(unsigned int*)0xD004000;		
			//*TEST32RAM = 0x55;
			//iprintf ("32 MB RAM ACCESS : %x\n\n",*TEST32RAM);
			// doPause(80, 140);
		}
		
		for (int i = 0; i < 60*2; i++) {
			swiWaitForVBlank();
		}
		
		scanKeys();

		if (keysHeld() & KEY_START)
			screenmode = 1;

	} else {
		scanKeys();

		if (keysHeld() & KEY_START) {
			graphicsInit();
			fontInit();
			screenmode = 1;
			for (int i = 0; i < 60; i++) {
				swiWaitForVBlank();
			}
		}
	}


	srand(time(NULL));

	while(1) {
	
		if (screenmode == 1) {
			
			bool selectmode = true;
			bool menuprinted = false;
			
			while(selectmode) {
				int pressed = 0;

				if (!menuprinted) {
					// Clear the screen so it doesn't over-print
					clearText();
					
					printSmall(true, 1, 2, username);
					printSmall(true, 192, 184, vertext);
					
					printLarge(false, 4, 4, "Settings: GUI");
					printLarge(false, 4, 64, "Settings: Bootstrap");
					
					int yPos;
					switch (settingscursor) {
						case 0:
						default:
							yPos = 24;
							break;
						case 1:
							yPos = 32;
							break;
						case 2:
							yPos = 48;
							break;
						case 3:
							yPos = 88;
							break;
						case 4:
							yPos = 96;
							break;
						case 5:
							yPos = 104;
							break;
						case 6:
							yPos = 112;
							break;
						case 7:
							yPos = 120;
							break;
					}
					
					printSmall(false, 4, yPos, ">");
					
					printSmall(false, 12, 24, "Theme");
					if(theme == 2)
						printSmall(false, 156, 24, "3DS HOME Menu");
					else if(theme == 1)
						printSmall(false, 156, 24, "DS Menu");
					else
						printSmall(false, 156, 24, "DSi Menu");

					printSmall(false, 12, 32, "Run last played ROM on startup");
					if(autorun)
						printSmall(false, 224, 40, "On");
					else
						printSmall(false, 224, 40, "Off");
						
					printSmall(false, 12, 48, "Show SRLoader logo on startup");
					if(showlogo)
						printSmall(false, 224, 56, "On");
					else
						printSmall(false, 224, 56, "Off");


					printSmall(false, 12, 88, "ARM9 CPU Speed");
					if(bstrap_boostcpu)
						printSmall(false, 156, 88, "133mhz (TWL)");
					else
						printSmall(false, 156, 88, "67mhz (NTR)");
					
					if (bstrap_boostcpu) {
						printSmall(false, 12, 96, "VRAM boost");
						if(bstrap_boostvram)
							printSmall(false, 224, 96, "On");
						else
							printSmall(false, 224, 96, "Off");
					}
					
					printSmall(false, 12, 104, "Debug");
					if(bstrap_debug)
						printSmall(false, 224, 104, "On");
					else
						printSmall(false, 224, 104, "Off");
						
					printSmall(false, 12, 112, "Lock ARM9 SCFG_EXT");
					if(bstrap_lockARM9scfgext)
						printSmall(false, 224, 112, "On");
					else
						printSmall(false, 224, 112, "Off");
						
					printSmall(false, 12, 120, "Unset donor ROM");
						

					if (settingscursor == 0) {
						printSmall(false, 4, 156, "The theme to use in SRLoader.");
					} else if (settingscursor == 1) {
						printSmall(false, 4, 148, "If turned on, hold B on");
						printSmall(false, 4, 156, "startup to skip to the");
						printSmall(false, 4, 164, "ROM select menu.");
						printSmall(false, 4, 172, "Press Y to start last played ROM.");
					} else if (settingscursor == 2) {
						printSmall(false, 4, 156, "The SRLoader logo will be");
						printSmall(false, 4, 164, "shown when you start");
						printSmall(false, 4, 172, "SRLoader.");
					} else if (settingscursor == 3) {
						printSmall(false, 4, 156, "Set to TWL to get rid of lags");
						printSmall(false, 4, 164, "in some games.");
					} else if (settingscursor == 4) {
						printSmall(false, 4, 156, "Allows 8 bit VRAM writes");
						printSmall(false, 4, 164, "and expands the bus to 32 bit.");
					} else if (settingscursor == 5) {
						printSmall(false, 4, 156, "Displays some text before");
						printSmall(false, 4, 164, "launched game.");
					} else if (settingscursor == 6) {
						printSmall(false, 4, 156, "Locks the ARM9 SCFG_EXT,");
						printSmall(false, 4, 164, "avoiding conflict with");
						printSmall(false, 4, 172, "recent libnds.");
					} else if (settingscursor == 7) {
						printSmall(false, 4, 156, "Unset currently set");
						printSmall(false, 4, 164, "donor ROM.");
					}

					menuprinted = true;
				}

				// Power saving loop. Only poll the keys once per frame and sleep the CPU if there is nothing else to do
				do {
					scanKeys();
					pressed = keysDownRepeat();
					swiWaitForVBlank();
				} while (!pressed);
				
				if (pressed & KEY_UP) {
					settingscursor -= 1;
					if (!bstrap_boostcpu && settingscursor == 4)
						settingscursor -= 1;
					menuprinted = false;
				}
				if (pressed & KEY_DOWN) {
					settingscursor += 1;
					if (!bstrap_boostcpu && settingscursor == 4)
						settingscursor += 1;
					menuprinted = false;
				}
					
				if (pressed & KEY_A) {
					switch (settingscursor) {
						case 0:
						default:
							theme += 1;
							if (theme > 2) theme = 0;
							menuprinted = false;
							break;
						case 1:
							autorun = !autorun;
							menuprinted = false;
							break;
						case 2:
							showlogo = !showlogo;
							menuprinted = false;
							break;
						case 3:
							bstrap_boostcpu = !bstrap_boostcpu;
							menuprinted = false;
							break;
						case 4:
							bstrap_boostvram = !bstrap_boostvram;
							menuprinted = false;
							break;
						case 5:
							bstrap_debug = !bstrap_debug;
							menuprinted = false;
							break;
						case 6:
							bstrap_lockARM9scfgext = !bstrap_lockARM9scfgext;
							menuprinted = false;
							break;
						case 7:
							arm7DonorPath = "";
							printSmall(false, 156, 120, "Done!");
							break;
					}
				}
				
				if (pressed & KEY_Y && settingscursor == 1) {
					screenmode = 0;
					selectmode = false;
					clearText();
					CIniFile bootstrapini( bootstrapinipath );
					bootstrapfilename = bootstrapini.GetString("NDS-BOOTSTRAP", "BOOTSTRAP_PATH","");
					bootstrapfilename = ReplaceAll( bootstrapfilename, "fat:/", "sd:/");
					int err = runNdsFile (bootstrapfilename.c_str(), 0, 0);
					iprintf ("Start failed. Error %i\n", err);
				}
				
				if (pressed & KEY_B) {
					clearText();
					printSmall(false, 4, 4, "Saving settings...");
					SaveSettings();
					screenmode = 0;
					selectmode = false;
					break;
				}
				
				if (settingscursor > 7) settingscursor = 0;
				else if (settingscursor < 0) settingscursor = 7;
			}

		} else {
			loadROMselect();
		}

	}

	return 0;
}
