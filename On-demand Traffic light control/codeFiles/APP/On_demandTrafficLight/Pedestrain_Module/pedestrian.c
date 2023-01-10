#include "TIMER0/timer0.h"
#include "LED/led.h"
#include "pedestrian.h"


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
    // busy wait 5 sec
	T0_delay_ms(5000);
    // transate to CAR_SteadyToStop state
    Pedestrian_State = State(PEDESTRIAN_SteadyToStop);
}
Define_State(PEDESTRIAN_SteadyToStop)
{
	// Pedestrian Green Led is on
	LED_ON(LED_3);

	// Other Leds is off
	LED_OFF(LED_5);
	LED_OFF(LED_0);
	
    // Pedestrian and Car Yellow Leds are blinking for 5 sec
	for(int i=0 ; i<5; i++)
	{
		LED_ON(LED_1);
		LED_ON(LED_4);
		T0_delay_ms(500);
		LED_OFF(LED_1);
		LED_OFF(LED_4);
		T0_delay_ms(500);
	}
	

	
	// transate to PEDESTRIAN_Waiting state
	Pedestrian_State = State(PEDESTRIAN_Waiting);
	
}


Define_State(PEDESTRIAN_Stop)
{
    // Pedestrian Red Led is on
	LED_ON(LED_5);
    // Other Leds is off
	LED_OFF(LED_3);
	LED_OFF(LED_3);
    // busy wait 5 sec
	//T0_delay_ms(5000);
	
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
     for(int i=0 ; i<5; i++)
     {
	     LED_ON(LED_1);
	     LED_ON(LED_4);
	     T0_delay_ms(500);
	     LED_OFF(LED_1);
	     LED_OFF(LED_4);
	     T0_delay_ms(500);
     }
   
    // busy wait 5 sec`
    // call Pedestrian_Done
    // transate to PEDESTRIAN_Go state
    Pedestrian_State = State(PEDESTRIAN_Go);
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
    (Normal_id == 1) ? (Pedestrian_State = State(PEDESTRIAN_Go)) : (Pedestrian_State = State(PEDESTRIAN_SteadyToGo));
	//Pedestrian_State();
}
