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

extern volatile bool Alert_Timer0A;
extern volatile bool Alert_Timer0B;
extern volatile bool Alert_ADC0_Conversion;

uint16_t curr_x_px, curr_y_px;
uint16_t x_left_threshold = (0xFFF / 4) * 3;
uint16_t y_up_threshold = (0xFFF / 4) * 3;
uint16_t x_right_threshold = (0xFFF / 4);
uint16_t y_down_threshold = (0xFFF / 4);


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
	
	  // Initialize switches and LEDs
  lp_io_init();

  // Enable PS2 joystick
  ps2_initialize_hw3();

  // Enable TIMER0 A and B for HW3
  timer_config_hw3();

  // Start TIMER0 A and B for HW3
  timer_start_hw3();


	//LCD init sequence: gpio + screen config 
	lcd_config_gpio();
	lcd_config_screen();
	
	// Initialize the TIMER0 to be a 
  //      32-bit
  //      one-shot
  //      count down
  //      no interrupts
  gp_timer_config_32(TIMER0_BASE, ONE_SHOT, false, false);
	
	//disable interrupts
	DisableInterrupts();
}


	void navigate_menu(void) {
		if (curr_y_px >= y_up_threshold) {
				select_menuItem(1);
		} 
		else if (curr_y_px <= y_down_threshold) {
				select_menuItem(0);
		} 			
	}


//*****************************************************************************
// MAIN
//*****************************************************************************
int 
main(void)
{
	
	char msg[180];
  initialize_hardware();
	sprintf(msg,"X Dir value : 0x%03x \ Y Dir value : 0x%03x\r",curr_x_px, curr_y_px);

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

      // Update current x position with current PS2 joystick ADC value
      curr_y_px = ADC0 -> SSFIFO2 & ADC_SSFIFO2_DATA_M;

      // Update current y position with current PS2 joystick ADC value
      curr_x_px = ADC0 -> SSFIFO2 & ADC_SSFIFO2_DATA_M;
		}
		
		
		sprintf(msg,"X Dir value : 0x%03x \ Y Dir value : 0x%03x\r",curr_x_px, curr_y_px);
		
		

	
  printMenu(); 

	navigate_menu();
	

  while(1){
		};
}
