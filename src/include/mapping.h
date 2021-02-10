
#ifndef MAPPING_H_
#define MAPPING_H_

#include "typedefs.h"
#include "defines.h"
#include "sensors.h"
#include "motors.h"
#include "corrective-action.h"

#if FALSE
// ----------------------------Remove for PIC------------------------------------
#define CURSOR(xx,yy,tt) disp_cs(2*(MAZESIZE-yy-1)+1, 4*xx+1, tt)  
#define VIRTUAL_WALL_NORTH horizontalwalls[xphysical][yphysical+1]
#define VIRTUAL_WALL_SOUTH horizontalwalls[xphysical][yphysical]
#define VIRTUAL_WALL_EAST verticalwalls[xphysical+1][yphysical]
#define VIRTUAL_WALL_WEST verticalwalls[xphysical][yphysical]
// ----------------------------Remove for PIC------------------------------------
#endif

#define MAZESIZE 16
#define QUEUESIZE 50
#define STARTING_CELL 0x00

// X,Y coords of the bottom-left goal cell
#define GOAL_X 7	
#define GOAL_Y 7
#define SURROUNDING_CELLS 4

// Movemouse modes
#define NORMAL 0
#define RUNMODE 1
#define BACKTRACK 2

// Make decisions
#define NORTH 1 
#define SOUTH 2
#define EAST  3  
#define WEST  4
#define FINISHED 5

// Mapping settings
#define UNTRAVELED 0 
#define SEEN 1
#define TRAVELED 2

// Open/closed wall options
#define OPEN 0
#define CLOSED 1

// Refers to the walls of the current cell
#define WALL_NORTH horizontal_wall_memory[xphysical][yphysical+1]
#define WALL_SOUTH horizontal_wall_memory[xphysical][yphysical]
#define WALL_EAST  vertical_wall_memory[xphysical+1][yphysical]
#define WALL_WEST  vertical_wall_memory[xphysical][yphysical]

// Refers to the cells adjacent to the current cell
#define CURRENT_CELL mapping_memory[xphysical][yphysical]
#define CELL_NORTH   mapping_memory[xphysical][yphysical+1]
#define CELL_SOUTH   mapping_memory[xphysical][yphysical-1]
#define CELL_EAST    mapping_memory[xphysical+1][yphysical]
#define CELL_WEST    mapping_memory[xphysical-1][yphysical]

// Refers to the walls of the current cell
#define FLOOD_WALL_NORTH  horizontal_wall_memory[xposition][yposition+1]
#define FLOOD_WALL_SOUTH  horizontal_wall_memory[xposition][yposition]
#define FLOOD_WALL_EAST   vertical_wall_memory[xposition+1][yposition]
#define FLOOD_WALL_WEST   vertical_wall_memory[xposition][yposition]

#define FLOOD_CELL_START   flood_memory[xposition][yposition]
#define FLOOD_CELL_NORTH   flood_memory[xposition][yposition+1]
#define FLOOD_CELL_SOUTH   flood_memory[xposition][yposition-1]
#define FLOOD_CELL_EAST    flood_memory[xposition+1][yposition]
#define FLOOD_CELL_WEST    flood_memory[xposition-1][yposition]

#define CURRENT_POSITION (xphysical << 4) + yphysical


// ----------------------------Mapping------------------------------------
void mapmaze(void);
void makedecision(void);
void movemouse(int mode);
void backtrack(void);
void physically_move(void);

int xphysical = 0;      
int yphysical = 0;
int xmemory = 0;      
int ymemory = 0;
int heading = NORTH;
int MappingComplete = FALSE;
int decision = 0;
int desired_heading = 0;
int endcell = 0;

// Sensors
u16_t forward_sensor = 0;
u16_t right_diag_sensor = 0;
u16_t left_diag_sensor = 0;
u16_t right_side_sensor = 0;
u16_t left_side_sensor = 0;

//--------------------------Mouse wall memory data---------------------------
int vertical_wall_memory[17][16] = 
	{{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
			
int horizontal_wall_memory[16][17] = 
    {{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	 {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}};
//--------------------------Mouse wall memory data---------------------------

int mapping_memory[16][16] = {0};

int foundmiddle = 0;

// ----------------------------Algorithm----------------------------------
void floodfill(int endlocation);
void increasetailpointer(void);
void increaseheadpointer(void);
void findshortestpath(int startcell, int mode);

int checkqueue[QUEUESIZE] = {0};
int headpointer = 0;
int tailpointer = 1;
int distancefromcenter = 0;
int movelist[100] = {0};
int movecounter = 0;
int priority[6] = {0};
int lastdecision = NORTH;
int returnmode = FALSE;
int run_mode = FALSE;
int backtrack_mode = FALSE;
int run_cnt = CLEARED;
int Retry = CLEARED;

int flood_memory[16][16] = {0};	

#endif // MAPPING_H_
