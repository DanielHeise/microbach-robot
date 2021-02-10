/**
 * 
 * file:            timers.c
 * author:          Daniel Heise
 * description:     implementation for timers on Microchip µC
 * 
 */
#include "timers.h"

/**
 * function:        init_timers
 * description:     initialization of the timers
 */
void init_timers(void)
{
	/* set up interrupts for Timer0 and Timer2 */
	GLOBAL_INT_ENABLE = ENABLE;
	PERIPHERAL_INT_ENABLE = ENABLE;
	INT_PRIORITY_ENABLE = YES;
	TIMER2_INT_ENABLE = ENABLE;
	TIMER2_INT_PRIORITY = HIGH;

	TMR2_PRESCALER = PRE_16;		// Set up prescaler for timer 2

	TIMER0_INTERRUPT = ENABLE;		// Enable Timer0 interrupt
	TIMER0_PRIORITY = HIGH;			// Timer0 interrupt has HIGH priority
	TIMER0_CONFIG = 0x07;			// Configuration in bit order starting with MSB: (7)timer OFF,
									// (6)16-bit size, (5)internal clk src, (4)trigger low-high,
									// (3)prescaler assigned, (2-0)1:256 prescale value
} // End init_timers