/*
 * EXTI.c
 *
 * Created: 1/3/2023 2:24:21 PM
 *  Author: Ahmed Naeem
 */ 


#include "EXTI.h"

/* */
void (*EXTI0_callback)();
void (*EXTI1_callback)();
void (*EXTI2_callback)();

void EXTI_Init(EXTI_Configs_t *EXTIx)
{
	switch (EXTIx->EXTI_x)
	{
	case 0:
	{
		// 1-Choose interrupt sensitivity
		// clear bit0, bit1
		MCUCR &= ~(0x03);
		// put bit0 , bit1 values in EXTI_sensitivity
		MCUCR |= (EXTIx->EXTI_sensitivity &0x03);
		
		//2- Enable INTx
		SET_BIT(GICR,6);
		
		//3- specify callback function
		EXTI0_callback = EXTIx->EXTI_callback;
		
	}break;
	case 1:
	{
		//1- Choose interrupt sensitivity
		// clear bit2, bit3
		MCUCR &= ~(0x0C);
		// put bit2 , bit3 values in EXTI_sensitivity
		MCUCR |= (EXTIx->EXTI_sensitivity & 0x0C);
		
		//2- Enable INT1
		SET_BIT(GICR,7);
		
		//3- specify callback function
		EXTI1_callback = EXTIx->EXTI_callback;
		
	}break;
	case 2:
	{
		//1- Choose interrupt sensitivity
		// clear bit6
		CLR_BIT(MCUCSR,6); 
		// put bit6 values in EXTI_sensitivity
		MCUCSR |= ((EXTIx->EXTI_sensitivity -2) &0x20);
		
		//2- Enable INT2
		SET_BIT(GICR,5);
		
		//3- specify callback function
		EXTI2_callback = EXTIx->EXTI_callback;
		
	}break;
	
	}
	
	//4- Enable GIE
	GIE_ENABLE();
	
	
}

void EXTI_DeInit(EXTI_Configs_t* EXTIx)
{
	switch (EXTIx->EXTI_x)
	{
		case 0:
		{	
			//Disable INT0
			SET_BIT(GICR,6);
		}break;
		case 1:
		{
			// Disable INT1
			CLR_BIT(GICR,7);
		}break;
		case 2:
		{
			// Disable INT2
			CLR_BIT(GICR,5);
			
		}break;
	}
	
}



void __vector_1(void) 
{
	EXTI0_callback();
}

void __vector_2(void) 
{
	EXTI1_callback();
}

void __vector_3(void)
{
	EXTI2_callback();
}