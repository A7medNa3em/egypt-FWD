/********************************************************************
 ********************************************************************
 ********************************************************************
 ***********             @author : Ahmed Naeem            ***********
 ***********             @date   : 17/9/2022              ***********
 ***********             @file   : terminal.h             ***********
 ********************************************************************
 ********************************************************************
 *********************************************************************/

#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdint.h>
#include <time.h>
#include "Card\card.h"

typedef struct ST_terminalData_t
{
    float transAmount;
    float maxTransAmount;
    struct tm transactionDate;
} ST_terminalData_t;

typedef enum EN_terminalError_t
{
    TERMINAL_OK,
    WRONG_DATE,
    EXPIRED_CARD,
    INVALID_CARD,
    INVALID_AMOUNT,
    EXCEED_MAX_AMOUNT,
    INVALID_MAX_AMOUNT,
} EN_terminalError_t;

/* Function prototypes */
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData);
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData);
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData);
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData);
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount);
EN_terminalError_t isValidCardPAN(ST_cardData_t *cardData); // Optional

/* Test APIs*/
void getTransactionDateTest(void);
void isCardExpriedTest(void);
void getTransactionAmountTest(void);
void isBelowMaxAmount_setMaxAmount_Test(void);

#endif