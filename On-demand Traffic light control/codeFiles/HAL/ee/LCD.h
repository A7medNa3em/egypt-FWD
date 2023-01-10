/*************************************************************
 *       @author :   Ahmed Naeem
 *       @date   :   28/11/2022
 *       @file   :   LCD.h
 *************************************************************/
#ifndef LCD_H
#define LCD_H
#include <stdint.h>
#include "LCD_cfg.h"
/*LCD APIs */
/* specify entery mode, display mode and operation mode then clear LCD*/
void LCD_Init(void);

void LCD_WriteChar(char ch, uint8_t row, uint8_t col);

void LCD_WriteString(char *str, uint8_t len, uint8_t row, uint8_t col);

void LCD_ClearDisplay(void);

void LCD_CreatCustomChar(uint8_t *ch, uint8_t len, uint8_t index);

void LCD_WriteCustomChar(uint8_t index, uint8_t row, uint8_t col);
#endif
