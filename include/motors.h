/**
 * 
 * file:            motors.h
 * author:          Daniel Heise
 * description:     interface for TODO
 * 
 */
#ifndef MOTORS_H_
#define MOTORS_H_

#include <htc.h>
#include "typedefs.h"
#include "defines.h"

#if defined(_18F8720)
    #include "timers-pic18f.h"  // motion_planning() needs access to the TIMER2 defines
#endif

/**
* MOTOR Settings
*/
/* Motor Directions */
#define LM_REVERSE			1
#define LM_FORWARD			0
#define RM_REVERSE			0
#define RM_FORWARD			1

u8_t moving = NO;
u8_t freq = 0;
u8_t direction, distance;
u8_t pwm_period_buff = CLEARED;
u8_t fake_ramped_down = CLEARED;

u16_t odometer = CLEARED;
u16_t Destination = CLEARED;
u16_t Second_Trip_Point = CLEARED;
u16_t LastDirection = FORWARD;

/**
 * PROTOTYPES
 */
void move(u8_t direction, u8_t distance);	// Determine Direction and Distance
void motion_planning(u8_t num_cells);		// Set PWM, DC, Odometer, Moving Flag & Timer2
void delay(u16_t time);

#endif // MOTORS_H_
