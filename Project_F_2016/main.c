// Copyright (c) 2015-16, Joe Krachey
// All rights reserved.
//
// Redistribution and use in source or binary form, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions in source form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimer in 
//    the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "main.h"

char group[] = "Group00";
char individual_1[] = "Shyamal Anadkat";
char individual_2[] = "Aaron Levin";
char individual_3[] = "Sneha Patri";

extern game_state_fsm game_state;
extern SELECTED_ITEM selected_item;


//************ENUMS********************//
typedef enum {
  DEBOUNCE_ONE,
  DEBOUNCE_1ST_ZERO,
  DEBOUNCE_2ND_ZERO,
  DEBOUNCE_PRESSED
}
DEBOUNCE_STATES;

//*****************************************************************************
// DISABLE INTERRUPTS 
//*****************************************************************************
void DisableInterrupts(void)
{
  __asm {
         CPSID  I
  }
}

//*****************************************************************************\
// ENABLE INTERRUPTS 
//*****************************************************************************
void EnableInterrupts(void)
{
  __asm {
    CPSIE  I
  }
}

//*****************************************************************************
// INIT HARDWARE AND PERIPHERALS 
//*****************************************************************************
void initialize_hardware(void)
{
	//enable interrupts
	EnableInterrupts();
	
	//init serial debug for printf
	init_serial_debug(true, true);
	
	//init leds and switches
	lp_io_init();

	//LCD init sequence: gpio + screen config 
	lcd_config_gpio();
	lcd_config_screen();
	
	// Initialize the TIMER0 to be a 
  //      32-bit
  //      one-shot
  //      count down
  //      no interrupts
  gp_timer_config_32(TIMER0_BASE, ONE_SHOT, false, false);
	
	ps2_initialize(); 
	
	//disable interrupts
	DisableInterrupts();
}

int debounce_sw1(void) {
  static uint16_t sw1_count = 0;
	bool return_value = false;
	
	
	if (lp_io_read_pin(SW1_BIT)) {
		sw1_count = 0;
	} else if (sw1_count <= 6) {
		sw1_count++;
	}
	
  if (!lp_io_read_pin(SW1_BIT)) {
		sw1_count++;
  } else {
		sw1_count = 0;
	}
	return sw1_count == 6;
}

void detect_button_press_main_menu() {
	//navigate menu.todo: make stateful 	
	if(debounce_sw1()) {
		
	switch(selected_item) {
		case PLAY_NOW:
			game_state = PLAY_NOW;
			break;
		case HIGH_SCORES:
			game_state = HIGH_SCORES;
			break;
		}
	}
}


//*****************************************************************************
// MAIN
//*****************************************************************************
int 
main(void)
{
	uint16_t y_adc_data;
  char msg[80];
  initialize_hardware();
	
	printf("\n\r");
  printf("**************************************\n\r");
  printf("* ECE353 - Final Project - Debug\n\r");
  printf("**************************************\n\r");
  printf("\n\r");
	
	update_ui_init_main_menu();
	
  while(1){
		
		// START: State Change Logic
		static game_state_fsm last_state = MENU;
		
		// If a state transition has occurred... initialize new state
		if( game_state != last_state) {
			last_state = game_state; // update last state to current state
			update_ui_init_new_state(game_state); // initialize the new state
		}
		// END: State Change Logic
 	
		
		// This part handles the current state
		switch(game_state) {
			
			case MENU:
				//get x and y adc values 
				y_adc_data = ps2_get_y();
				navigate_main_menu(y_adc_data);
				detect_button_press_main_menu();
				break;
			
			case PLAY:
				update_ui_play();
				break;
			
			case WIN:
				break;
			
			case LOSE:
				break;
		}
	}
}