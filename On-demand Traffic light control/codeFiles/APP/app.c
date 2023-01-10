/*
 * app.c
 *
 * Created: 12/31/2022 4:07:25 PM
 *  Author: Ahmed Naeem
 */ 


#include "app.h"
#include "On_demandTrafficLight/state.h"
#include "On_demandTrafficLight/Normal_Module/normal.h"
#include "On_demandTrafficLight/Pedestrain_Module/pedestrian.h"



#include "stdtypes.h"
#include "atmega32.h"
#include "bitmath.h"
#include "DIO/DIO.h"
#include "TIMER0/timer0.h"
#include "EXTI/EXTI.h"

#include "LED/led.h"
#include "LED/led_cfg.h"



void IRQ_ISR()
{
	//flag
	Pedestrian_Flag =1;
	Pedestrian_Request(Normal_Currenr_Id);
}


void APP_Init()
{
	LED_Init();
	TIMER0_Init();
	TIMER0_Start();
	EXTI_Configs_t IRQ0 ={EXTI_0,RISINING_EDGE,IRQ_ISR} ;
	EXTI_Init(&IRQ0);
	
	// states Init
	Normal_Init();
	Pedestrian_Init();
	
	
}

void APP_start()
{
	Pedestrian_State();
	
	if(Pedestrian_Flag == 1)
	{
		Normal_State = State(CAR_Wait);
	
	}
	Normal_State();
	
		
}

