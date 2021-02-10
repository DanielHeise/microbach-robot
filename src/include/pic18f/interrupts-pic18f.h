/**
 * 
 * file:            interrupts-pic18f.h
 * author:          Daniel Heise
 * description:     register configs specific to the PIC18F family of µC
 * 
 */
#ifndef INTERRUPTS_PIC18F_H
#define INTERRUPTS_PIC18F_H

#define RISING_EDGE     1
#define FALLING_EDGE    0

#define INT0_ENABLE     INT0IE      // INT0 External Interrupt Enable bit
#define INT1_ENABLE     INT1IE      // INT1 External Interrupt Enable bit
#define INT2_ENABLE     INT2IE      // INT2 External Interrupt Enable bit
#define INT3_ENABLE     INT3IE      // INT3 External Interrupt Enable bit

#define INT0_INT_EDGE   INTEDG0     // INTO Interrupt Edge Select bit
#define INT1_INT_EDGE   INTEDG1     // INT1 Interrupt Edge Select bit
#define INT2_INT_EDGE   INTEDG2     // INT2 Interrupt Edge Select bit
#define INT3_INT_EDGE   INTEDG3     // INT3 Interrupt Edge Select bit

#define INT1_PRIORITY   INT1IP      // INT1 External Interrupt Priority bit
#define INT2_PRIORITY   INT2IP      // INT2 External Interrupt Priority bit
#define INT3_PRIORITY   INT3IP      // INT3 External Interrupt Priority bit

#define INT0_INT_FLAG   INT0IF      // INT0 External Interrupt Flag bit
#define INT1_INT_FLAG   INT1IF      // INT1 External Interrupt Flag bit
#define INT2_INT_FLAG   INT2IF      // INT2 External Interrupt Flag bit
#define INT3_INT_FLAG   INT3IF      // INT3 External Interrupt Flag bit

#endif // INTERRUPTS_PIC18F_H