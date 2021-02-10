/**
 * 
 * file:            timers.h
 * author:          Daniel Heise
 * description:     interface for timers on Microchip µC
 * 
 */
#ifndef TIMERS_H_
#define TIMERS_H_

#include <htc.h>
#include "typedefs.h"
#include "defines.h"

#if defined(_18F8720)
    #include "timers-pic18f.h"
#endif

/**
* TIMER Settings
*/
u8_t map_timer = CLEARED;	// This timer is meant to keep track of how long the
                            //  mouse has been running through the maze. Once 
                            //  map_timer == 50, 7 minutes have passed.

/**
 * PROTOTYPES
 */
void init_timers(void);

#endif // TIMERS_H_
