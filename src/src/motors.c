/**
 * 
 * file:            motors.c
 * author:          Daniel Heise
 * description:     implementation for operating the stepper motors
 * 
 */
#include "motors.h"
#include "sensors.h"
#include "driver-boards.h"

/**
 * function:        move
 * description:     initialization of the universal synch/asynch rx/tx registers
 */
void move(u8_t direction, u8_t distance)
{
	DirectionBefore_LastDirection = LastDirection;			// Store the move before the most recent last move...ha
	switch(direction)
	{
		case FORWARD:										// Move Forward
				LM_DIR = LM_FORWARD;						// Left motor = Forward motion
				RM_DIR = RM_FORWARD;						// Right motor = Forward motion
				LastDirection = FORWARD;					// Set this as the last direction moved
				motion_planning(distance);					// Drive the motors
				break;
		case RIGHT:											// Move Right
				RM_DIR = RM_REVERSE;						// Right motor = Reverse motion
				LastDirection = RIGHT;						// Set this as the last direction moved
				motion_planning(distance);					// Drive the motors
				break;
		case LEFT:											// Move Left
				LM_DIR = LM_REVERSE;						// Left motor = Reverse motion
				LastDirection = LEFT;						// Set this as the last direction moved
				motion_planning(distance);					// Drive the motors
				break;
		case TURN_AROUND:									// Turn Around
				RM_DIR = RM_REVERSE;						// Right motor = Reverse motion
				LastDirection = TURN_AROUND;				// Set this as the last direction moved
				motion_planning(distance);					// Drive the motors
				break;
		default:	
				break;
	}

} // End move

/**
 * function:        motion_planning
 * description:     prep for the next move of the robot
 */
void motion_planning(u8_t num_cells)
{
	if(LastDirection != FORWARD || DirectionBefore_LastDirection != FORWARD)	// We need to give a very little pause BEFORE and AFTER turning or the
		delay(80);																// steps for the next decision will come too fast and the stepper 
																				// motors will stumble and fail; proper Delay(x) will vary with PWM speeds
	if(!num_cells)
	{
		if(CorrectLeft)
			Destination = (correction_cnt - REFERENCE_POINT);
		else //(CorrectRight)
			Destination = (REFERENCE_POINT - correction_cnt);
	}
	else
	{
		Destination = SINGLE_CELL * num_cells;
		Second_Trip_Point = Destination - FIRST_TRIP_POINT;
	}

	odometer = 0;				// reset the trip
	moving = 1;					// Set moving flag
	TIMER2_TIME = 0;			// Clear timer count value
	TIMER2 = ON;				// Turn ON the timer

} // End motion_planning

/**
 * function:        delay
 * description:     allow some arbitrary time to pass; meant for motor stabilzation
 */
void delay(u16_t time)
{
	u16_t m, n;
	for(m=0;m<time;m++)
	{
		for(n=0;n<250;n++);
	}
} // End delay
