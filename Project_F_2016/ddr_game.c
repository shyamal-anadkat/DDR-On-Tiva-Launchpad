#include "ddr_game.h"
  		  


//*****************************************************************************
// Initializes the UI for PLAY mode
//*****************************************************************************
 
void update_ui_init_play(void) {
 	lcd_clear_screen(LCD_COLOR_BLACK);
	add_arrow(ARROW_UP);
	add_arrow(ARROW_DOWN);
}

//*****************************************************************************
// Updates the entire user interface of the game in PLAY mode
// Increments all of the onscreen arrows by 1		  // Increments all of the onscreen arrows by 1
//*****************************************************************************
void update_ui_play(void) {
	animate_arrows();
}