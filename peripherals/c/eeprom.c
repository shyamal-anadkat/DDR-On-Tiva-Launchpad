#include "eeprom.h"

//*****************************************************************************
// Used to determine if the EEPROM is busy writing the last transaction to 
// non-volatile storage
//
// Paramters
//    i2c_base:   a valid base address of an I2C peripheral
//
// Returns
// I2C_OK is returned one the EEPROM is ready to write the next byte
//*****************************************************************************
static 
i2c_status_t eeprom_wait_for_write( int32_t  i2c_base)
{
  
  i2c_status_t status;
  
  if( !i2cVerifyBaseAddr(i2c_base) )
  {
    return  I2C_INVALID_BASE;
  }

  // Set the I2C address to be the EEPROM and in Write Mode
  status = i2cSetSlaveAddr(i2c_base, MCP24LC32AT_DEV_ID, I2C_WRITE);

  // Poll while the device is busy.  The  MCP24LC32AT will not ACK
  // writing an address while the write has not finished.
  do 
  {
    // The data we send does not matter.  This has been set to 0x00, but could
    // be set to anything
    status = i2cSendByte( i2c_base, 0x00, I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP);
    
    // Wait for the address to finish transmitting
    while ( I2CMasterBusy(i2c_base)) {};
    
    // If the address was not ACKed, try again.
  } while (I2CMasterAdrAck(i2c_base) == false);

  return  status;
}
  
  
//*****************************************************************************
// Writes a single byte of data out to the  MCP24LC32AT EEPROM.  
//
// Paramters
//    i2c_base:   a valid base address of an I2C peripheral
//
//    address:    16-bit address of the byte being written.  Only the lower
//                12 bits is used by the EEPROM
//
//    data:       Data written to the EEPROM.
//
// Returns
// I2C_OK if the byte was written to the EEPROM.
//*****************************************************************************
i2c_status_t eeprom_byte_write
( 
  uint32_t  i2c_base,
  uint16_t  address,
  uint8_t   data
)
{
  i2c_status_t status;
  
  // Before doing anything, make sure the I2C device is idle
  while ( I2CMasterBusy(i2c_base)) {};

  //==============================================================
  // Set the I2C address to be the EEPROM
	// ADD CODE
  //==============================================================
	status = i2cSetSlaveAddr(i2c_base, MCP24LC32AT_DEV_ID, I2C_WRITE);
	if ( status != I2C_OK ){return status;}
  
  // If the EEPROM is still writing the last byte written, wait
  eeprom_wait_for_write(i2c_base);
  
  //==============================================================
  // Send the Upper byte of the address
	// ADD CODE	
  //==============================================================
	status = i2cSendByte(i2c_base,(uint8_t)(address >> 8), I2C_MCS_START | I2C_MCS_RUN);
	if ( status != I2C_OK ){return status;}
  //==============================================================
  // Send the Lower byte of the address
	// ADD CODE
  //==============================================================
	status = i2cSendByte(i2c_base, (uint8_t)address, I2C_MCS_RUN);
	if ( status != I2C_OK ){return status;}
  //==============================================================
  // Send the Byte of data to write
	// ADD CODE
  //==============================================================
	status = i2cSendByte(i2c_base, data, I2C_MCS_RUN | I2C_MCS_STOP);
	if ( status != I2C_OK ){return status;}
	
  return status;
}

//*****************************************************************************
// Reads a single byte of data from the  MCP24LC32AT EEPROM.  
//
// Paramters
//    i2c_base:   a valid base address of an I2C peripheral
//
//    address:    16-bit address of the byte being read.  Only the lower
//                12 bits is used by the EEPROM
//
//    data:       data read from the EEPROM is returned to a uint8_t pointer.
//
// Returns
// I2C_OK if the byte was read from the EEPROM.
//*****************************************************************************
i2c_status_t eeprom_byte_read
( 
  uint32_t  i2c_base,
  uint16_t  address,
  uint8_t   *data
)
{
  i2c_status_t status;
  
  // Before doing anything, make sure the I2C device is idle
  while ( I2CMasterBusy(i2c_base)) {};

  // If the EEPROM is still writing the last byte written, wait
  eeprom_wait_for_write(i2c_base);

  //==============================================================
  // Set the I2C slave address to be the EEPROM and in Write Mode
	// ADD CODE
  //==============================================================
	status = i2cSetSlaveAddr(i2c_base, MCP24LC32AT_DEV_ID, I2C_WRITE);
	if ( status != I2C_OK ){return status;}

  //==============================================================
  // Send the Upper byte of the address
	// ADD CODE
  //==============================================================
	status = i2cSendByte(
		i2c_base,
		(uint8_t)(address >> 8),
		I2C_MCS_START | I2C_MCS_RUN
	);
	if ( status != I2C_OK ){return status;}

  //==============================================================
  // Send the Lower byte of the address
	// ADD CODE
  //==============================================================
	status = i2cSendByte(i2c_base, (uint8_t)(address), I2C_MCS_RUN);
	if ( status != I2C_OK ){return status;}

  //==============================================================
  // Set the I2C slave address to be the EEPROM and in Read Mode
	// ADD CODE
  //==============================================================
	status = i2cSetSlaveAddr(i2c_base, MCP24LC32AT_DEV_ID, I2C_READ);
	if ( status != I2C_OK ){return status;}

  //==============================================================
  // Read the data returned by the EEPROM
	// ADD CODE
  //==============================================================
	status = i2cGetByte(i2c_base, data, I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP);
	if ( status != I2C_OK ){return status;}
	
  return I2C_OK;
}

//*****************************************************************************
// Initialize the I2C peripheral
//*****************************************************************************
bool eeprom_init(void)
{
  
  if(gpio_enable_port(EEPROM_GPIO_BASE) == false)
  {
    return false;
  }
  
  // Configure SCL 
  if(gpio_config_digital_enable(EEPROM_GPIO_BASE, EEPROM_I2C_SCL_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_alternate_function(EEPROM_GPIO_BASE, EEPROM_I2C_SCL_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_port_control(EEPROM_GPIO_BASE, EEPROM_I2C_SCL_PCTL_M, EEPROM_I2C_SCL_PIN_PCTL)== false)
  {
    return false;
  }
    

  
  // Configure SDA 
  if(gpio_config_digital_enable(EEPROM_GPIO_BASE, EEPROM_I2C_SDA_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_open_drain(EEPROM_GPIO_BASE, EEPROM_I2C_SDA_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_alternate_function(EEPROM_GPIO_BASE, EEPROM_I2C_SDA_PIN)== false)
  {
    return false;
  }
    
  if(gpio_config_port_control(EEPROM_GPIO_BASE, EEPROM_I2C_SDA_PCTL_M, EEPROM_I2C_SDA_PIN_PCTL)== false)
  {
    return false;
  }
    
  //  Initialize the I2C peripheral
  if( initializeI2CMaster(EEPROM_I2C_BASE)!= I2C_OK)
  {
    return false;
  }
  return true;
}

/*Writes the 2 byte high_score in the arg to the EEPROM */
void write_high_score(uint16_t high_score) {
	
    uint8_t hs[2];
    hs[0] = (uint8_t) high_score;
		hs[1] = (high_score) >> 8;
	
		printf("Writing score to eeprom : %d\n\r", high_score);
		//write the 2 bytes
    eeprom_byte_write(I2C1_BASE, HIGH_SCORE_ADDR_START , hs[1]);
	  eeprom_byte_write(I2C1_BASE, HIGH_SCORE_ADDR_END, hs[0]);
}

/* Reads the 2 byte high score from EEPROM */
uint16_t read_high_score(void) {
		uint16_t read_score;
		uint8_t read_val;
	
		//read the two bytes 
    eeprom_byte_read(I2C1_BASE,(HIGH_SCORE_ADDR_START), &read_val);
		read_score = read_val << 8;
		eeprom_byte_read(I2C1_BASE,(HIGH_SCORE_ADDR_END), &read_val);
		read_score += read_val; 
	
		printf("score read:  %d\n\r", read_score);
		return read_score;
}

void write_game_mode(uint8_t game_mode) {
		printf("Writing game mode to eeprom : %d\n\r", game_mode);
		//write the 1 byte
    eeprom_byte_write(I2C1_BASE, GAME_MODE_ADDR, game_mode);
}

uint8_t read_game_mode(void) {
		uint8_t read_val;
	
    eeprom_byte_read(I2C1_BASE,GAME_MODE_ADDR, &read_val);
		printf("game mode read:  %d\n\r", read_val);
		return read_val;
}