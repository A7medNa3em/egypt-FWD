#include "pedestrian.h"
#include "../HAL/LED/led.h"


#define __P__  5000
/* module initialization*/
void Pedestrian_Init(void)
{
    /* init with PEDESTRIAN_Stop state */
    Pedestrian_State = State(PEDESTRIAN_Stop);
}

/* states handling function*/

/*the pedestrian's Green LED and the cars' Red LEDs will be on for five seconds,
 this means that pedestrians can cross the street while the pedestrian's Green LED is on.*/
Define_State(PEDESTRIAN_Go)
{
    // Pedestrian Green Led is on
	LED_ON(LED_3);
	LED_ON(LED_2);   // Car Red Led
    // Other Leds is off
	LED_OFF(LED_4);
	LED_OFF(LED_5);
	LED_OFF(LED_0);
	LED_OFF(LED_1);
    waitNoblock_msec(__P__);
    // transate to CAR_SteadyToStop state
	if(TS_DONE_FLAG == 1)
	{
    Pedestrian_State = State(PEDESTRIAN_SteadyToStop);
	TS_DONE_FLAG=0;
	}
}
Define_State(PEDESTRIAN_SteadyToStop)
{
	// Pedestrian Green Led is on
	LED_ON(LED_3);

	// Other Leds is off
	LED_OFF(LED_5);
	LED_OFF(LED_0);
	
    // Pedestrian and Car Yellow Leds are blinking for 5 sec
	  static int i=0;
	  waitNoblock_msec(__P__/10);
	  if(TS_DONE_FLAG == 1)
	  {
		  LED_TOGGLE(LED_1);
		  LED_TOGGLE(LED_4);
		  i++;
		  TS_DONE_FLAG=0;
	  }
	  
	// transate to PEDESTRIAN_Waiting state
	if(i>10)
	{
		Pedestrian_State = State(PEDESTRIAN_Waiting);
		i=0;
	}
	
}


Define_State(PEDESTRIAN_Stop)
{
    // Pedestrian Red Led is on
	LED_ON(LED_5);
    // Other Leds is off
	LED_OFF(LED_3);
	LED_OFF(LED_3);
	
}


/*Yellow LED is blinking, the pedestrian Red LED will be on then both Yellow LEDs start to blink for five seconds,
then the cars' Red LED and pedestrian Green LEDs are on for five seconds,
this means that pedestrian must wait until the Green LED is on.*/
Define_State(PEDESTRIAN_SteadyToGo)
{
	  // Pedestrian Red Led is on
	  LED_ON(LED_5);
	 //Pedestrian Green Led is off
	  LED_OFF(LED_3);
	  
     // Pedestrian and Car Yellow Leds are blinking for 5 sec
	   static int i=0;
	   waitNoblock_msec(__P__/10);
	  if(TS_DONE_FLAG == 1)
	  {
		  LED_TOGGLE(LED_1);
		  LED_TOGGLE(LED_4);
		  i++;
		  TS_DONE_FLAG=0;
	  }
   
    // transate to PEDESTRIAN_Go state
	if(i >10 )
	{
    Pedestrian_State = State(PEDESTRIAN_Go);
	i=0;
	}
}
Define_State(PEDESTRIAN_Waiting)
{
	PEDESTRIAN_Id = PEDESTRIAN_Waiting;
	LED_OFF(LED_3);
	LED_OFF(LED_4);
	LED_ON(LED_5);
	Pedestrian_State = State(PEDESTRIAN_Stop);
	Pedestrian_HandlingDone();
}

void Pedestrian_Request(int Normal_id)
{
    /*If pressed when the cars' Red LED is on, the pedestrian's in PEDESTRIAN_Go state
 -If pressed when the cars' Green LED is on or the cars'
 */
    if ((Normal_id == 1)&&  (Pedestrian_State == State(PEDESTRIAN_Stop)))
    {
      (Pedestrian_State = State(PEDESTRIAN_Go)) ;
    }else if( Pedestrian_State == State(PEDESTRIAN_Stop))
	{
		(Pedestrian_State = State(PEDESTRIAN_SteadyToGo));
		
	}
	
}
