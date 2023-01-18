#include "normal.h"


int Normal_Currenr_Id ;
int Pedestrian_Flag;


#define __P__  5000
/* module initialization*/
void Normal_Init(void)
{
    /* init with CAR_Stop state */
    Normal_State = State(CAR_Stop);
}

/* states handling function*/
Define_State(CAR_Go)
{
    NORMAL_Mode_Id = CAR_Go;
	Normal_Currenr_Id = 0;
    // Car Green Led is on
	LED_ON(LED_0);
    // Other Leds is off
	LED_OFF(LED_1);
	LED_OFF(LED_2);
    // busy wait 5 sec
	//T0_delay_ms(__P__);
	waitNoblock_msec(__P__);
    // transate to CAR_SteadyToStop state
	if(TS_DONE_FLAG == 1)
	{
    Normal_State = State(CAR_SteadyToStop);
	TS_DONE_FLAG=0;
	}
}
Define_State(CAR_SteadyToStop)
{
    NORMAL_Mode_Id = CAR_SteadyToStop;
	Normal_Currenr_Id = 0;
    // Car Green Led is on
	LED_ON(LED_0);
	// Other Leds is off
	LED_OFF(LED_2);
	
    // Car Yellow Led is blink for 5 sec
	static int i=0;
	waitNoblock_msec(__P__/10);
	if(TS_DONE_FLAG == 1)
	{
		LED_TOGGLE(LED_1);
		i++;
		TS_DONE_FLAG=0;
	}
	
	
    // transate to CAR_Stop state
	if(i>10)
	{
    Normal_State = State(CAR_Stop);
	i=0;
	}
}
Define_State(CAR_Stop)
{
    NORMAL_Mode_Id = CAR_Stop;
    Normal_Currenr_Id = 1;
    // Car Red Led is on
	LED_ON(LED_2);
	// Other Leds is off
	LED_OFF(LED_0);
	LED_OFF(LED_1);

	waitNoblock_msec(__P__);
    // transate to CAR_SteadyToGo state
	if(TS_DONE_FLAG == 1)
	{
    Normal_State = State(CAR_SteadyToGo);
	TS_DONE_FLAG=0;
	}
}
Define_State(CAR_SteadyToGo)
{
    NORMAL_Mode_Id = CAR_SteadyToGo;
	Normal_Currenr_Id = 0;
    // Car Red Led is on
    LED_ON(LED_2);
    // Other Leds is off
    LED_OFF(LED_0);
    
    // Car Yellow Led is blink for 5 sec
	waitNoblock_msec(__P__/10);
	static int i=0;
	if(TS_DONE_FLAG == 1)
	{
	    LED_TOGGLE(LED_1);
		i++;
		TS_DONE_FLAG =0;
		
	}
    
    // transte to CAR_Stop state
	if(i>10)
	{
		Normal_State = State(CAR_Go);
		i=0;
	}
}
Define_State(CAR_Wait)
{
	//do nothing
	    
}

void Pedestrian_HandlingDone()
{	
	Pedestrian_Flag =0;
	Normal_State = State(CAR_Go);
}