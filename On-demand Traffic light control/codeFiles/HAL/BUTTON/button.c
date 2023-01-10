/*
 * button.c
 *
 * Created: 12/31/2022 9:58:34 PM
 *  Author: Ahmed Naeem
 */ 

#include "stdtypes.h"
#include "DIO/DIO.h"
#include "button.h"
#include "button_cfg.h"



void BUTTON_Init()
{
	uint8 index=0;
	for(index = 0 ; index <ButtonConfigCount ; index++)
	{
		MCAL_DIO_InitPin(ButtonConfigs[index].buttonpin,ButtonConfigs[index].buttonport,INPUT,ButtonConfigs[index].internalpullup);
	}
	
}
BUTTON_Status_t BUTTON_GetStatus( BUTTON_t button)
{
	STATE_t ButtonState ;
	BUTTON_Status_t ButtonStatus;
	ButtonState = MCAL_DIO_ReadPin(ButtonConfigs[button].buttonpin,ButtonConfigs[button].buttonport);
	
	/*
		ACTIVE		STATE		XOR     ~
		-----------------------------------------
		LOW			LOW			0		1	(PRESSED)
		LOW			HIGH		1		0	(NOT_PRESSED)
		HIGH		LOW			1		0	(NOT_PRESSED)
		HIGH		HIGH		0		1   (PRESSED)
	*/
	
	ButtonStatus = ~( ButtonState ^ ButtonConfigs[button].activestate);
	
	return ButtonStatus;
	
}


