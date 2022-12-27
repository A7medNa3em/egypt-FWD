
#include "Test.h"
#include "Terminal/terminal.h"
#include "Card/card.h"
#include "Server/server.h"
#include <stdio.h>

void getCardHolderNameTest(void)
{
    ST_cardData_t TestCard;
    char tempstr[30];
    static uint8_t CasesCount;
    printf("Tester Name     : Ahmed Naeem \n");
    printf("Function Name   : getCardHolderName \n\n");
    while (1)
    {
        printf("Test Case %d \n", CasesCount + 1);
        printf("Expected Result : ");
        gets(tempstr);
        printf("Input Data \n\t");
        if (getCardHolderName(&TestCard) == CARD_OK)
            printf("Actual Result   : Ok Card Holder Name \n\n");
        else
            printf("Actual Result   : Error Card Holder Name \n\n");
        CasesCount++;
    }
}

void getCardExpiryDateTest(void)
{
    ST_cardData_t TestCard;
    char tempstr[10];
    static uint8_t CasesCount;
    printf("Tester Name     : Ahmed Naeem \n");
    printf("Function Name   : getCardExpiryDate \n\n");
    while (1)
    {
        printf("Test Case %d \n", CasesCount + 1);
        printf("Expected Result : ");
        gets(tempstr);
        printf("Input Data \n\t");
        if (getCardExpiryDate(&TestCard) == CARD_OK)
            printf("Actual Result   : Ok Card Expire Date  \n\n");
        else
            printf("Actual Result   : Error Card Expire Date \n\n");
        CasesCount++;
    }
}

void getCardPANTest(void)
{
    ST_cardData_t TestCard;
    char tempstr[20];
    static uint8_t CasesCount;
    printf("Tester Name     : Ahmed Naeem \n");
    printf("Function Name   : getCardPANTest \n\n");
    while (1)
    {
        printf("Test Case %d \n", CasesCount + 1);
        printf("Expected Result : ");
        gets(tempstr);
        printf("Input Data \n\t");
        if (getCardPAN(&TestCard) == CARD_OK)
            printf("Actual Result   : Ok Card PAN \n\n");
        else
            printf("Actual Result   : Error Card PAN\n\n");
        CasesCount++;
    }
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

void recieveTransactionDataTest(void)
{
}

void isBlockedAccountTest(void)
{
    ST_accountsDB_t *tempAccont;
    char tempstr[20];
    static uint8_t CasesCount;
    printf("Tester Name     : Ahmed Naeem \n");
    printf("Function Name   :isBlockedAccount \n");
    while (1)
    {
        printf("Test Case %d \n", CasesCount + 1);
        printf("Expected Result : ");
        gets(tempstr);
        printf("Input Data  RUNNING 0  BLOCKED 1  \n\t");
        //      RUNNING,
        // BLOCKED
        gets(tempstr);
        tempAccont->state = atoi(tempstr);
        printf("Actual Result   : Ok Account is NOT Blocked \n\n");
        if (isBlockedAccount(tempAccont) == SERVER_OK)
        {
        }
        else
        {
            printf("Actual Result   : Ok Account is Blocked \n\n");
        }

        CasesCount++;
    }
}