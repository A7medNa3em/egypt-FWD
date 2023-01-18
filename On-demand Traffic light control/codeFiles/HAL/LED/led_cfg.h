/*
 * led_cfg.h
 *
 * Created: 12/31/2022 4:30:49 PM
 *  Author: Ahmed Naeem
 */ 


#ifndef LED_CFG_H_
#define LED_CFG_H_

#include "led.h"


typedef struct
{
	PIN_t ledpin;
	PORT_t ledport;
	ActiveState_t activestate;
}LEDConfig_t;

extern LEDConfig_t LedConfigs[];
extern uint8 LedConfigCount ;

#endif /* LED_CFG_H_ */