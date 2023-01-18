/*
 * app.c
 *
 * Created: 12/31/2022 4:07:25 PM
 *  Author: Ahmed Naeem
 */ 


#include "app.h"

#include "../APP/On_demandTrafficLight/state.h"
#include "../APP/On_demandTrafficLight/Normal_Module/normal.h"
#include "../APP/On_demandTrafficLight/Pedestrain_Module/pedestrian.h"



void Request_ISR()
{
	Normal_State = State(CAR_Wait);
	TS_DONE_FLAG=0;
	Pedestrian_Request(Normal_Currenr_Id);
	
}


void APP_Init()
{
	LED_Init();
	Time_Inilization();
	EXTI_Configs_t IRQ0 ={EXTI_0,RISINING_EDGE,Request_ISR} ;
	EXTI_Init(&IRQ0);
	
	// states Init
    Normal_Init();
	Pedestrian_Init();
	
	
}

void APP_start()
{
	Pedestrian_State();
	Normal_State();
		
}

