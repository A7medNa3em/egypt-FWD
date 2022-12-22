/********************************************************************
 ********************************************************************
 ********************************************************************
 ***********             @author : Ahmed Naeem            ***********
 ***********             @date   : 17/9/2022              ***********
 ***********             @file   : card.f                 ***********
 ********************************************************************
 ********************************************************************
 *********************************************************************/

#ifndef CARD_H
#define CARD_H
#include <stdint.h>
#include <stdlib.h>

// Use the following typedef as-is:
typedef struct
{
    uint8_t Day;
    uint8_t Month;
    uint16_t Year;
} Date_t;

/* Card info Typedef*/
typedef struct ST_cardData
{
    uint8_t cardHolderName[25];
    uint8_t primaryAccountNumber[20];
    Date_t cardExpirationDate;
} ST_cardData_t;

/* Card Error enum*/
typedef enum EN_cardError
{
    CARD_OK,
    WRONG_NAME,
    WRONG_EXP_DATE,
    WRONG_PAN
} EN_cardError_t;

/* Function prototypes */
EN_cardError_t getCardHolderName(ST_cardData_t *cardData);
EN_cardError_t getCardExpiryDate(ST_cardData_t *cardData);
EN_cardError_t getCardPAN(ST_cardData_t *cardData);

/* test functions*/
void getCardHolderNameTest(void);
void getCardExpiryDateTest(void);
void getCardPANTest(void);

#endif