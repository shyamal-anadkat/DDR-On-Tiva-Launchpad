#include "mcp23017.h"

//uint8_t multi_button_val = BTN_NONE;

extern bool debugFlag;

/*IO EXPANDER INIT FOR LEDs AND PUSH BUTTONS*/
bool ioexpander_init()
{
	i2c_status_t status;
	
	if(gpio_enable_port(IOEXPANDER_GPIO_BASE) == false){ return false;}
	
	// Configure SCL 
  if(gpio_config_digital_enable(IOEXPANDER_GPIO_BASE, IOEXPANDER_I2C_SCL_PIN)== false){ return false; }
  if(gpio_config_alternate_function(IOEXPANDER_GPIO_BASE, IOEXPANDER_I2C_SCL_PIN)== false){ return false; }
  if(gpio_config_port_control(IOEXPANDER_GPIO_BASE, IOEXPANDER_I2C_SCL_PCTL_M, IOEXPANDER_I2C_SCL_PIN_PCTL)== false) {return false; }
    
  // Configure SDA 
  if(gpio_config_digital_enable(IOEXPANDER_GPIO_BASE, IOEXPANDER_I2C_SDA_PIN)== false){return false;}
  if(gpio_config_open_drain(IOEXPANDER_GPIO_BASE, IOEXPANDER_I2C_SDA_PIN)== false){return false; }  
  if(gpio_config_alternate_function(IOEXPANDER_GPIO_BASE, IOEXPANDER_I2C_SDA_PIN)== false){return false;}
	if(gpio_config_port_control(IOEXPANDER_GPIO_BASE, IOEXPANDER_I2C_SDA_PCTL_M, IOEXPANDER_I2C_SDA_PIN_PCTL)== false){return false;}
    
  // Initialize the I2C peripheral
  if( initializeI2CMaster(IOEXPANDER_I2C_BASE)!= I2C_OK){ return false;}
	
	// LED - DIR 
	status = ioexpander_byte_write(IOEXPANDER_I2C_BASE, IO_LED_DIR, 0x00);
	if(status != I2C_OK) return false;
	
	// TURN ALL LEDS ON
	status = ioexpander_byte_write(IOEXPANDER_I2C_BASE, IO_LED_GPIO_BASE ,0xFF);
	if(status != I2C_OK) return false;
	
	// FOR PUSH BUTTONS 
	i2cSetSlaveAddr(IOEXPANDER_I2C_BASE, MCP23017_DEV_ID, I2C_WRITE);
	i2cSendByte(IOEXPANDER_I2C_BASE, 0x0D, I2C_MCS_START | I2C_MCS_RUN);
	i2cSendByte(IOEXPANDER_I2C_BASE, 0x0F, I2C_MCS_RUN | I2C_MCS_STOP);

	return true;
}


/*	BYTE WRITE - SIMILAR TO EEPROM - NO WAIT*/
i2c_status_t ioexpander_byte_write( uint32_t  i2c_base, 
																		uint16_t  addr, 
																		uint8_t data) {
	i2c_status_t status;
  
  // Before doing anything, make sure the I2C device is idle
  while ( I2CMasterBusy(i2c_base)) {};

  //==============================================================
  // Set the I2C address to be the MCP23017
  //==============================================================
	status = i2cSetSlaveAddr(i2c_base, MCP23017_DEV_ID, I2C_WRITE);
	if ( status != I2C_OK ){return status;}
  
  //==============================================================
  // Send the Lower byte of the address
  //==============================================================
	status = i2cSendByte(i2c_base, (uint8_t)addr, I2C_MCS_START | I2C_MCS_RUN);
	if ( status != I2C_OK ){return status;}
	
  //==============================================================
  // Send the Byte of data to write
  //==============================================================
	status = i2cSendByte(i2c_base, data, I2C_MCS_RUN | I2C_MCS_STOP);
	if ( status != I2C_OK ){return status;}
	
  return status;
}
																		
/*	BYTE READ - SIMILAR TO EEPROM - NO WAIT */
i2c_status_t ioexpander_byte_read
( 
  uint32_t  i2c_base,
  uint16_t  addr,
  uint8_t   *data
) {
	
i2c_status_t status;
  
  // Before doing anything, make sure the I2C device is idle
  while ( I2CMasterBusy(i2c_base)) {};

  //==============================================================
  // Set the I2C slave address to be the EEPROM and in Write Mode
  //==============================================================
	status = i2cSetSlaveAddr(i2c_base, MCP23017_DEV_ID, I2C_WRITE);
	if ( status != I2C_OK ){return status;}

  //==============================================================
  // Send the Lower byte of the address
  //==============================================================
	status = i2cSendByte(i2c_base, (uint8_t)(addr), I2C_MCS_START | I2C_MCS_RUN);
	if ( status != I2C_OK ){return status;}

  //==============================================================
  // Set the I2C slave address to be the EEPROM and in Read Mode
  //==============================================================
	status = i2cSetSlaveAddr(i2c_base, MCP23017_DEV_ID, I2C_READ);
	if ( status != I2C_OK ){return status;}

  //==============================================================
  // Read the data returned by the EEPROM
  //==============================================================
	status = i2cGetByte(i2c_base, data, I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP);
	
  return status;
}
												

//*****************************************************************************
// PORT EXPANDER (DIRECTIONAL BUTTON PAD) FUNCTIONALITY
//*****************************************************************************

/*returns data returned by button presses*/
/* CHECK MACROS FOR UINT8_VALUES FOR BUTTON COMBINATIONS */
uint8_t get_button_data() {
	uint8_t data;
	
	//wait
	while(I2CMasterBusy(I2C1_BASE));

	//GPIOB read
	i2cSetSlaveAddr(I2C1_BASE, MCP23017_DEV_ID, I2C_WRITE);
	i2cSendByte(I2C1_BASE, IO_BUTTON_GPIO_BASE, I2C_MCS_START | I2C_MCS_RUN);
	i2cSetSlaveAddr(I2C1_BASE, MCP23017_DEV_ID, I2C_READ);
	i2cGetByte(I2C1_BASE, &data, I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_DATACK | I2C_MCS_STOP);
	return data;
}

uint8_t debounce_expander_fsm(uint8_t buttons_pressed) {
	static DEBOUNCE_STATES debounce_state = DEBOUNCE_ONE;	
	static uint8_t curr_btn_val = BTN_NONE;
	static uint8_t last_btn_val = BTN_NONE;
		
	curr_btn_val = buttons_pressed;
	
	switch(debounce_state) {
		case DEBOUNCE_ONE:
			if(curr_btn_val != BTN_NONE) {
				debounce_state = DEBOUNCE_1ST_ZERO;
				last_btn_val = curr_btn_val;
			}
			return BTN_NONE;
			
		case DEBOUNCE_1ST_ZERO:
			if(curr_btn_val == last_btn_val) debounce_state = DEBOUNCE_2ND_ZERO;
			else {
				last_btn_val = curr_btn_val;
				debounce_state = DEBOUNCE_ONE;
			}
			break;
			
		case DEBOUNCE_2ND_ZERO:
			if(curr_btn_val == last_btn_val) debounce_state = DEBOUNCE_PRESSED;
			else {
				last_btn_val = curr_btn_val;
				debounce_state = DEBOUNCE_ONE;
			}
			return BTN_NONE;
			
		case DEBOUNCE_PRESSED:
			if(curr_btn_val == last_btn_val) {
				debounce_state = DEBOUNCE_DONE;
			}
			else {
				last_btn_val = curr_btn_val;
				debounce_state = DEBOUNCE_ONE;
			}
			return curr_btn_val;
			
		case DEBOUNCE_DONE:
			if(curr_btn_val == last_btn_val) {
				debounce_state = DEBOUNCE_DONE;
			}
			else {
				last_btn_val = curr_btn_val;
				debounce_state = DEBOUNCE_ONE;
			}
			return BTN_NONE;
	}
	
}


/* tells us which button is pressed. please use the enum AARON !! */
uint8_t buttons_pressed() {
	
	uint8_t btn_data = debounce_expander_fsm(get_button_data());
	
	if(debugFlag) {
		switch( btn_data ){
			case BTN_D:
				printf("DOWN BTN PRESSED\n");
				break;
			case BTN_U:
				printf("UP BTN PRESSED\n");
				break;
			case BTN_L:
				printf("LEFT BTN PRESSED\n");
				break;
			case BTN_R:
				printf("RIGHT BTN PRESSED\n");
				break;
			case BTN_UD:
				printf("BTN_UD PRESSED\n");
				break;
			case BTN_UL:
				printf("BTN_UL PRESSED\n");
				break;
			case BTN_UR:
				printf("BTN_UR PRESSED\n");
				break;
			case BTN_LR:
				printf("BTN_LR PRESSED\n");
				break;
			case BTN_LD:
				printf("BTN_LD PRESSED\n");
				break;
			case BTN_DR:
				printf("BTN_DR PRESSED\n");
				break;
			default:
				//printf("NONE\n");
				break;
		}
	}
	
	return btn_data;

}

//*****************************************************************************
// PORT EXPANDER LED FUNCTIONALITY
//*****************************************************************************

/* turns off all LEDs by writing a 0x00 */
void turn_off_leds() {
	ioexpander_byte_write(IOEXPANDER_I2C_BASE, IO_LED_GPIO_BASE ,0x00);
}

/* turns on all LEDs by writing a 0xFF */
void turn_on_all_leds() {
	ioexpander_byte_write(IOEXPANDER_I2C_BASE, IO_LED_GPIO_BASE ,0xFF);
}

/* control led custom function */
void control_leds(uint8_t data) {
	ioexpander_byte_write(IOEXPANDER_I2C_BASE, IO_LED_GPIO_BASE , data);
}


