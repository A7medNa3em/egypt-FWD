/*
 * led.c
 *
 * Created: 12/31/2022 4:16:35 PM
 *  Author: ncm
 */ 


#include "stdtypes.h"
#include "DIO/DIO.h"
#include "led.h"
#include "led_cfg.h"

/* 
Initialize Led in Led configurations array as Output 
with configurable pin, port , with/without internal pull up resistor
and configurable activation state depend on HW connections 
*/
void LED_Init()
{
	uint8 index=0;
	 for (index = 0; index < LedConfigCount; index++)
	 {
		 MCAL_DIO_InitPin(LedConfigs[index].ledpin,LedConfigs[index].ledport,OUTPUT,FALSE);
	 }
	
}

/*Write high to Led*/
void LED_ON(LED_t led)
{
	MCAL_DIO_WritePin(LedConfigs[led].ledpin,LedConfigs[led].ledport,LedConfigs[led].activestate);
}

/*Write Low to Led*/
void LED_OFF(LED_t led)
{
	if(LedConfigs[led].activestate == ACTIVE_HIGH)
	MCAL_DIO_WritePin(LedConfigs[led].ledpin,LedConfigs[led].ledport, LOW);
	else
	{
	MCAL_DIO_WritePin(LedConfigs[led].ledpin,LedConfigs[led].ledport, HIGH);
	
	}
	
}

void LED_TOGGLE(LED_t led)
{
	MCAL_DIO_TogglePin(LedConfigs[led].ledpin,LedConfigs[led].ledport);
}