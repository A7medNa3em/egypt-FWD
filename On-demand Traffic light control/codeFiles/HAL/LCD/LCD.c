/*************************************************************
 *       @author :   Ahmed Naeem
 *       @date   :   28/11/2022
 *       @file   :   LCD.h
 *************************************************************/

/************************************************************/
/*includes*/
#include "atmega32.h"
#include "stdtypes.h"
#include "LCD.h"
#include "LCD_cfg.h"
#include "bitmath.h"
#include "TIMER0/timer0.h"
#include "DIO/DIO.h"



/************************************************************/
/* Helper Functions */

void delay(volatile uint32 time) {
	uint32 i, j;
	for (i = 0; i < time; i++)
	for (j = 0; j < 255; j++)
	;
}

/* Helper function to send command to LCD */
static void LCD_SendCommand(uint8 cmd)
{
	/* R/S --> LOW  command register */
	MCAL_DIO_WritePin(LCD_CNT_RS_PIN,LCD_CONTROL_REG , LOW);

	/* R/W --> LOW  Write */
	MCAL_DIO_WritePin( LCD_CNT_RW_PIN, LCD_CONTROL_REG ,LOW);

	/* Set E pin to high */
	MCAL_DIO_WritePin( LCD_CNT_E_PIN,LCD_CONTROL_REG , HIGH);

	/* 4 bit Mode*/
#if (LCD_OP_MODE == LCD_CMD_4_BIT_MODE)

	/* Frist Send 4 higher bits */
	MCAL_DIO_WritePin(LCD_DATA_PIN_4, LCD_DATA_REG,   GET_BIT(cmd, 4));
	MCAL_DIO_WritePin(LCD_DATA_PIN_5,LCD_DATA_REG ,   GET_BIT(cmd, 5));
	MCAL_DIO_WritePin( LCD_DATA_PIN_6,LCD_DATA_REG ,  GET_BIT(cmd, 6));
	MCAL_DIO_WritePin( LCD_DATA_PIN_7,LCD_DATA_REG ,  GET_BIT(cmd, 7));

	delay(50);
	/* reset E pin to low */
	MCAL_DIO_WritePin( LCD_CNT_E_PIN,LCD_CONTROL_REG , LOW);
	delay(50);
	/* Set E pin to high */
	MCAL_DIO_WritePin( LCD_CNT_E_PIN, LCD_CONTROL_REG ,HIGH);

	/* Then Send 4 Lower bits */
	MCAL_DIO_WritePin( LCD_DATA_PIN_4,LCD_DATA_REG, GET_BIT(cmd, 0));
	MCAL_DIO_WritePin( LCD_DATA_PIN_5,LCD_DATA_REG, GET_BIT(cmd, 1));
	MCAL_DIO_WritePin(LCD_DATA_PIN_6,LCD_DATA_REG, GET_BIT(cmd, 2));
	MCAL_DIO_WritePin( LCD_DATA_PIN_7,LCD_DATA_REG, GET_BIT(cmd, 3));

	/* 8 bit Mode*/
#elif (LCD_OP_MODE == LCD_CMD_8_BIT_MODE)

	/* Write data pins */
	MCAL_DIO_WritePin( LCD_DATA_PIN_0, LCD_DATA_REG , GET_BIT(cmd, 0));
	MCAL_DIO_WritePin( LCD_DATA_PIN_1, LCD_DATA_REG , GET_BIT(cmd, 1));
	MCAL_DIO_WritePin( LCD_DATA_PIN_2,LCD_DATA_REG  , GET_BIT(cmd, 2));
	MCAL_DIO_WritePin( LCD_DATA_PIN_3,LCD_DATA_REG  , GET_BIT(cmd, 3));
	MCAL_DIO_WritePin( LCD_DATA_PIN_4,LCD_DATA_REG  , GET_BIT(cmd, 4));
	MCAL_DIO_WritePin( LCD_DATA_PIN_5,LCD_DATA_REG  , GET_BIT(cmd, 5));
	MCAL_DIO_WritePin( LCD_DATA_PIN_6,LCD_DATA_REG  , GET_BIT(cmd, 6));
	MCAL_DIO_WritePin( LCD_DATA_PIN_7,LCD_DATA_REG  , GET_BIT(cmd, 7));

#endif

	delay(50);
	/* Set E pin to low */
	MCAL_DIO_WritePin(LCD_CNT_E_PIN,LCD_CONTROL_REG  , LOW);
	delay(50);
}

/* Helper function to send Data to LCD */
static void LCD_SendData(uint8 cmd)
{
	/* R/S --> High  Data register */
	MCAL_DIO_WritePin( LCD_CNT_RS_PIN,LCD_CONTROL_REG  , HIGH);

	/* R/W --> LOW  Write */
	MCAL_DIO_WritePin( LCD_CNT_RW_PIN, LCD_CONTROL_REG  ,LOW);

	/* Set E pin to high */
	MCAL_DIO_WritePin( LCD_CNT_E_PIN, LCD_CONTROL_REG  ,HIGH);

	/* 4 bit Mode*/
#if (LCD_OP_MODE == LCD_CMD_4_BIT_MODE)

	/* Frist Send 4 higher bits */
	MCAL_DIO_WritePin( LCD_DATA_PIN_4, LCD_DATA_REG  , GET_BIT(cmd, 4));
	MCAL_DIO_WritePin( LCD_DATA_PIN_5, LCD_DATA_REG  , GET_BIT(cmd, 5));
	MCAL_DIO_WritePin( LCD_DATA_PIN_6, LCD_DATA_REG  , GET_BIT(cmd, 6));
	MCAL_DIO_WritePin( LCD_DATA_PIN_7, LCD_DATA_REG  , GET_BIT(cmd, 7));

	delay(50);

	/* Set E pin to low */
	MCAL_DIO_WritePin( LCD_CNT_E_PIN, LCD_CONTROL_REG , LOW);

	delay(50);

	/* Set E pin to high */
	MCAL_DIO_WritePin( LCD_CNT_E_PIN, LCD_CONTROL_REG  ,HIGH);

	/* Then Send 4 Lower bits */
	MCAL_DIO_WritePin( LCD_DATA_PIN_4, LCD_DATA_REG  , GET_BIT(cmd, 0));
	MCAL_DIO_WritePin( LCD_DATA_PIN_5, LCD_DATA_REG  , GET_BIT(cmd, 1));
	MCAL_DIO_WritePin( LCD_DATA_PIN_6, LCD_DATA_REG  , GET_BIT(cmd, 2));
	MCAL_DIO_WritePin( LCD_DATA_PIN_7, LCD_DATA_REG  , GET_BIT(cmd, 3));

	/* 8 bit Mode*/

#elif (LCD_OP_MODE == LCD_CMD_8_BIT_MODE)

	/* Write data pins */
	MCAL_DIO_WritePin(LCD_DATA_PIN_0, LCD_DATA_REG   ,GET_BIT(cmd, 0));
	MCAL_DIO_WritePin( LCD_DATA_PIN_1,LCD_DATA_REG   ,GET_BIT(cmd, 1));
	MCAL_DIO_WritePin( LCD_DATA_PIN_2, LCD_DATA_REG  ,GET_BIT(cmd, 2));
	MCAL_DIO_WritePin( LCD_DATA_PIN_3, LCD_DATA_REG  ,GET_BIT(cmd, 3));
	MCAL_DIO_WritePin( LCD_DATA_PIN_4, LCD_DATA_REG  ,GET_BIT(cmd, 4));
	MCAL_DIO_WritePin( LCD_DATA_PIN_5, LCD_DATA_REG  ,GET_BIT(cmd, 5));
	MCAL_DIO_WritePin( LCD_DATA_PIN_6, LCD_DATA_REG  ,GET_BIT(cmd, 6));
	MCAL_DIO_WritePin( LCD_DATA_PIN_7, LCD_DATA_REG  ,GET_BIT(cmd, 7));

#endif

	delay(50);
	/* Set E pin to low */
	MCAL_DIO_WritePin(LCD_CONTROL_REG  , LCD_CNT_E_PIN, LOW);

delay(50);}

void LCD_Init(void)
{
	/* init Pins as output */
	/* First Send 4 higher bits */
	MCAL_DIO_InitPin( LCD_DATA_PIN_4,LCD_DATA_REG,OUTPUT,FALSE);
	MCAL_DIO_InitPin( LCD_DATA_PIN_5,LCD_DATA_REG,OUTPUT,FALSE);
	MCAL_DIO_InitPin( LCD_DATA_PIN_6,LCD_DATA_REG,OUTPUT,FALSE);
	MCAL_DIO_InitPin( LCD_DATA_PIN_7,LCD_DATA_REG,OUTPUT,FALSE);
	
	MCAL_DIO_InitPin( LCD_CNT_E_PIN,LCD_CONTROL_REG,OUTPUT,FALSE);
	MCAL_DIO_InitPin( LCD_CNT_RS_PIN,LCD_CONTROL_REG,OUTPUT,FALSE);
	MCAL_DIO_InitPin( LCD_CNT_RW_PIN,LCD_CONTROL_REG,OUTPUT,FALSE);

		/* 8 bit Mode*/

		#if (LCD_OP_MODE == LCD_CMD_8_BIT_MODE)

		/* Write data pins */
		MCAL_DIO_InitPin( LCD_DATA_PIN_0,LCD_DATA_REG,OUTPUT,FALSE);
		MCAL_DIO_InitPin( LCD_DATA_PIN_1,LCD_DATA_REG,OUTPUT,FALSE);
		MCAL_DIO_InitPin( LCD_DATA_PIN_2,LCD_DATA_REG,OUTPUT,FALSE);
		MCAL_DIO_InitPin( LCD_DATA_PIN_3,LCD_DATA_REG,OUTPUT,FALSE);

		#endif

	/* Send Operation mode*/
	LCD_SendCommand(LCD_OP_MODE);
	delay(50);
	/* Send entery mode*/
	LCD_SendCommand(LCD_ENTRY_MODE);
	delay(50);
	/* Send display mode command*/
	LCD_SendCommand(LCD_DISPLAY_MODE);
	delay(50);
	/* Clear the LCD and return home */
	LCD_SendCommand(LCD_CMD_CLEAR_DISPLAY);
	delay(50);}

/* Clear the LCD and return home */
void LCD_ClearDisplay(void)
{
	LCD_SendCommand(LCD_CMD_CLEAR_DISPLAY);
	delay(50);
	LCD_SendCommand(LCD_CMD_RETURN_HOME);
	delay(50);

}

void LCD_WriteChar(char ch, uint8 row, uint8 col)
{
	if (row == 0)
	{
		LCD_SendCommand(LCD_CMD_SET_DDRAM + col);
	}
	else if (row == 1)
	{
		LCD_SendCommand(LCD_CMD_SET_DDRAM + 0x40 + col);
	}
	delay(50);

	LCD_SendData(ch);
	delay(50);
	
}

void LCD_WriteString(char *str, uint8 len, uint8 row, uint8 col)
{

	for (uint8 index = 0; index < len; index++)
	{
		LCD_WriteChar(str[index], row, col + index);
	}
}

void LCD_CreatCustomChar(uint8 *ch, uint8 len, uint8 index)
{
	uint8 pos = 0;
	for (pos = 0; pos < len; pos++)
	{
		LCD_SendCommand(LCD_CMD_SET_CGRAM + (8 * index) + pos);
		LCD_SendData(ch[pos]);
	}
}

void LCD_WriteCustomChar(uint8 index, uint8 row, uint8 col)
{
	if (row == 0)
	{
		LCD_SendCommand(LCD_CMD_SET_DDRAM + col);
	}
	else if (row == 1)
	{
		LCD_SendCommand(LCD_CMD_SET_DDRAM + 0x40 + col);
	}

	LCD_SendData(index);
}


