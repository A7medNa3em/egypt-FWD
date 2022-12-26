/********************************************************************
 ********************************************************************
 ********************************************************************
 ***********             @author : Ahmed Naeem            ***********
 ***********             @date   : 17/9/2022              ***********
 ***********             @file   : terminal.c             ***********
 ********************************************************************
 ********************************************************************
 *********************************************************************/

#include <stdio.h>
#include "terminal.h"

ST_terminalData_t G_terminalData;
ST_terminalData_t *GP_terminalData = &G_terminalData;

// This function will ask for the transaction date and store it in terminal data.
// Transaction date is 10 characters string in the format DD/MM/YYYY, e.g 25/06/2022.
// If the transaction date is NULL or is less than 10 characters or wrong format will
// return the WRONG_DATE error, else return TERMINAL_OK.

/***
 *
 *      This function is modifed to read system time automatically
 *      If the transaction date is NULL  return the WRONG_DATE error, else return TERMINAL_OK.
 *
 */
EN_terminalError_t getTransactionDate(ST_terminalData_t *termData)
{

    EN_terminalError_t state = WRONG_DATE;
    time_t t;
    t = time(NULL);
    struct tm *tm = localtime(&t);
    if (tm == NULL)
    {
        state = WRONG_DATE;
    }
    else
    {
        state = TERMINAL_OK;

        termData->transactionDate.tm_mday = tm->tm_mday;
        termData->transactionDate.tm_mon = tm->tm_mon + 1;
        termData->transactionDate.tm_year = tm->tm_year + 1900;
    }

    return state;
}

// This function compares the card expiry date with the transaction date.
// If the card expiration date is before the transaction date will return EXPIRED_CARD,
// else return TERMINAL_OK.
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
    EN_terminalError_t state = EXPIRED_CARD;

    if (cardData->cardExpirationDate.Year > (termData->transactionDate.tm_year))
    {
        state = TERMINAL_OK;
    }
    else if (cardData->cardExpirationDate.Year == (termData->transactionDate.tm_year))
    {
        if (cardData->cardExpirationDate.Month > termData->transactionDate.tm_mon)
            state = TERMINAL_OK;
    }
    else
    {
        state = EXPIRED_CARD;
    }

    return state;
}

// This function asks for the transaction amount and saves it into terminal data.
// If the transaction amount is less than or equal to 0 will return INVALID_AMOUNT,
// else return TERMINAL_OK.
EN_terminalError_t getTransactionAmount(ST_terminalData_t *termData)
{
    char TempToken[25];
    EN_terminalError_t State = INVALID_AMOUNT;
    printf("Enter Transaction Amount  : ");
    gets(TempToken);
    termData->transAmount = atoi(TempToken);

    if (termData->transAmount <= 0)
        State = INVALID_AMOUNT;
    else
        State = TERMINAL_OK;
    return State;
}

// This function compares the transaction amount with the terminal max allowed amount.
// If the transaction amount is larger than the terminal max allowed amount will return EXCEED_MAX_AMOUNT,
// else return TERMINAL_OK.
EN_terminalError_t isBelowMaxAmount(ST_terminalData_t *termData)
{
    if (termData->maxTransAmount < termData->transAmount)
        return EXCEED_MAX_AMOUNT;
    else
        return TERMINAL_OK;
}

// This function takes the maximum allowed amount and stores it into terminal data.
// Transaction max amount is a float number.
// If transaction max amount less than or equal to 0 will return the INVALID_MAX_AMOUNT error,
//  else return TERMINAL_OK.
EN_terminalError_t setMaxAmount(ST_terminalData_t *termData, float maxAmount)
{
    termData->maxTransAmount = maxAmount;
    if (termData->maxTransAmount <= 0)
        return INVALID_MAX_AMOUNT;
    else
        return TERMINAL_OK;
}
