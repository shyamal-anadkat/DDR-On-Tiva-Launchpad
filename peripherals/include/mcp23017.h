#ifndef __MCP23017_H__
#define __MCP23017_H__

#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "TM4C123.h"
#include "driver_defines.h"
#include "gpio_port.h"
#include "i2c.h"

#define BUTTON_UP 		0
#define BUTTON_DOWN 	1
#define BUTTON_LEFT 	2
#define BUTTON_RIGHT  3

#define LED0 0
#define LED1 1
#define LED2 2
#define LED3 3
#define LED4 4
#define LED5 5
#define LED6 6
#define LED7 7

#define	  MCP23017_DEV_ID	0x27

#define 	IOEXPANDER_GPIO_BASE	GPIOA_BASE
#define 	IOEXPANDER_I2C_BASE		I2C1_BASE

#define   IOEXPANDER_I2C_SCL_PIN       	PA6
#define   IOEXPANDER_I2C_SDA_PIN       	PA7
#define   IOEXPANDER_I2C_SCL_PCTL_M     GPIO_PCTL_PA6_M
#define   IOEXPANDER_I2C_SCL_PIN_PCTL 	GPIO_PCTL_PA6_I2C1SCL
#define   IOEXPANDER_I2C_SDA_PCTL_M     GPIO_PCTL_PA7_M
#define   IOEXPANDER_I2C_SDA_PIN_PCTL  	GPIO_PCTL_PA7_I2C1SDA

#define 	IO_LED_GPIO_BASE      0x12
#define 	IO_BUTTON_GPIO_BASE   0x13

#define 	IO_LED_DIR    0x00 
#define 	IO_BUTTON_DIR 0x01 


typedef enum {BTN_UP, BTN_DOWN, BTN_LEFT, BTN_RIGHT, NONE} button_dir_t;

//*****FUNCTION DECLARATIONS*****
bool ioexpander_init(); //default : I2C1 BASE

i2c_status_t ioexpander_byte_write( uint32_t  i2c_base, uint16_t  addr, uint8_t data);

i2c_status_t ioexpander_byte_read ( uint32_t  i2c_base, uint16_t  addr, uint8_t *data);

uint8_t detect_button_press(void);

void turn_on_all_leds(void);

void turn_off_leds(void);

void control_leds(uint8_t data);

button_dir_t is_button_pressed();

#endif