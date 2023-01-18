/*
 *		 EXTI.h
 *
 *		Created: 1/3/2023 2:24:43 PM
 *		Author: Ahmed Naeem
 */ 


#ifndef EXTI_H_
#define EXTI_H_


#include "../LIB/atmega32.h"
#include "../LIB/stdtypes.h"
#include "../LIB/bitmath.h"



/***************** Interrupt Vectors ************************/
/*

in case providing fixed names for ISR 

#define EXTI0  __vector_1
#define EXTI1  __vector_2
#define EXTI2  __vector_3

#define ISR(INT_VECT)  void INT_VECT __attribute__((signal, used));\
void INT_VECT(void)
*/


void __vector_1(void) __attribute__((signal, used));
void __vector_2(void) __attribute__((signal, used));
void __vector_3(void) __attribute__((signal, used));




/************************** EXTI Configurations ******************************/
typedef enum
{
	EXTI_0,
	EXTI_1,
	EXTI_2,
}EXTI_num_t;

/* EXTI_sensitivity --> specify interrupt senstivity 
in pins ISCx0 , ISCx1 in MCUCR for INT0, INT1
and pin ISC2 in MCUCSR for INT2 (only falling or rising edge)		
 */
typedef enum
{
	LOW_LEVEL,
	TOGGLE_LEVEl,
	FALLING_EDGE,
	RISINING_EDGE,
	
}EXTI_sensitivity_t;

typedef struct  
{
	EXTI_num_t EXTI_x;						/* EXTI number */
	EXTI_sensitivity_t EXTI_sensitivity;
	void (*EXTI_callback)();				/* callback function for EXTI ISR */
	
}EXTI_Configs_t;



/************************************ EXTI APIs **********************************/


/* in app create EXTI_Configs_t with EXTI number , sensitivity , callback function*/
void EXTI_Init(EXTI_Configs_t* EXTIx);
void EXTI_DeInit(EXTI_Configs_t* EXTIx);




#endif /* EXTI_H_ */