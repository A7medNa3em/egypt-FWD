/************************************************************
 *
 * LCD_cfg.h
 *
 *  Created on: Nov 30, 2022
 *      Author: Ahmed Naeem
 *
 *      Here you configure LCD according to board specs and connectons
************************************************************/


#ifndef LCD_CFG_H
#define LCD_CFG_H


/************************************************************/
/* LCD configurations */

/* LCD Control pins */
#define LCD_CNT_RS_PIN GPIO_PIN8
#define LCD_CNT_RW_PIN GPIO_PIN9
#define LCD_CNT_E_PIN GPIO_PIN10

/* LCD Data Pins*/
#define LCD_DATA_PIN_0 GPIO_PIN0
#define LCD_DATA_PIN_1 GPIO_PIN1
#define LCD_DATA_PIN_2 GPIO_PIN2
#define LCD_DATA_PIN_3 GPIO_PIN3

#define LCD_DATA_PIN_4 GPIO_PIN4
#define LCD_DATA_PIN_5 GPIO_PIN5
#define LCD_DATA_PIN_6 GPIO_PIN6
#define LCD_DATA_PIN_7 GPIO_PIN7

#define LCD_REG GPIOA

/* LCD Configuration Commands */
#define LCD_CMD_CLEAR_DISPLAY				 (0x01)
#define LCD_CMD_RETURN_HOME 				 (0x02)
#define LCD_CMD_8_BIT_MODE 				     (0x38) /*DL:8 BIT N:2 LINES L:8*5 */
#define LCD_CMD_4_BIT_MODE 					 (0x28) /*DL:4 BIT N:2 LINES L:8*5 */
#define LCD_CMD_DISPLAY_CURSOR_BLINK_ON 	 (0x0F) /*D:ON BIT C:ON BLINK: ON */
#define LCD_CMD_CURSOR_INC_NO_DISPLAY_SHIFT  (0x06) /* I/D: Cursor incrementing, SH: No display shift */
#define LCD_CMD_CURSOR_DEC_NO_DISPLAY_SHIFT  (0x04) /* I/D: Cursor decrementing, SH: No display shift */
#define LCD_CMD_SET_CGRAM 					 (0x40)
#define LCD_CMD_SET_DDRAM 					 (0x80)

/* LCD General Configuration  */
#define LCD_OP_MODE LCD_CMD_8_BIT_MODE
#define LCD_ENTRY_MODE LCD_CMD_CURSOR_INC_NO_DISPLAY_SHIFT
#define LCD_DISPLAY_MODE LCD_CMD_DISPLAY_CURSOR_BLINK_ON


/************************************************************/


#endif /* INCLUDES_LCD_CFG_H_ */
