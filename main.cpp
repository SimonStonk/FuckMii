#include <iostream>
#include <stdlib.h>
#include <grrlib.h>
#include <math.h>
#include <cmath>
#include <wiiuse/wpad.h>
#include <fat.h>
#include <vector>
#include <algorithm>
#include <chrono>
#include <ctime>
#include <iterator>
using namespace std;

//Todo:
//object class maken
//Drawlist maken
//Collisionlist maken
//Collision, grounded
//Images laden, objecten tekenen
//Zwaartekracht
//File System

class Player {
	public:
		int health;		//can you read?
		float locx;		//x location
		float locy;		//y location
		float velx;		//x velocity
		float vely;		//y velocity
		bool grounded;	//whether or not a player is touching the ground
		void movex(){	
			locx = locx + velx;
		};				//fuckin move
		void movey(){
			locy = locy + vely;
		};				//just fuckin move
};

class Platform;

vector<Platform> PlatformList;

class Platform {
	public:
		int locx;
		int locy;
		int width;
		int height;
		Platform(int x, int y, int w, int h) : locx(x), locy(y), width(w), height(h) {PlatformList.push_back(*this);}
};



void DrawPlatforms() {
	for (const Platform& platform : PlatformList) {
        //Platforms getekend in zwart, nog zonder bitmap.
        GRRLIB_Rectangle(static_cast<f32>(platform.locx),
                         static_cast<f32>(platform.locy),
                         static_cast<f32>(platform.width),
                         static_cast<f32>(platform.height),
                         0x000000FF,  //Zwart
                         true);    
	}
}


const float Drag = 0.99;
const float Gravity = 0.5;
const int PointCorrectX = 190;
const int PointCorrectY = 75;
int Point1X;
int Point1Y;

//---------------------------------------------------------------------------------
int main() {
//---------------------------------------------------------------------------------
    // DIT MOET ALLEMAAL NOG IN EEN LOS BESTAND, BIJ DE LOSSE LEVELS. VERSCHILT NAMELIJK PER LEVEL WAAR JE WIL SPAWNEN
	Player Player1;
	Player1.locx = 200;
	Player1.locy = 200;
	Player1.velx = 0.00;
	Player1.vely = 0.00;

	// This function initialises the attached controllers
	WPAD_Init();
	WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR); //MOET VOOR ELKE CONTROLLER ZO

	GRRLIB_Init();
	ir_t ir1;

	GRRLIB_Settings.antialias = true;
	
	GRRLIB_SetBackgroundColour(0x00, 0x5B, 0xD1, 0xFF);
	
	GRRLIB_2dMode();
	
    //PlatformList.emplace_back(50, 50, 100, 100);
    //PlatformList.emplace_back(200, 50, 100, 100);
	Platform Platform1(50, 50, 100, 100);
	Platform Platform2 (200, 50, 100, 100);
	while(1) {


		WPAD_IR(WPAD_CHAN_0, &ir1);

		Point1X = ir1.sx - PointCorrectX;
		Point1Y = ir1.sy - PointCorrectY;
		
		// Call WPAD_ScanPads each loop, this reads the latest controller states
		WPAD_ScanPads();
		
		// WPAD_ButtonsDown tells us which buttons were pressed in this loop
		// this is a "one shot" state which will not fire again until the button has been released
		u32 pressed = WPAD_ButtonsDown(0);
		
		// We return to the launcher application via exit
		if ( pressed & WPAD_BUTTON_HOME ) exit(0);
		
		Player1.velx = Player1.velx * Drag; //drag x
		Player1.vely = Player1.vely + Gravity; //Gravity


		GRRLIB_Circle(Point1X, Point1Y, 3, 0xFF0000FF, 1); //VOORBEELD
		GRRLIB_Circle(Player1.locx, Player1.locy, 10, 0x00FF00FF, 1); // VOORBEELD
		
		
			
		if ( pressed & WPAD_BUTTON_RIGHT ) ++Player1.velx;
		if ( pressed & WPAD_BUTTON_LEFT ) --Player1.velx;
		if ( pressed & WPAD_BUTTON_DOWN ) ++Player1.vely;
		if ( pressed & WPAD_BUTTON_UP ) --Player1.vely;
		
		Player1.movex();
		Player1.movey();

		DrawPlatforms();

		GRRLIB_Render();


	}

	return 0;
}
