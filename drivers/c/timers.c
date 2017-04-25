/*Shyamal Anadkat 3/8/2017 */
#include "timers.h"


volatile bool Alert_Timer0A = false;
volatile bool Alert_Timer0B = false;

//*****************************************************************************
// Verifies that the base address is a valid GPIO base address
//*****************************************************************************
static bool verify_base_addr(uint32_t base_addr)
{
   switch( base_addr )
   {
     case TIMER0_BASE:
     case TIMER1_BASE:
     case TIMER2_BASE:
     case TIMER3_BASE:
     case TIMER4_BASE:
     case TIMER5_BASE:
     {
       return true;
     }
     default:
     {
       return false;
     }
   }
}

//*****************************************************************************
// Returns the RCGC and PR masks for a given TIMER base address
//*****************************************************************************
static bool get_clock_masks(uint32_t base_addr, uint32_t *timer_rcgc_mask, uint32_t *timer_pr_mask)
{
  // Set the timer_rcgc_mask and timer_pr_mask using the appropriate
  // #defines in ../include/sysctrl.h
  switch(base_addr)
  {
    case TIMER0_BASE:
    {
      *timer_rcgc_mask = SYSCTL_RCGCTIMER_R0;
      *timer_pr_mask = SYSCTL_PRTIMER_R0;
      break;
    }
    case TIMER1_BASE:
    {
      *timer_rcgc_mask = SYSCTL_RCGCTIMER_R1;
      *timer_pr_mask = SYSCTL_PRTIMER_R1;
      break;
    }
    case TIMER2_BASE:
    {
      *timer_rcgc_mask = SYSCTL_RCGCTIMER_R2;
      *timer_pr_mask = SYSCTL_PRTIMER_R2;
      break;
    }
    case TIMER3_BASE:
    {
      *timer_rcgc_mask = SYSCTL_RCGCTIMER_R3;
      *timer_pr_mask = SYSCTL_PRTIMER_R3;
      break;
    }
    case TIMER4_BASE:
    {
      *timer_rcgc_mask = SYSCTL_RCGCTIMER_R4;
      *timer_pr_mask = SYSCTL_PRTIMER_R4;
      break;
    }
    case TIMER5_BASE:
    {
      *timer_rcgc_mask = SYSCTL_RCGCTIMER_R5;
      *timer_pr_mask = SYSCTL_PRTIMER_R5;
      break;
    }
    default:
    {
      return false;
    }
  }
  return true;
}


//*****************************************************************************
// Waits for 'ticks' number of clock cycles and then returns.
//
//The function returns true if the base_addr is a valid general purpose timer
//*****************************************************************************
bool gp_timer_wait(uint32_t base_addr, uint32_t ticks)
{
  TIMER0_Type *gp_timer;
  
  // Verify the base address.
  if ( ! verify_base_addr(base_addr) )
  {
    return false;
  }

  // Type cast the base address to a TIMER0_Type struct
  gp_timer = (TIMER0_Type *)base_addr;

  //*********************    
  // ADD CODE
  //*********************
  
	gp_timer->CTL |= TIMER_CTL_TAEN; 
	
	//set interval 
	gp_timer->TAILR = ticks;
	
	gp_timer->ICR = TIMER_ICR_TATOCINT;
	
	//busy wait until a timer timeout occurs 
	while((gp_timer->RIS & TIMER_RIS_TATORIS) == 0){}
  
  return true;
}


//*****************************************************************************
// Configure a general purpose timer to be a 32-bit timer.  
//
// Paramters
//  base_address          The base address of a general purpose timer
//
//  mode                  bit mask for Periodic, One-Shot, or Capture
//
//  count_up              When true, the timer counts up.  When false, it counts
//                        down
//
//  enable_interrupts     When set to true, the timer generates and interrupt
//                        when the timer expires.  When set to false, the timer
//                        does not generate interrupts.
//
//The function returns true if the base_addr is a valid general purpose timer
//*****************************************************************************
bool gp_timer_config_32(uint32_t base_addr, uint32_t mode, bool count_up, bool enable_interrupts)
{
  uint32_t timer_rcgc_mask;
  uint32_t timer_pr_mask;
  TIMER0_Type *gp_timer;
  
  // Verify the base address.
  if ( ! verify_base_addr(base_addr) )
  {
    return false;
  }
  
  // get the correct RCGC and PR masks for the base address
  get_clock_masks(base_addr, &timer_rcgc_mask, &timer_pr_mask);
  
  // Turn on the clock for the timer
  SYSCTL->RCGCTIMER |= timer_rcgc_mask;

  // Wait for the timer to turn on
  while( (SYSCTL->PRTIMER & timer_pr_mask) == 0) {};
  
  // Type cast the base address to a TIMER0_Type struct
  gp_timer = (TIMER0_Type *)base_addr;
    
  //*********************    
  // ADD CODE
  //*********************
		
	//turn timers A and B off
	gp_timer->CTL &= ~ (TIMER_CTL_TAEN | TIMER_CTL_TBEN);

  // 32 bit mode
	gp_timer->CFG = TIMER_CFG_32_BIT_TIMER;
		
	// one shot count down mode 
	gp_timer->TAMR &= ~(TIMER_TAMR_TAMR_M);   //clear bits 
	gp_timer->TAMR |=  mode;                  //TIMER_TAMR_TAMR_M 
		
	// set direction 
	if(count_up) {
	gp_timer->TAMR |= TIMER_TAMR_TACDIR;
	} else {
	gp_timer->TAMR &= ~(TIMER_TAMR_TACDIR);
	};
  
	// enable/disable interruprs
	if(enable_interrupts) {
		gp_timer->IMR = TIMER_IMR_TATOIM; //enabled
	} else {
		gp_timer->IMR &= ~TIMER_IMR_TATOIM; //disabled
	} 

  return true;  
}



//***********************************************
// TIMER0A HANDLER FOR DDR
//***********************************************
void timer_config_hw3(void)
{
  uint32_t timer_rcgc_mask;
  uint32_t timer_pr_mask;
  TIMER0_Type *timer_t = (TIMER0_Type *) TIMER0_BASE;
	
	// Declare constants
	const uint8_t TIMER0A_PRESCALAR = 8;
	const uint8_t TIMER0B_PRESCALAR = 32;
	const uint16_t TIMER0A_LOAD_VALUE = 62500;
	const uint16_t TIMER0B_LOAD_VALUE = 46875;

	// get the correct RCGC and PR masks for the base address
  get_clock_masks(TIMER0_BASE, &timer_rcgc_mask, &timer_pr_mask);

	// set the clock for TIMER0
	SYSCTL->RCGCTIMER |= timer_rcgc_mask;
	
	while( (SYSCTL->PRTIMER & timer_pr_mask) == 0){};
	
	// Disable TIMER0A and TIMER0B
	timer_t->CTL &= ~(TIMER_CTL_TAEN | TIMER_CTL_TBEN);
	
	// Configure timer to be 16 bit
	timer_t->CFG &= ~TIMER_CFG_M;
	timer_t->CFG |= TIMER_CFG_16_BIT;
	
	// Clear bits in TAMR and TBMR
	timer_t->TAMR &= ~TIMER_TAMR_TAMR_M;
	timer_t->TBMR &= ~TIMER_TBMR_TBMR_M;
	
	// Set timer mode to count down
	timer_t->TAMR |= TIMER_TAMR_TAMR_PERIOD;
	timer_t->TBMR |= TIMER_TBMR_TBMR_PERIOD;
	
	// Set timer interrupts
	timer_t->IMR |= TIMER_IMR_TATOIM;
	timer_t->IMR |= TIMER_IMR_TBTOIM;
	
	// Set load register values
	timer_t->TAILR = TIMER0A_LOAD_VALUE;
	timer_t->TBILR = TIMER0B_LOAD_VALUE;
	
	// Set TIMER0A and TIMER0B prescalars
	timer_t->TAPR = TIMER0A_PRESCALAR;
	timer_t->TBPR = TIMER0B_PRESCALAR;
	
	// Set NVIC interrupts for TIMER0A and TIMER0B
	timer_nvic_config_hw3();
  
}

void timer_start_hw3(void)
{
	TIMER0_Type *timer_t = (TIMER0_Type *) TIMER0_BASE;
	
	// Enable the timers
	timer_t->CTL |= TIMER_CTL_TAEN;
	timer_t->CTL |= TIMER_CTL_TBEN;
	
	// Clear interrupt status bit
	timer_t->ICR |= TIMER_ICR_TATOCINT;
	timer_t->ICR |= TIMER_ICR_TBTOCINT;
	
}

void timer_nvic_config_hw3(void)
{
	NVIC_SetPriority(TIMER0A_IRQn, 2);
	NVIC_SetPriority(TIMER0B_IRQn, 1);
	NVIC_EnableIRQ(TIMER0A_IRQn);
	NVIC_EnableIRQ(TIMER0B_IRQn);
}

void TIMER0A_Handler(void) {
	
	// Set global timer alert variable to true for handling
	Alert_Timer0A = true;
	
	// Clear the interrupt status bit
	TIMER0->ICR |= TIMER_ICR_TATOCINT;
}

void TIMER0B_Handler(void) {
	
	// Set global timer alert variable to true for handling
	Alert_Timer0B = true;
		
	// Clear the interrupt status bit
	TIMER0->ICR |= TIMER_ICR_TBTOCINT;
}

