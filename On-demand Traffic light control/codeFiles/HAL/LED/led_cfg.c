/*
 * led_cfg.c
 *
 * Created: 12/31/2022 4:30:30 PM
 *  Author: Ahmed Naeem
 */ 

#include "led_cfg.h"


/* 
Led Configurations 
@note : Pin and Port must not be used by another resources
LED_t mapped to led index
i.e LED_0 --> LedConfigs[0]
*/

LEDConfig_t LedConfigs[]={
	
	{PIN_0 , PORT_A , ACTIVE_HIGH},
	{PIN_1 , PORT_A , ACTIVE_HIGH},
	{PIN_2 , PORT_A , ACTIVE_HIGH},
	{PIN_0 , PORT_B , ACTIVE_HIGH},
	{PIN_1 , PORT_B , ACTIVE_HIGH},
	{PIN_2 , PORT_B , ACTIVE_HIGH},
};



uint8 LedConfigCount = sizeof(LedConfigs)/sizeof(LEDConfig_t);