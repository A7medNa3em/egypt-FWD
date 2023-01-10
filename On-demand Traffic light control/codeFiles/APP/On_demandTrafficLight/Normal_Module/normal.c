#include "normal.h"
#include "TIMER0/timer0.h"
#include "LED/led.h"


int Normal_Currenr_Id ;
int Pedestrian_Flag;

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
	T0_delay_ms(5000);
    // transate to CAR_SteadyToStop state
    Normal_State = State(CAR_SteadyToStop);
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
	for(int i=0 ; i<5; i++)
	{
		LED_ON(LED_1);
		T0_delay_ms(500);
		LED_OFF(LED_1);
		T0_delay_ms(500);
	}
	
	
    // transate to CAR_Stop state
    Normal_State = State(CAR_Stop);
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
	// busy wait 5 sec
	T0_delay_ms(5000);
    // transate to CAR_SteadyToGo state
    Normal_State = State(CAR_SteadyToGo);
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
    for(int i=0 ; i<5; i++)
    {
	    LED_ON(LED_1);
	    T0_delay_ms(500);
	    LED_OFF(LED_1);
	    T0_delay_ms(500);
    }
    
    // transate to CAR_Stop state
    Normal_State = State(CAR_Go);
}
Define_State(CAR_Wait)
{
	//do nothing
	    LED_OFF(LED_0);
	    LED_OFF(LED_1);
	    
	    LED_OFF(LED_2);
	    
}

void Pedestrian_HandlingDone()
{	
	Pedestrian_Flag =0;
	Normal_State = State(CAR_Go);
}