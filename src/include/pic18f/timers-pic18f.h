/**
 * 
 * file:            timers-pic18f.h
 * author:          Daniel Heise
 * description:     register configs specific to the PIC18F family of µC
 * 
 */
#ifndef TIMERS_PIC18F_H
#define TIMERS_PIC18F_H

#define PRE_16                  0x02        // Prescaler Values:
#define PRE_4                   0x01        // ratios of Clock Source
#define PRE_1                   0x00

#define TIMER2                  TMR2ON      // Timer2 On/Off Control bit
#define TIMER2_TIME             TMR2        // Timer2 timer register (keeps counts)
#define TMR2_PRESCALER          T2CON       // Timer2 register with Prescaler Select bits
#define TIMER2_INT_ENABLE       TMR2IE      // Timer2 interrupt enable
#define TIMER2_INT_PRIORITY     TMR2IP      // Timer2 interrupt priority
#define UPDATE_ODOMETRY         TMR2IF      // Timer2 interrupt flag

#define TIMER4                  TMR4ON      // Timer4 On/Off Control bit
#define TMR4_PRESCALER          T4CON       // Timer4 register with Prescaler Select bits

#define TIMER0_CONFIG           T0CON       // Timer0 Control Register
#define TIMER0                  TMR0ON      // Timer0 On/Off bit
#define TIMER0_INTERRUPT        TMR0IE      // Timer0 interrupt Enable bit 
#define TIMER0_PRIORITY         TMR0IP      // Timer0 interrupt Priority bit
#define UPDATE_SEVEN_MIN_TMR    TMR0IF      // Timer0 interrupt flag

#define GLOBAL_INT_ENABLE       GIE     // global interrupt enable bit
#define PERIPHERAL_INT_ENABLE   PEIE    // peripheral interrupt enable bit
#define INT_PRIORITY_ENABLE     IPEN    // interrupt priority enable bit

#endif // TIMERS_PIC18F_H
