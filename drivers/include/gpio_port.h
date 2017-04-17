#ifndef __GPIO_PORT_F_H__
#define __GPIO_PORT_F_H__

#include "driver_defines.h"

/****************************************************************************
 * Return the GPIO IRQ Number
 ****************************************************************************/
IRQn_Type gpio_get_irq_num(uint32_t base);

//*****************************************************************************
// Enabling the clock for the port that was passed in.
//
// Paramters
//    baseAddr - Base address of GPIO port that is being enabled.
//
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
bool  gpio_enable_port(uint32_t baseAddr);


//*****************************************************************************
// Setting a pins as a digital enable requires writing to DEN register
//
// Paramters
//    baseAddr - Base address of GPIO port that is being enabled.
//    pins  -   A bit mask indicating which pins should be configured as digital
//              pins.  Modify only the bits where the bitmask is equal to 1.
//
// Use section 10.5 of the TM4C123 data sheet to determine the bits to set in 
// the DEN register.
//
//*****************************************************************************
bool  gpio_config_digital_enable(uint32_t baseAddr, uint8_t pins);


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
bool  gpio_config_enable_output(uint32_t baseAddr, uint8_t pins);


//*****************************************************************************
// Setting a GPIO pin as an input requires setting the DIR register
//
// Paramters
//    baseAddr - Base address of GPIO port that is being enabled.
//    pins  -   A bit mask indicating which pins should be configured as input
//              pins.  Modify only the bits where the bitmask is equal to 1.
//
// Use section 10.5 of the TM4C123 data sheet to determine the bits to set in 
// the DIR register.
//
//*****************************************************************************
bool gpio_config_enable_input(uint32_t baseAddr, uint8_t pins);


//*****************************************************************************
// Enabling a pull-up resistor requires setting the PUR regsiter
//
// Paramters
//    baseAddr - Base address of GPIO port that is being enabled.
//    pins  -   A bit mask indicating which pins should be configured with a 
//              pull-up resistor
//*****************************************************************************
bool  gpio_config_enable_pullup(uint32_t baseAddr, uint8_t pins);

//*****************************************************************************
// Enabling a pull-up resistor requires setting the PDR regsiter
//
// Paramters
//    baseAddr - Base address of GPIO port that is being enabled.
//    pins  -   A bit mask indicating which pins should be configured with a 
//              pull-down resistor
//*****************************************************************************
bool  gpio_config_enable_pulldown(uint32_t baseAddr, uint8_t pins);


//*****************************************************************************
// Configure pins as an analog input (AMSEL)
//
// Paramters
//    baseAddr - Base address of GPIO port that is being enabled.
//    pins  -   A bit mask indicating which pins should be configured as 
//              analog inputs
//*****************************************************************************
bool  gpio_config_analog_enable(uint32_t baseAddr, uint8_t pins);

//*****************************************************************************
// Configure pins as their alternate function (AFSEL)
//
// Paramters
//    baseAddr - Base address of GPIO port that is being enabled.
//    pins  -   A bit mask indicating which pins should be configured as 
//              alternate functions
//*****************************************************************************
bool  gpio_config_alternate_function(uint32_t baseAddr, uint8_t pins);

//*****************************************************************************
// Configure pins to set the specified port control register (PCTL)
//
// Paramters
//    baseAddr - Base address of GPIO port that is being enabled.
//    mask  -   A bit mask indicating which pins are being modified
//    pctl  -   The PCTL value to write into the register.
//*****************************************************************************
bool  gpio_config_port_control(uint32_t baseAddr, uint32_t mask, uint32_t pctl);

//*****************************************************************************
// Configure pins to be Open-Drain pins
//
// Paramters
//    baseAddr - Base address of GPIO port that is being enabled.
//    pins  -   A bit mask indicating which pins should be configured as 
//              opne-drain pins
//*****************************************************************************
bool  gpio_config_open_drain(uint32_t gpioBase, uint8_t pins);

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
bool  gpio_config_falling_edge_irq(uint32_t gpioBase, uint8_t pins);
#endif
