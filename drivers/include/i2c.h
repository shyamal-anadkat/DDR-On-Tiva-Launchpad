//*****************************************************************************
// i2c.h
// Author: jkrachey@wisc.edu
//*****************************************************************************

#ifndef __I2C_H__
#define __I2C_H__

#include <stdint.h>
#include <stdbool.h>
#include "TM4C123GH6PM.h"
#include "driver_defines.h"


typedef enum {
  I2C_OK, 
  I2C_NULL_PTR, 
  I2C_BUS_ERROR,
  I2C_ARBLST,
  I2C_ACK_RXED,
  I2C_NO_ACK,
  I2C_INVALID_BASE,
  I2C_INVALID_PARAM
} i2c_status_t;

typedef enum {
  I2C_READ  = I2C_MSA_RX,
  I2C_WRITE = I2C_MSA_TX
} i2c_read_write_t;


typedef struct {
  uint32_t    BaseAddr;
} I2C_CONFIG;

//*****************************************************************************
// Initializes a given I2C peripheral to operate at 100KHz.  This assumes
// MCU core is running at 50MHz
//
// Paramters:
//    base_addr:  The base address of the I2C peripheral that is being
//                configured
//
// Return Value:
//    Returns I2C_OK if the base address is a valid I2C peripheral
//    Returns I2C_INVALID_BASE if the base address is not a valid I2C address
//*****************************************************************************
i2c_status_t initializeI2CMaster(uint32_t base_addr);

//*****************************************************************************
// Sets the slave address that is currently being addressed.
//
// Paramters:
//    baseAddr:  The base address of the I2C peripheral that is being
//                configured
//    slaveAddr: The address of the slave device being accessed.  This is a 
//                7-bit slave address
//    readWrite: If the the transaction will be a read or write operation.
//               read = 0x01.  write = 0x00
// Return Value:
//    Returns I2C_OK if the base address is a valid I2C peripheral
//    Returns I2C_INVALID_BASE if the base address is not a valid I2C address
//*****************************************************************************
i2c_status_t i2cSetSlaveAddr(
  uint32_t baseAddr, 
  uint8_t slaveAddr,
  i2c_read_write_t readWrite
);


//*****************************************************************************
// Initiates a stop condition.  This function is used when the master does
// not receive and ACK.
//
// Paramters:
//    baseAddr:  The base address of the I2C peripheral that is being
//                configured
// Return Value:
//    Returns I2C_OK if the base address is a valid I2C peripheral
//    Returns I2C_INVALID_BASE if the base address is not a valid I2C address
//*****************************************************************************
i2c_status_t i2cStop(
  uint32_t baseAddr
)  ;

//*****************************************************************************
// Sends one byte of data over a I2C bus.  
//
// Paramters:
//    baseAddr:  The base address of the I2C peripheral that is being
//                configured
//    byte:      The next byte of the data transaction.
//    mcs:       Sets master control register of the I2C peripheral. Since a
//               data transaction can consist of multiple bytes, the value
//               of mcs is used to determine when start and stop bits are 
//               generated.
//
// Examples:
//    Sending control word (i2c address) + write 1st byte of data. This
//    assumes that additional bytes will follow in the transaction
//    i2cSendByte(I2C0_BASE, byte, I2C_MCS_START | I2C_MCS_RUN);
//
//    Sending a byte in the middle of a multi-byte operation. (> 2 bytes)
//    i2cSendByte(I2C0_BASE, byte, I2C_MCS_RUN);
//
//    Sending final byte  of data
//    i2cSendByte(I2C0_BASE, byte, I2C_MCS_RUN | I2C_MCS_STOP);
//
//    Sending control word (i2c address) + a single byte transaction.
//    i2cSendByte(I2C0_BASE, byte, I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP);
//
// Return Value:
//    Returns I2C_OK if the base address is a valid and the data was 
//    transmitted sucessfully.
//*****************************************************************************
i2c_status_t i2cSendByte(
  uint32_t baseAddr, 
  uint8_t byte, 
  uint8_t mcs
);

//*****************************************************************************
// Reads one byte of data over a I2C bus.  
//
// Paramters:
//    baseAddr:  The base address of the I2C peripheral that is being
//                configured
//    data:      The data read by the transaction.
//    mcs:       Sets master control register of the I2C peripheral. Since a
//               data transaction can consist of multiple bytes, the value
//               of mcs is used to determine when start and stop bits are 
//               generated.
//
// Examples:
//    * Sending control word (i2c address) + read 1st byte of data. This
//    * assumes that additional bytes be read after this byte.  This
//    * would be used for reading multiple bytes at consecutive addresses
//    * in the slave address.  
//    i2cGetByte(I2C0_BASE, byte, I2C_MCS_START | I2C_MCS_RUN);
//
//    * Reading a byte in the middle of a multi-byte operation. (> 2 bytes)
//    i2cGetByte(I2C0_BASE, byte, I2C_MCS_RUN);
//
//    * Reading final byte of data in a multi-byte read 
//    i2cGetByte(I2C0_BASE, byte, I2C_MCS_RUN | I2C_MCS_STOP);
//
//    * Sending control word (i2c address) + reading a single byte read.
//    i2cGetByte(I2C0_BASE, byte, I2C_MCS_START | I2C_MCS_RUN | I2C_MCS_STOP);
//
// Return Value:
//    Returns I2C_OK if the base address is a valid and the data was 
//    transmitted sucessfully.
//*****************************************************************************
i2c_status_t i2cGetByte(
  uint32_t baseAddr, 
  uint8_t *data, 
  uint8_t mcs
) ;

//*****************************************************************************
// Determines if the last byte of data transmitted was ACKed.  
//
// Paramters:
//    baseAddr:  The base address of the I2C peripheral that is being accessed
//
// Returns
//    Returns true if the data was ACKed
//    Returns false if the data was not ACKed or i2c_base is invalid
//*****************************************************************************
bool
I2CMasterDatAck(
uint32_t i2c_base
);

//*****************************************************************************
// Determines if the address (control word) was ACKed.  
//
// Paramters:
//    baseAddr:  The base address of the I2C peripheral that is being accessed
//
// Returns
//    Returns true if the address was ACKed
//    Returns false if the address was not ACKed or i2c_base is invalid
//*****************************************************************************
bool
I2CMasterAdrAck(
uint32_t i2c_base
);

//*****************************************************************************
// Determines if the I2C device is busy transmitting data.  
//
// Paramters:
//    baseAddr:  The base address of the I2C peripheral that is being accessed
//
// Returns
//    Returns true if the I2C device is busy
//    Returns false if the I2C device is NOT busy or i2c_base is invalid
//*****************************************************************************
bool
I2CMasterBusy(
uint32_t i2c_base
);

//*****************************************************************************
// verifies if the base addressed passed to a function is a valid I2C address
//*****************************************************************************
bool
i2cVerifyBaseAddr(
  uint32_t i2c_base
);

#endif
