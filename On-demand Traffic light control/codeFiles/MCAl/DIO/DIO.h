#ifndef DIO_H
#define DIO_H


#include "../LIB/atmega32.h"
#include "../LIB/stdtypes.h"
#include "../LIB/bitmath.h"



typedef enum
{
	ACTIVE_LOW,
	ACTIVE_HIGH,
}ActiveState_t;

typedef enum
{
    PIN_0,
    PIN_1,
    PIN_2,
    PIN_3,
    PIN_4,
    PIN_5,
    PIN_6,
    PIN_7
} PIN_t;
typedef enum
{
    PORT_A,
    PORT_B,
    PORT_C,
    PORT_D
} PORT_t;
typedef enum
{
    OUTPUT,
    INPUT,
} DIRECTION_t;
typedef enum
{
    FALSE,
    TRUE,
} PULLUP_t;
typedef enum
{
    LOW,
    HIGH,
} STATE_t;

typedef enum
{
	DIO_OK,
	DIO_UNCONFIGURED,
	DIO_ERROR,
} DIO_Error_t;


typedef struct
{
	PIN_t pin;
	PORT_t port;
	DIRECTION_t dir;
	PULLUP_t pullup;
} PinConfig_t;

/* MCAL_DIO_InitPin: Initialize the DIO pin (direction , pull) */
DIO_Error_t MCAL_DIO_InitPin(PIN_t pinx, PORT_t portx, DIRECTION_t dir , PULLUP_t pullup);
//void MCAL_DIO_InitPin(PinConfig_t* pinx);

/* DIO_Init: Initialize the DIO pins in Pin configurations array */
void MCAL_DIO_Init();

/* DIO_WritePin: Write High/Low on DIO pin */
DIO_Error_t MCAL_DIO_WritePin(PIN_t pin, PORT_t port, STATE_t state);

/* DIO_Write: Write High/Low on DIO pin */
DIO_Error_t MCAL_DIO_Write(PIN_t pin, PORT_t port, STATE_t state);

/* DIO_ReadPin: Read DIO pin state */
STATE_t MCAL_DIO_ReadPin(PIN_t pin, PORT_t port);

/* DIO_Read: Read DIO pin state  in pin configuration array */
DIO_Error_t MCAL_DIO_Read(PIN_t pin, PORT_t port, STATE_t *pinstate);

/* MCAL_DIO_TogglePin: convert state of DIO pin  */
DIO_Error_t MCAL_DIO_TogglePin(PIN_t pin, PORT_t port);

#endif