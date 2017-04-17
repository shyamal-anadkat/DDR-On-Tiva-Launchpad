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

#ifndef __LCD_H__
#define __LCD_H__

#include <stdint.h>
#include "driver_defines.h"
#include "gpio_port.h"

typedef enum {
  LEFT,
  RIGHT,
  CENTER
} lcd_justify_t;

#define LINE_HIGH     0xFF
#define LINE_LOW      0x00

#define ROUNDED_CORNERS  true
#define SQUARE_CORNERS   false
#define DELAY 100
#define ROWS  240
#define COLS  320
#define ROW_COUNT  1

#define ROUND_NONE    0
#define ROUNDED_LEFT  1
#define ROUNDED_RIGHT 2

#define LCD_COLOR_WHITE			0xFFFF
#define LCD_COLOR_BLACK			0x0000
#define LCD_COLOR_RED			  0xF800
#define LCD_COLOR_GREEN			0x07E0
#define LCD_COLOR_GREEN2		0xB723
#define LCD_COLOR_BLUE			0x001F
#define LCD_COLOR_BLUE2			0x051D
#define LCD_COLOR_YELLOW		0xFFE0
#define LCD_COLOR_ORANGE		0xFBE4
#define LCD_COLOR_CYAN			0x07FF
#define LCD_COLOR_MAGENTA		0xA254
#define LCD_COLOR_GRAY			0x7BEF 
#define LCD_COLOR_BROWN			0xBBCA



#define LCD_CMD_NOOP                            0x00
#define LCD_CMD_SOFTWARE_RESET                  0x01
#define LCD_CMD_READ_DISPLAY_INFO               0x04
#define LCD_CMD_READ_DISPLAY_STATUS             0x09
#define LCD_CMD_READ_DISPLAY_POWER_MODE         0x0A
#define LCD_CMD_READ_MADCTL                     0x0B
#define LCD_CMD_READ_DISPLAY_PIXEL_FORMAT       0x0C
#define LCD_CMD_READ_DISPLAY_IMAGE_FORMAT       0x0D
#define LCD_CMD_READ_DISPLAY_SIGNAL_FORMAT      0x0E
#define LCD_CMD_READ_DISPLAY_DIAGNOSTICS        0x0F
#define LCD_CMD_ENTER_SLEEP_MODE                0x10
#define LCD_CMD_SLEEP_OUT                       0x11
#define LCD_CMD_PARTIAL_MODE_ON                 0x12
#define LCD_CMD_NORMAL_DISPLAY_MODE_ON          0x13
#define LCD_CMD_DISPLAY_INVERSION_OFF           0x20
#define LCD_CMD_DISPLAY_INVERSION_ON            0x21
#define LCD_CMD_GAMMA_SET                       0x26
#define LCD_CMD_DISPLAY_OFF                     0x28
#define LCD_CMD_DISPLAY_ON                      0x29
#define LCD_CMD_SET_COLUMN_ADDR                 0x2A
#define LCD_CMD_SET_PAGE_ADDR                   0x2B
#define LCD_CMD_MEMORY_WRITE                    0x2C
#define LCD_CMD_COLOR_SET                       0x2D
#define LCD_CMD_MEMORY_READ                     0x2E
#define LCD_CMD_PARTIAL_AREA                    0x30
#define LCD_CMD_VERTICAL_SCROLL_DEFINITION      0x33
#define LCD_CMD_TEARING_EFFECT_LINE_OFF         0x34
#define LCD_CMD_TEARING_EFFECT_LINE_ON          0x35
#define LCD_CMD_MEMORY_ACCESS_CONTROL           0x36
#define LCD_CMD_VERTICAL_SCROLLING_START        0x37
#define LCD_CMD_IDLE_MODE_OFF                   0x38
#define LCD_CMD_IDLE_MODE_ON                    0x39
#define LCD_CMD_PIXEL_FORMAT_SET                0x3A
#define LCD_CMD_WRITE_MEMORY_CONTINUE           0x3C
#define LCD_CMD_READ_MEMORY_CONTINUE        		0x3E
#define LCD_CMD_SET_TEAR_SCANLINE            		0x44
#define LCD_CMD_GET_SCANLINE                		0x45
#define LCD_CMD_WRITE_DISPLAY_BRIGHTNESS        0x51
#define LCD_CMD_READ_DISPLAY_BRIGHTNESS         0x52
#define LCD_CMD_WRITE_CTRL_DISPLAY              0x53
#define LCD_CMD_READ_CTRL_DISPLAY               0x54
#define LCD_CMD_WRITE_CONTENT_ADAPTIVE_STUFF    0x55
#define LCD_CMD_READ_CONTENT_ADAPTIVE_STUFF     0x56
#define LCD_CMD_WRITE_CABC_MINIMUM_BRIGHTNESS   0x5E
#define LCD_CMD_READ_CABC_MINIMUM_BRIGHTNESS    0x5F
#define LCD_CMD_READ_ID1                				0xDA
#define LCD_CMD_READ_ID2                				0xDB
#define LCD_CMD_READ_ID3                				0xDC
#define LCD_CMD_RGB_INTERFACE_CONTROL_SIGNAL    0xB0
#define LCD_CMD_FRAME_CONTROL_NORMAL_MODE       0xB1
#define LCD_CMD_FRAME_CONTROL_IDLE_MODE         0xB2
#define LCD_CMD_FRAME_CONTROL_PARTIAL_MODE      0xB3
#define LCD_CMD_DISPLAY_INVERSION_MODE          0xB4
#define LCD_CMD_BLANKING_PORCH_CONTROL          0xB5
#define LCD_CMD_DISPLAY_FUNCTION_CONTROL        0xB6
#define LCD_CMD_ENTRY_MODE_SET                  0xB7
#define LCD_CMD_BACKLIGHT_CONTROL_1             0xB8
#define LCD_CMD_BACKLIGHT_CONTROL_2             0xB9
#define LCD_CMD_BACKLIGHT_CONTROL_3             0xBA
#define LCD_CMD_BACKLIGHT_CONTROL_4             0xBB
#define LCD_CMD_BACKLIGHT_CONTROL_5             0xBC
#define LCD_CMD_BACKLIGHT_CONTROL_6             0xBD
#define LCD_CMD_BACKLIGHT_CONTROL_7             0xBE
#define LCD_CMD_BACKLIGHT_CONTROL_8             0xBF
#define LCD_CMD_POWER_CONTROL_1                 0xC0
#define LCD_CMD_POWER_CONTROL_2                 0xC1
#define LCD_CMD_VCOMM_CONTROL_1                 0xC5
#define LCD_CMD_VCOMM_CONTROL_2                 0xC7
#define LCD_CMD_NV_MEMORY_WRITE                 0xD0
#define LCD_CMD_NV_MEMORY_PROTECTION_KEY        0xD1
#define LCD_CMD_NV_MEMORY_STATUS_READ           0xD2
#define LCD_CMD_READ_ID4                        0xD3
#define LCD_CMD_POSITIVE_GAMMA_CORRECTION       0xE0  
#define LCD_CMD_NEGATIVE_GAMMA_CORRECTION       0xE1  
#define LCD_CMD_DIGITAL_GAMMA_CONTROL_1         0xE2
#define LCD_CMD_DIGITAL_GAMMA_CONTROL_2         0xE3
#define LCD_CMD_INTERFACE_CONTROL               0xF6


#define LCD_CSX_PIN          (1 << 4)
#define LCD_CSX_GPIO_BASE    GPIOC_BASE
#define LCD_CSX_PORT        GPIOC

#define LCD_DCX_INSTR_PIN          (1 << 5)
#define LCD_DCX_INSTR_GPIO_BASE    GPIOC_BASE
#define LCD_DCX_INSTR_PORT         GPIOC
#define LCD_DATA_PACKET            0xFF
#define LCD_CMD_PACKET             0x00

#define LCD_WRX_PIN               (1 << 6)
#define LCD_WRX_GPIO_BASE         GPIOC_BASE
#define LCD_WRX_PORT              GPIOC

#define LCD_RDX_PIN                (1 << 7)
#define LCD_RDX_GPIO_BASE          GPIOC_BASE
#define LCD_RDX_PORT               GPIOC
  
#define LCD_DATA_PINS                0xFF
#define LCD_DATA_GPIO_BASE           GPIOB_BASE
#define LCD_DATA_PORT                GPIOB

// ADD CODE
#define LCD_CSX                     (*((volatile unsigned long *)0x40006040))
#define LCD_DCX                     (*((volatile unsigned long *)0x40006080))
#define LCD_WRX                     (*((volatile unsigned long *)0x40006100))
#define LCD_RDX                     (*((volatile unsigned long *)0x40006200))
#define LCD_DATA                    (*((volatile unsigned long *)0x400053FC))
	


/*******************************************************************************
* Function Name: lcd_set_pos
********************************************************************************
* Summary: Sets the boundries of the active portion of the screen.  When data
*          is written to the LCD, it will be written at addr of x0,y0.  
*
* Return:
*  Nothing
*******************************************************************************/
void lcd_set_pos(
  uint16_t x0,    // X coordinate for the start of the box
  uint16_t x1,    // X coordinate for the end of the box
  uint16_t y0,    // Y coordinate for the start of the box
  uint16_t y1     // Y coordinate for the end of the box
);

/*******************************************************************************
* Function Name: lcd_clear_screen
********************************************************************************
* Summary: clears the entire screen with the provided color.  
*
* Return:
*  Nothing
*******************************************************************************/
void lcd_clear_screen(
  uint16_t bColor   //  Color to paint the entire screen with
);


/*******************************************************************************
* Function Name: lcd_draw_box
********************************************************************************
* Summary: Draws an outline of a box.  The user specifies the width and color
*          of the border and the color to paint the inside of the box.
* Returns:
*  Nothing
*******************************************************************************/
void lcd_draw_box(
  uint16_t x_start,       // X coordinate for the starting address of the box
  uint16_t x_len,         // Length of the box in pixels
  uint16_t y_start,       // Y coordinate for the starting address of the box
  uint16_t y_len,         // Height of the box in pixels
  uint16_t fg_color,      // Border Color
  uint16_t bg_color,      // Fill Color
  uint16_t border_width   // Border Width in pixels
);

/*******************************************************************************
* Function Name: lcd_draw_image
********************************************************************************
* Summary: Prints an image centered at the coordinates set by x_start, y_start
* Returns:
*  Nothing
*******************************************************************************/
void lcd_draw_image(
  uint16_t x_start,                 // X coordinate starting address
  uint16_t image_width_bits,        // image width
  uint16_t y_start,                 // Y coordinate starting address
  uint16_t image_height_pixels,     // image height
  const uint8_t *image,             // bitmap of the image
  uint16_t fColor,                  // foreground color
  uint16_t bColor                   // background color
);

/*******************************************************************************
* Function Name: lcd_config_gpio
********************************************************************************
* Summary: Configures the GPIO pins used to implement the 8080 interface on the
*          LCD display
*
* Parameters 
*
* Return:
*  Nothing
*******************************************************************************/
void lcd_config_gpio(void);
  
/*******************************************************************************
* Function Name: lcd_config_screen
********************************************************************************
* Summary: After the configuration of the gpio pins, this function configures
*          the internal LCD controller chip.
* Returns:
*  Nothing
*******************************************************************************/  
void lcd_config_screen(void);

void lcd_draw_pixel(
  uint16_t x_start, 
  uint16_t image_width_bits, 
  uint16_t y_start, 
  uint16_t image_height_pixels, 
  uint16_t color
);

#endif

