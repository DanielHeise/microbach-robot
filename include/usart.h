/**
 * 
 * file:            usart.h
 * author:          Daniel Heise
 * description:     interface for USART on Microchip µC
 * 
 */
#ifndef USART_H_
#define USART_H_

#include <htc.h>
#include "typedefs.h"
#include "defines.h"

#if defined(_18F8720)
    #include "usart-pic18f.h"
#endif

/**
* USART Settings
*/
#define BAUD            1200                                // Baud Rate
#define baudsetting     ((u16_t)(FOSC/(64UL*BAUD)-1))       // Calculates baud value that needs
                                                            // loaded into the SPBRG register
/**
 * PROTOTYPES
 */
void init_usart(void);

#endif // USART_H_
