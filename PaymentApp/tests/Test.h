#ifndef TEST_H
#define TEST_H

#include "Terminal/terminal.h"
#include "Card/card.h"

/* Card test functions*/
void getCardHolderNameTest(void);
void getCardExpiryDateTest(void);
void getCardPANTest(void);

/* Terminal Test functions*/
void getTransactionDateTest(void);
void isCardExpriedTest(void);
void getTransactionAmountTest(void);
void isBelowMaxAmount_setMaxAmount_Test(void);

#endif