#include <stdlib.h>
#include <grrlib.h>
#include <math.h>
#include <wiiuse/wpad.h>
#include <fat.h>

//---------------------------------------------------------------------------------
int main() {
//---------------------------------------------------------------------------------
    
	// This function initialises the attached controllers
	WPAD_Init();
	WPAD_SetDataFormat(WPAD_CHAN_0, WPAD_FMT_BTNS_ACC_IR);

	GRRLIB_Init();
	ir_t ir1;

	GRRLIB_Settings.antialias = true;
	
	GRRLIB_SetBackgroundColour(0x00, 0x5B, 0xD1, 0xFF);

	while(1) {
		GRRLIB_2dMode();
		WPAD_IR(WPAD_CHAN_0, &ir1);

		// Call WPAD_ScanPads each loop, this reads the latest controller states
		WPAD_ScanPads();

		// WPAD_ButtonsDown tells us which buttons were pressed in this loop
		// this is a "one shot" state which will not fire again until the button has been released
		u32 pressed = WPAD_ButtonsDown(0);

		// We return to the launcher application via exit
		if ( pressed & WPAD_BUTTON_HOME ) exit(0);
		
		GRRLIB_Rectangle(60, 190, 200, 100, 0x808080FF, 1);
		GRRLIB_Rectangle(380, 190, 200, 100, 0x808080FF, 1);
		GRRLIB_Circle(ir1.sx, ir1.sy, 2, 0xFF0000FF, 1);


		GRRLIB_Render();
	}

	return 0;
}
