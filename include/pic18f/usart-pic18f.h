/**
 * 
 * file:            usart-pic18f.h
 * author:          Daniel Heise
 * description:     register configs specific to the PIC18F family of µC
 * 
 */
#ifndef USART_PIC18F_H
#define USART_PIC18F_H

#define FOSC			8000000L	// Freq of system clock; used for baudsetting calculation

#define TX_REGISTER     TXSTA1
#define RX_REGISTER     RCSTA1
#define BAUD_RATE_GEN   SPBRG1

#define TX_PIN          TRISC6
#define RX_PIN          TRISC7

#define TX_INT_ENABLE   TX1IE
#define TX_INT_PRI      TX1IP
#define RX_INT_ENABLE   RC1IE
#define RX_INT_PRI      RC1IP

#endif // USART_PIC18F_H
