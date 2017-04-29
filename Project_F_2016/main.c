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

extern volatile bool Alert_Timer0B;
extern volatile bool Alert_ADC0_Conversion;
extern volatile bool Alert_PortF;

bool debugFlag = true;

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
	
	ps2_initialize_hw3();
	//ps2_initialize();

	timer_config_hw3();
	
	timer_start_hw3();
	
	//GPIOF INTERRUPT SET for SW1
	init_interrupt_sw1();
 
	ft6x06_init();
	
	//disable interrupts
	DisableInterrupts();
}


void detect_button_press_main_menu() {
	//navigate menu.todo: make stateful 	
		
	switch(selected_item) {
		case PLAY_NOW:
			game_state = PLAY_NOW;
			break;
		case HIGH_SCORES:
			game_state = HIGH_SCORES;
			break;
		default:
			break;
		}
}


//*****************************************************************************
// MAIN
//*****************************************************************************
int 
main(void)
{
	uint8_t button_vals = 0;
	uint16_t y_adc_data;
  char msg[80];
	uint16_t x,y;
  uint8_t touch_event;
	
  initialize_hardware();
	init_arrow_queue();
	
	
	
	printf("\n\r");
  printf("**************************************\n\r");
  printf("* ECE353 - Final Project - Debug\n\r");
  printf("**************************************\n\r");
  printf("\n\r");
	
	update_ui_init_main_menu();
	
	ioexpander_init();
	
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
				/* get y adc values with AD0 interrupt */
				// TIMER0B HANDLER
				if (Alert_Timer0B) {
						// Start SS2 conversion
						ADC0 -> PSSI |= ADC_PSSI_SS2;
						Alert_Timer0B = false;
				}
				 // ADC COMPUTATION HANDLER (UPDATES PS2 X/Y VALUES)
				if (Alert_ADC0_Conversion) {
						// Toggle ADC0 Conversion notifier
						Alert_ADC0_Conversion = false;
						// Update current y position with current PS2 joystick ADC value
						y_adc_data = ADC0 -> SSFIFO2 & ADC_SSFIFO2_DATA_M;
						// y_adc_data = ps2_get_y();
						navigate_main_menu(y_adc_data);
				}
				
				if(Alert_PortF) {
					detect_button_press_main_menu();
					Alert_PortF = false;
				}	
				//y_adc_data = ps2_get_y();
				//navigate_main_menu(y_adc_data);
				//detect_button_press_main_menu();
				break;
			
			case PLAY:
				button_vals = buttons_pressed();
				update_ui_play(button_vals);
			
				touch_event = ft6x06_read_td_status();
				//printf("td status read: %d\n\r", touch_event); //DEBUG
				if(touch_event > 0 && touch_event!=255) {
					//print out x and y coordinates 
					x = ft6x06_read_x();
					y = ft6x06_read_y();
					printf("Touch Events :\tX: %d\t||\tY: %d \n\r", x, y);
				}
				break;
			
			case WIN:
				break;
			
			case LOSE:
				break;
		}
	}
}