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


//*****************************************************************************
// MAIN
//*****************************************************************************
int 
main(void)
{
	uint16_t x_adc_data, y_adc_data;
  char msg[80];
  initialize_hardware();
	
	printf("\n\r");
  printf("**************************************\n\r");
  printf("* ECE353 - Final Project - Debug\n\r");
  printf("**************************************\n\r");
  printf("\n\r");
	
	printMenu(); 
	select_menuItem(1);
	
  while(1){
		
		//get x and y adc values 
		x_adc_data = ps2_get_x();
    y_adc_data = ps2_get_y();
		
		//print x,y adc values for debug
    //printf("X Dir value : 0x%03x  Y Dir value : 0x%03x\r",x_adc_data, y_adc_data);

		//navigate menu.todo: make stateful 
	  navigate_menu(y_adc_data);
		
	};
}