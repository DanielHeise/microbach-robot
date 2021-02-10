/**
 * 
 * file:            usart.h
 * author:          Daniel Heise
 * description:     interface for external interrupts on Microchip µC
 * 
 */
#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include <htc.h>
#include "typedefs.h"
#include "defines.h"

#if defined(_18F8720)
    #include "interrupts-pic18f.h"
#endif

/**
 * PUSHBUTTON settings
 */
u8_t StartButton = NOT_PRESSED;

/**
 * PROTOTYPES
 */
void init_pushbuttons(void);

#endif // INTERRUPTS_H_
