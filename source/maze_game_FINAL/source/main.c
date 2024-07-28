/*===========================================
        GRRLIB (GX Version)
        - Template Code -

        Minimum Code To Use GRRLIB
============================================*/
#include <grrlib.h>
#include <ogc/lwp_watchdog.h>   // Needed for gettime and ticks_to_millisecs
#include <asndlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <gccore.h>
#include <math.h>
#include <wiiuse/wpad.h>
#include <gcmodplay.h>
#include "oggplayer.h"

//#include "font_png.h"
//#include "font2_png.h"
//#include "font3_ttf.h"
#include "BMfont5_png.h"
#include "anxiety_ogg.h"
#include "jazzgrade_ogg.h"
#include "amazonianDyslexia_ogg.h"
#include "maze_png.h"
#include "menu_png.h"
#include "controls_png.h"
#include "credits_png.h"
#include "wiimote_controls_png.h"
#include "nunchuck_controls_png.h"
#include "classic_controller_controls_png.h"
#include "win_png.h"
#include "lose_png.h"

#define rightheld() (WPAD_ButtonsHeld(0) & WPAD_BUTTON_RIGHT)
#define leftheld() (WPAD_ButtonsHeld(0) & WPAD_BUTTON_LEFT)
#define upheld() (WPAD_ButtonsHeld(0) & WPAD_BUTTON_UP)
#define downheld() (WPAD_ButtonsHeld(0) & WPAD_BUTTON_DOWN)
#define classicrightheld() (WPAD_ButtonsHeld(0) & WPAD_CLASSIC_BUTTON_RIGHT)
#define classicleftheld() (WPAD_ButtonsHeld(0) & WPAD_CLASSIC_BUTTON_LEFT)
#define classicupheld() (WPAD_ButtonsHeld(0) & WPAD_CLASSIC_BUTTON_UP)
#define classicdownheld() (WPAD_ButtonsHeld(0) & WPAD_CLASSIC_BUTTON_DOWN)

#define plusdown() (WPAD_ButtonsDown(0) & WPAD_BUTTON_PLUS) || (WPAD_ButtonsDown(0) & WPAD_CLASSIC_BUTTON_PLUS)
#define minusdown() (WPAD_ButtonsDown(0) & WPAD_BUTTON_MINUS) || (WPAD_ButtonsDown(0) & WPAD_CLASSIC_BUTTON_MINUS)
#define homedown() (WPAD_ButtonsDown(0) & WPAD_BUTTON_HOME) || (WPAD_ButtonsDown(0) & WPAD_CLASSIC_BUTTON_HOME)
#define adown() (WPAD_ButtonsDown(0) & WPAD_BUTTON_A) || (WPAD_ButtonsDown(0) & WPAD_CLASSIC_BUTTON_A)
#define bdown() (WPAD_ButtonsDown(0) & WPAD_BUTTON_B) || (WPAD_ButtonsDown(0) & WPAD_CLASSIC_BUTTON_B)
#define onedown() (WPAD_ButtonsDown(0) & WPAD_BUTTON_1)
#define twodown() (WPAD_ButtonsDown(0) & WPAD_BUTTON_2)

#define GRRLIB_BLACK   0x000000FF
#define GRRLIB_MAROON  0x800000FF
#define GRRLIB_GREEN   0x008000FF
#define GRRLIB_OLIVE   0x808000FF
#define GRRLIB_NAVY    0x000080FF
#define GRRLIB_PURPLE  0x800080FF
#define GRRLIB_TEAL    0x008080FF
#define GRRLIB_CYAN    0x00FFFFFF
#define GRRLIB_GRAY    0x808080FF
#define GRRLIB_SILVER  0xC0C0C0FF
#define GRRLIB_RED     0xFF0000FF
#define GRRLIB_LIME    0x00FF00FF
#define GRRLIB_YELLOW  0xFFFF00FF
#define GRRLIB_BLUE    0x0000FFFF
#define GRRLIB_FUCHSIA 0xFF00FFFF
#define GRRLIB_AQUA    0x00FFFFFF
#define GRRLIB_WHITE   0xFFFFFFFF

//static MODPlay play;

int main(int argc, char **argv) {
    // Initialise the Graphics & Video subsystem
    GRRLIB_Init();

    // Initialise the Wiimotes
    WPAD_Init();
    WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR); // allows usage of buttons, accelerometer, and ir sensor (a.k.a the thing that makes your wiimote go pointy point)

    // Initialise the audio subsystem
	ASND_Init();

    //GRRLIB_texImg *font = GRRLIB_LoadTexture(font_png);
    //GRRLIB_InitTileSet(font, 4, 6, 33);
    //GRRLIB_texImg *font2 = GRRLIB_LoadTexture(font2_png);
    //GRRLIB_InitTileSet(font2, 4, 6, 33);
    //GRRLIB_ttfFont *font3 = GRRLIB_LoadTTF(font3_ttf, font3_ttf_size);
    GRRLIB_texImg *tex_BMfont5 = GRRLIB_LoadTexture(BMfont5_png);
    GRRLIB_InitTileSet(tex_BMfont5, 8, 16, 0);
	GRRLIB_texImg *menu = GRRLIB_LoadTexture(menu_png);
	GRRLIB_texImg *controls = GRRLIB_LoadTexture(controls_png);
	GRRLIB_texImg *credits = GRRLIB_LoadTexture(credits_png);
	// note to self: MAKE SURE ALL DIMENSIONS ARE DIVISIBLE BY 4
	GRRLIB_texImg *wiimote_controls = GRRLIB_LoadTexture(wiimote_controls_png);
	GRRLIB_texImg *nunchuck_controls = GRRLIB_LoadTexture(nunchuck_controls_png);
	GRRLIB_texImg *classic_controller_controls = GRRLIB_LoadTexture(classic_controller_controls_png);
	GRRLIB_texImg *maze = GRRLIB_LoadTexture(maze_png);
	GRRLIB_texImg *win = GRRLIB_LoadTexture(win_png);
	GRRLIB_texImg *lose = GRRLIB_LoadTexture(lose_png);

    float x = 5;
    float y = 5;
    float ang0 = 0;
    float mag0 = 0;
    float ang1 = 0;
    float mag1 = 0;
	float joyx = 0;
	float joyy = 0;
	int song = 0;
	bool hover0;
	bool hover1;

	// gamestates
	const int GAMESTATES_MENU = 0;
	const int GAMESTATES_CONTROLS = 1;
	const int GAMESTATES_CREDITS = 2;
	const int GAMESTATES_GAME = 3;
	const int GAMESTATES_WIN = 4;
	const int GAMESTATES_LOSE = 5;
	int gamestate = GAMESTATES_MENU;
	
	// control menus
	const int CONTROLS_WIIMOTE = 0;
	const int CONTROLS_NUNCHUCK = 1;
	const int CONTROLS_CLASSIC_CONTROLLER = 2;
	int control_menu = CONTROLS_WIIMOTE;

	int rumblethreshold = 5;
	int rumbleclock = rumblethreshold;

    float rad(float deg) {
        return deg * 0.01745329;
    }

	void rumble(int threshold) {
		hover1 = true;
			if (hover0 != hover1) {
				rumblethreshold = threshold;
				rumbleclock = 0;
			}
		hover0 = true;
	}
	void unrumble() {
		hover1 = false;
		hover0 = false;
	}

	struct expansion_t othercontroller; //nunchuk or classic controller
	struct ir_t irsensor;

	PlayOgg(anxiety_ogg, anxiety_ogg_size, 0, OGG_INFINITE_TIME);

    // Loop forever
	while(1) {
		WPAD_SetVRes(0, 640, 480);
		WPAD_ScanPads();  // Scan the Wiimotes
		WPAD_Expansion(0,&othercontroller); // check if there's a controller connected to the wiimote
		WPAD_IR(0, &irsensor); // check the ir sensor

		if (gamestate == GAMESTATES_MENU) {
			bool play_button = GRRLIB_PtInRect(156, 191, 303, 118, irsensor.x, irsensor.y);
			bool controls_button = GRRLIB_PtInRect(29, 360, 181, 75, irsensor.x, irsensor.y);
			bool credits_button = GRRLIB_PtInRect(440, 367, 171, 71, irsensor.x, irsensor.y);
			if (play_button ||
			controls_button ||
			credits_button) {
				rumble(5);
				if (adown()) {
					if (play_button) gamestate = GAMESTATES_GAME;
					if (controls_button) gamestate = GAMESTATES_CONTROLS;
					if (credits_button) gamestate = GAMESTATES_CREDITS;
				}
			}
			else {
				unrumble();
			}
			GRRLIB_DrawImg(0,0,menu,0,1,1,GRRLIB_WHITE);
			GRRLIB_Circle(irsensor.x, irsensor.y, 5, GRRLIB_RED, 1);
		}
		if (gamestate == GAMESTATES_CONTROLS) {
			bool wiimote_button = GRRLIB_PtInRect(5, 418, 173, 58, irsensor.x, irsensor.y);
			bool nunchuck_button = GRRLIB_PtInRect(181, 418, 173, 58, irsensor.x, irsensor.y);
			bool classic_controller_button = GRRLIB_PtInRect(357, 417, 278, 59, irsensor.x, irsensor.y);
			if (bdown()) gamestate = GAMESTATES_MENU;
			if (wiimote_button || nunchuck_button || classic_controller_button) {
				rumble(5);
				if (adown()) {
					if (wiimote_button) control_menu = CONTROLS_WIIMOTE;
					if (nunchuck_button) control_menu = CONTROLS_NUNCHUCK;
					if (classic_controller_button) control_menu = CONTROLS_CLASSIC_CONTROLLER;
				}
			}
			else {
				unrumble();
			}
			GRRLIB_DrawImg(0,0,controls,0,1,1,GRRLIB_WHITE);
			GRRLIB_DrawImg(41,88,
			((control_menu == CONTROLS_WIIMOTE) ? wiimote_controls : ((control_menu == CONTROLS_NUNCHUCK) ? nunchuck_controls : ((control_menu == CONTROLS_CLASSIC_CONTROLLER) ? classic_controller_controls : wiimote_controls))),
			0,1,1,GRRLIB_WHITE);
			GRRLIB_Circle(irsensor.x, irsensor.y, 5, GRRLIB_RED, 1);
		}
		if (gamestate == GAMESTATES_CREDITS) {
			if (bdown()) gamestate = GAMESTATES_MENU;
			GRRLIB_DrawImg(0,0,credits,0,1,1,GRRLIB_WHITE);
		}
		if (gamestate == GAMESTATES_GAME) {
			// check if there's a nunchuck or classic controller connected
			if (othercontroller.type == WPAD_EXP_NUNCHUK) {
				//ang0 = othercontroller.nunchuk.js.ang;
				//mag0 = othercontroller.nunchuk.js.mag;
				// joyx = (othercontroller.nunchuk.js.pos.x / 32.0f / 3.0f) - 4.0f / 3.0f;
				// joyy = (othercontroller.nunchuk.js.pos.y / 32.0f / 3.0f) - 4.0f / 3.0f;
				joyx = (othercontroller.nunchuk.js.pos.x / 32.0f - 4.0f) / 3.0f;
				joyy = (othercontroller.nunchuk.js.pos.y / 32.0f - 4.0f) / 3.0f;
				//x += sin(rad(ang0)) * mag0;
				//y -= cos(rad(ang0)) * mag0;
				x += joyx;
				y -= joyy;
			}
			else {
				if (othercontroller.type == WPAD_EXP_CLASSIC) {
					ang0 = othercontroller.classic.ljs.ang;
					mag0 = othercontroller.classic.ljs.mag;
					ang1 = othercontroller.classic.rjs.ang;
					mag1 = othercontroller.classic.rjs.mag;
					x += sin(rad(ang0)) * mag0;
					y -= cos(rad(ang0)) * mag0;
					x += classicrightheld() ? 1 : (classicleftheld() ? -1 : 0);
					y -= classicupheld() ? 1 : (classicdownheld() ? -1 : 0);
				}
			}
			// this game is meant to be played sideways
			x += downheld() ? 1 : (upheld() ? -1 : 0);
			y += leftheld() ? 1 : (rightheld() ? -1 : 0);

			GRRLIB_DrawImg(0, 0, maze, 0, 1, 1, GRRLIB_WHITE);
			GRRLIB_Printf(100, 25, tex_BMfont5, GRRLIB_GREEN, 1, "x: %f Y: %f", x, y);
			//GRRLIB_Printf(100, 50, font, GRRLIB_TEAL, 2, " !\"#$&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");
			//GRRLIB_PrintfTTF(100, 75, font3, "please just work", 16, GRRLIB_TEAL);
			GRRLIB_Printf(100, 100, tex_BMfont5, GRRLIB_TEAL, 1, "ANG0: %f MAG0: %f", ang0, mag0);
			GRRLIB_Printf(100, 125, tex_BMfont5, GRRLIB_TEAL, 1, "ANG1: %f MAG1: %f", ang1, mag1);
			GRRLIB_Printf(100, 150, tex_BMfont5, GRRLIB_TEAL, 1, "joyX: %f joyY: %f", joyx, joyy);
			GRRLIB_Rectangle(x,y,10,10,GRRLIB_CYAN,1);
		}
		if (gamestate == GAMESTATES_WIN) {
			if (adown() | onedown()) gamestate = GAMESTATES_GAME;
			if (bdown() | twodown()) gamestate = GAMESTATES_MENU;
			GRRLIB_DrawImg(0, 0, win, 0, 1, 1, GRRLIB_WHITE);
		}
		if (gamestate == GAMESTATES_LOSE) {
			if (adown() | onedown()) gamestate = GAMESTATES_GAME;
			if (bdown() | twodown()) gamestate = GAMESTATES_MENU;
			GRRLIB_DrawImg(0, 0, lose, 0, 1, 1, GRRLIB_WHITE);
		}

		/* switch (gamestate) {
			case GAMESTATES_MENU:
				bool play_button = GRRLIB_PtInRect(156, 191, 303, 118, irsensor.sx, irsensor.sy);
				bool controls_button = GRRLIB_PtInRect(29, 360, 181, 75, irsensor.sx, irsensor.sy);
				bool credits_button = GRRLIB_PtInRect(440, 367, 171, 71, irsensor.sx, irsensor.sy);
				if (play_button ||
				controls_button ||
				credits_button) {
					rumble(5);
					if (adown()) {
						if (play_button) gamestate = GAMESTATES_GAME;
						if (controls_button) gamestate = GAMESTATES_CONTROLS;
						if (credits_button) gamestate = GAMESTATES_CREDITS;
					}
				}
				else {
					unrumble();
				}
				GRRLIB_DrawImg(0,0,menu,0,1,1,GRRLIB_WHITE);
			case GAMESTATES_CONTROLS:
				const int CONTROLS_WIIMOTE = 0;
				const int CONTROLS_NUNCHUCK = 1;
				const int CONTROLS_CLASSIC_CONTROLLER = 2;
				int control_menu = CONTROLS_WIIMOTE;
				bool wiimote_button = GRRLIB_PtInRect(5, 418, 173, 58, irsensor.sx, irsensor.sy);
				bool nunchuck_button = GRRLIB_PtInRect(181, 418, 173, 58, irsensor.sx, irsensor.sy);
				bool classic_controller_button = GRRLIB_PtInRect(357, 417, 278, 59, irsensor.sx, irsensor.sy);
				if (bdown()) gamestate = GAMESTATES_MENU;
				if (wiimote_button || nunchuck_button || classic_controller_button) {
					rumble(5);
					if (adown()) {
						if (wiimote_button) control_menu = CONTROLS_WIIMOTE;
						if (nunchuck_button) control_menu = CONTROLS_NUNCHUCK;
						if (classic_controller_button) control_menu = CONTROLS_CLASSIC_CONTROLLER;
					}
				}
				else {
					unrumble();
				}
				GRRLIB_DrawImg(0,0,controls,0,1,1,GRRLIB_WHITE);
				GRRLIB_DrawImg(41,88,
				((control_menu == CONTROLS_WIIMOTE) ? wiimote_controls : ((control_menu == CONTROLS_NUNCHUCK) ? nunchuck_controls : ((control_menu == CONTROLS_CLASSIC_CONTROLLER) ? classic_controller_controls : wiimote_controls))),
				0,1,1,GRRLIB_WHITE);
			case GAMESTATES_CREDITS:
				if (bdown()) gamestate = GAMESTATES_MENU;
				GRRLIB_DrawImg(0,0,credits,0,1,1,GRRLIB_WHITE);
			case GAMESTATES_GAME:
				// check if there's a nunchuck or classic controller connected
				if (othercontroller.type == WPAD_EXP_NUNCHUK) {
					//ang0 = othercontroller.nunchuk.js.ang;
					//mag0 = othercontroller.nunchuk.js.mag;
					joyx = (othercontroller.nunchuk.js.pos.x / 32.0f / 3.0f) -4.0f / 3.0f;
					joyy = (othercontroller.nunchuk.js.pos.y / 32.0f / 3.0f) -4.0f / 3.0f;
					//x += sin(rad(ang0)) * mag0;
					//y -= cos(rad(ang0)) * mag0;
					x += joyx;
					y -= joyy;
				}
				else {
					if (othercontroller.type == WPAD_EXP_CLASSIC) {
						ang0 = othercontroller.classic.ljs.ang;
						mag0 = othercontroller.classic.ljs.mag;
						ang1 = othercontroller.classic.rjs.ang;
						mag1 = othercontroller.classic.rjs.mag;
						x += sin(rad(ang0)) * mag0;
						y -= cos(rad(ang0)) * mag0;
						x += classicrightheld() ? 1 : (classicleftheld() ? -1 : 0);
						y -= classicupheld() ? 1 : (classicdownheld() ? -1 : 0);
					}
				}
				// this game is meant to be played sideways
				x += downheld() ? 1 : (upheld() ? -1 : 0);
				y += leftheld() ? 1 : (rightheld() ? -1 : 0);

				GRRLIB_DrawImg(0, 0, maze, 0, 1, 1, GRRLIB_WHITE);
				GRRLIB_Printf(100, 25, tex_BMfont5, GRRLIB_GREEN, 1, "x: %f Y: %f", x, y);
				//GRRLIB_Printf(100, 50, font, GRRLIB_TEAL, 2, " !\"#$&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~");
				//GRRLIB_PrintfTTF(100, 75, font3, "please just work", 16, GRRLIB_TEAL);
				GRRLIB_Printf(100, 100, tex_BMfont5, GRRLIB_TEAL, 1, "ANG0: %f MAG0: %f", ang0, mag0);
				GRRLIB_Printf(100, 125, tex_BMfont5, GRRLIB_TEAL, 1, "ANG1: %f MAG1: %f", ang1, mag1);
				GRRLIB_Printf(100, 150, tex_BMfont5, GRRLIB_TEAL, 1, "joyX: %f joyY: %f", joyx, joyy);
				GRRLIB_Rectangle(x,y,10,10,GRRLIB_CYAN,1);
			case GAMESTATES_WIN:

			case GAMESTATES_LOSE:

		} */
        
		if (rumbleclock < rumblethreshold) {
			WPAD_Rumble(0, 1);
			rumbleclock++;
		}
		else {
			WPAD_Rumble(0, 0);
		}

		if (plusdown()) {
			song++;
			if (song > 2) song = 0;
			StopOgg();
			if (song == 0) PlayOgg(anxiety_ogg, anxiety_ogg_size, 0, OGG_INFINITE_TIME);
			if (song == 1) PlayOgg(jazzgrade_ogg, jazzgrade_ogg_size, 0, OGG_INFINITE_TIME);
			if (song == 2) PlayOgg(amazonianDyslexia_ogg, amazonianDyslexia_ogg_size, 0, OGG_INFINITE_TIME);
		}

		if (minusdown()) {
			song--;
			if (song < 0) song = 2;
			StopOgg();
			if (song == 0) PlayOgg(anxiety_ogg, anxiety_ogg_size, 0, OGG_INFINITE_TIME);
			if (song == 1) PlayOgg(jazzgrade_ogg, jazzgrade_ogg_size, 0, OGG_INFINITE_TIME);
			if (song == 2) PlayOgg(amazonianDyslexia_ogg, amazonianDyslexia_ogg_size, 0, OGG_INFINITE_TIME);
		}

        // If [HOME] was pressed on the first Wiimote, break out of the loop
        if ((homedown()) && ((gamestate == GAMESTATES_MENU) | (gamestate == GAMESTATES_CONTROLS) | (gamestate == GAMESTATES_CREDITS))) break;
		if ((homedown()) && (gamestate == GAMESTATES_GAME)) gamestate = GAMESTATES_MENU;
        GRRLIB_Render();  // Render the frame buffer to the TV
    }
    //GRRLIB_FreeTexture(font);
    //GRRLIB_FreeTexture(font2);
    //GRRLIB_FreeTTF(font3);
    GRRLIB_FreeTexture(tex_BMfont5);
	GRRLIB_FreeTexture(menu);
	GRRLIB_FreeTexture(controls);
	GRRLIB_FreeTexture(credits);
	GRRLIB_FreeTexture(wiimote_controls);
	GRRLIB_FreeTexture(nunchuck_controls);
	GRRLIB_FreeTexture(classic_controller_controls);
	GRRLIB_FreeTexture(maze);
	GRRLIB_FreeTexture(win);
	GRRLIB_FreeTexture(lose);
    GRRLIB_Exit(); // Be a good boy, clear the memory allocated by GRRLIB

	StopOgg();
    exit(0);  // Use exit() to exit a program, do not use 'return' from main()
}
