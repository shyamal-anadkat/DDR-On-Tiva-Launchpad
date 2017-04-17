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
		
  
  // If the EEPROM is still writing the last byte written, wait
  eeprom_wait_for_write(i2c_base);
  
  //==============================================================
  // Send the Upper byte of the address
	// ADD CODE	
  //==============================================================

  //==============================================================
  // Send the Lower byte of the address
	// ADD CODE
  //==============================================================
  
  //==============================================================
  // Send the Byte of data to write
	// ADD CODE
  //==============================================================

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


  //==============================================================
  // Send the Upper byte of the address
	// ADD CODE
  //==============================================================


  //==============================================================
  // Send the Lower byte of the address
	// ADD CODE
  //==============================================================


  //==============================================================
  // Set the I2C slave address to be the EEPROM and in Read Mode
	// ADD CODE
  //==============================================================


  //==============================================================
  // Read the data returned by the EEPROM
	// ADD CODE
  //==============================================================
  
  return I2C_OK;
}

//*****************************************************************************
// Test the EEPROM
//*****************************************************************************
void test_eeprom(void)
{
  
  uint8_t write_data[EEPROM_TEST_NUM_BYTES];
  uint8_t read_data[EEPROM_TEST_NUM_BYTES];
  bool passed = true;
  int i;
  
		printf("==== Starting EEPROM Test ====\n\r");
	
  // Write data to the EEPROM
  for(i = 0; i < EEPROM_TEST_NUM_BYTES; i++)
  {
    write_data[i] = rand();
    eeprom_byte_write(EEPROM_I2C_BASE,i,write_data[i]);
  }

  // Read data back from the EEPROM
  for(i = 0; i < EEPROM_TEST_NUM_BYTES; i++)
  {
    eeprom_byte_read(EEPROM_I2C_BASE,i,&(read_data[i]));
  }
  
  // Verify that the bytes written match the bytes read
  for(i = 0; i < EEPROM_TEST_NUM_BYTES; i++)
  {
		printf("\tAddr 0x%04x.  write: 0x%02x read: 0x%02x\n\r", i, write_data[i], read_data[i]);
    if( write_data[i] != read_data[i])
    {
      passed = false;
    }
  }
  
  // Print if the test passed or failed.
  if ( passed == true)
  {
      printf("\tEEPROM Test Passed\n\r");
  }
  else
  {
      printf("\tEEPROM Test Failed\n\r");
  }
  
		printf("==== Stopping EEPROM Test ====\n\n\r");
}

