/**
 * 
 * file:            interrupts.c
 * author:          Daniel Heise
 * description:     implementation for external interrupts on Microchip µC (PIC18F8720)
 * 
 */
#include "interrupts.h"

/**
 * function:        init_pushbuttons
 * description:     initialization the external interrupts for pushbutton inputs
 */
void init_pushbuttons(void)
{
	INT0_ENABLE = INT1_ENABLE = INT2_ENABLE = INT3_ENABLE = SET;
	INT0_INT_EDGE = INT1_INT_EDGE = INT2_INT_EDGE = INT3_INT_EDGE = RISING_EDGE;
	INT1_PRIORITY = INT2_PRIORITY = INT3_PRIORITY = HIGH;
	INT0_INT_FLAG = INT1_INT_FLAG = INT2_INT_FLAG = INT3_INT_FLAG = CLEARED;

} // init_pushbuttons()