/**
 * 
 * file:            corective-action.c
 * author:          Daniel Heise
 * description:     TODO
 * 
 */
#include "corrective-action.h"
#include "sensors.h"
#include "driver-boards.h"
#include "motors.h"
#include "mapping.h"


/**
 * function:        corrective_action
 * description:     TODO
 */
void corrective_action(void)
{
	u8_t right_diff = CLEARED;
	u8_t left_diff = CLEARED;
	u8_t wall_config = CLEARED;

	if(*IRsensor_ptr[RIGHT_DIAG_SENSOR] > wall_voltage[RIGHT_DIAG_SENSOR] - 100)		// IF there is a RIGHT Wall in the next cell
		wall_config = 1;
	else
		wall_config = 0;
	if(*IRsensor_ptr[LEFT_DIAG_SENSOR] > wall_voltage[LEFT_DIAG_SENSOR] - 100)			// IF there is a LEFT Wall in the next cell
		wall_config = (wall_config << 1) + 1;
	else
		wall_config = (wall_config << 1) + 0;
	if(*IRsensor_ptr[LEFT_SIDE_SENSOR] > wall_voltage[LEFT_SIDE_SENSOR] - 50)			// IF there is a LEFT Wall in the current cell
		wall_config = (wall_config << 1) + 1;
	else
		wall_config = (wall_config << 1) + 0;
	if(*IRsensor_ptr[RIGHT_SIDE_SENSOR] > wall_voltage[RIGHT_SIDE_SENSOR] - 50)			// IF there is a RIGHT Wall in the current cell
		wall_config = (wall_config << 1) + 1;
	else
		wall_config = (wall_config << 1) + 0;


	switch(wall_config)
	{
		case NO_CORRECTION:
			CorrectRight = NO;
			CorrectLeft = NO;
			break;
//********************************************************
		case USE_RIGHT_SIDE:
			if(*IRsensor_ptr[RIGHT_SIDE_SENSOR] > IRtables[RIGHT_SIDE_SENSOR][2])			// We are within 3cm on the RIGHT Side Sensor
			{   			/* Too close to Right wall */
				CorrectRight = NO;
				CorrectLeft = YES;
			}
			else if(*IRsensor_ptr[RIGHT_SIDE_SENSOR] < IRtables[RIGHT_SIDE_SENSOR][4])		// We are outside 3.8cm on the RIGHT Side Sensor
			{   			/* Too far from Right wall */
				CorrectRight = YES;
				CorrectLeft = NO;
			}
			break;
//********************************************************
		case USE_LEFT_SIDE:
			if(*IRsensor_ptr[LEFT_SIDE_SENSOR] > IRtables[LEFT_SIDE_SENSOR][2])			// We are within 3cm on the LEFT Side Sensor
			{   			/* Too close to Left wall */
				CorrectRight = YES;
				CorrectLeft = NO;
			}
			else if(*IRsensor_ptr[LEFT_SIDE_SENSOR] < IRtables[LEFT_SIDE_SENSOR][4])		// We are outside 4cm on the LEFT Side Sensor
			{   			/* Too far from Left wall */
				CorrectRight = NO;
				CorrectLeft = YES;
			}
			break;
//********************************************************
		case USE_BOTH_SIDES:
			if(IRtables[RIGHT_SIDE_SENSOR][3] > *IRsensor_ptr[RIGHT_SIDE_SENSOR])		// Compare both walls
				right_diff = (IRtables[RIGHT_SIDE_SENSOR][3] - *IRsensor_ptr[RIGHT_SIDE_SENSOR]);
			if(IRtables[LEFT_SIDE_SENSOR][3] > *IRsensor_ptr[LEFT_SIDE_SENSOR])
			 	left_diff = (IRtables[LEFT_SIDE_SENSOR][3] - *IRsensor_ptr[LEFT_SIDE_SENSOR]);	// If Left wall is closer...
		
			if(right_diff > left_diff)
			{
				CorrectRight = YES;
				CorrectLeft = NO;
			}
			else //(right_diff < left_diff)
			{
				CorrectRight = NO;
				CorrectLeft = YES;
			}
			break;
//********************************************************
		case USE_LEFT_DIAG:
			if(*IRsensor_ptr[LEFT_DIAG_SENSOR] > wall_voltage[LEFT_DIAG_SENSOR])		// IF the LEFT Diagonal Sensor is too close
			{   		/* Too close to Left wall */
				CorrectRight = YES;
				CorrectLeft = NO;
			}
			else if(*IRsensor_ptr[LEFT_DIAG_SENSOR] < wall_voltage[LEFT_DIAG_SENSOR])	// ELSE IF the LEFT Diagonal Sensor is too far
			{   		/* Too far from Left wall */
				CorrectRight = NO;
				CorrectLeft = YES;
			}
			break;
//********************************************************
		case USE_LEFT_DIAG_RIGHT_SIDE:
			if(		(*IRsensor_ptr[LEFT_DIAG_SENSOR] < wall_voltage[LEFT_DIAG_SENSOR]				)	// IF the LEFT Diagonal Sensor is too close,
				||	(*IRsensor_ptr[RIGHT_SIDE_SENSOR] > IRtables[RIGHT_SIDE_SENSOR][2] 	/* 3cm */	))	// OR we are within 3cm on the RIGHT Side Sensor,
			{   					/* Too close to Right wall */
				CorrectRight = NO;
				CorrectLeft = YES;
			}
			else if(	(*IRsensor_ptr[LEFT_DIAG_SENSOR] < wall_voltage[LEFT_DIAG_SENSOR]				)	// IF the LEFT Diagonal Sensor is too far,
					||	(*IRsensor_ptr[RIGHT_SIDE_SENSOR] < IRtables[RIGHT_SIDE_SENSOR][4]	/* 3.8cm */	))	// OR we are outside 4cm on the RIGHT Side Sensor,
			{   					/* Too far from Right wall */
				CorrectRight = YES;
				CorrectLeft = NO;
			}
			break;
//********************************************************
		case USE_LEFT_DIAG_LEFT_SIDE:
			if(		(*IRsensor_ptr[LEFT_DIAG_SENSOR] > wall_voltage[LEFT_DIAG_SENSOR]				)	// IF the LEFT Diagonal Sensor is too close,
				||	(*IRsensor_ptr[LEFT_SIDE_SENSOR] > IRtables[LEFT_SIDE_SENSOR][2] 	/* 3cm */	))	// OR we are within 3cm on the LEFT Side Sensor,
			{   					/* Too close to Left wall */
				CorrectRight = YES;
				CorrectLeft = NO;
			}
			else if(	(*IRsensor_ptr[LEFT_DIAG_SENSOR] < wall_voltage[LEFT_DIAG_SENSOR]				)	// IF the LEFT Diagonal Sensor is too far,
					||	(*IRsensor_ptr[LEFT_SIDE_SENSOR] < IRtables[LEFT_SIDE_SENSOR][4]	/* 4cm */	))	// OR we are outside 4cm on the LEFT Side Sensor,
			{   					/* Too far from Left wall */
				CorrectRight = NO;
				CorrectLeft = YES;
			}
			break;
//********************************************************
		case USE_LEFT_DIAG_BOTH_SIDES:
			if(		(*IRsensor_ptr[LEFT_DIAG_SENSOR] > wall_voltage[LEFT_DIAG_SENSOR]				)	// IF the LEFT Diagonal Sensor is too close,
				||	(*IRsensor_ptr[LEFT_SIDE_SENSOR] > IRtables[LEFT_SIDE_SENSOR][2] 	/* 3cm */	)	// OR we are within 3cm on the LEFT Side Sensor,
				|| 	(*IRsensor_ptr[RIGHT_SIDE_SENSOR] < IRtables[RIGHT_SIDE_SENSOR][4] 	/* 4cm */	))	// OR we are outside 4cm on the RIGHT Side Sensor
			{   					/* Too close to Left wall */
				CorrectRight = YES;
				CorrectLeft = NO;
			}
			else if(	(*IRsensor_ptr[LEFT_DIAG_SENSOR] < wall_voltage[LEFT_DIAG_SENSOR]				)	// ELSE IF the LEFT Diagonal Sensor is too far,
					||	(*IRsensor_ptr[LEFT_SIDE_SENSOR] < IRtables[LEFT_SIDE_SENSOR][4]	/* 4cm */	)	// OR we are outside 4cm on the LEFT Side Sensor,
					|| 	(*IRsensor_ptr[RIGHT_SIDE_SENSOR] > IRtables[RIGHT_SIDE_SENSOR][2] 	/* 3cm */	))	// OR we are within 3cm on the RIGHT Side Sensor
			{   					/* Too far from Left wall */
				CorrectRight = NO;
				CorrectLeft = YES;
			}
			break;
//********************************************************
		case USE_RIGHT_DIAG:
			if(*IRsensor_ptr[RIGHT_DIAG_SENSOR] > wall_voltage[RIGHT_DIAG_SENSOR])			// IF the RIGHT Diagonal Sensor is too close
			{   		/* Too close to Right wall */
				CorrectRight = NO;
				CorrectLeft = YES;
			}
			else if(*IRsensor_ptr[RIGHT_DIAG_SENSOR] < wall_voltage[RIGHT_DIAG_SENSOR])		// ELSE IF the RIGHT Diagonal Sensor is too far
			{   		/* Too far from Right wall */
				CorrectRight = YES;
				CorrectLeft = NO;
			}
			break;
//********************************************************
		case USE_RIGHT_DIAG_RIGHT_SIDE:
			if(		(*IRsensor_ptr[RIGHT_DIAG_SENSOR] > wall_voltage[RIGHT_DIAG_SENSOR]				)	// IF the RIGHT Diagonal Sensor is too close,
				||	(*IRsensor_ptr[RIGHT_SIDE_SENSOR] > IRtables[RIGHT_SIDE_SENSOR][2] 	/* 3cm */	))	// OR we are within 3cm on the RIGHT Side Sensor,
			{   					/* Too close to Right wall */
				CorrectRight = NO;
				CorrectLeft = YES;
			}
			else if(	(*IRsensor_ptr[RIGHT_DIAG_SENSOR] < wall_voltage[RIGHT_DIAG_SENSOR]				)	// IF the RIGHT Diagonal Sensor is too far,
					||	(*IRsensor_ptr[RIGHT_SIDE_SENSOR] < IRtables[RIGHT_SIDE_SENSOR][4]	/* 4cm */	))	// OR we are outside 4cm on the RIGHT Side Sensor,
			{   					/* Too far from Right wall */
				CorrectRight = YES;
				CorrectLeft = NO;
			}
			break;
//********************************************************
		case USE_RIGHT_DIAG_LEFT_SIDE:
			if(		(*IRsensor_ptr[RIGHT_DIAG_SENSOR] < wall_voltage[RIGHT_DIAG_SENSOR]				)	// IF the RIGHT Diagonal Sensor is too close,
				||	(*IRsensor_ptr[LEFT_SIDE_SENSOR] > IRtables[LEFT_SIDE_SENSOR][2] 	/* 3cm */	))	// OR we are within 3cm on the LEFT Side Sensor,
			{   					/* Too close to Left wall */
				CorrectRight = YES;
				CorrectLeft = NO;
			}
			else if(	(*IRsensor_ptr[RIGHT_DIAG_SENSOR] > wall_voltage[RIGHT_DIAG_SENSOR]				)	// IF the RIGHT Diagonal Sensor is too far,
					||	(*IRsensor_ptr[LEFT_SIDE_SENSOR] < IRtables[LEFT_SIDE_SENSOR][4]	/* 3.8cm */	))	// OR we are outside 4cm on the LEFT Side Sensor,
			{   					/* Too far from Left wall */
				CorrectRight = NO;
				CorrectLeft = YES;
			}
			break;
//********************************************************
		case USE_RIGHT_DIAG_BOTH_SIDES:
			if(		(*IRsensor_ptr[RIGHT_DIAG_SENSOR] < wall_voltage[RIGHT_DIAG_SENSOR]				)	// IF the RIGHT Diagonal Sensor is too close,
				||	(*IRsensor_ptr[LEFT_SIDE_SENSOR] > IRtables[LEFT_SIDE_SENSOR][2] 	/* 3cm */	)	// OR we are within 3cm on the LEFT Side Sensor,
				|| 	(*IRsensor_ptr[RIGHT_SIDE_SENSOR] < IRtables[RIGHT_SIDE_SENSOR][4] 	/* 4cm */	))	// OR we are outside 4cm on the RIGHT Side Sensor
			{   					/* Too close to Left wall */
				CorrectRight = YES;
				CorrectLeft = NO;
			}
			else if(	(*IRsensor_ptr[RIGHT_DIAG_SENSOR] > wall_voltage[RIGHT_DIAG_SENSOR]				)	// ELSE IF the RIGHT Diagonal Sensor is too far,
					||	(*IRsensor_ptr[LEFT_SIDE_SENSOR] < IRtables[LEFT_SIDE_SENSOR][4]	/* 4cm */	)	// OR we are outside 4cm on the LEFT Side Sensor,
					|| 	(*IRsensor_ptr[RIGHT_SIDE_SENSOR] > IRtables[RIGHT_SIDE_SENSOR][2] 	/* 3cm */	))	// OR we are within 3cm on the RIGHT Side Sensor
			{   					/* Too far from Left wall */
				CorrectRight = NO;
				CorrectLeft = YES;
			}
			break;
//********************************************************
		case USE_BOTH_DIAGS:
		case USE_BOTH_DIAGS_RIGHT_SIDE:
		case USE_BOTH_DIAGS_LEFT_SIDE:
		case USE_BOTH_DIAGS_BOTH_SIDES:
			if(wall_voltage[RIGHT_DIAG_SENSOR] > *IRsensor_ptr[RIGHT_DIAG_SENSOR])						// Compare both walls
				right_diff = (wall_voltage[RIGHT_DIAG_SENSOR] - *IRsensor_ptr[RIGHT_DIAG_SENSOR]);
			if(wall_voltage[LEFT_DIAG_SENSOR] > *IRsensor_ptr[LEFT_DIAG_SENSOR])
			 	left_diff = (wall_voltage[LEFT_DIAG_SENSOR] - *IRsensor_ptr[LEFT_DIAG_SENSOR]);			// If Left wall is closer...
		
			if(right_diff > left_diff)
			{
				CorrectRight = YES;
				CorrectLeft = NO;
			}
			else if(right_diff < left_diff)
			{
				CorrectRight = NO;
				CorrectLeft = YES;
			}
			break;
//********************************************************
		default:											// There should be no corrective action by default
			CorrectRight = NO;
			CorrectLeft = NO;
			break;
	}
//********************************************************

	correct_right = correct_left = NO;

} // End corrective_action

/**
 * function:        motion_control
 * description:     TODO
 */
void motion_control(void)
{
	++odometer;						// Increment the amount of steps moved
	/**************************************************************/
	/* Corrective Action (ratio based) -- 1:8 correction factor   */
	/**************************************************************/
	if(CorrectRight && (r_cnt < 1) && LastDirection == FORWARD)		// Drifted too far left, correct Right					
	{
		++r_cnt;								// Ratio count (right correction)
		++r_correction_cnt;						// Total number of corrections to the Right
		PWM_RM_DC = CLEARED;					// Kill Right Motor duty cycle
		PWM_LM_DC = PWM_PERIOD >> 1;			// Set Left Motor duty cycle to 50%
		
	}
	else if(CorrectLeft && (l_cnt < 1) && LastDirection == FORWARD)		// Drifted too far right, correct Left
	{
		++l_cnt;								// Ratio count (left correction)
		++l_correction_cnt;						// Total number of corrections to the Left
		PWM_LM_DC = CLEARED;					// Kill Left Motor duty cycle
		PWM_RM_DC = PWM_PERIOD >> 1;			// Set Right Motor duty cycle to 50%
	}
	else
	{
		if(LastDirection == FORWARD)					// We went straight the last two cells
		{
			++f_cnt;									// Ratio count (forward movement)
			PWM_LM_DC = PWM_RM_DC = PWM_PERIOD >> 1;	// Set duty cycle to 50% if not correcting
		}
	}

	if(f_cnt > 8 || (LastDirection != FORWARD))			// Clear the Corrective Action ratio and counters if we have moved Forward
		r_cnt = l_cnt = f_cnt = CLEARED;				// the amount specified for f_cnt or the last movement was not FORWARD

	/**************************************************************/
	/**************************************************************/
	if(odometer == 3000)							// When the mouse has traveled approximately 90% of the destination, check to see
	{												// which motor corrected more, take that value and add it onto the end (destination).
		if(r_correction_cnt > l_correction_cnt)		// After so much correction the error accumulates and the mouse will come up short
			Destination += r_correction_cnt;		// if this is not done...this compensates for the compensation...ha
		else
			Destination += l_correction_cnt;
	}
	switch(LastDirection)
	{
		case FORWARD:
			/*** Check Forward Sensor for proximity to front wall ***/
			if(*IRsensor_ptr[FORWARD_SENSOR] >= IRtables[FORWARD_SENSOR][4] - 25)		// This ensures the mouse stops no closer than 
			{																			// 4cm in front of a wall.
				if(!ramped_down)						// If the mouse never ramped down because of priority (it saw a turn and abruptly
					fake_ramped_down = TRUE;			// stopped to take it) this fake flag is set so it ramps back up after the turn
				DestinationReached = CLEARED;
				odometer = CLEARED;
				moving = NO;
			}
			/*** Ramp Up ***/
			if(		(odometer < 400)														// Ramp up during the first 400 steps of the trip
				&& ((odometer & 0x07) == 0)													// AND Change the speed 13 times within these steps
				&& ((ramped_down)															// AND If we ramped down
				||  (fake_ramped_down && (DirectionBefore_LastDirection != FORWARD)))	)	// OR Ramp up if the ramp down was faked out
			{ 	
				if(backtrack_mode || run_mode)									// Backtracking or Running ramp up profile
				{
					PWM_PERIOD = SMOOTH_START - (55*odometer/100);				// Adjust PWM depending on step count value
					PWM_LM_DC = PWM_RM_DC = PWM_PERIOD >> 1;					// Adjust Duty Cycle for new PWM
					ramped_up = TRUE;
				}
				else															// Mapping Speed ramp up profile
				{
					PWM_PERIOD = SMOOTH_START - (52*odometer/100);				// Adjust PWM depending on step count value
					PWM_LM_DC = PWM_RM_DC = PWM_PERIOD >> 1;					// Adjust Duty Cycle for new PWM
					ramped_up = TRUE;
				}
			}
			/*** Cruising Speed ***/
			else if(odometer == FIRST_TRIP_POINT)
			{
				if(backtrack_mode || run_mode)									// Move faster when Backtracking or Running
				{
					PWM_PERIOD = CRUISE_SPEED - 10;								// Adjust PWM to equal X cells/second
					PWM_LM_DC = PWM_RM_DC = PWM_PERIOD >> 1;					// Adjust Duty Cycle for new PWM
					ramped_down = fake_ramped_down = CLEARED;
				}
				else															// Mapping Speed
				{
					PWM_PERIOD = CRUISE_SPEED;									// Adjust PWM to equal X cells/second
					PWM_LM_DC = PWM_RM_DC = PWM_PERIOD >> 1;					// Adjust Duty Cycle for new PWM
					ramped_up = ramped_down = fake_ramped_down = CLEARED;
				}
			}
			/*** Ramp Down ***/
			else if(	(!DestinationReached)												// Ramp down if the destination is not reached yet
					&& 	(*IRsensor_ptr[FORWARD_SENSOR] >= IRtables[FORWARD_SENSOR][8])		// AND If there is a wall coming up
					||  (odometer >= 3100 && odometer < Destination && RampDown)		)	// OR If the mouse has traveled approximately 94% but 
			{																				// less than 100% of the destination AND RampDown is TRUE
				pwm_period_buff = CRUISE_SPEED + (96*(odometer-2995)/169);			// Adjust PWM depending on step count value
				if(pwm_period_buff < CRUISE_SPEED-18)								// This prevents the equation above from rolling back around on
					pwm_period_buff = CRUISE_SPEED-18;								// itself, causing a large PWM_PERIOD value resulting in the mouse
				PWM_PERIOD = pwm_period_buff;										// literally "jumping" at the destination
				PWM_LM_DC = PWM_RM_DC = PWM_PERIOD >> 1;							// Adjust Duty Cycle for new PWM
				ramped_down = TRUE;
			}
			/*** Destination ***/
			else if(odometer == Destination)										// The mouse has reached its Destination
			{
				if(		(*IRsensor_ptr[FORWARD_SENSOR] < IRtables[FORWARD_SENSOR][4] - 25)
					&&  (*IRsensor_ptr[FORWARD_SENSOR] > 200)								)
				{
					DestinationReached = YES;
					Destination += 3000;
				}
				else
				{
					if(!ramped_down)
						fake_ramped_down = TRUE;
					DestinationReached = CLEARED;
					odometer = CLEARED;								// Reset odometer
					moving = NO;									// Clear moving flag
				}			
			}
		case RIGHT:
		case LEFT:
			/*** Steady turn speed ***/
			PWM_PERIOD = 90;								// Adjust PWM depending on step count value
			PWM_LM_DC = PWM_RM_DC = PWM_PERIOD >> 1;		// Adjust Duty Cycle for new PWM
			/*** Full Turn ***/
			if(odometer == _90_DEGREE_TURN)					// this check is required
			{
				odometer = CLEARED;							// Reset odometer
				moving = NO;								// Clear moving flag			
			}
		case TURN_AROUND:
			/*** Steady turn speed ***/
			PWM_PERIOD =  35;								// Adjust PWM depending on step count value
			PWM_LM_DC = PWM_RM_DC = PWM_PERIOD >> 1;		// Adjust Duty Cycle for new PWM
			/*** Full Turn ***/
			if(odometer == _180_DEGREE_TURN)				// this check is required
			{
				odometer = CLEARED;							// Reset odometer
				moving = NO;								// Clear moving flag			
			}
		default:
			break;
	}

	if(moving)
	{
		TIMER2_TIME = CLEARED;			// Flush out any contents in the Timer2 register
		TIMER2 = ON;
	}
	UpdateMotionControl = FALSE;		// Reset for another round of control
	UPDATE_ODOMETRY = CLEARED;			// Clear timer2 interrupt flag
} // End motion_control
