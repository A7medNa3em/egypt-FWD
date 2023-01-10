/*
 * led.h
 *
 * Created: 12/31/2022 4:16:16 PM
 *  Author: ncm
 */ 


#ifndef LED_H_
#define LED_H_

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

void LED_Init();
void LED_ON(LED_t led);
void LED_OFF(LED_t led);
void LED_TOGGLE(LED_t led);


#endif /* LED_H_ */