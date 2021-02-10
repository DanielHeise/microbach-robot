#ifndef DEFINES_H_
#define DEFINES_H_

#define FALSE 0
#define TRUE 1

/******************************/
/******** DEFINES *************/
/******************************/
/* Moving Directions */
#define FORWARD				0x00
#define RIGHT				0x01
#define LEFT				0x02
#define TURN_AROUND			0x03
#define PIVOT				0x00
/* Distances */
#define SINGLE_CELL				((u32_t)(397 * STEP_SIZE))
#define _90_DEGREE_TURN			((u32_t)(160 * STEP_SIZE))
#define _180_DEGREE_TURN		((u32_t)((_90_DEGREE_TURN*2)))
#define FIRST_TRIP_POINT		((u16_t)(SINGLE_CELL/4))
/* Speeds */
#define SMOOTH_START		255
#define HALF_SPEED			((u8_t)(SMOOTH_START - (36*SINGLE_CELL/678)))
#define CRUISE_SPEED		45
#define SMOOTH_STOP			255
/* Miscellaneous */
#define ENABLE			1
#define DISABLE			0
#define OUTPUT			0
#define INPUT			1
#define NO				0
#define YES				1
#define OFF				0
#define ON				1
#define MOTOR_ENABLE	0
#define MOTOR_DISABLE	1
/* Miscellaneous */
#define REFERENCE_POINT		10000
#define CLEARED			0
#define SET				1
#define LOW				0
#define HIGH			1
#define END_OF_LIST		3
#define NOT_PRESSED		0
#define PRESSED			1

#endif // DEFINES_H_
