/*
 * timer_0.c
 *
 * Created: 1/2/2023 9:52:24 PM
 *  Author: Ahmed Naeem
 */ 

#include "atmega32.h"
#include "stdtypes.h"
#include "bitmath.h"
#include "timer0.h"
#include "timer0_cfg.h"

/* Timer 0 overflow ISR call back function*/
void (*TIMER0_OVF_CallBackFun)(void) ;

/* Timer 0 Output Compare ISR call back function*/
void (*TIMER0_COMP_CallBackFun)(void) ;
/*
*
*		 @fun		  : TIMER0_Init
*		 @Description : Initialize timer 0 with its configurations
*						- Mode
*						- Enable/disable Interrupt
*
*/
void TIMER0_Init()
{
 /* 1- Set mode */
	CLR_BIT(TCCR0 , 3);
	CLR_BIT(TCCR0 , 6);
	/* first bit at bit6 WGM00 */
	TCCR0 |= ((TIM0_MOD << 6) & 0x40);
	/* second bit at bit3 WGM01 */
	TCCR0 |= (((TIM0_MOD >> 1) << 3) & 0x08);
	
	
/* 2- Enable Interrupt */
	#if TIMER0_ENABLE_INTERRUPT
	/* Enable Global Interrupt*/
	GIE_ENABLE();
	/* check mode */
	/* TOV0 enable */
	SET_BIT(TIMSK ,0);
	/* OCF0 enable */
	SET_BIT(TIMSK ,1);
	#endif 
	
}




/*
*
*		 @fun		  : TIMER0_Start
*		 @Description : start timer 0 by enable clock
*						based on TIM0_CLOCK_SELECT macro
*
*/
void TIMER0_Start()
{
	/* clear first 3 bits in TCCR0 then put value of TIM0_CLOCK_SELECT */
	
	TCCR0 &= ~(0x07);
	TCCR0 |= (TIM0_CLOCK_SELECT & 0x07);
	
}


/*
*
*		 @fun		  : TIMER0_Stop
*		 @Description : stop timer 0 by disable clock
*
*
*/
void TIMER0_Stop()
{
	/* clear first 3 bits in TCCR0 */
	TCCR0 &= ~(0xf7);
}


/*
*
*		 @fun			 : TIMER0_ReadTimerValue
*		 @Description	 : Read TCNT0 value
*        @Pre-conditions : Timer 0 is initialized at any mode
*						   and stated
*/
void TIMER0_ReadTimerValue(uint8 * value)
{
	*value = TCNT0;
}


/*
*
*		 @fun			 : TIMER0_SetTimerValue
*		 @Description	 : Set TCNT0 value
*
*/
void TIMER0_SetTimerValue(uint8 value)
{
	TCNT0 = value;
}





/*
*
*		 @fun			 : TIMER0_SetBusyWait_us
*		 @Description	 : Generate rime delay (busy wait period) in micro second
*						   Max period for single over flow in case of 8MHz
*                           ------------------------------------
*						   Pre-scaler          Max period 
*						   ------------------------------------
*						   8                  256  
*						   64				  2_048
*						   256				  16_384
*						   1024               65_536
*						   --------------------------------------
*		@PRECONDTION  : TIMER CLK SOURCE IS clock with prescaler geater than 1
*
*/
void TIMER0_SetBusyWait_us(uint64 period)
{
	uint32  NumOfOverflows  ;
	volatile uint32 TickTime ;
	uint8 preload;
	uint64 DesiredTicks, requiredNumOfOverflows;
	
	
	
	/* Calculate tick time*/
	TickTime = ((TIM0_PRESCALER * 1000000U) / SYS_CLK) ;
	DesiredTicks =(uint64) period / TickTime ;
	
	if(DesiredTicks < TIMER0_MAX_TICKS)
	{
		TCNT0 = TIMER0_MAX_TICKS - DesiredTicks;
		
		/* waiting TOV0 flag */
		while(GET_BIT(TIFR ,0) == 1);
		/* Set TOV0 flag to clear*/
		SET_BIT(TIFR ,0 );
		
	}
	else if(DesiredTicks == TIMER0_MAX_TICKS)
	{
		TCNT0 = 0;
		
		/* waiting TOV0 flag */
		while(GET_BIT(TIFR ,0) == 1);
		/* Set TOV0 flag to clear*/
		SET_BIT(TIFR ,0 );
		
	}
	else if(DesiredTicks >TIMER0_MAX_TICKS)
	{
		/* Calculate pre-load and number of overflows */
		requiredNumOfOverflows = ((uint64)DesiredTicks * 100)/TIMER0_MAX_TICKS ;  // scaled x100 to get fraction
		
		NumOfOverflows = requiredNumOfOverflows /100 ;
		
		/*Method 2 --> preload for only first overflow
			fraction = requiredNumOfOverflows - NumOfOverflows *100
		*/
		
		// Method 1  --> prload for every preload overflow
		if((requiredNumOfOverflows - NumOfOverflows *100 ) > 0)
		{
			NumOfOverflows++;
		}
		
		// preload = TIMER0_MAX_TICKS - (fraction *  TIMER0_MAX_TICKS /100 )
		preload = TIMER0_MAX_TICKS - DesiredTicks/NumOfOverflows ; 
		
		TCNT0 = preload;
		
		while(NumOfOverflows > 0)
		{
			NumOfOverflows--;
			/* waiting TOV0 flag */
			while(GET_BIT(TIFR ,0) != 1);
			
			/* Set TOV0 flag to clear*/
			SET_BIT(TIFR ,0 );
		
			TCNT0 = preload;
			
		}
	}
}

void T0_delay_ms(uint64 Period)
{
	uint32 i;

	for(i=0; i<1000; i++ )
	{
		TIMER0_SetBusyWait_us(Period);
	}
}


/*
*
*		 @fun			 : TIMER0_ReadFlag
*		 @Description	 : Read TOVF0 in normal mode
*						   Read OCF0 in CTC mode
*
*/
uint8 TIMER0_ReadFlag()
{
	uint8 flag;
	#if TIM0_MOD == TIM0_MOD_NORMAL 
	flag = GET_BIT(TIFR ,0);
	#elif TIM0_MOD == TIM0_MOD_CTC
	flag = GET_BIT(TIFR ,1);
	#endif
	
	return flag;
}


/*
*		 @fun			 : TIMER0_SetOutputCompareValue
*		 @Description	 : Set Output Compare register by a value
*
*/
void TIMER0_SetOutputCompareValue(uint8 value)
{
	OCR0 = value;
}


/*
*		 @fun			 : TIMER0_SetOutputComparePinMode
*		 @Description	 : Set Output Compare Pin Mode according to @ref  TIMER0_OC0_MOd
						   The OC0 value will not be visible on the port pin unless 
						   the data direction for the pin is set to output
						 
*
*/
void TIMER0_SetOutputComparePinMode(OC0_MOd_t MODE)
{
	/* Set bit PB2 as output if connected */
	 if (MODE > 0)
	 {
	 SET_BIT(DDRB,3);
	 
	 }
	
	/* Set mode of OC0 pin mode
	   COM01 bit5   COM00 bit4  in RCCR0
	 */
	TCCR0 &= ~(0x30);
	TCCR0 |= ((MODE <<4) & 0x30 );
	
}





void __vector_10 (void) __attribute__((signal));
void __vector_10 (void)
{
	if (TIMER0_COMP_CallBackFun != NULL)
	{
		TIMER0_COMP_CallBackFun();
	}
	
}

void __vector_11 (void) __attribute__((signal));
void __vector_11 (void)
{
	if (TIMER0_OVF_CallBackFun != NULL)
	{
		TIMER0_OVF_CallBackFun();
	}
}



