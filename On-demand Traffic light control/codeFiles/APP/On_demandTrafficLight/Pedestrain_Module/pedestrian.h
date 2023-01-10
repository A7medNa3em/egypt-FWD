#ifndef PEDESTRIAN_H
#define PEDESTRIAN_H

#include "state.h"

/* Pedestrian Mode states */

enum
{
    PEDESTRIAN_Go,
    PEDESTRIAN_SteadyToStop,
    PEDESTRIAN_Stop,
    PEDESTRIAN_SteadyToGo,
	PEDESTRIAN_Waiting,

} PEDESTRIAN_Id;

/* module initialization*/
void Pedestrian_Init(void);

/* states handling function*/
Define_State(PEDESTRIAN_Go);
Define_State(PEDESTRIAN_SteadyToStop);
Define_State(PEDESTRIAN_Stop);
Define_State(PEDESTRIAN_SteadyToGo);
Define_State(PEDESTRIAN_Waiting);


void (*Pedestrian_State)();

#endif