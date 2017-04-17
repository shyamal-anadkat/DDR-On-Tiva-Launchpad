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

#include "uart.h"

/****************************************************************************
 * Verify that the uart base address is valid
 ****************************************************************************/
bool verify_uart_base(uint32_t base)
{
   switch(base)
   {
     case UART0_BASE:
     case UART1_BASE:
     case UART2_BASE:
     case UART3_BASE:
     case UART4_BASE:
     case UART5_BASE:
     case UART6_BASE:
     case UART7_BASE:
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
 * Return the RCGC Mask
 ****************************************************************************/
uint32_t uart_get_rcgc_mask(uint32_t base)
{
   switch(base)
   {
     case UART0_BASE:
     {
       return SYSCTL_RCGCUART_R0;
     }
     case UART1_BASE:
     {
       return SYSCTL_RCGCUART_R1;
     }
     case UART2_BASE:
     {
        return SYSCTL_RCGCUART_R2;
     }
     case UART3_BASE:
     {
       return SYSCTL_RCGCUART_R3;
     }
     case UART4_BASE:
     {
       return SYSCTL_RCGCUART_R4;
     }
     case UART5_BASE:
     {
       return SYSCTL_RCGCUART_R5;
     }
     case UART6_BASE:
     {
       return SYSCTL_RCGCUART_R6;
     }
     case UART7_BASE:
     {
       return SYSCTL_RCGCUART_R7;
     }
     default:
     {
       return 0;
     }
   }
}


/****************************************************************************
 * Return the RCGC Mask
 ****************************************************************************/
uint32_t uart_get_pr_mask(uint32_t base)
{
   switch(base)
   {
     case UART0_BASE:
     {
       return SYSCTL_PRUART_R0;
     }
     case UART1_BASE:
     {
       return SYSCTL_PRUART_R1;
     }
     case UART2_BASE:
     {
        return SYSCTL_PRUART_R2;
     }
     case UART3_BASE:
     {
       return SYSCTL_PRUART_R3;
     }
     case UART4_BASE:
     {
       return SYSCTL_PRUART_R4;
     }
     case UART5_BASE:
     {
       return SYSCTL_PRUART_R5;
     }
     case UART6_BASE:
     {
       return SYSCTL_PRUART_R6;
     }
     case UART7_BASE:
     {
       return SYSCTL_PRUART_R7;
     }
     default:
     {
       return 0;
     }
   }
}

/****************************************************************************
 * Return the IRQ Number
 ****************************************************************************/
IRQn_Type uart_get_irq_num(uint32_t base)
{
   switch(base)
   {
     case UART0_BASE:
     {
       return UART0_IRQn;
     }
     case UART1_BASE:
     {
       return UART1_IRQn;
     }
     case UART2_BASE:
     {
        return UART2_IRQn;
     }
     case UART3_BASE:
     {
       return UART3_IRQn;
     }
     case UART4_BASE:
     {
       return UART4_IRQn;
     }
     case UART5_BASE:
     {
       return UART5_IRQn;
     }
     case UART6_BASE:
     {
       return UART6_IRQn;
     }
     case UART7_BASE:
     {
       return UART7_IRQn;
     }
     default:
     {
       return 0;
     }
   }
}


/****************************************************************************
 * This routine transmits a single character out the UART / COM port.
 * Only the lower 8 bits of the 'data' variable are transmitted.
 ****************************************************************************/
void uart_tx_poll(uint32_t base, char data)
{
  UART0_Type *myUart =((UART0_Type *) base);

  if( verify_uart_base(base) == false)
  {
    return;
  }

  if ( data != 0)
  {
    while( ((myUart->FR)&(UART_FR_TXFF)) != 0 );
    myUart->DR = data;
  }
  return;
}

/****************************************************************************
 * This routine transmits a character string out the UART / COM port.
 * Only the lower 8 bits of the 'data' variable are transmitted.
 ****************************************************************************/
void uart_tx_poll_string(uint32_t base, char *data)
{
  UART0_Type *myUart =((UART0_Type *) base);

  if( verify_uart_base(base) == false)
  {
    return;
  }

  if ( data != 0)
  {
    while(*data != '\0')
    {
      while( ((myUart->FR)&(UART_FR_TXFF)) != 0 );
      myUart->DR = *data;
      data++;
    }
  }
  return;
}

/****************************************************************************
 * This routine returns a character received from the UART/COM port.
 * If blocking is enabled, this routine should not return until data
 * is available. If blocking is disabled and no data is available,
 * this function should return 0.
 ****************************************************************************/
char uart_rx_poll(uint32_t base, bool block)
{
  UART0_Type *myUart =((UART0_Type *) base);

  if( verify_uart_base(base) == false)
  {
    return 0;
  }

  if( (block == false) && !(myUart->FR & UART_FR_RXFE))
  {
       return myUart->DR;
  }
  else if((block == false) && (myUart->FR & UART_FR_RXFE))
  {
    return 0;
  }

  while(myUart->FR & UART_FR_RXFE && block)
  {
    // Wait
  }

   return myUart->DR;
}

//************************************************************************
// Configure a UART to be 115200, 8N1.  
//************************************************************************
bool uart_init(uint32_t uart_base, bool enable_rx_irq, bool enable_tx_irq)
{
    
    UART0_Type *uart = (UART0_Type *)(uart_base);
    uint32_t rcgc_mask;
    uint32_t pr_mask;
    
    if (verify_uart_base(uart_base) == false)
    {
      return false;
    }
    
    rcgc_mask = uart_get_rcgc_mask(uart_base);
    pr_mask = uart_get_pr_mask(uart_base);
    
    // ADD CODE

		// Turn the clock on using the rcgc_mask
	  SYSCTL->RCGCUART|= rcgc_mask; 

    // Wait for the PRUART to indicate the port is ready
		while( (SYSCTL->PRUART  & pr_mask) == 0) 
		{}	
			
	  // Configure the Line Control for 8N1, FIFOs
    uart->LCRH =   UART_LCRH_WLEN_8 | UART_LCRH_FEN;
			
		//Disable the UART (CTL)
    uart->CTL &= ~UART_CTL_UARTEN;
			
		//set the baud rate to be 115200.
		uart->IBRD = 27;
		uart->FBRD = 8; 
			
		uart->LCRH &= UART_LCRH_FEN;
		uart->LCRH |= UART_LCRH_WLEN_8;
			
		if (enable_rx_irq) {
			uart->IM = UART_IM_RXIM | UART_IM_RTIM;
		}
		
		if(enable_tx_irq) {
		//do nothing till next ICE
			uart->IM |= UART_IM_TXIM;
		}
		
		if(enable_rx_irq || enable_tx_irq) {
		
		//set priority to 0 
		NVIC_SetPriority(uart_get_irq_num(uart_base), 0);
			
		//enable the NVIC 
		NVIC_EnableIRQ(uart_get_irq_num(uart_base));
		
		}
		
		uart->CTL = (UART_CTL_RXE|UART_CTL_TXE|UART_CTL_UARTEN);
		
}



