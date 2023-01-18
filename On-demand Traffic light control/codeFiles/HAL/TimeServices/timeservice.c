/*
 * timeservice.c
 *
 * Created: 1/17/2023 11:17:05 PM
 *  Author: ncm
 */ 
#include "timeservice.h"

volatile uint8 TS_DONE_FLAG =0;
static uint8 TS_preload;
static uint32 NofOVF;
static uint8 Firstflag =0;

void TOV0_ISR()
{
	static uint32 OVFcount;
	OVFcount++;
	if(OVFcount >= NofOVF)
	{
		TS_DONE_FLAG=1;
		TIMER0_Stop();
		OVFcount=0;
		Firstflag =0;
	}
	else
	{
		TCNT0 = TS_preload;
	}
	
}
void Time_Inilization()
{
	TIMER0_Init();
	TIMER0_OVF_CallBackFun=TOV0_ISR;
	
}
void waitNoblock_msec(uint16 NofSec)
{
    uint64 Nofmsec;
	static uint16 PrevNofSec;
	
	if((Firstflag==0) || (NofSec !=PrevNofSec ))
	{
		Nofmsec =(uint64)NofSec * 1000;
		NofOVF =TIMER0_Calculate(Nofmsec,&TS_preload);
		TIMER0_Start(TS_preload);
		PrevNofSec = NofSec;
		Firstflag=1; 
	}
	
}