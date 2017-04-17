#include "lcd.h"

/*******************************************************************************
* Function Name: delayms
********************************************************************************
* Summary: Adds delay in between function calls.
* Return:
*  Nothing
*******************************************************************************/
static void delayms(uint16_t count)
{
    int i,j;                                                                                
    for(i=0;i<count;i++)                                                                    
       {
       for(j=0;j<5000;j++);
       }                                                                                     
}
/*******************************************************************************
* Function Name: lcd_write_cmd_u8
********************************************************************************
* Summary: Writes an 8-bit command used to identify which characteristic of the
*          LCD will be modified
* Return:
*  Nothing
*******************************************************************************/ 
__INLINE static void lcd_write_cmd_u8(uint8_t DL)
{
  // ADD CODE
  
  // Start a transaction to the LCD by setting LCD_CSX low
	LCD_CSX = 0;
	
  // Indicate this is a command by setting the value on the LCD_DCX GPIO Pin
	LCD_DCX = 0x00;
  
  // Send the 8 bits of the command
	LCD_DATA = DL;
  
  // Set the write signal LCD_WRX low
	LCD_WRX = 0;

  // Set the write signal LCD_WRX high
	LCD_WRX = 0xFF;

  // End the transaction to the LCD by setting LCD_CSX high
	LCD_CSX = 0xFF;
}

/*******************************************************************************
* Function Name: lcd_write_data_u8
********************************************************************************
* Summary: Writes 8-bits of data to the specified LCD characteristic
* Return:
*  Nothing
*******************************************************************************/ 
__INLINE static void  lcd_write_data_u8 (uint8_t x)
{
  // ADD CODE
  
  // Start a transaction to the LCD by setting LCD_CSX low
	LCD_CSX = 0;

  // Indicate this is a data packet by setting the value on the LCD_DCX GPIO Pin
	LCD_DCX = 0xFF;
  
  // Send the 8 bits of data
	LCD_DATA = x;
    
  // Set the write signal LCD_WRX low
	LCD_WRX = 0;

  // Set the write signal LCD_WRX high
	LCD_WRX = 0xFF;

  // End the transaction to the LCD by setting LCD_CSX high
	LCD_CSX = 0xFF;
}

/*******************************************************************************
* Function Name: lcd_write_data_u16
********************************************************************************
* Summary: 
* Return:
*  Nothing
*******************************************************************************/ 
__INLINE static void  lcd_write_data_u16(uint16_t y)
{
  // ADD CODE
  uint8_t DH = y>>8;      // Bits 15-8 of the pixel color
  uint8_t DL = y;        // Bits 7-0 of the pixel color

  // Start a transaction to the LCD by setting LCD_CSX low
  LCD_CSX = 0;
	
  // Indicate this is a data packet by setting the value on the LCD_DCX GPIO Pin
  LCD_DCX = 0xFF;
	
  // Send the upper 8 bits of the current pixel's color 
	LCD_DATA = DH;
	
  // Set the write signal LCD_WRX low
	LCD_WRX = 0;
	
  // Set the write signal LCD_WRX high
	LCD_WRX = 0xFF;
	
  // Send the lower 8 bits of the current pixel's color
	LCD_DATA = DL;
	
  // Set the write signal LCD_WRX low
	LCD_WRX = 0;

  // Set the write signal LCD_WRX high
	LCD_WRX = 0xFF;
	
  // End the transaction to the LCD by setting LCD_CSX high
	LCD_CSX = 0xFF;
}

/*******************************************************************************
* Function Name: lcd_set_pos
********************************************************************************
* Summary: Sets the boundries of the active portion of the screen.  When data
*          is written to the LCD, it will be written at addr of x0,y0.  
*
* Return:
*  Nothing
*******************************************************************************/
void lcd_set_pos(uint16_t x0,uint16_t x1,uint16_t y0,uint16_t y1)
{
  lcd_write_cmd_u8(LCD_CMD_SET_COLUMN_ADDR);
  lcd_write_data_u16(x0);
  lcd_write_data_u16(x1);
  lcd_write_cmd_u8(LCD_CMD_SET_PAGE_ADDR);
  lcd_write_data_u16(y0);
  lcd_write_data_u16(y1);
  lcd_write_cmd_u8(LCD_CMD_MEMORY_WRITE);
}

/*******************************************************************************
* Function Name: lcd_clear_screen
********************************************************************************
* Summary: clears the entire screen with the provided color.  
*
* Return:
*  Nothing
*******************************************************************************/
void lcd_clear_screen(uint16_t bColor)
{
  uint16_t i,j;
  lcd_set_pos(0,ROWS - 1, 0,COLS - 1);
  
  for (i=0;i< COLS ;i++)
  {
        for(j= 0; j < ROWS; j++)
        {
            lcd_write_data_u16(bColor);
        }
  }
}

/*******************************************************************************
* Function Name: lcd_draw_image
********************************************************************************
* Summary: Prints an image centered at the coordinates set by x_start, y_start
* Returns:
*  Nothing
*******************************************************************************/
void lcd_draw_image(
  uint16_t x_start, 
  uint16_t image_width_bits, 
  uint16_t y_start, 
  uint16_t image_height_pixels, 
  const uint8_t *image, 
  uint16_t fColor, 
  uint16_t bColor
)
{
  uint16_t i,j;
  uint8_t data;
  uint16_t byte_index;
  uint16_t bytes_per_row;
  uint16_t x0;
  uint16_t x1;
  uint16_t y0;
  uint16_t y1;
 
  x0 = x_start;
  x1 = x_start + image_width_bits-1;
  
  y0 = y_start;
  y1 = y_start  + image_height_pixels-1 ;
  
  lcd_set_pos(x0, x1, y0, y1);
  
  bytes_per_row = image_width_bits / 8;
  if( (image_width_bits % 8) != 0)
  {
    bytes_per_row++;
  }
  
  for (i=0;i< image_height_pixels ;i++)
  {
        for(j= 0; j < image_width_bits; j++)
        {
            if( (j %8) == 0)
            {
              byte_index = (i*bytes_per_row) + j/8;
              data = image[byte_index];
            }
            if ( data & 0x80)
            {
                lcd_write_data_u16(fColor);
            }
            else
            {
                lcd_write_data_u16(bColor);
            }
            data  = data << 1;
        }
  }
}



/*******************************************************************************
* Function Name: lcd_draw_pixel
********************************************************************************
* Summary: draws single pixel  
*
* Return:
*  Nothing
*******************************************************************************/
void lcd_draw_pixel(
  uint16_t x_start, 
  uint16_t image_width_bits, 
  uint16_t y_start, 
  uint16_t image_height_pixels, 
  uint16_t color
)
{
  uint16_t x0;
  uint16_t x1;
  uint16_t y0;
  uint16_t y1;
 
  x0 = x_start;
  x1 = x_start + image_width_bits-1;
  
  y0 = y_start;
  y1 = y_start  + image_height_pixels-1 ;
  
  lcd_set_pos(x0, x1, y0, y1);
	lcd_write_data_u16(color);
  
}

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
void lcd_config_gpio(void)
{
  // Configure Chip Select
  gpio_enable_port(LCD_CSX_GPIO_BASE);
  gpio_config_digital_enable( LCD_CSX_GPIO_BASE, LCD_CSX_PIN);
  gpio_config_enable_output( LCD_CSX_GPIO_BASE, LCD_CSX_PIN);
  gpio_config_enable_pullup( LCD_CSX_GPIO_BASE, LCD_CSX_PIN);
  LCD_CSX_PORT->DATA |= LCD_CSX_PIN;
  
  // Configure Data/Instruction Select
  gpio_enable_port(LCD_DCX_INSTR_GPIO_BASE);
  gpio_config_digital_enable( LCD_DCX_INSTR_GPIO_BASE, LCD_DCX_INSTR_PIN);
  gpio_config_enable_output( LCD_DCX_INSTR_GPIO_BASE, LCD_DCX_INSTR_PIN);
  gpio_config_enable_pullup( LCD_DCX_INSTR_GPIO_BASE, LCD_DCX_INSTR_PIN);
  LCD_DCX_INSTR_PORT->DATA &= ~LCD_DCX_INSTR_PIN;
  
  // Configure Write Signal
  gpio_enable_port(LCD_WRX_GPIO_BASE);
  gpio_config_digital_enable( LCD_WRX_GPIO_BASE, LCD_WRX_PIN);
  gpio_config_enable_output( LCD_WRX_GPIO_BASE, LCD_WRX_PIN);
  gpio_config_enable_pullup( LCD_WRX_GPIO_BASE, LCD_WRX_PIN);
  LCD_WRX_PORT->DATA |=  LCD_WRX_PIN;
  
  // Configure Read Signal
  gpio_enable_port(LCD_RDX_GPIO_BASE);
  gpio_config_digital_enable( LCD_RDX_GPIO_BASE, LCD_RDX_PIN);
  gpio_config_enable_output( LCD_RDX_GPIO_BASE, LCD_RDX_PIN);
  gpio_config_enable_pullup( LCD_RDX_GPIO_BASE, LCD_RDX_PIN);
  LCD_RDX_PORT->DATA |= LCD_RDX_PIN;
   
  // Configure the Data pins
  gpio_enable_port(LCD_DATA_GPIO_BASE);
  gpio_config_digital_enable( LCD_DATA_GPIO_BASE, LCD_DATA_PINS);
  gpio_config_enable_output( LCD_DATA_GPIO_BASE, LCD_DATA_PINS);
  gpio_config_enable_pullup( LCD_DATA_GPIO_BASE, LCD_DATA_PINS);
  LCD_DATA_PORT->DATA = 0x00;
}

/*******************************************************************************
* Function Name: lcd_config_screen
********************************************************************************
* Summary: After the configuration of the gpio pins, this function configures
*          the internal LCD controller chip.
* Returns:
*  Nothing
*******************************************************************************/  
void lcd_config_screen(void)

{   
  lcd_write_cmd_u8(LCD_CMD_SOFTWARE_RESET); //software reset
  delayms(5);

  lcd_write_cmd_u8(LCD_CMD_SLEEP_OUT);
  delayms(120);
   lcd_write_cmd_u8(0xCF);   
  lcd_write_data_u8(0x00); 
  lcd_write_data_u8(0x83); 
  lcd_write_data_u8(0X30);    
      
   lcd_write_cmd_u8(0xED);   
  lcd_write_data_u8(0x64); 
  lcd_write_data_u8(0x03); 
  lcd_write_data_u8(0X12); 
  lcd_write_data_u8(0X81); 
      
   lcd_write_cmd_u8(0xE8);   
  lcd_write_data_u8(0x85); 
  lcd_write_data_u8(0x01); 
  lcd_write_data_u8(0x79); 
      
   lcd_write_cmd_u8(0xCB);   
  lcd_write_data_u8(0x39); 
  lcd_write_data_u8(0x2C); 
  lcd_write_data_u8(0x00); 
  lcd_write_data_u8(0x34); 
  lcd_write_data_u8(0x02); 
      
   lcd_write_cmd_u8(0xF7);   
  lcd_write_data_u8(0x20); 
      
   lcd_write_cmd_u8(0xEA);   
  lcd_write_data_u8(0x00); 
  lcd_write_data_u8(0x00);  
    
   lcd_write_cmd_u8(LCD_CMD_POWER_CONTROL_2);    //Power control 
  lcd_write_data_u8(0x11);   //SAP[2:0];BT[3:0] 
      
   lcd_write_cmd_u8(LCD_CMD_VCOMM_CONTROL_1);    //VCM control 1 
  lcd_write_data_u8(0x34); 
  lcd_write_data_u8(0x3D); 
      
   lcd_write_cmd_u8(LCD_CMD_VCOMM_CONTROL_2);    //VCM control 2 
  lcd_write_data_u8(0xC0); 
    
   lcd_write_cmd_u8(LCD_CMD_MEMORY_ACCESS_CONTROL);    // Memory Access Control 
  lcd_write_data_u8(0xC8); 
      
   lcd_write_cmd_u8(LCD_CMD_PIXEL_FORMAT_SET);      // Pixel format 
  lcd_write_data_u8(0x55);  //16bit 
    
   lcd_write_cmd_u8(LCD_CMD_FRAME_CONTROL_NORMAL_MODE);        // Frame rate
  lcd_write_data_u8(0x00);   
  lcd_write_data_u8(0x1D);  //61Hz
      
   lcd_write_cmd_u8(0xB6);    // Display Function Control 
  lcd_write_data_u8(0x0A); 
  lcd_write_data_u8(0xA2); 
  lcd_write_data_u8(0x27);
  lcd_write_data_u8(0x00);

  lcd_write_cmd_u8(LCD_CMD_ENTRY_MODE_SET); //Entry mode 
  lcd_write_data_u8(0x07);
    
      
   lcd_write_cmd_u8(LCD_CMD_DISPLAY_FUNCTION_CONTROL);    // 3Gamma Function Disable 
  lcd_write_data_u8(0x08); 
      
   lcd_write_cmd_u8(LCD_CMD_GAMMA_SET);    //Gamma curve selected 
  lcd_write_data_u8(0x01); 
      

  lcd_write_cmd_u8(LCD_CMD_POSITIVE_GAMMA_CORRECTION); //positive gamma correction
  lcd_write_data_u8(0x1f);
  lcd_write_data_u8(0x1a);
  lcd_write_data_u8(0x18);
  lcd_write_data_u8(0x0a);
  lcd_write_data_u8(0x0f);
  lcd_write_data_u8(0x06);
  lcd_write_data_u8(0x45);
  lcd_write_data_u8(0x87);
  lcd_write_data_u8(0x32);
  lcd_write_data_u8(0x0a);
  lcd_write_data_u8(0x07);
  lcd_write_data_u8(0x02);
  lcd_write_data_u8(0x07);
  lcd_write_data_u8(0x05);
  lcd_write_data_u8(0x00);
  
  lcd_write_cmd_u8(LCD_CMD_NEGATIVE_GAMMA_CORRECTION); //negamma correction
  lcd_write_data_u8(0x00);
  lcd_write_data_u8(0x25);
  lcd_write_data_u8(0x27);
  lcd_write_data_u8(0x05);
  lcd_write_data_u8(0x10);
  lcd_write_data_u8(0x09);
  lcd_write_data_u8(0x3a);
  lcd_write_data_u8(0x78);
  lcd_write_data_u8(0x4d);
  lcd_write_data_u8(0x05);
  lcd_write_data_u8(0x18);
  lcd_write_data_u8(0x0d);
  lcd_write_data_u8(0x38);
  lcd_write_data_u8(0x3a);
  lcd_write_data_u8(0x1f);
      
   lcd_write_cmd_u8(LCD_CMD_SLEEP_OUT);    //Exit Sleep 
  delayms(120);
   lcd_write_cmd_u8(LCD_CMD_DISPLAY_ON);    //Display on 
  delayms(50);
  LCD_RDX=0xFF;  

}

