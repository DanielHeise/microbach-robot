/**
 * 
 * file:            debug.h
 * author:          Daniel Heise
 * description:     macro buffers to collect debug information
 * 
 */
#ifndef DEBUG_H_
#define DEBUG_H_

#include "typedefs.h"

/**
 * MACROS
 */
#ifdef DEBUG_MOTORS
	void motor_trace(u16_t x);
	u16_t mqueue_ptr = 0;
	u16_t motor_queue[200];
#endif
#ifdef DEBUG_SENSORS
	void sensor_trace(u16_t x);
	u16_t squeue_ptr = 0;
	u16_t sensor_queue[200];
#endif
#ifdef DEBUG_CORRECTIVE_ACTION
	void corrective_action_trace(u16_t x);
	u16_t caqueue_ptr = 0;
	u16_t corrective_action_queue[200] = 0;
#endif

#endif // DEBUG_H_