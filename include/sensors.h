/**
 * 
 * file:            sensors.h
 * author:          Daniel Heise
 * description:     interface for TODO
 * 
 */
#ifndef SENSORS_H_
#define SENSORS_H_

#include <htc.h>
#include "typedefs.h"
#include "defines.h"

#if defined(_18F8720)
	#include "sensors-pic18f.h"
#endif

/**
* SENSOR Settings
*/
enum SENSOR_LIST
{
	FORWARD_SENSOR,
	RIGHT_DIAG_SENSOR,
	LEFT_DIAG_SENSOR,
	RIGHT_SIDE_SENSOR,
	LEFT_SIDE_SENSOR,

	OUT_OF_SENSORS
};

u8_t channel[] = {
					0x34, 		/* AN13	- Forward Sensor 	*/
					0x1C, 		/* AN7	- Right Diag Sensor */
					0x24,	    /* AN9	- Left Diag Sensor	*/
					0x3C, 		/* AN15 - Right Sensor 		*/
					0x38,	    /* AN14 - Left Sensor 		*/

					0x34  };	/* Default to AN13 - Forward Sensor */

u16_t wall_voltage[] = {
						  /*370*/424, 			/* Forward Sensor Voltage 		*/
						  326,//340,//303, 		/* Right Diag Sensor Voltage 	*/
						  338,//334,//304, 		/* Left Diag Sensor Voltage 	*/
						  /*345*/272, 			/* Right Side Sensor Voltage 	*/
						  /*347*/262};  		/* Left Side Sensor Voltage 	*/

u16_t *IRsensor_ptr[5]; /*= {
						 		forward_sensor_ptr,
						 		right_diag_sensor_ptr,
						 		left_diag_sensor_ptr,
						 		right_side_sensor_ptr,
						 		left_side_sensor_ptr	};*/

//				 array # ->   0   1   2   3   4   5   6   7   8   9   10  11  12
u16_t IRtables[5][13] = {	{414,557,631,621,575,530,485,457,424,399,371,348,330},		// Front Sensor Voltages
							{000,000,000,000,000,000,000,000,000,000,000,000,000},		// Right Diag Sensor Voltages
							{000,000,000,000,000,000,000,000,000,000,000,000,000},		// Left Diag Sensor Voltages
							{428,401,357,341,330,318,311,283,272,260,248,236,229},		// Right Side Sensor Voltages
							{414,383,362,347,335,300,288,274,262,252,240,227,219}	};	// Left Side Sensor Voltages
// 					  cm ->   2	 2.5  3 (3.4)3.8  4.5  5  5.5  6  6.5  7  7.5  8

u8_t AnalogRead = FALSE;
u8_t ir_sensor, CorrectionRequired, check_front_sensor, front_sensor_check;
u8_t CorrectRight, correct_right, CorrectLeft, correct_left;
u8_t r_cnt, l_cnt, f_cnt;
u8_t RampDown = FALSE;
u8_t ramped_down = TRUE;
u8_t ramped_up = FALSE;
u8_t DestinationReached = FALSE;
u8_t DirectionBefore_LastDirection = CLEARED;

u16_t correction_cnt = REFERENCE_POINT;
u16_t r_correction_cnt = CLEARED;
u16_t l_correction_cnt = CLEARED;

/**
 * PROTOTYPES
 */
void read_sensors(u8_t FirstSensorToRead, u8_t LastSensorToRead);
u16_t analyze_sensor_data(u8_t current_sensor);
void stablize_channel(void);

#endif // SENSORS_H_
