#ifndef KEYPAD_CFG_H
#define KEYPAD_CFG_H

#include "stdtypes.h"
#include "DIO/DIO.h"

typedef struct
{
	PinConfig_t rows[4]; 	 	/*Rows are outputs*/
	PinConfig_t cols[4]; 		/*columns are inputs*/
	STATE_t defState;			    /*default state*/
}KeypadConfg_t;



extern KeypadConfg_t Keypads[];
extern uint8 KeypadsCount;

extern uint8 KeypadChars[4][4];

#endif
