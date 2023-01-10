/*
 * timer_0.h
 *
 * Created: 1/2/2023 9:52:49 PM
 *  Author: ncm
 */ 


#ifndef TIMER_0_H_
#define TIMER_0_H_

#include "stdtypes.h"




/*----------------------------------------------------
				   	Timer0 Configurations 
-----------------------------------------------------*/


/* Timer 0 bits */
#define TIMER0_BITS_NUM   8
/* Number of ticks to reach Overflow*/
#define TIMER0_MAX_TICKS    256



/********************** Mode **********************/

/*
		--------------------------------------------------------
	    WGM01   WGM01	Mode                OCR0		TOV0
		--------------------------------------------------------
		0		0		Normal		        Immediate	 MAX
		0		1		PWM, Phase Correct  TOP			 BOTTOM
		1		0		CTC                 Immediate	 MAX
		1		1		Fast PWM            BOTTOM		 MAX
		--------------------------------------------------------
*/


/* @ref TIM0_MOD */
#define TIM0_MOD_NORMAL 						0
#define TIM0_MOD_PWM_PHASE_CORRECT	 			1
#define TIM0_MOD_CTC                			2
#define TIM0_MOD_PWM_FAST                		3


/********************** Clock select **********************/

/* @ref TIM0_CS*/
#define TIM0_CS_STOPPED 					0
#define TIM0_CS_PRESCALER_1					1
#define TIM0_CS_PRESCALER_8					2
#define TIM0_CS_PRESCALER_64				3
#define TIM0_CS_PRESCALER_256				4
#define TIM0_CS_PRESCALER_1024 				5

#define TIM0_CS_EXTERNAL_F_EDGE				6
#define TIM0_CS_EXTERNAL_R_EDGE				7


/******************* CTC Mode Configurations *******************/

/* @ref  TIMER0_OC0_Mod */
/*
			COM01 COM00
			 0	  0			Normal port operation, OC0 disconnected.
			 0    1			Toggle OC0 on compare match
			 1    0			Clear OC0 on compare match
			 1    1			Set OC0 on compare match
*/
typedef enum 
{
	TIMER0_OC0_DISCONNECTED,
	TIMER0_OC0_TOGGLE,
	TIMER0_OC0_CLR,
	TIMER0_OC0_SET,
}OC0_MOd_t;




/*************************************************************************
--------------------------------------------------------------------------
							 	Timer0 APIs 
--------------------------------------------------------------------------
*************************************************************************/

/* Delay micro second MACRO */
/*
#define T0_delay_us(Period) (\
							do{\
							 TIMER0_Start(); \
							 TIMER0_SetBusyWait_us(Period);\
							 TIMER0_Stop();\
							}while(0)) */

/*
*
*		 @fun		  : TIMER0_Init
*		 @Description : Initialize timer 0 with its configurations
*						- Mode 
*						- Enable/disable Interrupt
*
*/
void TIMER0_Init();

void T0_delay_ms(uint64 Period);

/*
*
*		 @fun		  : TIMER0_Start
*		 @Description : start timer 0 by enable clock
*						based on TIM0_CLOCK_SELECT macro
*						
*/
void TIMER0_Start();


/*
*
*		 @fun		  : TIMER0_Stop
*		 @Description : stop timer 0 by disable clock
*						
*
*/
void TIMER0_Stop();


/*
*
*		 @fun			 : TIMER0_ReadTimerValue
*		 @Description	 : Read TCNT0 value 
*        @Pre-conditions : Timer 0 is initialized at any mode 
*						   and stated 
*/
void TIMER0_ReadTimerValue(uint8 * value);


/*
*
*		 @fun			 : TIMER0_SetTimerValue
*		 @Description	 : Set TCNT0 value 
*       
*/
void TIMER0_SetTimerValue(uint8 value);




/*
*
*		 @fun			 : TIMER0_SetBusyWait_us
*		 @Description	 : Generate rime delay (busy wait period) in micro second
*						   Max period for single overflow in case of 8MHz clock
*                           ------------------------------------
*						   Pre-scaler          Max period
*						   ------------------------------------
*						   8                  256
*						   64				  2_048
*						   256				  16_384
*						   1024               65_536
*						   --------------------------------------
*		@Pre-conditions : TIMER CLK SOURCE IS clock with prescaler greater than 1
*
*/
void TIMER0_SetBusyWait_us(uint64 period);


/*
*
*		 @fun			 : TIMER0_ReadFlag
*		 @Description	 : Read TOVF0 in normal mode
*						   Read OCF0 in CTC mode
*     
*/
uint8 TIMER0_ReadFlag();

/*
*		 @fun			 : TIMER0_SetOutputCompareValue
*		 @Description	 : Set Output Compare register by a value
*						   
*/
void TIMER0_SetOutputCompareValue(uint8 value);


/*
*		 @fun			 : TIMER0_SetOutputComparePinMode
*		 @Description	 : Set Output Compare Pin Mode according to  @ref  TIMER0_OC0_Mod
						   The OC0 value will not be visible on the port pin unless the data direction for the
				            pin is set to output
						 
*
*/
void TIMER0_SetOutputComparePinMode(OC0_MOd_t MODE);






/*
*		TIMER0 Set CallBack Function
*		Set CallBack Function to be called  at ISR in case of interrupt 
*/
/* Timer 0 overflow ISR call back function*/
extern void (*TIMER0_OVF_CallBackFun)(void) ;

/* Timer 0 Output Compare ISR call back function*/
extern void (*TIMER0_COMP_CallBackFun)(void) ;


#endif /* TIMER_0_H_ */