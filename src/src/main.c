/* DEBUG CODE */
#undef DEBUG_MOTORS
#undef DEBUG_SENSORS
#undef DEBUG_CORRECTIVE_ACTION

/* MAIN CODE */
#include <htc.h>				// include all PIC HighTec Compiler chip headers
#include "main.h"
#include "defines.h"

#include "usart.h"
#include "interrupts.h"
#include "timers.h"
#include "adc.h"
#include "driver-boards.h"
#include "corrective-action.h"
#include "sensors.h"
#include "mapping.h"

/*********************/
/******** ISR ********/
/*********************/
void interrupt isr(void)				// Interrupt Service Routine
{
	/****************************************************************/
	/* The rest of the functionality for this pushbutton was not	*/
	/* finished. Doing this normally breaks the thought process		*/
	/* Best not to touch...											*/
	/****************************************************************/
	if(RETRY_PUSHBTN)					// "Retry" Pushbutton
	{
		StartButton = PRESSED;
		ramped_down = TRUE;
		delay(500);
		RETRY_PUSHBTN = CLEARED;		// Clear External Interrupt0 flag
	}
	else if(CALIBRATE_PUSHBTN)			// "Calibrate" Pushbutton a.k.a SKIP TO RUN MODE
	{
		delay(500);
		CALIBRATE_PUSHBTN = CLEARED;	// Clear External Interrupt1 flag
	}
	/****************************************************************/
	/****************************************************************/
	else if(START_PUSHBTN)				// "Start" Pushbutton
	{
		StartButton = PRESSED;
		delay(500);						// slight delay before robot starts to move
		SEVEN_MIN_TMR = ON;				// Start 7 minute timer
		START_PUSHBTN = CLEARED;		// Clear External Interrupt2 flag
	}
	/****************************************************************/
	/* The rest of the functionality for this pushbutton was not	*/
	/* finished. Doing this normally breaks the thought process		*/
	/* Best not to touch...											*/
	/****************************************************************/
	else if(STOP_PUSHBTN)				// "Stop" Pushbutton
	{
		StartButton = NOT_PRESSED;
		Retry = YES;
		xphysical = yphysical = 0;		// Reset physical position and memory back to (0,0)
		TOSU = 0x00;					// Redirect Progam Counter to the Main routine;
		TOSH = 0x55;					// Sit and wait for the Start Pushbutton is pressed
		TOSL = 0x14;
		STOP_PUSHBTN = CLEARED;			// Clear External Interrupt3 flag
	}
	/****************************************************************/
	/****************************************************************/
	else if(UPDATE_SEVEN_MIN_TMR)
	{
		++map_timer;					// This will increment every 8.38848 seconds; 50 = 7 mins, 72 = 10 mins 3 secs
		if(map_timer > MAXTIME && (foundmiddle == TRUE))
			MappingComplete = TRUE;
		UPDATE_SEVEN_MIN_TMR = CLEARED;	// Clear Timer0 interrupt flag
	}
	else if(UPDATE_ODOMETRY)			// Motor/Motion Control is done within this portion of the ISR
	{
		TIMER2 = OFF;					// Shut off timer2 NOW; will continue to run if not!! This means missed counts!!!
		UpdateMotionControl = TRUE;
	} // End UPDATE_ODOMETRY

} // End interrupt isr

//*******************************************************************

/****************/
/* Main Routine */
/****************/
int main()
{ 	
	DIAG_LED_PORT = OUTPUT;			// Diagnostic LED port

	SEVEN_MIN_TMR =  OFF;			// Make sure both timers are off before 
	ODOMETRY_DRIVER = CLEARED;		//	the mouse starts moving

	init_usart();					// Initialize the EUSART **USED FOR DEBUGGING**
	init_pushbuttons();				// Initialize the User Pushbuttons
	init_timers();					// Initialize the TIMERS
	init_adc();						// Initialize the ADC
	init_driver_boards();			// Initialize the Motor Driver Board I/O

	IRsensor_ptr[0] = &forward_sensor;				// Initialize pointers to specific addresses
	IRsensor_ptr[1] = &right_diag_sensor;			// for each sensor on the mouse
	IRsensor_ptr[2] = &left_diag_sensor;
	IRsensor_ptr[3] = &right_side_sensor;
	IRsensor_ptr[4] = &left_side_sensor;

	// Mapping algorithm. Will continue mapping as long as we havent found the center. If we have and the timer is up then break out.
	while(!MappingComplete)
	{
		// Hold the mouse at the starting cell with the wheels locked until the start button is pressed
		while(StartButton == NOT_PRESSED);
		// 
		if(Retry)
		{
			Retry = CLEARED;
			movemouse(BACKTRACK);
		}
	
		// Calls the function to read the sensors 
		read_sensors(RIGHT_SIDE_SENSOR, LEFT_SIDE_SENSOR); 

		// Takes the sensor data and stores it in memory
		mapmaze();

		// Decide which way to look next
		makedecision();

		// desired_heading == 5 means backtrack was run
		if(desired_heading != 5)	// && !moving *************************
		{
			// Move the mouse in that direction
			movemouse(NORMAL);
		}
	}
    // Read the last cell before continuing
 	read_sensors(RIGHT_SIDE_SENSOR, LEFT_SIDE_SENSOR); 
	mapmaze();

	// No matter where we end up we can flood from current position back to the 
	//	starting cell then travel there
	floodfill(CURRENT_POSITION);
	findshortestpath(STARTING_CELL,BACKTRACK);

	// Get the mouse back to the starting cell
	returnmode = TRUE;
	movemouse(BACKTRACK);
	
	// Now that the mouse is back home we can flood for the shortest route from start to center
	// finds the goal cell (center 4 cells are always known) and floods from there
	floodfill(endcell);

	// Now to traverse the memory array from start (0,0) to finish following the shortest path
	findshortestpath(STARTING_CELL,RUNMODE);

	// Follow the route to the goal cells. Run 3 times (Meanth to have increasing speed on each run)
	while(run_cnt < 3)
	{
		movemouse(RUNMODE);
		movemouse(BACKTRACK);
		++run_cnt;
	}	
	return(0);
}
