/**
 * 
 * file:            usart.c
 * author:          Daniel Heise
 * description:     implementation for USART on Microchip µC
 * 
 */
#include "usart.h"

/**
 * function:        init_usart
 * description:     initialization of the universal synch/asynch rx/tx registers
 */
void init_usart(void)
{
	TX_REGISTER = 0x20;				// 8-bit TX, TX Enabled, Asynchronous, High Speed
	RX_REGISTER = 0x90;				// Serial Port Enabled, 8-bit RX, RX Enabled

	BAUD_RATE_GEN = baudsetting;	// Set baud rate
	TX_PIN = OUTPUT;				// TX pin set to OUTPUT
	RX_PIN = INPUT;					// RX pin set to INPUT

	TX_INT_ENABLE = 0;				// TX Interrupt Enable
	TX_INT_PRI = 0;					// TX Interrupt Priority
	RX_INT_ENABLE = 0;				// RX Interrupt Enable
	RX_INT_PRI = 0;					// RX Interrupt Priority

} // init_usart()