// Copyright (c) 2015, Joe Krachey
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

#include "driver_defines.h"

          
//*****************************************************************************
// Verifies that the base address is a valid GPIO base address
//*****************************************************************************
static bool verify_base_addr(uint32_t baseAddr)
{
   switch( baseAddr )
   {
     case GPIOA_BASE:
     case GPIOB_BASE:
     case GPIOC_BASE:
     case GPIOD_BASE:
     case GPIOE_BASE:
     case GPIOF_BASE:
     {
       return true;
     }
     default:
     {
       return false;
     }
   }
}

/****************************************************************************
 * Return the GPIO IRQ Number
 ****************************************************************************/
IRQn_Type gpio_get_irq_num(uint32_t base)
{
   switch(base)
   {
     case GPIOA_BASE:
     {
       return GPIOA_IRQn;
     }
     case GPIOB_BASE:
     {
       return GPIOB_IRQn;
     }
     case GPIOC_BASE:
     {
        return GPIOC_IRQn;
     }
     case GPIOD_BASE:
     {
       return GPIOD_IRQn;
     }
     case GPIOE_BASE:
     {
       return GPIOE_IRQn;
     }
     case GPIOF_BASE:
     {
       return GPIOF_IRQn;
     }
     default:
     {
       return 0;
     }
   }
}


//*****************************************************************************
// Enabling the clock for the port that was passed in.
//    1.  Verify that the address passed in is a valid base address for a 
//        GPIO Port.  See line 1545 of TM4C123GH6PM.h to a list of #defines
//        for valid GPIO Ports.
//
//    2. Turn on the clock for the given port in RGCGPIO
//
//        ../include/sysctrl.h contains many useful
//        #defines that will make your code more readable and less mistake prone.
//        Search for SYSCTL_RCGCGPIO in that file.
//
//        Example 
//        SYSCTL->RCGCGPIO |= SYSCTL_RCGCGPIO_R0;
//
//    2. Wait until the clock is on by checking PRGPIO
//
//        ../include/sysctrl.h contains many useful
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
__weak bool  gpio_enable_port(uint32_t baseAddr)
{
  uint32_t rcgc_mask = 0;
  uint32_t pr_mask = 0;
  
  // Verify that the base address and set rcgc_mask and pr_mask
   switch( baseAddr )
   {
     case GPIOA_BASE:
     {
       // Set rcgc_mask and pr_mask for GPIO Port A
					rcgc_mask =SYSCTL_RCGCGPIO_R0;
					pr_mask = SYSCTL_PRGPIO_R0;
       break;
     }
     case GPIOB_BASE:
     {
       // Set rcgc_mask and pr_mask for GPIO Port B
			 	  rcgc_mask =SYSCTL_RCGCGPIO_R1;
					pr_mask = SYSCTL_PRGPIO_R1;
       break;
     }
     case GPIOC_BASE:
     {
       // Set rcgc_mask and pr_mask for GPIO Port C
			 	  rcgc_mask =SYSCTL_RCGCGPIO_R2;
					pr_mask = SYSCTL_PRGPIO_R2;
       break;
     }
     case GPIOD_BASE:
     {
       // Set rcgc_mask and pr_mask for GPIO Port D
			 	  rcgc_mask =SYSCTL_RCGCGPIO_R3;
					pr_mask = SYSCTL_PRGPIO_R3;
       break;
     }
     case GPIOE_BASE:
     {
       // Set rcgc_mask and pr_mask for GPIO Port E
			 	  rcgc_mask =SYSCTL_RCGCGPIO_R4;
					pr_mask = SYSCTL_PRGPIO_R4;
       break;
     }
     case GPIOF_BASE:
     {
       // Set rcgc_mask and pr_mask for GPIO Port F
			 	  rcgc_mask =SYSCTL_RCGCGPIO_R5;
					pr_mask = SYSCTL_PRGPIO_R5;
       break;
     }
     default:
     {
       return false;
     }
   }
   
   // Turn the clock on using the rcgc_mask
	   SYSCTL->RCGCGPIO |= rcgc_mask; 

   // Wait for the PRGPIO to indicate the port is ready
			while( (SYSCTL->PRGPIO & pr_mask) == 0) 
				{}	
    
   // If PortD set the LOCK and CR registers
   if(baseAddr == GPIOD_BASE )
  {
     GPIO_PORTD_LOCK_R = 0x4C4F434B ;
     GPIO_PORTD_CR_R = 0xFF;
  }

   // If PortF set the LOCK and CR registers
  if(baseAddr == GPIOF_BASE )

  {
     GPIO_PORTF_LOCK_R = 0x4C4F434B ;
     GPIO_PORTF_CR_R = 0xFF;
  }
  
  return true;
}

//*****************************************************************************
// Setting a pins as a digital enable requires writing to DEN register
//
// Paramters
//    pins  -   A bit mask indicating which pins should be configured as digital
//              pins.  Modify only the bits where the bitmask is equal to 1.
//
// Use section 10.5 of the TM4C123 data sheet to determine the bits to set in 
// the DEN register.
//
//*****************************************************************************
__weak bool  gpio_config_digital_enable(uint32_t baseAddr, uint8_t pins)
{
  GPIOA_Type  *gpioPort;
  
  // Verify that the base address is a valid GPIO base address
  // using the verify_base_addr function provided above
  // Type Cast the base address to a GPIOA_Type pointer
	if(!verify_base_addr(baseAddr)) { return false; }
	
  gpioPort = (GPIOA_Type *)baseAddr;
  gpioPort->DEN |= pins;
  return true;
}

//*****************************************************************************
// Setting a GPIO pin as an output requires setting the DIR register
//
// Paramters
//    pins  -   A bit mask indicating which pins should be configured as output
//              pins.  Modify only the bits where the bitmask is equal to 1.
//
// Use section 10.5 of the TM4C123 data sheet to determine the bits to set in 
// the DIR register.
//*****************************************************************************
__weak bool  gpio_config_enable_output(uint32_t baseAddr, uint8_t pins)
{
  GPIOA_Type  *gpioPort;
  
  // Verify that the base address is a valid GPIO base address
  // using the verify_base_addr function provided above
	if(!verify_base_addr(baseAddr)) { return false; }
	gpioPort = (GPIOA_Type *)baseAddr;
	
	gpioPort->DIR |= pins;
  return true;
}

//*****************************************************************************
// Setting a GPIO pin as an input requires setting the DIR register
//
// Paramters
//    pins  -   A bit mask indicating which pins should be configured as input
//              pins.  Modify only the bits where the bitmask is equal to 1.
//
// Use section 10.5 of the TM4C123 data sheet to determine the bits to set in 
// the DIR register.
//
//*****************************************************************************
__weak bool  gpio_config_enable_input(uint32_t baseAddr, uint8_t pins)

{
  GPIOA_Type  *gpioPort;

  // Verify that the base address is a valid GPIO base address
  // using the verify_base_addr function provided above
	if(!verify_base_addr(baseAddr)) { return false; }
	gpioPort = (GPIOA_Type *)baseAddr;
	
	gpioPort->DIR &= ~pins;
  return true;
  
}


//*****************************************************************************
// Enabling a pull-up resistor requires setting the PUR regsiter
//
// Paramters
//    baseAddr - Base address of GPIO port that is being enabled.
//    pins  -   A bit mask indicating which pins should be configured with a 
//              pull-up resistor
//*****************************************************************************
__weak bool  gpio_config_enable_pullup(uint32_t baseAddr, uint8_t pins)
{
  GPIOA_Type  *gpioPort;

  // Verify that the base address is a valid GPIO base address
  // using the verify_base_addr function provided above
	if(!verify_base_addr(baseAddr)) { return false; }
	gpioPort = (GPIOA_Type *)baseAddr;
	
	gpioPort->PUR |= pins;
  return true;
}

//*****************************************************************************
// Enabling a pull-up resistor requires setting the PDR regsiter
//
// Paramters
//    baseAddr - Base address of GPIO port that is being enabled.
//    pins  -   A bit mask indicating which pins should be configured with a 
//              pull-down resistor
//*****************************************************************************
__weak bool  gpio_config_enable_pulldown(uint32_t baseAddr, uint8_t pins)
{
  GPIOA_Type  *gpioPort;

  // Verify that the base address is a valid GPIO base address
  // using the verify_base_addr function provided above
	if(!verify_base_addr(baseAddr)) { return false; }
  
	gpioPort = (GPIOA_Type *)baseAddr;
	gpioPort->PDR |= pins;
  return true;
}


//*****************************************************************************
__weak bool  gpio_config_analog_enable(uint32_t baseAddr, uint8_t pins)
{
  GPIOA_Type  *gpioPort;

  // Verify that the base address is a valid GPIO base address
  // using the verify_base_addr function provided above
	if(!verify_base_addr(baseAddr)) { return false; }
	gpioPort = (GPIOA_Type *)baseAddr;
	gpioPort->AMSEL |= pins;
	
  return true;
}

//*****************************************************************************
__weak bool  gpio_config_alternate_function(uint32_t baseAddr, uint8_t pins)
{
  GPIOA_Type  *gpioPort;

  // Verify that the base address is a valid GPIO base address
  // using the verify_base_addr function provided above
	if(!verify_base_addr(baseAddr)) { return false; }
	gpioPort = (GPIOA_Type *)baseAddr;
	gpioPort->AFSEL |= pins;
	
  return true;
}


//*****************************************************************************
bool  gpio_config_port_control(uint32_t baseAddr, uint32_t mask, uint32_t pctl)
{
   GPIOA_Type  *gpioPort;

  // Verify that the base address is a valid GPIO base address
  // using the verify_base_addr function provided above
  if(!verify_base_addr(baseAddr)) { return false; }
	gpioPort = (GPIOA_Type *)baseAddr;
	
	//clear bits
	gpioPort->PCTL &= ~(mask);
	
	gpioPort->PCTL |= (pctl);
  return true;
}

/******************************************************************************
 *
 *****************************************************************************/
bool  gpio_config_open_drain(uint32_t gpioBase, uint8_t pins)
{
  GPIOA_Type  *gpioPort;
	
  // Verify that the base address is a valid GPIO base address
  // using the verify_base_addr function provided above
	if(!verify_base_addr(gpioBase)) { return false; }
	gpioPort = (GPIOA_Type *)gpioBase;
	
	gpioPort->ODR |= (pins);
	
  return true;
}

//******************************************************************************
// Enabling a GPIO pin to generate and interrupt on the falling edge of a signal
//
// Paramters
//    baseAddr - Base address of GPIO port that is being enabled.
//    pins  -   A bit mask indicating which pins should be configured to 
//              generate a falling edge interrupt.  A 1 in the bitmask
//              indicates that the pin will generate an interrupt.  A 0 in the 
//              bit mask indicates that the pin should not be modifed from
//              its current configuration.
//
// Returns
//      true    if gpioBase is a valid GPIO Port  Address
//      false   if gpioBase is not a valid GPIO Port Address 
//*****************************************************************************
bool  gpio_config_falling_edge_irq(uint32_t gpioBase, uint8_t pins)
{
  // GPIOA_Type  *gpioPort;

  // Verify that the base address is a valid GPIO base address
  // using the verify_base_addr function provided above
	// if(!verify_base_addr(gpioBase)) { return false; }
	// gpioPort = (GPIOA_Type *)gpioBase;
  return true;
}
