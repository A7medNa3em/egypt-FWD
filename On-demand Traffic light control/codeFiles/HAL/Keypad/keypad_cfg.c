#include "atmega32.h"
#include "stdtypes.h"
#include "keypad_cfg.h"
#include "DIO/DIO.h"


/* Available keypads and its pins, ports and default state*/
KeypadConfg_t Keypads[] =
{
		{
				{
						{  PIN_0, PORT_B, OUTPUT, FALSE},
						{  PIN_1, PORT_B, OUTPUT, FALSE},
						{  PIN_2, PORT_B, OUTPUT, FALSE},
						{  PIN_3, PORT_B, OUTPUT, FALSE}
				},

				{
						{  PIN_4, PORT_B, INPUT, FALSE},
						{  PIN_5, PORT_B, INPUT, FALSE},
						{  PIN_6, PORT_B, INPUT, FALSE},
						{  PIN_7, PORT_B, INPUT, FALSE},

				},

				LOW
		}
};

 uint8 KeypadChars[4][4] = {
										{'7' ,'8' ,'9' ,'A'},
										{'4', '5', '6', 'B'},
										{'1', '2', '3', 'C'},
										{'#' , '=', '0' , 'D'}
};

uint8 KeypadsCount = sizeof(Keypads) / sizeof(KeypadConfg_t);
