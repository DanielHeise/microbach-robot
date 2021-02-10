/**
 * 
 * file:            adc-pic18f.h
 * author:          Daniel Heise
 * description:     register configs specific to the PIC18F family of µC
 * 
 */
#ifndef ADC_PIC18F_H
#define ADC_PIC18F_H

#define AVDD                0
#define AVSS                0
#define RIGHT_JUSTIFIED     1
                                            /* ADCON0 */
#define ANALOG_CH_BIT_3     CHS3            // Analog channel select bits
#define ANALOG_CH_BIT_2     CHS2
#define ANALOG_CH_BIT_1     CHS1
#define ANALOG_CH_BIT_0     CHS0
                                            /* ADCON1 */
#define AD_PORT_CFG_BIT_3   PCFG3           // A/D Port Configuration Control bits
#define AD_PORT_CFG_BIT_2   PCFG2
#define AD_PORT_CFG_BIT_1   PCFG1
#define AD_PORT_CFG_BIT_0   PCFG0
                                            /* ADCON2 */
#define AD_CONV_CLK_BIT_2   ADCS2           // A/D Conversion Clock Select bits
#define AD_CONV_CLK_BIT_1   ADCS1
#define AD_CONV_CLK_BIT_0   ADCS0

#define ADC                 ADON            // ADC Enable bit
#define START_READING       GODONE          // ADC Conversion Status bit
#define ADC_INPROGRESS      START_READING
#define ADC_PREF            VCFG1
#define ADC_NREF            VCFG0
#define ADC_RESULT          ADFM
#define ADC_INTERRUPT       ADIE
#define ADC_PRIORITY        ADIP
#define ADC_CHANNEL         ADCON0
#define ADC_RESULT_HIGH     ADRESH          // A/D Result High Register
#define ADC_RESULT_LOW      ADRESL          // A/D Result Low Register

#define ANALOG_IN_0      TRISH5             // AN13 input
#define ANALOG_IN_1      TRISH6             // AN14 input
#define ANALOG_IN_2      TRISH7             // AN15 input
#define ANALOG_IN_3      TRISF2             // AN7 input
#define ANALOG_IN_4      TRISF4             // AN9 input

#endif // ADC_PIC18F_H
