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

#include "launchpad_io.h"

//*****************************************************************************
// Enabling PortF will require the following steps                          
//    1. Turn on the clock for PORTF in RCGCGPIO
//
//        ONLY modify the bit for PORTF!
//
//        Search the datahseet for RCGCGPIO to determine
//        the correct value to set each register to.
//
//        In ther drivers group, driver_defines.h contains many useful
//        #defines that will make your code more readable and less mistake prone.
//        Search for SYSCTL_RCGCGPIO in that file.
//
//        Example 
//        SYSCTL->RCGCGPIO = val;
//
//    2. Wait until the clock is on by checking PRGPIO
//
//      Search the datahseet for PRGPIO to determine
//      the correct value to set each register to.
//
//
//        In ther drivers group, driver_defines.h contains many useful
//        #defines that will make your code more readable and less mistake prone.
//        Search for SYSCTL_PRGPIO in that file.
//
//        Example 
//        val = SYSCTL->PRGPIO;
//
//    Steps 3 & 4 are only necessary for Ports F and D.
//
//    3. We need to set the LOCK register to 0x4C4F434B.
//
//       Example code:
//       GPIO_PORTF_LOCK_R = 0x4C4F434B ;
//
//    4. Set the commit register
//      
//        Example Code:
//        GPIO_PORTF_CR_R = 0xFF;
//*****************************************************************************
static __inline void  port_f_enable_port(void)
{
  SYSCTL->RCGCGPIO |= SYSCTL_RCGCGPIO_R5;
	while( !( SYSCTL->PRGPIO & SYSCTL_PRGPIO_R5 ) );
	
	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R = 0xFF;
}


//*****************************************************************************
// Setting a GPIOF pins as a digital enable requires writing to DEN register
//
// Paramters
//    bit_mask  -   A bit mask indicating which pins should be configured as digital
//              pins.  Modify only the bits where the bitmask is equal to 1.
//
// Use section 10.5 of the TM4C123 data sheet to determine the bits to set in 
// the DEN register.
//
//  Code Example
//  GPIOx->DEN = val;
//*****************************************************************************
static __inline void  port_f_digital_enable(uint8_t bit_mask)
{
	GPIOF->DEN |= bit_mask;
}


//*****************************************************************************
// Setting a GPIO pin as an output requires setting the DIR register
//
// Paramters
//    bit_mask  -   A bit mask indicating which pins should be configured as output
//              pins.  Modify only the bits where the bitmask is equal to 1.
//
// Use section 10.5 of the TM4C123 data sheet to determine the bits to set in 
// the DIR register.
//
//  Code Example
//  GPIOx->DIR = val;
//*****************************************************************************
static __inline void  port_f_enable_output(uint8_t bit_mask)
{
  GPIOF->DIR |= bit_mask;
}

//*****************************************************************************
// Setting a GPIO pin as an input requires setting the DIR register
//
// Paramters
//    bit_mask  -   A bit mask indicating which pins should be configured as inputs
//              pins.  Modify only the bits where the bitmask is equal to 1.
//
// Use section 10.5 of the TM4C123 data sheet to determine the bits to set in 
// the DIR register.
//
//  Code Example
//  GPIOx->DIR = val;
//*****************************************************************************
static __inline void  port_f_enable_input(uint8_t bit_mask)
{
	GPIOF->DIR &= ~bit_mask;
}

//*****************************************************************************
// Enables a pullup resistors for GPIOF
//
// Paramters
//    bit_mask  -   A bit mask indicating which pins should be configured
//                  with pullup resistors enabled
//
// Use section 10.5 of the TM4C123 data sheet to determine the bits to set in 
// the PUR register.
//
//  Code Example
//  GPIOx->PUR = val;
//*****************************************************************************
static __inline void  port_f_enable_pull_up(uint8_t bit_mask)
{
	GPIOF->PUR = bit_mask; 
}

//*****************************************************************************
// Sets a given GPIO pin to 1.  All other pins retain their value
//
// Paramters
//    pin_number  The pin number of port F to turn on
//              
//
//*****************************************************************************
void  lp_io_set_pin(uint8_t pin_number)
{
	GPIOF->DATA |= (1 << pin_number);
}

//*****************************************************************************
// Clears a given GPIO pin to 0.  All other pins retain their value
//
// Paramters
//    pin_number  The pin number of port F to turn off
//              
//
//*****************************************************************************
void  lp_io_clear_pin(uint8_t pin_number)
{
	GPIOF->DATA &= ~(1 << pin_number);
}

//*****************************************************************************
// Reads a the current value of a pin.
//
// Paramters
//    pin_number  The pin number to be read
//              
// Returns
//    true if the value is a 1 
//    false if the value is a 0
//*****************************************************************************
bool  lp_io_read_pin(uint8_t pin_number)
{
  return GPIOF->DATA & (1 << pin_number);
}

/*********************************************************************************
* Summary:
* Configures the GPIO pins connected to the Launchpad LEDs and push buttons
*
********************************************************************************/
void lp_io_init(void)
{
	port_f_enable_port();
	port_f_digital_enable(RED_M | BLUE_M | GREEN_M | SW1_M | SW2_M);
	port_f_enable_output(RED_M | BLUE_M | GREEN_M);
	
	port_f_enable_input(SW1_M | SW2_M);
	port_f_enable_pull_up(SW1_M | SW2_M);
}

