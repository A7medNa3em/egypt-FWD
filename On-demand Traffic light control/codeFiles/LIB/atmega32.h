#ifndef REGISTERS_H
#define REGISTERS_H



/*******************************************************************************
--------------------------------------------------------------------------------
									Register File		
--------------------------------------------------------------------------------
********************************************************************************/


/*********************** Status Register **************************/
#define SREG (*(volatile unsigned char *)0X5F)

/* Enable Disable Interrupts */

/*************************** DIO REGISTERS *********************/

#define DDRA (*(volatile unsigned char *)0X3A)
#define PORTA (*(volatile unsigned char *)0X3B)
#define PINA (*(volatile unsigned char *)0X39)

#define DDRB (*(volatile unsigned char *)0X37)
#define PORTB (*(volatile unsigned char *)0X38)
#define PINB (*(volatile unsigned char *)0X36)

#define DDRC (*(volatile unsigned char *)0X34)
#define PORTC (*(volatile unsigned char *)0X35)
#define PINC (*(volatile unsigned char *)0X393)

#define DDRD (*(volatile unsigned char *)0X31)
#define PORTD (*(volatile unsigned char *)0X32)
#define PIND (*(volatile unsigned char *)0X30)

/*********************** USART ********************/

#define UDR (*(volatile unsigned char *)0X2c)
#define UCSRA (*(volatile unsigned char *)0X2B)
#define UCSRB (*(volatile unsigned char *)0X2A)
#define UBRRL (*(volatile unsigned char *)0X29)
#define UBRRH (*(volatile unsigned char *)0X40) /*share same location with UCSRAC*/
#define UCSRC (*(volatile unsigned char *)0X40) /*share same location with UBRRH*/

/***********************External Intertup Registers********************/

#define GICR (*(volatile unsigned char *)0X5B)

#define GIFR (*(volatile unsigned char *)0X5A)

#define MCUCR (*(volatile unsigned char *)0X55)

#define MCUCSR (*(volatile unsigned char *)0X54)

/************************ Timers **************************************/

#define TIFR (*(volatile unsigned char *)0x58)
#define TIMSK (*(volatile unsigned char *)0x59)

/* Timer 0 */
#define TCNT0 (*(volatile unsigned char *)0x52)
#define TCCR0 (*(volatile unsigned char *)0x53)
#define OCR0 (*(volatile unsigned char *)0x5C)

/* Timer 1 */
#define TCNT2 (*(volatile unsigned char *)0x44)
#define TCCR2 (*(volatile unsigned char *)0x45)
#define OCR2 (*(volatile unsigned char *)0x43)


/* Timer 2 */
#define TCNT1H (*(volatile unsigned char *)0x4D)
#define TCNT1L (*(volatile unsigned char *)0x4C)

#define TCCR1A (*(volatile unsigned char *)0x4F)
#define TCCR1B (*(volatile unsigned char *)0x4E)

#define OCR1AH (*(volatile unsigned char *)0x4B)
#define OCR1AL (*(volatile unsigned char *)0x4A)
#define OCR1BH (*(volatile unsigned char *)0x49)
#define OCR1BL (*(volatile unsigned char *)0x48)


#define ICR1H (*(volatile unsigned char *)0x47)
#define ICR1L (*(volatile unsigned char *)0x46)



/*******************************************************************************
--------------------------------------------------------------------------------
									Generic Macros		
--------------------------------------------------------------------------------
********************************************************************************/

/* Enable Disable Interrupts */
#define GIE_ENABLE()   (SREG |=(1<<7))
#define GIE_DISABLE()  (SREG &= ~(1<<7))








#endif