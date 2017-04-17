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

 #ifndef __SERIAL_DEBUG_H__
 #define __SERIAL_DEBUG_H__

#include "gpio_port.h"
#include "pc_buffer.h"
#include "uart.h"
#include "driver_defines.h"

#define UART_BUFFER_SIZE 80

struct __FILE 
{
    int handle;  
};

enum 
{
    STDIN_HANDLE,
    STDOUT_HANDLE,
    STDERR_HANDLE,
    DEBUG_HANDLE,
    BLUETOOTH_HANDLE
} ;

extern FILE *SERIAL_DEBUG;
extern FILE *BLUETOOTH;

extern void DisableInterrupts(void);
extern void EnableInterrupts(void);

extern PC_Buffer UART0_Tx_Buffer;
extern PC_Buffer UART0_Rx_Buffer;
extern PC_Buffer UART5_Tx_Buffer;
extern PC_Buffer UART5_Rx_Buffer;


//*****************************************************************************
// Fill out the #defines below to configure which pins are connected to
// the serial debug UART
//*****************************************************************************
#define   SERIAL_DBG_GPIO_BASE    GPIOA_BASE
#define   SERIAL_DBG_RX_PIN       PA0
#define   SERIAL_DBG_TX_PIN       PA1
#define   SERIAL_DBG_RX_PCTL_M    GPIO_PCTL_PA0_M
#define   SERIAL_DBG_TX_PCTL_M    GPIO_PCTL_PA1_M
#define   SERIAL_DBG_RX_PCTL      GPIO_PCTL_PA0_U0RX
#define   SERIAL_DBG_TX_PCTL      GPIO_PCTL_PA1_U0TX
#define   SERIAL_DEBUG_UART_BASE  UART0_BASE

//************************************************************************
// Configures the serial debug interface at 115200.
// UART IRQs can be anbled using the two paramters to the function.
//************************************************************************
bool init_serial_debug(bool enable_rx_irq, bool enable_tx_irq);

/****************************************************************************
 *
 ****************************************************************************/
int serial_debug_rx(PC_Buffer *rx_buffer, bool block);

/****************************************************************************
 *
 ****************************************************************************/
void serial_debug_tx(uint32_t uart_base, PC_Buffer *tx_buffer, int data);

#endif
