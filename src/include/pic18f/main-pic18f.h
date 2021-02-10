#ifndef MAIN_PIC18F_H_
#define MAIN_PIC18F_H_

#define DIAG_LED_PORT       TRISH0
#define SEVEN_MIN_TMR       TIMER0
#define ODOMETRY_DRIVER     TIMER2

#define RETRY_PUSHBTN       INT0IF
#define CALIBRATE_PUSHBTN   INT1IF
#define START_PUSHBTN       INT2IF
#define STOP_PUSHBTN        INT3IF

#endif // MAIN_PIC18F_H_