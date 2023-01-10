/*************************************************************
 *       @author :   Ahmed Naeem
 *       @date   :   28/11/2022
 *       @file   :   LCD.h
 *************************************************************/

/************************************************************/
/*includes*/
#include "LCD.h"
#include "LCD_cfg.h"
#include "bitmath.h"
#include "GPIO.h"
#include "stm32f103x6.h"


/************************************************************/
/* Helper Functions */

void delay_ms(uint32_t time) {
	uint32_t i, j;
	for (i = 0; i < time; i++)
		for (j = 0; j < 255; j++)
			;
}
/* Helper function to send command to LCD */
static void LCD_SendCommand(uint8_t cmd)
{
	/* R/S --> LOW  command register */
	MCAL_GPIO_WritePin(LCD_REG ,LCD_CNT_RS_PIN, LOW);

	/* R/W --> LOW  Write */
	MCAL_GPIO_WritePin(LCD_REG , LCD_CNT_RW_PIN, LOW);

	/* Set E pin to high */
	MCAL_GPIO_WritePin(LCD_REG , LCD_CNT_E_PIN, HIGH);

	/* 4 bit Mode*/
#if (LCD_OP_MODE == LCD_CMD_4_BIT_MODE)

	/* Frist Send 4 higher bits */
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_4, GET_BIT(cmd, 4));
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_5, GET_BIT(cmd, 5));
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_6, GET_BIT(cmd, 6));
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_7, GET_BIT(cmd, 7));

	delay_ms(10);

	/* reset E pin to low */
	MCAL_GPIO_WritePin(LCD_REG , LCD_CNT_E_PIN, LOW);

	delay_ms(10);

	/* Set E pin to high */
	MCAL_GPIO_WritePin(LCD_REG , LCD_CNT_E_PIN, HIGH);

	/* Then Send 4 Lower bits */
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_4, GET_BIT(cmd, 0));
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_5, GET_BIT(cmd, 1));
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_6, GET_BIT(cmd, 2));
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_7, GET_BIT(cmd, 3));

	/* 8 bit Mode*/
#elif (LCD_OP_MODE == LCD_CMD_8_BIT_MODE)

	/* Write data pins */
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_0, GET_BIT(cmd, 0));
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_1, GET_BIT(cmd, 1));
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_2, GET_BIT(cmd, 2));
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_3, GET_BIT(cmd, 3));
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_4, GET_BIT(cmd, 4));
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_5, GET_BIT(cmd, 5));
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_6, GET_BIT(cmd, 6));
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_7, GET_BIT(cmd, 7));

#endif

	delay_ms(1);

	/* Set E pin to low */
	MCAL_GPIO_WritePin(LCD_REG , LCD_CNT_E_PIN, LOW);

	delay_ms(5);
}

/* Helper function to send Data to LCD */
static void LCD_SendData(uint8_t cmd)
{
	/* R/S --> High  Data register */
	MCAL_GPIO_WritePin(LCD_REG , LCD_CNT_RS_PIN, HIGH);

	/* R/W --> LOW  Write */
	MCAL_GPIO_WritePin(LCD_REG , LCD_CNT_RW_PIN, LOW);

	/* Set E pin to high */
	MCAL_GPIO_WritePin(LCD_REG , LCD_CNT_E_PIN, HIGH);

	/* 4 bit Mode*/
#if (LCD_OP_MODE == LCD_CMD_4_BIT_MODE)

	/* Frist Send 4 higher bits */
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_4, GET_BIT(cmd, 4));
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_5, GET_BIT(cmd, 5));
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_6, GET_BIT(cmd, 6));
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_7, GET_BIT(cmd, 7));

	delay_ms(10);

	/* Set E pin to low */
	MCAL_GPIO_WritePin(LCD_REG , LCD_CNT_E_PIN, LOW);

	delay_ms(10);

	/* Set E pin to high */
	MCAL_GPIO_WritePin(LCD_REG , LCD_CNT_E_PIN, HIGH);

	/* Then Send 4 Lower bits */
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_4, GET_BIT(cmd, 0));
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_5, GET_BIT(cmd, 1));
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_6, GET_BIT(cmd, 2));
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_7, GET_BIT(cmd, 3));

	/* 8 bit Mode*/

#elif (LCD_OP_MODE == LCD_CMD_8_BIT_MODE)

	/* Write data pins */
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_0, GET_BIT(cmd, 0));
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_1, GET_BIT(cmd, 1));
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_2, GET_BIT(cmd, 2));
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_3, GET_BIT(cmd, 3));
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_4, GET_BIT(cmd, 4));
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_5, GET_BIT(cmd, 5));
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_6, GET_BIT(cmd, 6));
	MCAL_GPIO_WritePin(LCD_REG , LCD_DATA_PIN_7, GET_BIT(cmd, 7));

#endif

	delay_ms(10);

	/* Set E pin to low */
	MCAL_GPIO_WritePin(LCD_REG , LCD_CNT_E_PIN, LOW);

	delay_ms(10);
}

void LCD_Init(void)
{
	/* init Pins as output */

	/* Send Operation mode*/
	LCD_SendCommand(LCD_OP_MODE);
	delay_ms(10);

	/* Send entery mode*/
	LCD_SendCommand(LCD_ENTRY_MODE);
	delay_ms(10);

	/* Send display mode command*/
	LCD_SendCommand(LCD_DISPLAY_MODE);
	delay_ms(10);

	/* Clear the LCD and return home */
	LCD_SendCommand(LCD_CMD_CLEAR_DISPLAY);
	delay_ms(10);
}

/* Clear the LCD and return home */
void LCD_ClearDisplay(void)
{
	LCD_SendCommand(LCD_CMD_CLEAR_DISPLAY);
	delay_ms(10);
	LCD_SendCommand(LCD_CMD_RETURN_HOME);
	delay_ms(10);

}

void LCD_WriteChar(char ch, uint8_t row, uint8_t col)
{
	if (row == 0)
	{
		LCD_SendCommand(LCD_CMD_SET_DDRAM + col);
	}
	else if (row == 1)
	{
		LCD_SendCommand(LCD_CMD_SET_DDRAM + 0x40 + col);
	}

	LCD_SendData(ch);
}

void LCD_WriteString(char *str, uint8_t len, uint8_t row, uint8_t col)
{

	for (uint8_t index = 0; index < len; index++)
	{
		LCD_WriteChar(str[index], row, col + index);
	}
}

void LCD_CreatCustomChar(uint8_t *ch, uint8_t len, uint8_t index)
{
	uint8_t pos = 0;
	for (pos = 0; pos < len; pos++)
	{
		LCD_SendCommand(LCD_CMD_SET_CGRAM + (8 * index) + pos);
		LCD_SendData(ch[pos]);
	}
}

void LCD_WriteCustomChar(uint8_t index, uint8_t row, uint8_t col)
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


