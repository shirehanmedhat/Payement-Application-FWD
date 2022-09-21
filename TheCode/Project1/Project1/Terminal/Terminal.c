/*****************Name : Shirehan Medhat Abd elsalam  *****************/
#include<stdio.h>
#include"../Library/STDTYPES.h"
#include "../Card/Card.h"
#include"Terminal.h"

EN_terminalError_t getTransactionDate(ST_terminalData_t* termData)
{
    if (termData != NULL)
    {
        uint32_t  Days, Months, years;
        //Get Month and Day from user
        printf("\n Enter the transaction data in the format DD/MM/YYYY \n");
        scanf_s(" %d", &Days);
        scanf_s(" %d", &Months);
        scanf_s(" %d", &years);
        //Check the validation of the date
        if (((Days <= 31) && (Months <= 12)&& (Months >0) && (Months != 2) && (years >= 2022)) || ((Days <= 28) && (Months == 2)))
        {
            // separate the Day variable into digits
            for (uint8_t i = 1; Days > 0; i--)
            {
                termData->transactionDate[i] = Days % 10; // separate the last digit from the Day
                Days = Days / 10;
                if ((Days == 0) && (i == 1))
                {
                    termData->transactionDate[0] = 0;
                }
            }
            termData->transactionDate[2] = '/';

            // separate the Month variable into digits
            for (uint8_t i = 4; Months > 0; i--)
            {
                termData->transactionDate[i] = Months % 10;  // separate the last digit from the Month
                Months = Months / 10;
                if ((Months == 0) && (i == 4))
                {
                    termData->transactionDate[3] = 0;
                }
            }
           
            termData->transactionDate[5] = '/';

            // separate the Year variable into digits
            for (uint8_t i = 9; years > 0; i--)
            {
                termData->transactionDate[i] = years % 10;  // separate the last digit from the Year
                years = years / 10;
            }


            return terminal_OK;
        }
        else
        {
            return WRONG_DATE;
        }
    }

}

EN_terminalError_t isCardExpired(ST_cardData_t cardData, ST_terminalData_t termData)
{
    //Convert the months From digits into numbers
    uint8_t monthCard = (10 * cardData.cardExpirationDate[0]) + (cardData.cardExpirationDate[1]);
    uint8_t yearCard = (10 * cardData.cardExpirationDate[3]) + (cardData.cardExpirationDate[4]);

    uint8_t monthterm = (10 * (termData.transactionDate[3])) + (termData.transactionDate[4]);
    uint8_t yearterm = (10 * termData.transactionDate[8]) + (termData.transactionDate[9]);

    if (yearCard == yearterm)
    {
        if (monthCard >= monthterm)
        {
            return terminal_OK;
        }
        else
        {
            return EXPIRED_CARD;
        }

    }
    else if (yearCard > yearterm)
    {
        return terminal_OK;
    }
    else
    {
        return EXPIRED_CARD;
    }


}



EN_terminalError_t getTransactionAmount(ST_terminalData_t* termData)
{ 
    if (termData!=NULL)
    {
        printf("\nEnter the Transaction Amount \n");
        scanf_s("%f", &termData->transAmount);
        if ((termData->transAmount) > 0)
        {
            return terminal_OK;
        }
        else
        {
            return INVALID_AMOUNT;
        }
    }

    
}


EN_terminalError_t setMaxAmount(ST_terminalData_t* termData)
{
    if (termData != NULL)
    {
        termData->maxTransAmount = 5000.0;
        if (termData->maxTransAmount > 0)
        {
            return terminal_OK;
        }
        else
        {
            return INVALID_MAX_AMOUNT;
        }
    }
}


EN_terminalError_t isBelowMaxAmount(ST_terminalData_t* termData)
{
    if (termData != NULL)
    {
        if ((termData->maxTransAmount) >= (termData->transAmount))
        {
            return terminal_OK;
        }
        else if ((termData->maxTransAmount) < (termData->transAmount))
        {
            return EXCEED_MAX_AMOUNT;
        }
    }
}

