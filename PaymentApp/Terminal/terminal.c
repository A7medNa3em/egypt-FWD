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

void getTransactionDateTest(void)
{
    ST_terminalData_t TestTerm;
    char tempstr[20];
    static uint8_t CasesCount;
    printf("Tester Name     : Ahmed Naeem \n");
    printf("Function Name   : getTransactionDate \n\n");
    while (1)
    {
        printf("Test Case %d \n", CasesCount + 1);
        printf("Expected Result : ");
        gets(tempstr);
        printf("Input Data \t");
        gets(tempstr);
        if (getTransactionDate(&TestTerm) == TERMINAL_OK)
        {
            printf("Actual Result   : Ok Transaction Date \n");
            printf("\t %d/%d/%d \n\n", TestTerm.transactionDate.tm_mday, TestTerm.transactionDate.tm_mon, TestTerm.transactionDate.tm_year);
        }
        else
            printf("Actual Result   : Error Transaction Date\n\n");
        CasesCount++;
    }
}

// This function compares the card expiry date with the transaction date.
// If the card expiration date is before the transaction date will return EXPIRED_CARD,
// else return TERMINAL_OK.
EN_terminalError_t isCardExpired(ST_cardData_t *cardData, ST_terminalData_t *termData)
{
    EN_terminalError_t state = EXPIRED_CARD;

    // printf("Transaction Date %d/%d/%d \n", termData->transactionDate.tm_mday, termData->transactionDate.tm_mon, termData->transactionDate.tm_year);
    // printf("Expiration  Date %d/%d/%d \n", cardData->cardExpirationDate.Day, cardData->cardExpirationDate.Month, cardData->cardExpirationDate.Year);

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

void isCardExpriedTest(void)
{
    ST_terminalData_t TestTerm;
    ST_cardData_t TestCard;
    char tempstr[20];
    static uint8_t CasesCount;
    printf("Tester Name     : Ahmed Naeem \n");
    printf("Function Name   : isCardExpired \n\n");
    while (1)
    {
        printf("Test Case %d \n", CasesCount + 1);
        printf("Expected Result : ");
        gets(tempstr);
        printf("Input Data \t");
        if ((getCardExpiryDate(&TestCard) == CARD_OK) && (getTransactionDate(&TestTerm) == TERMINAL_OK))
        {

            if (isCardExpired(&TestCard, &TestTerm) == TERMINAL_OK)
            {
                printf("Actual Result   : Ok Card is NOT Expired \n\n");
            }
            else
                printf("Actual Result   : Error Card is Expired \n\n");
        }
        else
            printf("Actual Result   : Error wrong date \n\n");
        CasesCount++;
    }
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

void getTransactionAmountTest(void)
{
    ST_terminalData_t TestTerm;
    char tempstr[20];
    static uint8_t CasesCount;
    printf("Tester Name     : Ahmed Naeem \n");
    printf("Function Name   : getTransactionDate \n\n");
    while (1)
    {
        printf("Test Case %d \n", CasesCount + 1);
        printf("Expected Result : ");
        gets(tempstr);
        printf("Input Data \n\t");
        if (getTransactionAmount(&TestTerm) == TERMINAL_OK)
        {
            printf("Actual Result   : Ok Transaction Amount \n");
        }
        else
            printf("Actual Result   : Error Invalid Transaction Amount\n\n");
        CasesCount++;
    }
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

void isBelowMaxAmount_setMaxAmount_Test(void)
{
    ST_terminalData_t TestTerm;
    char tempstr[20];
    static uint8_t CasesCount;
    printf("Tester Name     : Ahmed Naeem \n");
    printf("Function Name   : setMaxAmount and isBelowMaxAmount \n\n");
    while (1)
    {
        printf("Test Case %d \n", CasesCount + 1);
        printf("Expected Result : ");
        gets(tempstr);
        printf("Input Data \n\t");
        getTransactionAmount(&TestTerm);
        printf("Enter Max Amount \t");
        gets(tempstr);

        if (setMaxAmount(&TestTerm, atoi(tempstr)) == TERMINAL_OK)
        {
            printf("Actual Result   : Ok Valid Max Amount \n");
        }
        else
            printf("Actual Result   : Error Invalid Max Amount \n");

        if (isBelowMaxAmount(&TestTerm) == TERMINAL_OK)
        {
            printf("Actual Result   : Ok -> NOT EXCEED_MAX_AMOUNT  \n\n");
        }
        else
            printf("Actual Result   : Error ->  EXCEED_MAX_AMOUNT \n\n");
        CasesCount++;
    }
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
