/*
 * led.h
 *
 * Created: 12/31/2022 4:16:16 PM
 *  Author: ncm
 */ 



#ifndef LED_H_
#define LED_H_

#include "../LIB/atmega32.h"
#include "../LIB/stdtypes.h"
#include "../LIB/bitmath.h"
#include "../MCAl/DIO/DIO.h"
#include "../MCAl/TIMER0/timer0.h"
#include "../MCAL/EXTI/EXTI.h"

typedef enum
{
	LED_0,
	LED_1,	
	LED_2,
	LED_3,
	LED_4,
	LED_5,
	LED_6,
	LED_7,
}LED_t;


typedef enum
{
	LED_OK,
	LED_UNCONFIGURED,
	LED_ERROR,
}LED_Error_t;


void LED_Init();
LED_Error_t LED_ON(LED_t led);
LED_Error_t LED_OFF(LED_t led);
LED_Error_t LED_TOGGLE(LED_t led);


#endif /* LED_H_ */