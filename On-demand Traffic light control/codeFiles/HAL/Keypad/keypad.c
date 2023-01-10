/*************************************************************
 *       @author :   Ahmed Naeem
 *       @date   :   28/11/2022
 *       @file   :   stm32f103x6.h
 *************************************************************/

/*************************************************************
 *  Includes
 */

#include "atmega32.h"
#include "DIO/DIO.h"
#include "keypad.h"
#include "keypad_cfg.h"



/*************************************************************
 *   @param [in]- Nothing
 *   @brief  initialization for number of 4x4 Keypads init rows as output and write
 *   		default state to it according to connection
 *   		and init columns as input
 *   @retval none
 */
void KeyPad_init()
{
	uint8 index_1 = 0,index_2 = 0;


	for (index_1 = 0; index_1 < KeypadsCount; index_1++)
	{
		for (index_2 = 0; index_2 < 4; index_2++)
		{
			/* Init rows and columns*/
			MCAL_DIO_InitPin(Keypads[index_1].rows[index_2].pin ,Keypads[index_1].rows[index_2].port,Keypads[index_1].rows[index_2].dir,Keypads[index_1].rows[index_2].pullup);
			MCAL_DIO_InitPin(Keypads[index_1].cols[index_2].pin ,Keypads[index_1].cols[index_2].port,Keypads[index_1].cols[index_2].dir,Keypads[index_1].cols[index_2].pullup);

			/* Write default state to rows pins according to HW connections */
			MCAL_DIO_WritePin(Keypads[index_1].rows[index_2].pin ,Keypads[index_1].rows[index_2].port ,Keypads[index_1].defState);
		}
	}
}


/*************************************************************
 *   @param [in] - keypad index according to HW connection
 *   @param [out]- row and column number for pressed key
 *   @brief  Get Key pressed or not and key row and column
 *   @retval key pressing status
 */
KeyStatus_t GetKeyPressed(uint8 *row, uint8 *colum , Keypad_t Keypad_index)
{
	KeyStatus_t pressstatus = KEY_NOT_PRESSED;
	uint8 rowindex = 0, colindex = 0, breakFlag = 0;
	STATE_t drive_state = LOW;


	/*Check drive state by inverting default state*/
	if (LOW == Keypads[Keypad_index].defState)
	{
		drive_state = HIGH;
	}
	else if (HIGH == Keypads[Keypad_index].defState)
	{
		drive_state = LOW;
	}

	/*monitor rows by drive state and check column status */
	for (rowindex = 0; rowindex < 4; rowindex++)
	{
		/*monitor rows by drive state*/
		MCAL_DIO_WritePin(Keypads[Keypad_index].rows[rowindex].pin ,Keypads[Keypad_index].rows[rowindex].port,drive_state );

		/*check column status */
		for (colindex = 0; colindex < 4; colindex++)
		{
			if (drive_state == MCAL_DIO_ReadPin(Keypads[Keypad_index].cols[colindex].pin, Keypads[Keypad_index].cols[colindex].port))
			{
				pressstatus = KEY_PRESSED;
				*colum = colindex;
				*row = rowindex;
				breakFlag = 1;
				/* Wait Until Key is OFF */
				while(drive_state == MCAL_DIO_ReadPin(Keypads[Keypad_index].cols[colindex].pin, Keypads[Keypad_index].cols[colindex].port));
			}
		}
		/* return row state again to default state */
		MCAL_DIO_WritePin(Keypads[Keypad_index].rows[rowindex].pin ,Keypads[Keypad_index].rows[rowindex].port,Keypads[Keypad_index].defState );

		if(breakFlag == 1)
			break;
	}


	return pressstatus ;

}


