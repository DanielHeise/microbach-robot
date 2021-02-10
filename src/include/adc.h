/**
 * 
 * file:            adc.h
 * author:          Daniel Heise
 * description:     interface for analog-digital converters on Microchip µC
 * 
 */
#ifndef ADC_H_
#define ADC_H_

#include <htc.h>
#include "defines.h"

#if defined(_18F8720)
    #include "adc-pic18f.h"
#endif

/**
* ADC Settings
*/


/**
 * PROTOTYPES
 */
void init_adc(void);

#endif // ADC_H_
