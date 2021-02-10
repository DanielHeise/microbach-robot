/**
 * 
 * file:            adc.c
 * author:          Daniel Heise
 * description:     implementation for ADC on Microchip µC (PIC18F8720)
 * 
 */
#include "adc.h"

/**
 * function:        init_usart
 * description:     initialization of the A/D converter
 */
void init_adc(void)
{
/* ADCON0 */
	ADC = ENABLE;					// Enable the ADC peripheral
	ANALOG_CH_BIT_3 = SET;			//------------------------------
	ANALOG_CH_BIT_2 = SET;			// Start with Channel 13
	ANALOG_CH_BIT_1 = CLEARED;		//     AN13 (pin 21)
	ANALOG_CH_BIT_0 = SET;			//------------------------------
	ADC_INPROGRESS = CLEARED;		// Ensure the ADC is doing nothing
/* ADCON1 */
	ADC_PREF = AVDD;
	ADC_NREF = AVSS;
	AD_PORT_CFG_BIT_3 = CLEARED;	//------------------------------
	AD_PORT_CFG_BIT_2 = CLEARED;	// Configure the port I/O
	AD_PORT_CFG_BIT_1 = CLEARED;	// as Analog
	AD_PORT_CFG_BIT_0 = CLEARED;	//------------------------------
/* ADCON2 */
	ADC_RESULT = RIGHT_JUSTIFIED;	// Right justify the ADC result for max resolution
	AD_CONV_CLK_BIT_2 = SET;		//------------------------------
	AD_CONV_CLK_BIT_1 = CLEARED;	// ADC Conversion CLK = FOSC/16
	AD_CONV_CLK_BIT_0 = SET;		//------------------------------
/* Configure ADC Interrupt */
	ADC_INTERRUPT = DISABLE;
	ADC_PRIORITY = HIGH;
/* Port I/O */
	ANALOG_IN_0 = INPUT;
	ANALOG_IN_1 = INPUT;
	ANALOG_IN_2 = INPUT;
	ANALOG_IN_3 = INPUT;
	ANALOG_IN_4 = INPUT;
	
	ADC_RESULT_HIGH = ADC_RESULT_LOW = CLEARED;		// Clear ambiguous data in result registers

} // End init_adc
