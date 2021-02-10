
#include "mapping.h"

/********************/
/* Map Maze Routine */
/********************/
void mapmaze(void)
{
	// Mark we have been here before
	CURRENT_CELL = TRAVELED;

    // Stores the wall data from sensors in diffferent places depending on which direction the mouse is facing
	switch(heading)
	{
		case NORTH:
		{
			WALL_NORTH = forward_sensor;
			WALL_EAST  = right_side_sensor;
			WALL_WEST  = left_side_sensor;
			break;
		}
		case SOUTH:
		{
			WALL_SOUTH = forward_sensor;
			WALL_EAST  = left_side_sensor;
			WALL_WEST  = right_side_sensor;
			break;
		}
		case EAST:
		{
			WALL_NORTH = left_side_sensor;
			WALL_SOUTH = right_side_sensor;
			WALL_EAST  = forward_sensor;
			break;
		}
		case WEST:
		{
			WALL_NORTH = right_side_sensor;
			WALL_SOUTH = left_side_sensor;
			WALL_WEST  = forward_sensor;
			break;
		}
	}

	// If no wall is present and we have not been there before then mark the cell as seen
	 if((WALL_NORTH == 0) && (CELL_NORTH != TRAVELED))
		 CELL_NORTH = SEEN;

 	 if((WALL_SOUTH == 0) && (CELL_SOUTH != TRAVELED))
		 CELL_SOUTH = SEEN;

	 if((WALL_EAST  == 0) && (CELL_EAST != TRAVELED))
		 CELL_EAST = SEEN;

	 if((WALL_WEST  == 0) && (CELL_WEST != TRAVELED))
		 CELL_WEST = SEEN;

    // If within the goal cells then set the found middle flag to be compared with timer later
	if((xphysical == GOAL_X) || (xphysical == GOAL_X + 1))
	{
		if((yphysical == GOAL_Y) || (yphysical == GOAL_Y + 1))
		{
			foundmiddle = TRUE;
			endcell = (xphysical << 4) + yphysical;
			if(xphysical == GOAL_X)
			{
				// Once we are in the center then prevent the mouse from mapping the remaining 4 goal cells
				CELL_EAST = TRAVELED;
				WALL_EAST = 1;
				if(yphysical == GOAL_Y)
				{
					WALL_NORTH  = 1;
					CELL_NORTH = TRAVELED;
				}
				else
				{
					WALL_SOUTH = 1;
					CELL_SOUTH = TRAVELED;
				}
			}
			else
			{
				CELL_WEST = TRAVELED;
				WALL_WEST = 1;
				if(yphysical == GOAL_Y)
				{
					WALL_NORTH  = 1;
					CELL_NORTH = TRAVELED;
				}
				else
				{
					WALL_SOUTH  = 1;
					CELL_SOUTH = TRAVELED;
				}
			}
		}
	}
}

/*************************/
/* Make Decision Routine */
/*************************/
void makedecision(void)
{
	int step = 0;
	desired_heading = 0;

	// If we are around the goal cell go there, if not then try to move forward by choosing the previous decision
	if((xphysical >= GOAL_X - SURROUNDING_CELLS) && (xphysical <= GOAL_X + SURROUNDING_CELLS + 1))
	{
		if((yphysical >= GOAL_Y - SURROUNDING_CELLS) && (yphysical <= GOAL_Y + SURROUNDING_CELLS + 1))
		{
			if((xphysical >= GOAL_X - SURROUNDING_CELLS) && (xphysical < GOAL_X))
				priority[0] = EAST;
			else if((xphysical <= GOAL_X + SURROUNDING_CELLS + 1) && (xphysical > GOAL_X + 1))
				priority[0] = WEST;
			else if((yphysical >= GOAL_Y - SURROUNDING_CELLS) && (yphysical < GOAL_Y))
				priority[0] = NORTH;
			else if((yphysical <= GOAL_Y + SURROUNDING_CELLS + 1) && (yphysical > GOAL_Y + 1))
				priority[0] = SOUTH;
		}
		else
			// If a direction could not be chosen then opt to go straight
			priority[0] = lastdecision;
	}
	else
	{
	// Defaults to north since first cell is always north
	priority[0] = lastdecision;
	priority[1] = lastdecision;
	}

	// Determine which of the four quadrants we are in and set movement priorities
	if(yphysical <= GOAL_Y)
	{
		// bottom half of maze
		priority[2] = NORTH;
		if(xphysical <= GOAL_X)
		{
			// left half of maze
			priority[3] = EAST;
			priority[4] = SOUTH;
			priority[5] = WEST;
		}
		else 
		{
			// right half of maze
			priority[3] = WEST;
			priority[4] = EAST;
			priority[5] = SOUTH;
		}
	}
	else{
		// top half of maze
		priority[2] = SOUTH;
		if(xphysical <= GOAL_X)
		{
			// left half of maze
			priority[3] = EAST;
			priority[4] = NORTH;
			priority[5] = WEST;
		}
		else 
		{
			// right half of maze
			priority[3] = WEST;
			priority[4] = EAST;
			priority[5] = NORTH;
		}
	}
	
	// choose direction based on priority. Will run through until it finds a cell to travel to
	// If no cell is found it continues on 
	while((step <= 5) && (desired_heading == 0))
	{
		switch(priority[step])
		{
			case NORTH:
			{
				// If there is no wall in this direction AND we havent been to that cell before then choose this as the route to take
				if((WALL_NORTH == 0) && (CELL_NORTH < TRAVELED))
				{
					desired_heading = NORTH;
					if(mapping_memory[xphysical][yphysical + 1] == TRAVELED)
						RampDown = TRUE;
				}
				break;
			}
			case SOUTH:
			{
				if((WALL_SOUTH == 0) && (CELL_SOUTH < TRAVELED))
				{
					desired_heading = SOUTH;
					if(mapping_memory[xphysical][yphysical - 1] == TRAVELED)
						RampDown = TRUE;
				}
				break;
			}
			case EAST:
			{
				if((WALL_EAST == 0) && (CELL_EAST < TRAVELED))
				{
					desired_heading = EAST;
					if(mapping_memory[xphysical + 1][yphysical] == TRAVELED)
						RampDown = TRUE;
				}
				break;
			}
			case WEST:
			{
				if((WALL_WEST == 0) && (CELL_WEST < TRAVELED))
				{
					desired_heading = WEST;
					if(mapping_memory[xphysical - 1][yphysical + 1] == TRAVELED)
						RampDown = TRUE;
				}
				break;
			}
		}
		step++;
	}
	// If no decision is made then we are at a dead end or surrounded by cells we have been to - So backtrack
	if(desired_heading == 0)
	{
		backtrack();
		// Keeps mouse from moving without thinking first when leaving backtrack
		desired_heading = 5;
	}	
}

/*********************/
/* Movemouse Routine */
/*********************/
void movemouse(int mode)
{
	switch(mode)
	{
		// Move the mouse one cell in any direction
		case NORMAL:
		{
			physically_move();
			break;
		}
		// Follow the list generated for run mode. Speed could be increased here
		case RUNMODE:
		{	
			run_mode = SET;
			desired_heading = movelist[0];
			for(movecounter = 0; movelist[movecounter] != 5; movecounter++)
			{
				desired_heading = movelist[movecounter];
				if(movelist[movecounter] != movelist[movecounter + 1])
					RampDown = TRUE;
				physically_move();
			}
			run_mode = CLEARED;
			break;
		}
		// Called during backtrack mode, this case will have the mouse follow a list backwards to get to another cell
		case BACKTRACK:
		{	
			backtrack_mode = SET;
			// Go to the end of the move list and work in reverse
			for(movecounter -= 1;movecounter >= 0;movecounter --)
			{
				desired_heading = movelist[movecounter];
				
				// Reverse directions since the list is backwards
				if(desired_heading == NORTH)
					desired_heading = SOUTH;
				else if(desired_heading == SOUTH)
					desired_heading = NORTH;
				else if(desired_heading == EAST)
					desired_heading = WEST;
				else if(desired_heading == WEST)
					desired_heading = EAST;

				// If we have to turn along the route then ramp down to prevent slip
				if(movelist[movecounter] != movelist[movecounter - 1])
					RampDown = TRUE;

				physically_move();
				// Stop backtracking if we are done mapping/ This is to prevent backtracking a large number of cells before the check would have been run again
				if(MappingComplete && (returnmode == FALSE))
					break;
			}
			backtrack_mode = CLEARED;
			break;
		}
	}
}

/***************************/
/* Physically Move Routine */
/***************************/
void physically_move(void)
{
	RH0 ^= 1;							// Everytime this routine is called the mouse is making a new decision,
										// toggle the LED when this happens to let the user know when it does
	lastdecision = desired_heading;

	// Takes current heading and figures out what to do to get to the desired heading
	switch(desired_heading)
	{
		// Mouse is currently facing north
		case NORTH:
			{
				yphysical++;
				// Which way is the desired move?
				switch(heading)
				{
					case NORTH:
						{
							// Send the command to move in this direction
							move(FORWARD,1);
							break;
						}
					case SOUTH:
						{
							move(TURN_AROUND,1);
							break;
						}
					case EAST:
						{
							move(LEFT,1);
							break;
						}
					case WEST:
						{
							move(RIGHT,1);
							break;
						}
				}
				break;
			}
		case SOUTH:
			{
				yphysical--;
				switch(heading)
				{
					case NORTH:
						{
							move(TURN_AROUND,1);
							break;
						}
					case SOUTH:
						{
							move(FORWARD,1);
							break;
						}
					case EAST:
						{
							move(RIGHT,1);
							break;
						}
					case WEST:
						{
							move(LEFT,1);
							break;
						}
				}
				break;
			}
		case EAST:
			{
				xphysical++;
				switch(heading)
				{
					case NORTH:
						{
							move(RIGHT,1);
							break;
						}
					case SOUTH:
						{
							move(LEFT,1);
							break;
						}
					case EAST:
						{
							move(FORWARD,1);
							break;
						}
					case WEST:
						{
							move(TURN_AROUND,1);
							break;
						}
				}
				break;
			}
		case WEST:
			{
				xphysical--;
				switch(heading)
				{
					case NORTH:
						{
							move(LEFT,1);
							break;
						}
					case SOUTH:
						{
							move(RIGHT,1);
							break;
						}
					case EAST:
						{
							move(TURN_AROUND,1);
							break;
						}
					case WEST:
						{
							move(FORWARD,1);
							break;
						}
				}
				break;
			}
	}

/******************************************/
/* Corrective Action Readings happen here */
/******************************************/
	AnalogRead = YES;				// Inside the read_sensors routine, this ensures the ADC values
									// are not formatted for a digital output, instead they are stored raw
	while(moving)					
	{
		read_sensors(RIGHT_DIAG_SENSOR, LEFT_DIAG_SENSOR);					// When moving only use the Forward, Right & Left Diagonal sensors
																			// to make corrections, read_sensors will do the rest
		if((correct_right || correct_left) && LastDirection == FORWARD)		// This ensures there is no corrective action during a turn
			corrective_action();
	}
	AnalogRead = NO;										// The mouse is no longer moving, kill this flag
	r_correction_cnt = l_correction_cnt = CLEARED;			// and clear the correction counters
	
	if(LastDirection != FORWARD)					// If the mouse just made a turn or any kind, force an immediate move FORWARD,
	{												// this will give them main algorithm a break from decision making
		move(FORWARD, 1);

		AnalogRead = YES;
		while(moving)
		{
			read_sensors(RIGHT_DIAG_SENSOR, LEFT_DIAG_SENSOR);					// When moving only use the Forward, Right & Left Diagonal sensors
																				// to make corrections, read_sensors will do the rest
			if((correct_right || correct_left) && LastDirection == FORWARD)		// This ensures there is no corrective action during a turn
				corrective_action();
		}
		AnalogRead = NO;										// The mouse is no longer moving, kill this flag
		r_correction_cnt = l_correction_cnt = CLEARED;			// and clear the correction counters
	}

	// Our current heading is now equal to the way we moved
	heading = desired_heading;
	RampDown = FALSE;
}

/*********************/
/* Backtrack Routine */
/*********************/
void backtrack(void)
{
	int closestcell = -1;
	int shortestdistance = 255;
	int distancefromgoal = 0;
	int xtrack = 0;
	int ytrack = 0;

	// Flood from the mouses current position to every known cell
	floodfill(CURRENT_POSITION);

	// Go through the cell array and compare the distance from the current position (from floodfill) to all cells we have SEEN but not traveled to
	for(ytrack = 0; ytrack < MAZESIZE; ytrack++)
	{
		for(xtrack = 0; xtrack < MAZESIZE; xtrack++)
		{
			if(mapping_memory[xtrack][ytrack] == 1)
			{
				distancefromgoal = flood_memory[xtrack][ytrack];
				if(distancefromgoal < shortestdistance)
				{
					shortestdistance = distancefromgoal;
					closestcell = (xtrack << 4) + ytrack;
				}
			}
		}
	}
	// If there are no cells left to travel to then we have finished mapping the maze
	if(closestcell == -1)
		MappingComplete = TRUE;
	// If we aren't done then travel to the closest cell found
	else
	{
		findshortestpath(closestcell,BACKTRACK);
		movemouse(BACKTRACK);
	}
}

//This function adds cells adjacent to the headpointer to the tailpointer for later evaluation
void floodfill(int endlocation)
{
	int firstcellclear = 0;
	int yclear = 0;
	int xclear = 0;

	headpointer = 0;
	tailpointer = 1;

	// Clear the flooding array
	for(yclear = 0; yclear < MAZESIZE; yclear++)
	{
		for(xclear = 0; xclear < MAZESIZE; xclear++)
		{
			flood_memory[xclear][yclear] = 0xFF;
		}
	}

	checkqueue[headpointer] = endlocation;

	do{
		// Break up the x,y coordinates so they can be used to traverse the wall array
		int xposition = (checkqueue[headpointer] & 0xF0) / 0x10;
		int yposition = checkqueue[headpointer] & 0x0F;

		// Set the cell we are flooding from to a distance of 0
		if (firstcellclear == FALSE)
		{
			flood_memory[xposition][yposition] = 0;
			firstcellclear = TRUE;
		}

		// Distance from the center is stored per position
		distancefromcenter = FLOOD_CELL_START;

		// If the North cell is open then store its location so it can be flooded later
		if((FLOOD_WALL_NORTH == 0) && (FLOOD_CELL_NORTH == 255))
		{
			// Store this cells distance from the center in the memory array
			FLOOD_CELL_NORTH = distancefromcenter + 1;
			checkqueue[tailpointer] = checkqueue[headpointer] + 0x01;
			increasetailpointer();
		}

		// If the South cell is open then store its location so it can be flooded later
		if((FLOOD_WALL_SOUTH == 0) && (FLOOD_CELL_SOUTH == 255))
		{
			FLOOD_CELL_SOUTH = distancefromcenter + 1;
			checkqueue[tailpointer] = checkqueue[headpointer] - 0x01;
			increasetailpointer();
		}

		// If the East cell is open then store its location so it can be flooded later
		if((FLOOD_WALL_EAST == 0) && (FLOOD_CELL_EAST == 255))
		{
			FLOOD_CELL_EAST = distancefromcenter + 1;
			checkqueue[tailpointer] = checkqueue[headpointer] + 0x10;
			increasetailpointer();
		}

		// If the West cell is open then store its location so it can be flooded later
		if((FLOOD_WALL_WEST == 0) && (FLOOD_CELL_WEST == 255))
		{
			FLOOD_CELL_WEST = distancefromcenter + 1;
			checkqueue[tailpointer] = checkqueue[headpointer] - 0x10;
			increasetailpointer();
		}
		
		// Clear the queue at headpointer before moving to the next location
		checkqueue[headpointer] = 0x00;
		// Begin looking at the next cell in the flood
		increaseheadpointer();
	}while(headpointer != tailpointer);
}

// Increases the tailpointer or sets it back to zero if full
void increasetailpointer(void)
{
	if(tailpointer < QUEUESIZE-1)
		tailpointer++;
	else
		tailpointer = 0;
}
// Increases the headpointer or sets it back to zero if full
void increaseheadpointer(void)
{
	if(headpointer < QUEUESIZE-1)
		headpointer++;
	else
		headpointer = 0;
}

void findshortestpath(int startcell, int mode)
{
	// Break up the x,y coordinates so they can be used to traverse the wall array
	int xlocation = (startcell & 0xF0) / 0x10;
	int ylocation = startcell & 0x0F;
	int decision = 0;

	int distance = flood_memory[xlocation][ylocation];	
	movecounter = 0;
	do{
		decision = -1;
		distance = flood_memory[xlocation][ylocation];

		// NORTH 1 
		if((flood_memory[xlocation][ylocation+1] == distance - 1) && (ylocation < 15))
		{
			if(horizontal_wall_memory[xlocation][ylocation+1] == 0)
			{
				distance = flood_memory[xlocation][ylocation+1];
				decision = NORTH;
			}
		}
		// SOUTH 2
		if((flood_memory[xlocation][ylocation-1] == distance - 1) && (ylocation > 0))
		{
			if(horizontal_wall_memory[xlocation][ylocation] == 0)
			{
				distance = flood_memory[xlocation][ylocation-1];
				decision = SOUTH;
			}
		}
		// EAST  3 
		if((flood_memory[xlocation+1][ylocation] == distance - 1) && (xlocation < 15))
		{
			if(vertical_wall_memory[xlocation+1][ylocation] == 0)
			{
				distance = flood_memory[xlocation][ylocation+1];
				decision = EAST;
			}
		}
		// WEST  4
		if((flood_memory[xlocation-1][ylocation] == distance - 1) && (xlocation > 0))
		{
			if(vertical_wall_memory[xlocation][ylocation] == 0)
			{
				distance = flood_memory[xlocation][ylocation-1];
				decision = WEST;
			}
		}
		// FINISHED 5
		if((distance == 0) && (decision == -1))
			decision = FINISHED;

		if(decision == NORTH)
			ylocation++;
		if(decision == SOUTH)
			ylocation--;
		if(decision == EAST)
			xlocation++;
		if(decision == WEST)
			xlocation--;
		
		movelist[movecounter] = decision;
		if(decision != 5)
			movecounter ++;
	}while(decision != FINISHED);
}
