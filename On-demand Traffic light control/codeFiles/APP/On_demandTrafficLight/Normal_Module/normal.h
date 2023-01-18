#ifndef NORMAL_H
#define NORMAL_H

#include "../APP/On_demandTrafficLight/state.h"
#include "../HAL/LED/led.h"
#include "../HAL/TimeServices/timeservice.h"


/* Normal Mode states */
enum
{
    CAR_Go,
    CAR_SteadyToStop,
    CAR_Stop,
    CAR_SteadyToGo,
	CAR_Wait,

} NORMAL_Mode_Id;

/* module initialization*/
void Normal_Init(void);

/* states handling function*/
Define_State(CAR_Go);
Define_State(CAR_SteadyToStop);
Define_State(CAR_Stop);
Define_State(CAR_SteadyToGo);
Define_State(CAR_Wait);


void (*Normal_State)();

extern int Normal_Currenr_Id ;
extern int Pedestrian_Flag;

#endif