/**
 * 
 * file:            driver-boards.h
 * author:          Daniel Heise
 * description:     interface for motor driver boards
 * 
 */
#ifndef DRIVER_BOARDS_H_
#define DRIVER_BOARDS_H_

#include <htc.h>
#include "defines.h"

/**
* DRIVER BOARD Settings
*/
/* I/O Pins Used */
#define LM_ENABLE           RG1
#define RM_ENABLE           RJ6
#define LM_STEP             CCP4
#define RM_STEP             CCP1
#define LM_DIR              RG2
#define RM_DIR              RJ7
#define MS1                 RD1
#define MS2                 RD2
#define MS3                 RD3
#define _RESET              RD4
//#define _SLEEP              RD5

/* Pin Tri-States: Input or Output */
#define LM_ENABLE_PIN       TRISG1              // Driver Board Enable				
#define RM_ENABLE_PIN       TRISJ6              // Driver Board Enable
#define LM_STEP_PIN         TRISG3              // PWM
#define RM_STEP_PIN         TRISC2              // PWM
#define LM_DIR_PIN          TRISG2              // Motor Direction
#define RM_DIR_PIN          TRISJ7              // Motor Direction
#define MS1_PIN             TRISD1              // MS1-3 Determine Step size
#define MS2_PIN             TRISD2
#define MS3_PIN             TRISD3
#define _RESET_PIN          TRISD4              // Driver Board Reset
//#define _SLEEP_PIN            TRISD5              // Driver Board Sleep

/* PWM */
#define PWM_PERIOD          PR2                 // Pulse Peiod
#define PWM_SLOW_PERIOD     PR4
#define PWM_LM_DC           CCPR4L              // Duty Cycle
#define PWM_RM_DC           CCPR1L              // Duty Cycle
#define SETUP_LM_PWM_A      CCP4M2              // PWM Mode => M2 & M3 = 1
#define SETUP_LM_PWM_B      CCP4M3	
#define SETUP_RM_PWM_A      CCP1M2              // PWM Mode => M2 & M3 = 1
#define SETUP_RM_PWM_B      CCP1M3

/* Step Sizes */
#define FULL                1
#define HALF                2
#define QUARTER             4
#define EIGHTH              8
#define SIXTEENTH           16
#define STEP_SIZE           EIGHTH

/**
 * PROTOTYPES
 */
void init_driver_boards(void);
void init_stepping(void);

#endif // DRIVER_BOARDS_H_
