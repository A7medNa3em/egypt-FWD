/*
 * button.h
 *
 * Created: 12/31/2022 9:59:05 PM
 *  Author: ncm
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

#include "DIO/DIO.h"


typedef enum
{
	BUTTON_0,
	BUTTON_1,
	BUTTON_2,
}BUTTON_t;


typedef enum
{
	NOT_PRESSED,
	PRESSED,
}BUTTON_Status_t;

void BUTTON_Init();
BUTTON_Status_t BUTTON_GetStatus( BUTTON_t button);






#endif /* BUTTON_H_ */