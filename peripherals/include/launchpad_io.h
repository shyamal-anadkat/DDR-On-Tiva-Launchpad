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

#ifndef __LAUNCHPAD_IO__
#define __LAUNCHPAD_IO__
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#include "TM4C123.h"
#include "driver_defines.h"

// ADD CODE 01
#define   RED_BIT       1
#define   BLUE_BIT      2
#define   GREEN_BIT     3
#define   SW1_BIT       4
#define   SW2_BIT       0

#define   RED_M     (1 << RED_BIT)
#define   BLUE_M    (1 << BLUE_BIT)
#define   GREEN_M   (1 << GREEN_BIT)

#define   SW1_M     (1 << SW1_BIT)
#define   SW2_M     (1 << SW2_BIT)


/********************************************************************************
* Summary:
* Configures the GPIO pins connected to the Launchpad LEDs and push buttons
*
*******************************************************************************/
void lp_io_init(void);


//*****************************************************************************
// Sets a given GPIO pin to 1.  All other pins retain their value
//
// Paramters
//    pin_number  The pin number of port F to turn on
//              
//
//*****************************************************************************
void  lp_io_set_pin(uint8_t pin_number);

//*****************************************************************************
// Clears a given GPIO pin to 0.  All other pins retain their value
//
// Paramters
//    pin_number  The pin number of port F to turn off
//              
//
//*****************************************************************************
void  lp_io_clear_pin(uint8_t pin_number);

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
bool  lp_io_read_pin(uint8_t pin_number);


#endif
