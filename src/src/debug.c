/**
 * 
 * file:            debug.c
 * author:          Daniel Heise
 * description:     trace buffers to hold debug information
 * 
 */
#include "debug.h"


#ifdef DEBUG_MOTORS
/**
 * function:        motor_trace
 * description:     load new value into trace buffer
 */
void motor_trace(u16_t x)
{
	motor_queue[mqueue_ptr++] = x;
} // End motor_trace
#endif


#ifdef DEBUG_SENSORS
/**
 * function:        sensor_trace
 * description:     load new value into trace buffer
 */
void sensor_trace(u16_t x)
{
	sensor_queue[squeue_ptr] = x;
	if(squeue_ptr == 200)
		squeue_ptr = CLEARED;
	else
		squeue_ptr++;

} // End sensor_trace
#endif

#ifdef DEBUG_CORRECTIVE_ACTION
/**
 * function:        corrective_action_trace
 * description:     load new value into trace buffer
 */
void corrective_action_trace(u16_t x)
{
	corrective_action_queue[caqueue_ptr] = x;
	if(caqueue_ptr == 200)
		caqueue_ptr = CLEARED;
	else
		caqueue_ptr++;;

} // End corrective_action_trace
#endif

//*******************************************************************