/**
 * 
 * file:            adc.c
 * author:          Daniel Heise
 * description:     implementation for ADC on Microchip µC (PIC18F8720)
 * 
 */
#include "driver-boards.h"
#include "motors.h"				// LM_FORWARD, etc.

/**
 * function:        init_driver_boards
 * description:     initialization of the motor driver boards
 */
void init_driver_boards(void)
{
	LM_ENABLE_PIN = OUTPUT;			// Left Motor
	LM_STEP_PIN = OUTPUT;
	LM_DIR_PIN = OUTPUT;
	LM_DIR = LM_FORWARD;

	RM_ENABLE_PIN = OUTPUT;			// Right Motor
	RM_STEP_PIN = OUTPUT;
	RM_DIR_PIN  = OUTPUT;
	RM_DIR = RM_FORWARD;

	MS1_PIN = OUTPUT;				// Both Motors
	MS2_PIN = OUTPUT;
	MS3_PIN = OUTPUT;
	_RESET_PIN = OUTPUT;

	_RESET = 1;//DISABLE;			// No Resetting

	init_stepping();				// Init MS1-3

	LM_ENABLE = MOTOR_ENABLE;		// Enable motors
	RM_ENABLE = MOTOR_ENABLE;

} // End init_driver_boards

/**
 * function:        init_stepping
 * description:     initialization of stepper motor step size/increments
 */
void init_stepping(void)
{
	SETUP_LM_PWM_A = SETUP_LM_PWM_B = YES;		// !!!! DO NOT MIX & MATCH !!!! BOTH A & B MUST BE EITHER YES OR NO
	SETUP_RM_PWM_A = SETUP_RM_PWM_B = YES;		// YES = PWM Mode, NO = CCP Module Disabled	
	PWM_LM_DC = PWM_RM_DC = 0;					// PWM Duty Cycle

	switch(STEP_SIZE)
	{
		case HALF:				// Half Step
			MS1 = 1;
			MS2 = 0;
			MS3 = 0;
			break;
		case QUARTER:			// Quarter Step
			MS1 = 0;
			MS2 = 1;
			MS3 = 0;
			break;
		case EIGHTH:			// Eighth Step
			MS1 = 1;
			MS2 = 1;
			MS3 = 0;
			break;
		case SIXTEENTH:			// Sixteenth Step
			MS1 = 1;
			MS2 = 1;
			MS3 = 1;
			break;
		default:				// Full Step
			MS1 = 0;
			MS2 = 0;
			MS3 = 0;
			break;
	}

} // End init_stepping
