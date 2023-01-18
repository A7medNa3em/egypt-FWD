/*
 * led.c
 *
 * Created: 12/31/2022 4:16:35 PM
 *  Author: ncm
 */ 

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
LED_Error_t LED_ON(LED_t led)
{
	
	LED_Error_t LED_state = LED_ERROR;
	if(led <LedConfigCount )
	{
		LED_state = LED_OK;
		MCAL_DIO_WritePin(LedConfigs[led].ledpin,LedConfigs[led].ledport,LedConfigs[led].activestate);
	}
	else
	{
		LED_state = LED_UNCONFIGURED;
	}
	
	return LED_state;
	
}

/*Write Low to Led*/
LED_Error_t LED_OFF(LED_t led)
{
	LED_Error_t LED_state = LED_ERROR;
	if(led <LedConfigCount )
	{
		LED_state = LED_OK;
		if(LedConfigs[led].activestate == ACTIVE_HIGH)
		{
		MCAL_DIO_WritePin(LedConfigs[led].ledpin,LedConfigs[led].ledport, LOW);
		
		}
		else if(LedConfigs[led].activestate == ACTIVE_LOW)
		{
			MCAL_DIO_WritePin(LedConfigs[led].ledpin,LedConfigs[led].ledport, HIGH);
		}
		else
		{
			LED_state = LED_ERROR;
			
		}
		
	}
	else
	{
		LED_state = LED_UNCONFIGURED;
		
	}
	
	return LED_state;
	
	
}

LED_Error_t LED_TOGGLE(LED_t led)
{
	
	LED_Error_t LED_state = LED_ERROR;
	if(led <LedConfigCount )
	{
		LED_state = LED_OK;
	MCAL_DIO_TogglePin(LedConfigs[led].ledpin,LedConfigs[led].ledport);
	
	}
	else
	{
		LED_state = LED_UNCONFIGURED;
	}
	
	return LED_state;
}