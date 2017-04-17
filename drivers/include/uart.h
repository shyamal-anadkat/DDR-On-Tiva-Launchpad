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

#ifndef __UART_H__
#define __UART_H__

#include "driver_defines.h"

//************************************************************************
// Configure a UART to be 115200, 8N1.  
//************************************************************************
bool uart_init(uint32_t uart_base, bool enable_rx_irq, bool enable_tx_irq);

/****************************************************************************
 * This routine transmits a character out the UART / COM port.
 * Only the lower 8 bits of the 'data' variable are transmitted.
 ****************************************************************************/
void uart_tx_poll(uint32_t base, char data);

/****************************************************************************
 * This routine transmits a single character out the UART / COM port.
 * Only the lower 8 bits of the 'data' variable are transmitted.
 ****************************************************************************/
void uart_tx_poll_string(uint32_t base, char *data);
  
/****************************************************************************
 * This routine returns a character received from the UART/COM port.
 * If blocking is enabled, this routine should not return until data
 * is available. If blocking is disabled and no data is available,
 * this function should return 0.
 ****************************************************************************/
char uart_rx_poll(uint32_t base, bool block);


/****************************************************************************
 * Verify that the uart base address is valid
 ****************************************************************************/
bool verify_uart_base(uint32_t base);

/****************************************************************************
 * Return the RCGC Mask
 ****************************************************************************/
uint32_t uart_get_rcgc_mask(uint32_t base);

/****************************************************************************
 * Return the PRUART Mask
 ****************************************************************************/
uint32_t uart_get_pr_mask(uint32_t base);

/****************************************************************************
 * Return the IRQ Number for the UART
 ****************************************************************************/
IRQn_Type uart_get_irq_num(uint32_t base);


#endif
