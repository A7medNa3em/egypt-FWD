/*
 * timeservice.h
 *
 * Created: 1/17/2023 11:17:27 PM
 *  Author: ncm
 */ 


#ifndef TIMESERVICE_H_
#define TIMESERVICE_H_

#include "../MCAl/TIMER0/timer0.h"

extern volatile uint8 TS_DONE_FLAG;

void Time_Inilization();

/* NofSec number of seconds */
void waitNoblock_msec(uint16 NofSec);




#endif /* TIMESERVICE_H_ */