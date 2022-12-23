#include <stdio.h>
#include <string.h>
#include "server.h"

/* Create a global array of ST_accountsDB_t for the valid accounts database. */
ST_accountsDB_t accountsDB[255] =
    {
        {2000.0, RUNNING, "2610200537864434"},
        {2000.0, BLOCKED, "9536951593365605"},
        {4000.0, RUNNING, "4903478079245246"},
        {4000.0, BLOCKED, "8751876247081216"},
        {6000.0, RUNNING, "4719802455979296"},
        {6000.0, BLOCKED, "6907940726884180"},
        {8000.0, RUNNING, "6263565997807508"},
        {8000.0, BLOCKED, "3358065963483406"},
        {10000.0, RUNNING, "4068975151313987"},
        {10000.0, BLOCKED, "2652623873444840"}};

ST_accountsDB_t *accountsDBptr = accountsDB; // to search for a valid account
ST_accountsDB_t *valid_account_ptr = 0;      // to store the address of the valid account

ST_transaction_t transactionsDB[255] = {0};

ST_transaction_t *GP_transactionsDB = transactionsDB;
ST_transaction_t *transaction_reference = 0; // the pointer used to access transactionsDB array

EN_transState_t transaction_state = 0;
uint32_t transactionsDB_index = 0; // index to be added on transactionDBptr to access transactionsDB array

// This function will take all transaction data and validate its data, it contains all server logic.
// It checks the account details and amount availability.
// If the account does not exist return FRAUD_CARD, if the amount is not available will
// return DECLINED_INSUFFECIENT_FUND, if the account is blocked will return DECLINED_STOLEN_CARD,
//  if a transaction can't be saved will return INTERNAL_SERVER_ERROR , else returns APPROVED.
// It will update the database with the new balance.
EN_transState_t recieveTransactionData(ST_transaction_t *transData)
{
    EN_transState_t trans_error_type = 0;
    EN_serverError_t account_validity = 0;
    EN_serverError_t account_state = 0;
    EN_serverError_t amount_availability = 0;
    EN_serverError_t transaction_saved = 0;
    ST_transaction_t *save_transaction_ptr = transData;

    account_validity = isValidAccount(GP_cardData, accountsDBptr);
    account_state = isBlockedAccount(valid_account_ptr);
    amount_availability = isAmountAvailable(GP_terminalData, valid_account_ptr);

    if (account_validity == ACCOUNT_NOT_FOUND)
    {
        trans_error_type = FRAUD_CARD;
        transaction_state = FRAUD_CARD;
    }
    else if (account_state == BLOCKED_ACCOUNT)
    {
        trans_error_type = DECLINED_STOLEN_CARD;
        transaction_state = DECLINED_STOLEN_CARD;
    }
    else if (amount_availability == LOW_BALANCE)
    {
        trans_error_type = DECLINED_INSUFFECIENT_FUND;
        transaction_state = DECLINED_INSUFFECIENT_FUND;
    }
    else
    {
        trans_error_type = APPROVED;
        transaction_state = APPROVED;
        valid_account_ptr->balance = valid_account_ptr->balance - GP_terminalData->transAmount;
    }

    transaction_saved = saveTransaction(save_transaction_ptr);
    if (transaction_saved != SERVER_OK)
    {
        trans_error_type = INTERNAL_SERVER_ERROR;
        transaction_state = INTERNAL_SERVER_ERROR;
    }

    return trans_error_type;
}

// This function will take card data and validate if the account related to this card exists or not.
// It checks if the PAN exists or not in the server's database (searches for the card PAN in the DB).
// If the PAN doesn't exist will return ACCOUNT_NOT_FOUND and the account reference will be NULL,
// else will return SERVER_OK and return a reference to this account in the DB.
EN_serverError_t isValidAccount(ST_cardData_t *cardData, ST_accountsDB_t *accountRefrence)
{
    EN_serverError_t server_error_type = 0;
    uint32_t PAN_cmp = 0;
    valid_account_ptr = 0;

    for (uint16_t i = 0; i < number_of_accounts; i++)
    {
        PAN_cmp = 0;
        PAN_cmp = strcmp(cardData->primaryAccountNumber, accountRefrence->primaryAccountNumber);

        if (PAN_cmp == 0)
        {
            server_error_type = SERVER_OK;
            valid_account_ptr = accountRefrence;
            break;
        }
        accountRefrence++;
    }

    if (valid_account_ptr == 0)
    {
        server_error_type = ACCOUNT_NOT_FOUND;
    }

    return server_error_type;
}

// This function takes a reference to the account into the database and verifies if it is blocked or not.
// If the account is running it will return SERVER_OK,
// else if the account is blocked it will return BLOCKED_ACCOUNT.
EN_serverError_t isBlockedAccount(ST_accountsDB_t *accountRefrence)
{
    EN_serverError_t server_error_type = 0;
    if (accountRefrence != 0)
    {
        if (accountRefrence->state == RUNNING)
        {
            server_error_type = SERVER_OK;
        }
        else if (accountRefrence->state == BLOCKED)
        {
            server_error_type = BLOCKED_ACCOUNT;
        }
    }

    return server_error_type;
}

// This function will take terminal data and a reference to the account in the database and check
// if the account has a sufficient amount to withdraw or not.
// It checks if the transaction's amount is available or not.
// If the transaction amount is greater than the balance in the database will return LOW_BALANCE, else will return SERVER_OK.
EN_serverError_t isAmountAvailable(ST_terminalData_t *termData, ST_accountsDB_t *accountRefrence)
{
    EN_serverError_t server_error_type = 0;
    if (accountRefrence != 0)
    {
        if (termData->transAmount > accountRefrence->balance)
        {
            server_error_type = LOW_BALANCE;
        }
        else
        {
            server_error_type = SERVER_OK;
        }
    }

    return server_error_type;
}

// This function will store all transaction data in the transactions database.
// It gives a sequence number to a transaction, this number is incremented once a transaction is
// processed into the server, you must check the last sequence number in the server to give the new transaction a new sequence number.
// It saves any type of transaction, APPROVED, DECLINED_INSUFFECIENT_FUND, DECLINED_STOLEN_CARD, FRAUD_CARD, INTERNAL_SERVER_ERROR.
// It will list all saved transactions using the listSavedTransactions function.
// Assuming that the connection between the terminal and server is always connected, then it will return SERVER_OK.
EN_serverError_t saveTransaction(ST_transaction_t *transData)
{
    EN_serverError_t server_error_type = SERVER_OK;

    transData = transData + transactionsDB_index;
    transaction_reference = transData;

    /*copy card Data*/
    strcpy(transData->cardHolderData.cardHolderName, GP_cardData->cardHolderName);

    transData->cardHolderData.cardExpirationDate.Day = GP_cardData->cardExpirationDate.Day;
    transData->cardHolderData.cardExpirationDate.Month = GP_cardData->cardExpirationDate.Month;
    transData->cardHolderData.cardExpirationDate.Year = GP_cardData->cardExpirationDate.Year;

    strcpy(transData->cardHolderData.primaryAccountNumber, GP_cardData->primaryAccountNumber);

    /*copy terminal Data*/
    transData->terminalData.transactionDate.tm_mday = GP_terminalData->transactionDate.tm_mday;
    transData->terminalData.transactionDate.tm_mon = GP_terminalData->transactionDate.tm_mon;
    transData->terminalData.transactionDate.tm_year = GP_terminalData->transactionDate.tm_year;

    transData->terminalData.transAmount = GP_terminalData->transAmount;
    transData->terminalData.maxTransAmount = GP_terminalData->maxTransAmount;

    transData->transState = transaction_state;

    transData->transactionSequenceNumber = 1 + transactionsDB_index;

    listSavedTransactions();

    transactionsDB_index++;

    return server_error_type;
}

void listSavedTransactions(void)
{
    printf("#########################");
    printf("\n");
    printf("Transaction Sequence Number: %ld", transaction_reference->transactionSequenceNumber);
    printf("\n");
    printf("Transaction Date: %d/%d/%d", transaction_reference->terminalData.transactionDate.tm_mday, transaction_reference->terminalData.transactionDate.tm_mon, transaction_reference->terminalData.transactionDate.tm_year);
    printf("\n");
    printf("Transaction Amount: %f", transaction_reference->terminalData.transAmount);
    printf("\n");
    switch (transaction_reference->transState)
    {
    case APPROVED:
        printf("Transaction State: Approved");
        break;

    case DECLINED_INSUFFECIENT_FUND:
        printf("Transaction State: Declined -> Insufficient fund");
        break;

    case DECLINED_STOLEN_CARD:
        printf("Transaction State: Declined -> Blocked Account");
        break;

    case FRAUD_CARD:
        printf("Transaction State: Declined -> Fraud Card");
        break;

    case INTERNAL_SERVER_ERROR:
        printf("Transaction State: Declined -> Internal Server Error");
        break;
    }
    printf("\n");
    printf("Terminal Max Amount: %f", transaction_reference->terminalData.maxTransAmount);
    printf("\n");
    printf("Cardholder Name: %s", transaction_reference->cardHolderData.cardHolderName);
    printf("\n");
    printf("PAN: %s", transaction_reference->cardHolderData.primaryAccountNumber);
    printf("\n");
    printf("Card Expiration Date: %d/%d/%d", transaction_reference->cardHolderData.cardExpirationDate.Day, transaction_reference->cardHolderData.cardExpirationDate.Month, transaction_reference->cardHolderData.cardExpirationDate.Year);
    printf("\n");
    printf("#########################");
    printf("\n");
}