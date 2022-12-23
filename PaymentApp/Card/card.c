/********************************************************************
 ********************************************************************
 ********************************************************************
 ***********             @author : Ahmed Naeem            ***********
 ***********             @date   : 17/9/2022              ***********
 ***********             @file   : card.c                 ***********
 ********************************************************************
 ********************************************************************
 *********************************************************************/

#include "card.h"
#include <stdio.h>
#include <string.h>

ST_cardData_t G_cardData;
ST_cardData_t *GP_cardData = &G_cardData;

// This function will ask for the cardholder's name and store it into card data.
// Cardholder name is 24 alphabetic characters string max and 20 min.
// If the cardholder name is NULL, less than 20 characters or more than 24
// will return a WRONG_NAME error, else return CARD_OK.
EN_cardError_t getCardHolderName(ST_cardData_t *cardData)
{
    char TempToken[30];
    EN_cardError_t CardState = WRONG_NAME;
    // printf("Please Enter Your Data \n");
    printf("Enter Cardholder Name    : ");
    gets(TempToken);

    /* Check Cardholder name is 24 alphabetic characters string max and 20 min. */
    if ((strlen(TempToken) >= 20) && (strlen(TempToken) <= 24))
    {
        /* True condition inset into cardData */
        for (uint8_t i = 0; i < strlen(TempToken); i++)
        {
            cardData->cardHolderName[i] = TempToken[i];
        }
        CardState = CARD_OK;
    }
    else
    {
        CardState = WRONG_NAME;
    }

    return CardState;
}

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

// This function will ask for the card expiry date and store it in card data.
// (Modified) Card expiry date is Date_t DD/MM/YYYY.
// If the card expiry date is NULLor has the wrong format
//  will return the WRONG_EXP_DATE error, else return CARD_OK.
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData)
{
    char TempToken[10];
    Date_t TempDate;
    EN_cardError_t CardState = WRONG_EXP_DATE;

    printf("Enter Expiry Data : \n");
    printf("Day   : ");
    gets(TempToken);
    TempDate.Day = atoi(TempToken);
    printf("Month : ");
    gets(TempToken);
    TempDate.Month = atoi(TempToken);
    printf("Year  :");
    gets(TempToken);
    TempDate.Year = atoi(TempToken);
    printf(" \n");

    // /*get Date in format/
    // /*convert char to int by - 48*/
    // TempDate.Month = (uint8_t)(TempToken[0] - 48) * 10 + (uint8_t)(TempToken[1] - 48);
    // TempDate.Year = (uint8_t)(TempToken[3] - 48) * 10 + (uint8_t)(TempToken[4] - 48);

    /* Check Card expiry date is 5 characters string in the format "MM/YY", e.g "05/25". */
    if ((TempDate.Day > 0) && (TempDate.Day <= 31) && (TempDate.Month <= 12) && (TempDate.Month > 0))
    {
        /* True condition inset into cardData */
        cardData->cardExpirationDate.Day = TempDate.Day;
        cardData->cardExpirationDate.Month = TempDate.Month;
        cardData->cardExpirationDate.Year = TempDate.Year;

        CardState = CARD_OK;
    }
    else
    {
        CardState = WRONG_EXP_DATE;
    }

    return CardState;
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

// This function will ask for the card's Primary Account Number and store it in card data.
// PAN is 20 numeric characters string, 19 character max, and 16 character min.
// If the PAN is NULL, less than 16 or more than 19 characters,
// will return the WRONG_PAN error, else return CARD_OK.
EN_cardError_t getCardPAN(ST_cardData_t *cardData)
{
    char TempToken[25];
    EN_cardError_t CardState = WRONG_EXP_DATE;
    printf("Enter PAN   : ");
    gets(TempToken);

    if ((strlen(TempToken) >= 16) && (strlen(TempToken) <= 19))
    {
        /* True condition inset into cardData */
        for (uint8_t i = 0; i < strlen(TempToken); i++)
        {
            cardData->primaryAccountNumber[i] = TempToken[i];
        }
        CardState = CARD_OK;
    }
    else
    {
        CardState = WRONG_PAN;
    }

    return CardState;
}
