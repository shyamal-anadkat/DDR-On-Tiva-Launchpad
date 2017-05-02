// Copyright (c) 2014-16, Joe Krachey
// All rights reserved.
//
// Redistribution and use in binary form, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions in binary form must reproduce the above copyright 
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

#include "ps2.h"


/*******************************************************************************
* Function Name: initialize_adc_gpio_pins
********************************************************************************
* Used to initialize the PS2 joystick GPIO pins for both the analog inputs
*
* Configuration Info
*		Fill out relevant information in ps2.h.  ps2.h defines 
*		how various peripherals are physically connected to the board.
*******************************************************************************/
static void initialize_adc_gpio_pins(void)
{
	// Enable GPIO Port
	gpio_enable_port(PS2_GPIO_BASE);
	
	// Enable the pins as input pins
	gpio_config_enable_input(PS2_GPIO_BASE, PS2_X_DIR_MASK | PS2_Y_DIR_MASK);
	
	// Configure the pins as analog pins
	gpio_config_analog_enable(PS2_GPIO_BASE, PS2_X_DIR_MASK | PS2_Y_DIR_MASK);
	
	// Configure alternate function
	gpio_config_alternate_function(PS2_GPIO_BASE, PS2_X_DIR_MASK | PS2_Y_DIR_MASK);
	
}

/*******************************************************************************
* Function Name: ps2_initialize
********************************************************************************
* Initializes the GPIO pins connected to the PS2 Joystick.  It also configures
* ADC0 to use Sample Sequencer #3 to convert a programmable channel number.
*******************************************************************************/
void ps2_initialize(void)
{
	initialize_adc_gpio_pins();
	initialize_adc(PS2_ADC_BASE);
}

/*******************************************************************************
* Function Name: ps2_initialize
********************************************************************************
* Initializes the GPIO pins connected to the PS2 Joystick.  It also configures
* ADC0 to use Sample Sequencer #2 to convert a programmable channel number.
*******************************************************************************/
void ps2_initialize_hw3()
{
	initialize_adc_gpio_pins();
	initialize_adc_hw3();
}

/*******************************************************************************
* Function Name: ps2_get_x
********************************************************************************
*Returns the most current reading of the X direction  Only the lower 12-bits
* contain data.
********************************************************************************/
uint16_t ps2_get_x(void)
{
  uint16_t adc_val;
  adc_val = get_adc_value(PS2_ADC_BASE, PS2_X_ADC_CHANNEL);
  return adc_val;
}

/*******************************************************************************
* Function Name: ps2_get_y
********************************************************************************
* Returns the most current reading of the Y direction.  Only the lower 12-bits
*  contain data.
********************************************************************************/
uint16_t ps2_get_y(void)
{
  uint16_t adc_val;
  adc_val = get_adc_value(PS2_ADC_BASE, PS2_Y_ADC_CHANNEL);
  return adc_val;
}


ps2_dir_t ps2_debounce(uint16_t y_adc_val) {
	static DEBOUNCE_STATES debounce_ps2_state = DEBOUNCE_ONE;	
	static ps2_dir_t curr_ps2_dir = PS2_DIR_NONE;
	static ps2_dir_t last_ps2_dir = PS2_DIR_NONE;
	
	// Determine current direction based on ADC value and thresholds
	curr_ps2_dir = (y_adc_val > PS2_THRSHLD_UP) ? PS2_DIR_UP : (y_adc_val < PS2_THRSHLD_DOWN) ? PS2_DIR_DOWN : PS2_DIR_NONE;
	
		switch(debounce_ps2_state) {
		case DEBOUNCE_ONE:
			if(curr_ps2_dir != PS2_DIR_NONE) {
				debounce_ps2_state = DEBOUNCE_1ST_ZERO;
				last_ps2_dir = curr_ps2_dir;
			}
			return PS2_DIR_NONE;
			
		case DEBOUNCE_1ST_ZERO:
			if(curr_ps2_dir == last_ps2_dir) debounce_ps2_state = DEBOUNCE_2ND_ZERO;
			else {
				last_ps2_dir = curr_ps2_dir;
				debounce_ps2_state = DEBOUNCE_ONE;
			}
			return PS2_DIR_NONE;
			
		case DEBOUNCE_2ND_ZERO:
			if(curr_ps2_dir == last_ps2_dir) debounce_ps2_state = DEBOUNCE_PRESSED;
			else {
				last_ps2_dir = curr_ps2_dir;
				debounce_ps2_state = DEBOUNCE_ONE;
			}
			return PS2_DIR_NONE;
			
		case DEBOUNCE_PRESSED:
			if(curr_ps2_dir == last_ps2_dir) {
				debounce_ps2_state = DEBOUNCE_DONE;
			}
			else {
				curr_ps2_dir = curr_ps2_dir;
				debounce_ps2_state = DEBOUNCE_ONE;
			}
			return curr_ps2_dir;
			
		case DEBOUNCE_DONE:
			if(curr_ps2_dir == last_ps2_dir) {
				debounce_ps2_state = DEBOUNCE_DONE;
			}
			else {
				last_ps2_dir = curr_ps2_dir;
				debounce_ps2_state = DEBOUNCE_ONE;
			}
			return PS2_DIR_NONE;
	}
}

