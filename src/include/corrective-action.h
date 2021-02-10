/**
 * 
 * file:            sensors.h
 * author:          Daniel Heise
 * description:     interface for TODO
 * 
 */
#ifndef CORRECTIVE_ACTION_H_
#define CORRECTIVE_ACTION_H_

#include <htc.h>
#include "typedefs.h"
#include "defines.h"

/**
* CORRECTIVE ACTION Settings
*/
u8_t UpdateMotionControl = FALSE;

enum CORRECTIVE_WALL_CONFIGS
{
    NO_CORRECTION,
    USE_RIGHT_SIDE,
    USE_LEFT_SIDE,
    USE_BOTH_SIDES,
    USE_LEFT_DIAG,
    USE_LEFT_DIAG_RIGHT_SIDE,
    USE_LEFT_DIAG_LEFT_SIDE,
    USE_LEFT_DIAG_BOTH_SIDES,
    USE_RIGHT_DIAG,
    USE_RIGHT_DIAG_RIGHT_SIDE,
    USE_RIGHT_DIAG_LEFT_SIDE,
    USE_RIGHT_DIAG_BOTH_SIDES,
    USE_BOTH_DIAGS,
    USE_BOTH_DIAGS_RIGHT_SIDE,
    USE_BOTH_DIAGS_LEFT_SIDE,
    USE_BOTH_DIAGS_BOTH_SIDES,

    LAST_CONFIG
};

/**
 * PROTOTYPES
 */
void corrective_action(void);
void motion_control(void);

#endif // CORRECTIVE_ACTION_H_
