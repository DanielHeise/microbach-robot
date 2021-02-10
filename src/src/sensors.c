/**
 * 
 * file:            sensors.c
 * author:          Daniel Heise
 * description:     implementation for TODO
 * 
 */
#include "sensors.h"
#include "adc.h"

/************************************************************************
| Read Sensor Routine:													|
|	This routine chooses an A/D channel, reads the voltage and stores	|
|	the value in the appropriate sensor variable for analysis			|
************************************************************************/
void read_sensors(u8_t FirstSensorToRead, u8_t LastSensorToRead)
{
	ir_sensor = FORWARD_SENSOR;
	ADC_CHANNEL = (ADC_CHANNEL & 0xC3) | channel[ir_sensor];
	stablize_channel();							// 11.5 uSecs

	while(!(ir_sensor > LastSensorToRead))
	{
		START_READING = YES;						// Start reading sensor
		while(ADC_INPROGRESS);										// Assign channel selection to unmasked bits, store in ADCON0
		*IRsensor_ptr[ir_sensor] = analyze_sensor_data(ir_sensor);
		if(!AnalogRead && (ir_sensor == FORWARD_SENSOR))
			ir_sensor = FirstSensorToRead - 1;
		++ir_sensor;
		ADC_CHANNEL = (ADC_CHANNEL & 0xC3) | channel[ir_sensor];	// Mask off appropriate bits for munipulation (bits 2-5)

		if(!(*IRsensor_ptr[ir_sensor-1] > wall_voltage[ir_sensor-1] - 100))
			LastSensorToRead = LEFT_SIDE_SENSOR;
	}
	ir_sensor = CLEARED;

} // read_sensors()

/************************************************************************
| Analyze Sensor Data Function:											|
|	This function takes the A/D result registers just read in and		|
|	calculates the voltage to determine if a wall is present or not		|
************************************************************************/
u16_t analyze_sensor_data(u8_t current_sensor)
{
	/********* Locals *********************/
	enum{ NO_WALL, WALL };
	u16_t hi_byte, result_buff;
	u16_t lo_byte, data_buff;
	/**************************************/

	hi_byte = result_buff = CLEARED;
	lo_byte = data_buff = CLEARED;

	lo_byte = ADRESL;						// TMR0 Lower Byte
	hi_byte = ADRESH << 8;					// TMR0 Upper Byte
	result_buff = (lo_byte + hi_byte);		// Calculate TMR0 time

	if(!AnalogRead)
	{
		if(result_buff > wall_voltage[current_sensor])		// Voltage Reading
			data_buff = WALL;
		else
			data_buff = NO_WALL;
	}
	else
	{
		if(result_buff < wall_voltage[current_sensor])
		{
			if(current_sensor == RIGHT_SIDE_SENSOR)
				correct_right = YES;
			else /* (current_sensor == LEFT_SIDE_SENSOR) */
				correct_left = YES;
		}	
		else
		{
			if(!(correct_right || correct_left))
			{
				CorrectRight = CorrectLeft = NO;
			}
		}
		data_buff = result_buff;

	}

	return(data_buff);

} // End analyze_sensor_data

/************************************************************************
| Stablize_Channel Routine:												|
|	This routine runs long enough for the ADC channels to stablize		|
|	over the required Tad time	(approximately 11.5us)					|
************************************************************************/
void stablize_channel(void)
{
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();
	NOP();

} // End stablize_channel
