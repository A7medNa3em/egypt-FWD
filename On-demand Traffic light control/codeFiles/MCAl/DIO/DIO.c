
#include "DIO.h"
#include "DIO_cfg.h"


/* MCAL_DIO_InitPin: Initialize the DIO pin (direction , pull) */
DIO_Error_t MCAL_DIO_InitPin(PIN_t pinx, PORT_t portx, DIRECTION_t dir , PULLUP_t pullup)
{
	DIO_Error_t DIO_state = DIO_OK;
        switch (portx)
        {
        case PORT_A:
		{
            if (INPUT == dir)
            {
                CLR_BIT(DDRA, pinx);
                if (TRUE == pullup)
                {
                    SET_BIT(PORTA, pinx);
                }
            }
            else if (OUTPUT == dir)
            {
                SET_BIT(DDRA, pinx);
            }
		}
			
            break;
        case PORT_B:
            if (INPUT == dir)
            {
                CLR_BIT(DDRB, pinx);
                if (TRUE == pullup)
                {
                    SET_BIT(PORTB, pinx);
                }
            }
            else if (OUTPUT == dir)
            {
                SET_BIT(DDRB, pinx);
            }
            break;
        case PORT_C:
            if (INPUT == dir)
            {
                CLR_BIT(DDRC, pinx);
                if (TRUE == pullup)
                {
                    SET_BIT(PORTC, pinx);
                }
            }
            else if (OUTPUT == dir)
            {
                SET_BIT(DDRC, pinx);
            }
            break;

        case PORT_D:
            if (INPUT == dir)
            {
                CLR_BIT(DDRD, pinx);
                if (TRUE == pullup)
                {
                    SET_BIT(PORTD, pinx);
                }
            }
            else if (OUTPUT == dir)
            {
                SET_BIT(DDRD, pinx);
            }
            break;
			
			default:
			{
				DIO_state=DIO_ERROR ;	
			}
        }
    
	return DIO_state;
}

/* DIO_Init: Initialize the DIO pins in configurations array */
void MCAL_DIO_Init()
{
	uint8 index = 0;

	for (index = 0; index < PinConfigCount; index++)
	{

		MCAL_DIO_InitPin(PinConfigs[index].pin,PinConfigs[index].port,PinConfigs[index].dir,PinConfigs[index].pullup);
		
	}
}


/* DIO_WritePin: Write High/Low on DIO pin  */
DIO_Error_t MCAL_DIO_WritePin(PIN_t pin, PORT_t port, STATE_t state)
{
	DIO_Error_t DIO_state = DIO_OK;

        switch (port)
        {
        case PORT_A:
            if (HIGH == state)
            {
                SET_BIT(PORTA, pin);
            }
            else if (LOW == state)
            {
                CLR_BIT(PORTA, pin);
            }
            break;

        case PORT_B:
            if (HIGH == state)
            {
                SET_BIT(PORTB, pin);
            }
            else if (LOW == state)
            {
                CLR_BIT(PORTB, pin);
            }
            break;

        case PORT_C:
            if (HIGH == state)
            {
                SET_BIT(PORTC, pin);
            }
            else if (LOW == state)
            {
                CLR_BIT(PORTC, pin);
            }
			else
			{
				DIO_state = DIO_ERROR;
			}
            break;

        case PORT_D:
            if (HIGH == state)
            {
                SET_BIT(PORTD, pin);
            }
            else if (LOW == state)
            {
                CLR_BIT(PORTD, pin);
            }
            break;
			default:
			{
				DIO_state = DIO_ERROR;
			}
        }
		
	return DIO_state;
    
}

/* MCAL_DIO_TogglePin: convert state of DIO pin  */
DIO_Error_t MCAL_DIO_TogglePin(PIN_t pin, PORT_t port)
{
	DIO_Error_t DIO_state= DIO_OK;
	switch (port)
	{
	case PORT_A:
	TOGGLE_PIN(PORTA, pin);
	break;

	case PORT_B:
	TOGGLE_PIN(PORTB, pin);
	break;

	case PORT_C:
	TOGGLE_PIN(PORTC, pin);
	break;

	case PORT_D:
	TOGGLE_PIN(PORTD, pin);
	break;
	default:DIO_state= DIO_ERROR;
	}
	
	return DIO_state;

}

/* DIO_Write: Write High/Low on DIO pin in pin configuration array */
DIO_Error_t MCAL_DIO_Write(PIN_t pin, PORT_t port, STATE_t state)
{
	DIO_Error_t ErrorType= DIO_UNCONFIGURED;

	uint8 index = 0;

	for (index = 0; index < PinConfigCount; index++)
	{
		if((pin ==PinConfigs[index].pin) && (port == PinConfigs[index].port))
		{
		MCAL_DIO_WritePin(PinConfigs[index].pin,PinConfigs[index].port,state);
		ErrorType= DIO_OK;
		break;
		}
		
	}
	
	
	return ErrorType;
	
}

/* DIO_ReadPin: Read DIO pin state */
STATE_t MCAL_DIO_ReadPin(PIN_t pin, PORT_t port)
{
    
    STATE_t pinstate = LOW;

        switch (port)
        {
        case PORT_A:
            pinstate = GET_BIT(PINA, pin);
            break;

        case PORT_B:
            pinstate = GET_BIT(PINB, pin);
            break;

        case PORT_C:
            pinstate = GET_BIT(PINC, pin);
            break;

        case PORT_D:
            pinstate = GET_BIT(PIND, pin);

            break;
        }
    

    return pinstate;
}

/* DIO_Read: Read DIO pin state  in pin configuration array */
DIO_Error_t MCAL_DIO_Read(PIN_t pin, PORT_t port, STATE_t * pinstate)
{
	
	DIO_Error_t ErrorType= DIO_UNCONFIGURED;

	uint8 index = 0;

	for (index = 0; index < PinConfigCount; index++)
	{
		if((pin ==PinConfigs[index].pin) && (port == PinConfigs[index].port))
		{
			*pinstate =MCAL_DIO_ReadPin(PinConfigs[index].pin,PinConfigs[index].port);
			ErrorType= DIO_OK;
			break;
		}
		
	}
	
	
	return ErrorType;
	
	
}